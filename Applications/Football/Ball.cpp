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
    // TODO : different width and height according to the sprite
    int p_width = SPRITE_WIDTH;
    int b_width = SPRITE_WIDTH;
    int p_height = SPRITE_HEIGHT;
    int b_height = SPRITE_HEIGHT;
    //
    if (
        (this->x<=p->get_x() + p_width) && 
        (this->x>=p->get_x() - b_width) &&
        (this->y<=p->get_y() + b_height) &&
        (this->y>=p->get_y() - p_height)
    )
        return true;
    return false;
}

void Ball :: move() {

}

void Ball :: run() {
    while (true)
    {
        if (isColliding(p1)){
            this->x = p1->get_x() + SPRITE_WIDTH;
            this->y = p1->get_y() + SPRITE_HEIGHT;
        }
        vga->clear(0);
		vga->plot_sprite(get_data(), SPRITE_WIDTH, SPRITE_HEIGHT, get_x(), get_y());
		vga->swapBuffer(); // call this after you finish drawing your frame to display it, it avoids screen tearing
        thread_yield();
    }
    thread_exit();
}