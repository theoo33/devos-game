#ifndef FIELD_H
#define FIELD_H

#include <sextant/Activite/Threads.h>

#include <sextant/sprite.h>
#include <sextant/types.h>
#include "Ball.h"
#include <drivers/EcranBochs.h>

typedef struct {
    int left_upper_x;
    int left_upper_y;
    int WIDTH;
    int HEIGHT;
} ZONE;

class Field {
    public:
        Field(
            unsigned char* background_data,
            EcranBochs* vga_entry,
            const ZONE& borders,
            const ZONE& left_goal,
            const ZONE& right_goal
        );
        bool has_scored(Ball* b);
        bool outside_field(int x, int y, int width, int height);

    
    private:
        int width;
        int height;
        unsigned char* background_data;
        EcranBochs* vga;
        ZONE field_dimensions;
        ZONE left_goal;
        ZONE right_goal;
        
};

#endif