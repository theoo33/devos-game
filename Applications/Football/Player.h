#ifndef PLAYER_H
#define PLAYER_H

#include <sextant/sprite.h>

class Player {
    public:
        int get_x();
        void set_x(int new_x);
        int get_y();
        void set_y(int new_y);
        unsigned char* get_data();
        Player(int x, int y, unsigned char* data);

    private:
        int x;
        int y;
        unsigned char* data = sprite_data;
        
};

#endif