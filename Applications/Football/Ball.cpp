#include "Ball.h"
#include "Player.h"
#include <drivers/EcranBochs.h>

Ball :: Ball(
    int x, 
    int y, 
    char SPEED, 
    unsigned char* data, 
    Player* p1, 
    Player* p2,
    EcranBochs* vga_entry
) :
    x(x),
    y(y),
    SPEED(SPEED),
    data(data),
    p1(p1),
    p2(p2),
    vga(vga_entry)
{};

int Ball :: get_x(){return x;}
int Ball :: get_y(){return y;}
unsigned char* Ball :: get_data(){return data;}
void Ball :: set_x(int new_x){x=new_x;}
void Ball :: set_y(int new_y){y=new_y;}

bool Ball :: isColliding(Player* p) {
    // first we calculate a possible contact on each side of the ball
    bool contact_left = (
        (p->get_x() + p->PLAYER_WIDTH >= x) &&
        (p->get_x() + p->PLAYER_WIDTH <= x + BALL_WIDTH)
    );
    bool contact_right = (
        (p->get_x() >= x) &&
        (p->get_x() <= x + BALL_WIDTH)
    );
    bool contact_up = (
        (p->get_y() + p->PLAYER_HEIGHT >= y) &&
        (p->get_y() + p->PLAYER_HEIGHT <= y + BALL_HEIGHT)
    );
    bool contact_down = (
        (p->get_y() >= y) &&
        (p->get_y() <= y + BALL_HEIGHT)
    );
    if ((contact_left || contact_right) && (contact_down || contact_up))
        return true;
    return false;
}

void Ball :: getOrientation(Player* p) {
    int x_diff = x - p->get_x();
    int y_diff = y - p->get_y();

    int x_diff_sign;
    int y_diff_sign;
    if (x_diff > 0) x_diff_sign = 1;
    else x_diff_sign = -1;
    if (y_diff > 0) y_diff_sign = 1;
    else y_diff_sign = -1;

    if (
        ((x_diff * x_diff_sign) <= 2 * (y_diff * y_diff_sign)) 
        && (3 * (x_diff * x_diff_sign) >= 2 * (y_diff * y_diff_sign))
    ) {
        towards_x = x_diff_sign;
        towards_y = y_diff_sign;  
    }
    else {
        if ((x_diff * x_diff_sign) > (y_diff * y_diff_sign)) {
            towards_x = x_diff_sign;
            towards_y = 0;
        }
        else {
            towards_x = 0;
            towards_y = y_diff_sign;
        }
    }
    
}


void Ball :: move() {

}

void Ball :: run() {
    while (true)
    {
        if (isColliding(p1)){
            getOrientation(p1);
            x = x + (towards_x * SPEED);
            y = y + (towards_y * SPEED);
        }
        vga->plot_sprite(get_data(), SPRITE_WIDTH, SPRITE_HEIGHT, get_x(), get_y());
        thread_yield();
    }
    thread_exit();
}