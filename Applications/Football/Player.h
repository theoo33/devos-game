#ifndef PLAYER_H
#define PLAYER_H

#include <sextant/sprite.h>
#include <sextant/types.h>

class Player {
    public:
        ui8_t UP_KEY;
        ui8_t DOWN_KEY;
        ui8_t LEFT_KEY;
        ui8_t RIGHT_KEY;
        int get_x();
        void set_x(int new_x);
        int get_y();
        void set_y(int new_y);
        unsigned char* get_data();
        Player(int x, int y, unsigned char* data, ui8_t up, ui8_t down, ui8_t left, ui8_t right);

    private:
        int x;
        int y;
        unsigned char* data = sprite_data;
        
};

#endif