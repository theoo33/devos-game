#ifndef SCORE_H
#define SCORE_H

#include <sextant/sprite.h>
#include <sextant/types.h>
#include <sextant/Activite/Threads.h>
#include <drivers/EcranBochs.h>

class Score : public Threads {
    public:
        Score(
            int x,
            int y,
            int team
        );
        void increment();
        unsigned char* show_sprite();
        const int HEIGHT = SPRITE_NUMBER_HEIGHT;
        const int WIDTH = SPRITE_NUMBER_WIDTH;
        unsigned char* zero_data;
        unsigned char* one_data;
        unsigned char* two_data;
        unsigned char* three_data;
        int x;
        int y;
    private:
        int count;
};
#endif