#ifndef FIELD_H
#define FIELD_H

#include <sextant/Activite/Threads.h>

#include <sextant/sprite.h>
#include <sextant/types.h>
#include "Ball.h"
#include <drivers/EcranBochs.h>

class Field {
    public:
        Field(
            unsigned char* data,
            EcranBochs* vga_entry
        );
        void run();
        void set_borders(ZONE dimensions);
        void set_left_goal(ZONE dimensions);
        void set_right_goal(ZONE dimensions);
        bool has_scored(Ball* b);
        bool outside_field(Ball* b);

    
    private:
        unsigned char* data;
        EcranBochs* vga;
        ZONE field_dimensions;
        ZONE left_goal;
        ZONE right_goal;
        
};

struct ZONE {
    static const int left_upper_x ;
    static const int left_upper_y;
    static const int WIDTH;
    static const int HEIGHT;
};

#endif