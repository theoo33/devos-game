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
        const int BALL_HEIGHT = SPRITE_HEIGHT;
        const int BALL_WIDTH = SPRITE_WIDTH;

        Ball(
            int x, 
            int y, 
            char SPEED, 
            unsigned char* data,
            Player* p1,
            Player* p2,
            EcranBochs* vga
        );

        int get_x();
        void set_x(int new_x);
        int get_y();
        void set_y(int new_y);
        unsigned char* get_data();
        
        void run();
        
        
        private:
        int x;
        int y;
        int towards_x;
        int towards_y;
        Player* p1;
        Player* p2;
        unsigned char* data = sprite_data;
        EcranBochs* vga;
        bool isColliding(Player*);
        void getOrientation(Player*);
        void move();

        
};

#endif