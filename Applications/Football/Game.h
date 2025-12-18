#ifndef GAME_H
#define GAME_H

#include <drivers/timer.h>
#include <drivers/speaker.h>
#include <sextant/Activite/Threads.h>
#include <drivers/EcranBochs.h>

class Game : public Threads{
    public:
        Game(EcranBochs* vga_entry, Timer* timer_entry, Speaker* speaker_entry, ui16_t width, ui16_t height);

        void init_match();
        void stop_match();
        void draw_time(int screen_width, int space_between);

        void run();

        bool game_started;
        bool game_finished;

    private:
        EcranBochs* vga;
        Timer* timer;
        Speaker* speaker;

        const ui16_t WIDTH;
        const ui16_t HEIGHT;

        // Track which events have been triggered to avoid multiple signals
        bool half_time_triggered = false;
        bool end_match_triggered = false;
};

#endif
