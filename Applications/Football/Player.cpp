#include "Player.h"
#include <drivers/EcranBochs.h>
#include <drivers/Clavier.h>
#include "sextant/types.h"
#include "Field.h"


extern bool key_pressed[126];
extern int FRAME_SKIP;
extern unsigned char sprite_player_red_left[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];
extern unsigned char sprite_player_red_right[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];
extern unsigned char sprite_player_blue_left[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];
extern unsigned char sprite_player_blue_right[SPRITE_PLAYER_WIDTH*SPRITE_PLAYER_HEIGHT];

Player::Player(int x_pos, 
    int y_pos, 
    char team, 
    int speed, 
    EcranBochs* vga_entry,
    Field* field_entry) : 
        x(x_pos), 
        y(y_pos), 
        team(team), 
        SPEED(speed),
        vga(vga_entry),
        field(field_entry)
        {
            if (team == 1) {
                data = sprite_player_blue_right;
                KEY_UP = AZERTY::K_Z;
                KEY_DOWN = AZERTY::K_S;
                KEY_LEFT = AZERTY::K_Q;
                KEY_RIGHT = AZERTY::K_D;
            } else {
                data = sprite_player_red_left;
                KEY_UP = AZERTY::K_O;
                KEY_DOWN = AZERTY::K_L;
                KEY_LEFT = AZERTY::K_K;
                KEY_RIGHT = AZERTY::K_M;
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
        if (y > field->field.left_upper_y) y -= SPEED;
	}
    if (key_pressed[Player::KEY_LEFT] ) {
        if (x > field->field.left_upper_x) x -= SPEED;
        if (team == 1) data = sprite_player_red_left;
        else data = sprite_player_blue_left;
    }
    if (key_pressed[Player::KEY_DOWN]) {
        if(y + PLAYER_HEIGHT + SPEED < field->field.right_lower_y)
            y += SPEED;
    }
    if (key_pressed[Player::KEY_RIGHT]) {
        if(x + PLAYER_WIDTH + SPEED < field->field.right_lower_x)
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
