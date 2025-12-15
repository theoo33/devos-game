#ifndef PLAYER_H
#define PLAYER_H

#include <sextant/sprite.h>
#include <sextant/types.h>
#include <sextant/Activite/Threads.h>
#include <drivers/EcranBochs.h>
#include "Field.h"



class Player : public Threads {
    public:
        Player(int x, int y, char team, int SPEED, EcranBochs* vga_entry, Field* field_entry);
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
        bool is_any_key_pressed();
        void move(ui16_t WIDTH, ui16_t HEIGHT);
        
        void run();
        void stop(){Exit();};

        void reset_position(bool second_half);
        void set_character_direction(bool second_half);
        
        const int PLAYER_HEIGHT = SPRITE_PLAYER_HEIGHT;
        const int PLAYER_WIDTH = SPRITE_PLAYER_WIDTH;
        
    private:
        int x;
        int y;
        char team;
        unsigned char* data;
        EcranBochs* vga;
        Field* field;
        
};

#endif