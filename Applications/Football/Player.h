#ifndef PLAYER_H
#define PLAYER_H

#include <sextant/sprite.h>
#include <sextant/types.h>

class Player {
    public:
        ui8_t KEY_UP;
        ui8_t KEY_DOWN;
        ui8_t KEY_LEFT;
        ui8_t KEY_RIGHT;
        int SPEED;
        int get_x();
        void set_x(int new_x);
        int get_y();
        void set_y(int new_y);
        unsigned char* get_data();
        Player(int x, int y, unsigned char* data, int SPEED_SLOWDOWN_COEF, ui8_t up, ui8_t down, ui8_t left, ui8_t right);
        bool is_any_key_pressed();
        void move(ui16_t WIDTH, ui16_t HEIGHT);

    private:
        int x;
        int y;
        unsigned char* data = sprite_data;
        
};

#endif