#ifndef FIELD_H
#define FIELD_H

#include <sextant/Activite/Threads.h>

#include <sextant/sprite.h>
#include <sextant/types.h>
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
            EcranBochs* vga_entry,
            const ZONE& borders,
            const ZONE& left_goal,
            const ZONE& right_goal
        );
        int has_scored(int x, int y, int width, int height);
        bool outside_field(int x, int y, int width, int height);

        int width;
        int height;
        EcranBochs* vga;
        ZONE field;
        ZONE left_goal;
        ZONE right_goal;
        void paint();

        int get_center_x(){ return center_x; };
        int get_center_y(){ return center_y; };
        
    private:
        int center_x;
        int center_y;
        
        
};

#endif