#include "handler_speaker.h"
#include <drivers/speaker.h>
#include <drivers/timer.h>

// Track speaker state
static unsigned int speaker_start_time = 0;
static unsigned int speaker_duration = 0;
static bool speaker_is_playing = false;

// Called from speaker.play() to register a sound
void speaker_register_sound(unsigned int duration_ms) {
    extern Timer timer;
    speaker_start_time = timer.getSecondes() * 1000;
    speaker_duration = duration_ms;
    speaker_is_playing = true;
}

// Handler called on timer interrupt to check if sound should stop
void handler_speaker(int intid) {
    extern Timer timer;
    
    if (speaker_is_playing) {
        unsigned int current_time = timer.getSecondes() * 1000;
        if ((current_time - speaker_start_time) >= speaker_duration) {
            extern Speaker speaker;
            speaker.stop();
            speaker_is_playing = false;
        }
    }
}
