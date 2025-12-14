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
    int right_lower_x;
    int right_lower_y;
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

        int width;
        int height;
        unsigned char* background_data;
        EcranBochs* vga;
        ZONE field;
        ZONE left_goal;
        ZONE right_goal;

        int has_scored(int x, int y, int width, int height);
        bool outside_field(int x, int y, int width, int height);
        int get_center_x() { return center_x; }
        int get_center_y() { return center_y; }
        void paint();

    private:
        int center_x;
        int center_y;
        
};

#endif