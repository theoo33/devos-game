#ifndef BALL_H
#define BALL_H

#include <sextant/Activite/Threads.h>

#include <sextant/sprite.h>
#include <sextant/types.h>
#include "Player.h"
#include <drivers/EcranBochs.h>

typedef struct {
    int x;
    int y;
} Vector;

class Ball : public Threads {
    public:
        const int BALL_HEIGHT = SPRITE_BALL_HEIGHT;
        const int BALL_WIDTH = SPRITE_BALL_WIDTH;

        Ball(
            int x, 
            int y, 
            int acc, 
            int friction,
            unsigned char* data,
            Player* p1,
            Player* p2,
            EcranBochs* vga
        );

        int get_x(){ return x; };
        void set_x(int new_x) { x = new_x; };
        int get_y(){ return y; };
        void set_y(int new_y) { y = new_y; };

        unsigned char* get_data() { return data; };

        int get_speed(){ return speed; };
        void set_speed(int new_speed){ speed = new_speed; };

        int get_counter(){ return counter_till_next_speed; };
        void set_counter(int new_counter){ counter_till_next_speed = new_counter; };
        
        void run();
        
        Vector movement;
        
        private:
        int x; // position x of ball
        int y; // position y of ball
        int x_diff; // between player and ball at contact time
        int y_diff; // between player and ball at contact time
        // int x_diff; // x_diff dx (-1, 0 or 1)
        // int y_diff; // y_diff dy (-1, 0 or 1)
        int towards_x;
        int towards_y;
        int err; 
        int speed; // current ball speed
        int acc; // acceleration = max speed
        int friction; // dictates speed deceleration
        int dx; // movement for each iteration
        int dy; // movement for each iteration
        int counter_till_next_speed;
        Player* p1;
        Player* p2;
        unsigned char* data = sprite_data;
        EcranBochs* vga;

        bool isColliding(Player*);
        void bresenhamInit();
        void bresenhamGetOrientation();
        void move();

        
};

#endif