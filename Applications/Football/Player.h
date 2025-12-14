#ifndef PLAYER_H
#define PLAYER_H

#include <sextant/sprite.h>
#include <sextant/types.h>
#include <sextant/Activite/Threads.h>
#include <drivers/EcranBochs.h>



class Player : public Threads {
    public:
        Player(int x_pos, int y_pos, int SPEED, int team, EcranBochs* vga_entry);
        ui8_t KEY_UP;
        ui8_t KEY_DOWN;
        ui8_t KEY_LEFT;
        ui8_t KEY_RIGHT;
        int SPEED;
        EcranBochs* vga;
        int get_x();
        void set_x(int new_x);
        int get_y();
        void set_y(int new_y);
        unsigned char* get_data();
        bool is_any_key_pressed();
        void move(ui16_t WIDTH, ui16_t HEIGHT);

        void run();
        
        const int PLAYER_HEIGHT = SPRITE_PLAYER_HEIGHT;
        const int PLAYER_WIDTH = SPRITE_PLAYER_WIDTH;

    private:
        int x;
        int y;
        int team;
        unsigned char* data;
        
};

#endif