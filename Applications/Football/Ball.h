#ifndef BALL_H
#define BALL_H

#include <sextant/Activite/Threads.h>

#include <sextant/sprite.h>
#include <sextant/types.h>
#include "Player.h"
#include <drivers/EcranBochs.h>

class Ball : public Threads {
    public:
        char SPEED;
        int get_x();
        void set_x(int new_x);
        int get_y();
        void set_y(int new_y);
        unsigned char* get_data();
        Ball(
            int x, 
            int y, 
            char SPEED, 
            unsigned char* data,
            Player* p1,
            Player* p2,
            EcranBochs* vga
        );
        void run();
        
        private:
        int x;
        int y;
        Player* p1;
        Player* p2;
        unsigned char* data = sprite_data;
        EcranBochs* vga;
        bool isColliding(Player*);
        void move();
        
};

#endif