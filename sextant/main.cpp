#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <drivers/PortSerie.h>

// TP2
#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <drivers/timer.h>
#include <drivers/Clavier.h>
// TP3
#include <sextant/memoire/memoire.h>

// TP4
#include <sextant/ordonnancements/cpu_context.h>
#include <sextant/ordonnancements/preemptif/thread.h>
#include <sextant/types.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <sextant/Synchronisation/Mutex/Mutex.h>

#include <hal/pci.h>
#include <drivers/vga.h>
#include <drivers/EcranBochs.h>

#include <sextant/sprite.h>
#include <Applications/Football/Player.h>
#include <Applications/Football/Ball.h>
#include <Applications/Football/Field.h>
#include <Applications/Football/Score.h>
#include <Applications/Football/HalfManager.h>

extern char __e_kernel,__b_kernel, __b_data, __e_data,  __b_stack, __e_load ;
int i;

extern vaddr_t bootstrap_stack_bottom; //Adresse de début de la pile d'exécution
extern size_t bootstrap_stack_size;//Taille de la pile d'exécution

Score* red_score;
Score* blue_score;
Player* player1;
Player* player2;
Field* field;
Ball* ball;
HalfManager* half_manager;

// GAME CONSTANTS
int FRAME_SKIP = 5;
ui16_t WIDTH = 640, HEIGHT = 400;
const char PLAYER_SPEED = 1;
const int BALL_SPEED = 6;
const int BALL_FRICTION = 1;
static int TEAM_1 = 1;
static int TEAM_2 = 2;
int HALF_TIME = 120; // Half-time duration in seconds
/*	End constant declaration	*/
 
Timer timer;

// Timer handler that calls both ticTac and sched_clk
void timer_handler_combined(int intid) {
	ticTac(intid);
	sched_clk(intid);
}

void draw_time(EcranBochs* vga,int screen_width, int space_between){
	int minutes = timer.getSecondes()/60;
	int seconds = timer.getSecondes()%60;
	if (minutes<10) vga->draw_number(screen_width/2-2*space_between,1,0,255,2);
	vga->draw_number(screen_width/2-space_between,1,minutes,255,2);
	vga->draw_char(screen_width/2,1,':',255,2);
	if (seconds<10) vga->draw_number(screen_width/2+space_between,1,0,255,2);
	vga->draw_number(screen_width/2+2*space_between,1,seconds,255,2);
		
}

