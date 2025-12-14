#include "Player.h"
#include <drivers/EcranBochs.h>
#include "sextant/types.h"
#include <drivers/Clavier.h>


extern bool key_pressed[126];
extern int FRAME_SKIP;
extern unsigned char sprite_player_red_left[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];
extern unsigned char sprite_player_red_right[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];
extern unsigned char sprite_player_blue_left[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];
extern unsigned char sprite_player_blue_right[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];

Player::Player(int x_pos, 
    int y_pos, 
    int speed, 
    int team,
    EcranBochs* vga_entry) : 
        x(x_pos), 
        y(y_pos), 
        SPEED(speed),
        vga(vga_entry) 
        {
        if (team == 1) {
            KEY_UP = AZERTY::K_Z;
            KEY_DOWN = AZERTY::K_S;
            KEY_LEFT = AZERTY::K_Q;
            KEY_RIGHT = AZERTY::K_D;
            data = sprite_player_red_right;
        }
        else {
            KEY_UP = AZERTY::K_O;
            KEY_DOWN = AZERTY::K_L;
            KEY_LEFT = AZERTY::K_K;
            KEY_RIGHT = AZERTY::K_M;
            data = sprite_player_blue_left;
        }
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
        if (team == 1) data = sprite_player_red_left;
        else data = sprite_player_blue_left;
    }
    if (key_pressed[Player::KEY_DOWN]) {
        if(y + PLAYER_HEIGHT + SPEED < HEIGHT)
            y += SPEED;
    }
    if (key_pressed[Player::KEY_RIGHT]) {
        if(x + PLAYER_WIDTH + SPEED < WIDTH)
            x += SPEED;
        if (team == 1) data = sprite_player_red_right;
        else data = sprite_player_blue_right;
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
        vga->plot_sprite(get_data(), PLAYER_WIDTH, PLAYER_HEIGHT, get_x(), get_y());
        frame++;
        thread_yield();
    }
    thread_exit();
}
