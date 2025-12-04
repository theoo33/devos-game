#include "Player.h"
#include <drivers/EcranBochs.h>
#include "sextant/types.h"

extern bool key_pressed[126];
extern int FRAME_SKIP;

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

Player::Player(int x_pos, 
    int y_pos, 
    unsigned char* data, 
    int speed, 
    ui8_t key_up, 
    ui8_t key_down, 
    ui8_t key_left, 
    ui8_t key_right, 
    EcranBochs* vga_entry){

    x=x_pos; y=y_pos; 
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
        if (y > 0) y -= SPEED;
	}
    if (key_pressed[Player::KEY_LEFT] ) {
        if (x > 0) x -= SPEED;
    }
    if (key_pressed[Player::KEY_DOWN]) {
        if(y + SPRITE_HEIGHT + SPEED < HEIGHT)
            y += SPEED;
    }
    if (key_pressed[Player::KEY_RIGHT]) {
        if(x + SPRITE_WIDTH + SPEED < WIDTH)
            x += SPEED;
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
        if ((frame % FRAME_SKIP) == 0) {
            if (is_any_key_pressed()) {
                move(vga->getWidth(), vga->getHeight());
            }
            frame = 0;
        }
        vga->plot_sprite(get_data(), SPRITE_WIDTH, SPRITE_HEIGHT, get_x(), get_y());
        frame++;
        thread_yield();
    }
    thread_exit();
}
