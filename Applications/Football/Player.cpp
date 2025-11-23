#include "Player.h"
#include "sextant/types.h"

Player::Player(int x, int y, unsigned char* data, ui8_t up, ui8_t down, ui8_t left, ui8_t right): 
    x(x), 
    y(y), 
    data(data),
    UP_KEY(up),
    DOWN_KEY(down),
    LEFT_KEY(left),
    RIGHT_KEY(right)
{};

int Player::get_x() {return x;};
void Player::set_x(int new_x) {x=new_x;};

int Player::get_y() {return y;};
void Player::set_y(int new_y) {y=new_y;};

unsigned char* Player::get_data() {return data;};