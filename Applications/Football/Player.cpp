#include "Player.h"

Player::Player(int x, int y, unsigned char* data): x(x), y(y), data(data){};

int Player::get_x() {return x;};
void Player::set_x(int new_x) {x=new_x;};

int Player::get_y() {return y;};
void Player::set_y(int new_y) {y=new_y;};

unsigned char* Player::get_data() {return data;};