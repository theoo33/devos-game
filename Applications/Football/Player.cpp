#include "Player.h"
#include <drivers/EcranBochs.h>
#include "sextant/types.h"

extern bool key_pressed[126];

// Player::Player(int x, 
//     int y, 
//     unsigned char* data, 
//     int speed, 
//     ui8_t key_up, 
//     ui8_t key_down, 
//     ui8_t key_left, 
//     ui8_t key_right, 
//     EcranBochs* vga_entry):

//     x(x), y(y), 
//     data(data),
//     SPEED(speed),
//     KEY_UP(key_up),
//     KEY_DOWN(key_down),
//     KEY_LEFT(key_left),
//     KEY_RIGHT(key_right),
//     vga(vga_entry)
// {};

Player::Player(int x, 
    int y, 
    unsigned char* data, 
    int speed, 
    ui8_t key_up, 
    ui8_t key_down, 
    ui8_t key_left, 
    ui8_t key_right, 
    EcranBochs* vga_entry){

    x=x; y=y; 
    data=data;
    SPEED=speed;
    KEY_UP=key_up;
    KEY_DOWN=key_down;
    KEY_LEFT=key_left;
    KEY_RIGHT=key_right;
    vga=vga_entry;
};

bool Player::is_any_key_pressed() {
    return (key_pressed[Player::KEY_UP] 
        || key_pressed[Player::KEY_DOWN] 
        || key_pressed[Player::KEY_LEFT] 
        || key_pressed[Player::KEY_RIGHT]);
}

void Player::move(ui16_t WIDTH, ui16_t HEIGHT) {
    if (key_pressed[Player::KEY_UP]) {
        Player::set_y(Player::get_y()-Player::SPEED);
        if (Player::get_y() < 0) Player::set_y(Player::get_y()+HEIGHT);
	}
    if (key_pressed[Player::KEY_LEFT] ) {
        Player::set_x(Player::get_x()-Player::SPEED);
        if (Player::get_x() < 0) Player::set_x(Player::get_x()+WIDTH);
    }
    if (key_pressed[Player::KEY_DOWN]) {
        Player::set_y((Player::get_y() + Player::SPEED) % HEIGHT);
    }
    if (key_pressed[Player::KEY_RIGHT]) {
        Player::set_x(((Player::get_x() + Player::SPEED) % WIDTH));
    }
}

int Player::get_x() {return x;};
void Player::set_x(int new_x) {x=new_x;};

int Player::get_y() {return y;};
void Player::set_y(int new_y) {y=new_y;};
unsigned char* Player::get_data() {return data;};

void Player::run() {
	int frame = 0;
	while (true) {
		if (is_any_key_pressed()) {
            move(vga->getWidth(), vga->getHeight());
            frame = 0;
		}
		++frame;
		vga->clear(0);
		vga->plot_sprite(get_data(), SPRITE_WIDTH, SPRITE_HEIGHT, get_x(), get_y());
		vga->swapBuffer(); // call this after you finish drawing your frame to display it, it avoids screen tearing
		thread_yield();
	}
    thread_exit();
}
