#include "speaker.h"
#include <hal/fonctionsES.h>
#include <drivers/timer.h>
#include <sextant/interruptions/handler/handler_speaker.h>

#define PIT_CHANNEL_2 0x42
#define PIT_CONTROL 0x43
#define SPEAKER_PORT 0x61
#define PIT_FREQUENCY 1193180  // Base frequency of PIT

Speaker::Speaker() {
    stop();
}

void Speaker::set_frequency(unsigned int frequency) {
    if (frequency == 0) return;
    
    unsigned int divisor = PIT_FREQUENCY / frequency;
    
    // Set PIT channel 2 to mode 3 (square wave)
    ecrireOctet(0xB6, PIT_CONTROL);  // 10110110 binary
    
    // Send divisor (LSB first, then MSB)
    ecrireOctet(divisor & 0xFF, PIT_CHANNEL_2);
    ecrireOctet((divisor >> 8) & 0xFF, PIT_CHANNEL_2);
}

void Speaker::set_enabled(bool enabled) {
    ui8_t value = lireOctet(SPEAKER_PORT);
    
    if (enabled) {
        // Enable speaker: set bits 0 and 1
        value |= 0x03;
    } else {
        // Disable speaker: clear bits 0 and 1
        value &= ~0x03;
    }
    
    ecrireOctet(value, SPEAKER_PORT);
}

void Speaker::play(unsigned int frequency, unsigned int duration_ms) {
    set_frequency(frequency);
    set_enabled(true);
    
    // Register with handler to stop after duration
    speaker_register_sound(duration_ms);
}

void Speaker::stop() {
    set_enabled(false);
}
