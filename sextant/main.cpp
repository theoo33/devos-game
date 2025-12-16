#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <drivers/PortSerie.h>

// TP2
#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <sextant/interruptions/handler/handler_speaker.h>
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
#include <drivers/speaker.h>

#include <sextant/sprite.h>
#include <sextant/menu.h>
#include <sextant/music.h>
#include <Applications/Football/Game.h>

extern char __e_kernel,__b_kernel, __b_data, __e_data,  __b_stack, __e_load ;

extern vaddr_t bootstrap_stack_bottom; //Adresse de début de la pile d'exécution
extern size_t bootstrap_stack_size;//Taille de la pile d'exécution

extern bool key_pressed[126];

ui16_t WIDTH = 640, HEIGHT = 400; // screen dimensions

Game* game;
Timer timer;
Speaker speaker;  // Global speaker instance

// Timer handler that calls ticTac, handler_speaker, and sched_clk
void timer_handler_combined(int intid) {
	ticTac(intid);
	handler_speaker(intid);
	sched_clk(intid);
}


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Ecran ecran;
	Clavier c;


	idt_setup();
	irq_setup();
	//Initialisation de la frequence de l'horloge

	timer.i8254_set_frequency(1000);
	irq_set_routine(IRQ_TIMER, ticTac);

	asm volatile("sti\n");//Autorise les interruptions

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
	vga.plot_sprite( menu_background, GAME_WIDTH, GAME_HEIGHT, 0, 0 );

	game = new Game(&vga, &timer, &speaker, WIDTH, HEIGHT);
	
	while (true) {
		if (game->game_finished) {
			Sextant_main(0,0);
		}
		if (key_pressed[AZERTY::K_RETURN] && !game->game_started){
			game->init_match();
			game->start();
			game->game_started = true;
		}
		thread_yield();
	}

}