void init_match(EcranBochs* vga){
	red_score_sem = new Semaphore(1);
	red_score_sem->P();
	blue_score_sem = new Semaphore(1);
	blue_score_sem->P();

	static int TEAM_1 = 1;
	static int TEAM_2 = 2;

	field = new Field( 
        vga,  // Pass the address of the vga object
        ZONE{ 20, 20, WIDTH-20, HEIGHT-20 },
        ZONE{ 20, 150, 70, 250 },
		ZONE{ WIDTH - 70, 150, WIDTH - 20, 250 }
    );

	blue_score = new Score(
		WIDTH/2+10,10,
		TEAM_1,
		blue_score_sem
	);

	red_score = new Score(
		WIDTH/2-(SPRITE_NUMBER_WIDTH+10),10,
		TEAM_2,
		red_score_sem
	);

	player1 = new Player(
		WIDTH/2-(SPRITE_PLAYER_WIDTH+50), (HEIGHT-SPRITE_PLAYER_HEIGHT)/2, sprite_player_red_right, PLAYER_SPEED,
		TEAM_1,
		vga
	);

	player2 = new Player(
		WIDTH/2+50, (HEIGHT-SPRITE_PLAYER_HEIGHT)/2, sprite_data, PLAYER_SPEED,
		TEAM_2,
		vga
	);

	ball = new Ball(
		field->get_center_x() - SPRITE_BALL_WIDTH / 2, 
		field->get_center_y() - SPRITE_BALL_HEIGHT / 2, 
		BALL_SPEED, BALL_FRICTION, sprite_ball_data,
		player1,
		player2,
		vga,
		field
	);
	half_manager = new HalfManager(vga);

	/*Start threads*/
	red_score->start();
	blue_score->start();
	player1->start();
	player2->start();
	ball->start();
	half_manager->start();

}


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Ecran ecran;
	Clavier c;

	idt_setup();
	irq_setup();
	//Initialisation de la frequence de l'horloge

	timer.i8254_set_frequency(1000);
	irq_set_routine(IRQ_TIMER, ticTac);

	asm volatile("sti\n"); //Autorise les interruptions

	irq_set_routine(IRQ_KEYBOARD, handler_clavier);

	multiboot_info_t* mbi;
	mbi = (multiboot_info_t*)addr;

	mem_setup(& __e_kernel,(mbi->mem_upper<<10) + (1<<20),&ecran);

	ecran.effacerEcran(NOIR);

	thread_subsystem_setup(bootstrap_stack_bottom, bootstrap_stack_size);
	sched_subsystem_setup();

	irq_set_routine(IRQ_TIMER, timer_handler_combined);

	// initialize pci bus to detect GPU address
	checkBus(0);

	EcranBochs vga(WIDTH, HEIGHT, VBE_MODE::_8);
	vga.set_palette(palette_vga);

	vga.init();

	init_match(&vga);
	
	// Track which events have been triggered to avoid multiple signals
	bool half_time_triggered = true;
	bool end_match_triggered = true;
	
	while (true) {
		field->paint();
		// vga.plot_sprite(scoreBoard_data,246,143,WIDTH/2-143,1);
		// vga.set_palette(palette_numbers);
		vga.plot_sprite(red_score->show_sprite(),red_score->WIDTH,red_score->HEIGHT,red_score->x,red_score->y);
		vga.plot_sprite(blue_score->show_sprite(),blue_score->WIDTH,blue_score->HEIGHT,blue_score->x,blue_score->y);
		// vga.set_palette(palette_vga);

		int scorer = field->has_scored(ball->get_x(), ball->get_y(),ball->BALL_WIDTH,ball->BALL_HEIGHT);
		if (half_manager->half_passed) {
			scorer = 2 - scorer + 1; // invert scoring team after half-time
		}
		if (scorer == TEAM_1) {
			blue_score->sem->V();
		}

		if (scorer == TEAM_2) {
			red_score->sem->V();
		}
		// Test if ball is outside field
		if (field->outside_field(ball->get_x(), ball->get_y(), ball->BALL_WIDTH, ball->BALL_HEIGHT)) {
			ball->set_x(field->get_center_x() - SPRITE_BALL_WIDTH / 2);
			ball->set_y(field->get_center_y() - SPRITE_BALL_HEIGHT / 2);
			ball->set_speed(0);
			ball->set_counter(0);
		}

		if (timer.getSecondes()==HALF_TIME && !half_time_triggered){
			half_manager->half_time_sem->V();
			half_time_triggered = true;
			ball->set_x(WIDTH / 2);
			ball->set_y(HEIGHT / 2);
			player1->set_x(WIDTH / 2 + 50);
			player1->set_y((HEIGHT - SPRITE_PLAYER_HEIGHT) / 2);
			player2->set_x(WIDTH/2-(SPRITE_PLAYER_WIDTH+50));
			player2->set_y((HEIGHT - SPRITE_PLAYER_HEIGHT) / 2);
			red_score->x= WIDTH/2+10;
			blue_score->x= WIDTH/2-(SPRITE_NUMBER_WIDTH+10);
		}
		if ((
				timer.getSecondes()==2*HALF_TIME||
				red_score->get_count()==3||
				blue_score->get_count()==3
			) 
			&& !end_match_triggered) {
			end_match_triggered = true;
			half_manager->half_time_sem->V();

			// Restart match
			timer.reset();
			Sextant_main(0,0);
		}
		
		draw_time(&vga,WIDTH,10);

		thread_yield();
		vga.swapBuffer();
	}

}