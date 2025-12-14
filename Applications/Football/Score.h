#ifndef SCORE_H
#define SCORE_H

#include <sextant/sprite.h>
#include <sextant/types.h>
#include <sextant/Activite/Threads.h>
#include <drivers/EcranBochs.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>

class Score : public Threads {
    public:
        Score(
            int x,
            int y,
            int team,
            Semaphore* sem
        );
        void run();
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
        int get_count(){return count;};
        Semaphore* sem;
    private:
        int count;
};
#endif