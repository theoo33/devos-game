#include "Game.h"

#include <drivers/timer.h>
#include <drivers/speaker.h>
#include <drivers/EcranBochs.h>

#include <Applications/Football/Player.h>
#include <Applications/Football/Ball.h>
#include <Applications/Football/Field.h>
#include <Applications/Football/Score.h>
#include <Applications/Football/HalfManager.h>

Score* red_score;
Score* blue_score;
Player* player1;
Player* player2;
Field* field;
Ball* ball;
HalfManager* half_manager;

/* CONSTANTS */
int FRAME_SKIP = 5; // to slow down movement
const char PLAYER_SPEED = 1; // in pixel per frame
const int BALL_SPEED = 6;
const int BALL_FRICTION = 1;
static int TEAM_1 = 1;
static int TEAM_2 = 2;
int HALF_TIME = 120; // Half-time duration in seconds
/*	End constant declaration	*/


Game::Game(EcranBochs* vga_entry, Timer* timer_entry, Speaker* speaker_entry, ui16_t width, ui16_t height)
    : vga(vga_entry), timer(timer_entry), speaker(speaker_entry), WIDTH(width), HEIGHT(height) {
        game_started = false;
        game_finished = false;
    };


/* TIME DISPLAY */
void Game::draw_time(int screen_width, int space_between){
	int minutes = timer->getSecondes()/60;
	int seconds = timer->getSecondes()%60;
	if (minutes<10) vga->draw_number(screen_width/2-2*space_between,1,0,255,2);
	vga->draw_number(screen_width/2-space_between,1,minutes,255,2);
	vga->draw_char(screen_width/2,1,':',255,2);
	if (seconds<10) vga->draw_number(screen_width/2+space_between,1,0,255,2);
	vga->draw_number(screen_width/2+2*space_between,1,seconds,255,2);	
}


void Game::init_match() {
    half_time_triggered = false;
    end_match_triggered = false;
    music_started = false;

    // Implementation of match initialization logic goes here
    field = new Field( 
        vga,  // Pass the address of the vga object
        ZONE{ 20, 20, WIDTH-20, HEIGHT-20 },
        ZONE{ 20, 150, 70, 250 },
		ZONE{ WIDTH - 70, 150, WIDTH - 20, 250 }
    );

	red_score = new Score(
		field->get_center_x()-(SPRITE_NUMBER_WIDTH+10),10,TEAM_1
	);
	blue_score = new Score(
		field->get_center_x()+10,10,TEAM_2
	);
	player1 = new Player(
		field->get_center_x()-(SPRITE_PLAYER_WIDTH+50), field->get_center_y() - SPRITE_PLAYER_HEIGHT/2, 
		TEAM_1, PLAYER_SPEED, vga, field
	);
	player2 = new Player(
		field->get_center_x()+50, field->get_center_y() - SPRITE_PLAYER_HEIGHT/2, 
		TEAM_2, PLAYER_SPEED, vga, field
	);
	ball = new Ball(
		field->get_center_x() - SPRITE_BALL_WIDTH/2, field->get_center_y() - SPRITE_BALL_HEIGHT/2, 
		BALL_SPEED, BALL_FRICTION, sprite_ball_data,
		player1, player2, vga, field
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

void Game::stop_match() {
    // Implementation of match stopping logic goes here
    red_score->stop();
    blue_score->stop();
	player1->stop();
    player2->stop();
    ball->stop();
    half_manager->stop();
}


void Game::run() {
    // Implementation of the main game loop goes here
	
	while (true) {
		
		field->paint();

		// Start music on first iteration
		if (!music_started) {
			music_started = true;
			// main_theme(&speaker);
			timer->reset();
		}

		// vga.plot_sprite(scoreBoard_data,246,143,WIDTH/2-143,1);
		// vga.set_palette(palette_numbers);
		// vga.set_palette(palette_vga);
		vga->plot_sprite(red_score->show_sprite(),red_score->WIDTH,red_score->HEIGHT,red_score->x,red_score->y);
		vga->plot_sprite(blue_score->show_sprite(),blue_score->WIDTH,blue_score->HEIGHT,blue_score->x,blue_score->y);

		// GOAL LOGIC
		int scorer = field->has_scored(ball->get_x(), ball->get_y(),ball->BALL_WIDTH,ball->BALL_HEIGHT);
		if (half_manager->half_passed) {
			scorer = 2 - scorer + 1; // invert scoring team after half-time
		}
		if (scorer == TEAM_1) {
			blue_score->sem->V();
			speaker->play(400, 100);  // Goal sound: 800Hz for 200ms
			ball->reset_position();
			player1->reset_position(half_time_triggered);
			player1->set_character_direction(half_time_triggered);
			player2->reset_position(half_time_triggered);
			player2->set_character_direction(half_time_triggered);
		}

		if (scorer == TEAM_2) {
			red_score->sem->V();
			speaker->play(400, 100);  // Goal sound: 800Hz for 200ms
			ball->reset_position();
			player1->reset_position(half_time_triggered);
			player2->set_character_direction(half_time_triggered);
			player2->reset_position(half_time_triggered);
			player2->set_character_direction(half_time_triggered);
		}

		// HALF-TIME AND END-MATCH LOGIC
		if (timer->getSecondes()==HALF_TIME && !half_time_triggered){
			half_manager->half_time_sem->V();
			half_time_triggered = true;
			speaker->play(100, 100);
			speaker->play(500, 100);
			speaker->play(100, 100);
			ball->reset_position();
			player1->reset_position(half_time_triggered);
			player1->set_character_direction(half_time_triggered);
			player2->reset_position(half_time_triggered);
			player2->set_character_direction(half_time_triggered);
			red_score->x= field->get_center_x() +10;
			blue_score->x= field->get_center_x()-(SPRITE_NUMBER_WIDTH+10);
		}
		if ((
				timer->getSecondes()==2*HALF_TIME||
				red_score->get_count()==3||
				blue_score->get_count()==3
			) 
			&& !end_match_triggered) {
			end_match_triggered = true;
			half_manager->half_time_sem->V();

			// End match
			timer->reset();
            game_started = false;
            game_finished = true;
            stop_match();
            break;
		}
		
        draw_time(WIDTH,10);
        
        thread_yield();
        vga->swapBuffer();
	}
    thread_exit();
}

