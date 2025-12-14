#ifndef SPEAKER_H
#define SPEAKER_H

#include <sextant/types.h>

// Forward declaration
void speaker_register_sound(unsigned int duration_ms);

class Speaker {
public:
    Speaker();
    
    // Play a frequency (in Hz) for a duration (in milliseconds)
    // Non-blocking: registers sound with handler, returns immediately
    void play(unsigned int frequency, unsigned int duration_ms);
    
    // Stop playing immediately
    void stop();
    
private:
    // Set speaker frequency via PIT channel 2
    void set_frequency(unsigned int frequency);
    
    // Enable/disable speaker
    void set_enabled(bool enabled);
};

#endif
