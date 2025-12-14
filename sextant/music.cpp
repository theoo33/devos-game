#include <drivers/speaker.h>
#include <sextant/Synchronisation/Spinlock/Spinlock.h>

static Spinlock delay_lock_main_theme;
static int delay_count_main_theme = 0;

// Wait using spinlock to allow interrupts
void wait_ms_main_theme(unsigned int duration_ms) {
    for (volatile unsigned int i = 0; i < duration_ms * 100; i++) {
        delay_lock_main_theme.Take(&delay_count_main_theme);
        delay_lock_main_theme.Release(&delay_count_main_theme);
    }
}

// Auto-generated from audio file
// Sequence of speaker.play(frequency, duration_ms) calls
void main_theme(Speaker* speaker) {
    // Silence for 400ms
    speaker->stop();
    wait_ms_main_theme(400);
    speaker->play(730, 1500);  // 730Hz for 1500ms
    wait_ms_main_theme(1500);
    speaker->play(780, 1500);  // 780Hz for 1500ms
    wait_ms_main_theme(1500);
    speaker->play(160, 100);  // 160Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 400);  // 780Hz for 400ms
    wait_ms_main_theme(400);
    speaker->play(160, 200);  // 160Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(490, 200);  // 490Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(160, 200);  // 160Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(490, 100);  // 490Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(660, 200);  // 660Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(160, 200);  // 160Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(660, 100);  // 660Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 200);  // 780Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(160, 200);  // 160Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 100);  // 780Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(990, 100);  // 990Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(2930, 100);  // 2930Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(130, 100);  // 130Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(60, 100);  // 60Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(440, 100);  // 440Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(520, 100);  // 520Hz for 100ms
    wait_ms_main_theme(100);
    // Silence for 100ms
    speaker->stop();
    wait_ms_main_theme(100);
    speaker->play(70, 200);  // 70Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(520, 100);  // 520Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(660, 100);  // 660Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(60, 100);  // 60Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(70, 200);  // 70Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 200);  // 780Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 100);  // 780Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(1040, 200);  // 1040Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(440, 100);  // 440Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(520, 200);  // 520Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 500);  // 780Hz for 500ms
    wait_ms_main_theme(500);
    speaker->play(770, 100);  // 770Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 900);  // 780Hz for 900ms
    wait_ms_main_theme(900);
    speaker->play(730, 1000);  // 730Hz for 1000ms
    wait_ms_main_theme(1000);
    speaker->play(780, 500);  // 780Hz for 500ms
    wait_ms_main_theme(500);
    speaker->play(490, 100);  // 490Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 400);  // 780Hz for 400ms
    wait_ms_main_theme(400);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 200);  // 780Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 100);  // 780Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(880, 200);  // 880Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 300);  // 60Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(780, 100);  // 780Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(740, 100);  // 740Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 100);  // 780Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(590, 100);  // 590Hz for 100ms
    wait_ms_main_theme(100);
    // Silence for 100ms
    speaker->stop();
    wait_ms_main_theme(100);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(490, 100);  // 490Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(590, 100);  // 590Hz for 100ms
    wait_ms_main_theme(100);
    // Silence for 100ms
    speaker->stop();
    wait_ms_main_theme(100);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 200);  // 780Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 300);  // 60Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(780, 200);  // 780Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 300);  // 60Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(780, 200);  // 780Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 200);  // 60Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 100);  // 780Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(590, 200);  // 590Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(580, 500);  // 580Hz for 500ms
    wait_ms_main_theme(500);
    speaker->play(590, 100);  // 590Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(580, 600);  // 580Hz for 600ms
    wait_ms_main_theme(600);
    speaker->play(120, 100);  // 120Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(580, 200);  // 580Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(650, 1100);  // 650Hz for 1100ms
    wait_ms_main_theme(1100);
    speaker->play(520, 100);  // 520Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(650, 400);  // 650Hz for 400ms
    wait_ms_main_theme(400);
    speaker->play(520, 100);  // 520Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(650, 300);  // 650Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(50, 100);  // 50Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(520, 300);  // 520Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(50, 200);  // 50Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(440, 100);  // 440Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(520, 200);  // 520Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(70, 200);  // 70Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(490, 100);  // 490Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(590, 100);  // 590Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(540, 100);  // 540Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(730, 500);  // 730Hz for 500ms
    wait_ms_main_theme(500);
    speaker->play(490, 100);  // 490Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 400);  // 780Hz for 400ms
    wait_ms_main_theme(400);
    speaker->play(490, 200);  // 490Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 300);  // 780Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(490, 200);  // 490Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 300);  // 780Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(490, 100);  // 490Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 400);  // 780Hz for 400ms
    wait_ms_main_theme(400);
    speaker->play(80, 100);  // 80Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(390, 100);  // 390Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(490, 200);  // 490Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(80, 200);  // 80Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(490, 100);  // 490Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(660, 100);  // 660Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(650, 100);  // 650Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(80, 100);  // 80Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(90, 100);  // 90Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(660, 100);  // 660Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 100);  // 780Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(1560, 100);  // 1560Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(650, 200);  // 650Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(780, 400);  // 780Hz for 400ms
    wait_ms_main_theme(400);
    speaker->play(440, 100);  // 440Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 1400);  // 780Hz for 1400ms
    wait_ms_main_theme(1400);
    speaker->play(440, 100);  // 440Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(780, 300);  // 780Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(60, 100);  // 60Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(440, 100);  // 440Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(520, 200);  // 520Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(60, 100);  // 60Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(50, 100);  // 50Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(520, 100);  // 520Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(660, 100);  // 660Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(690, 100);  // 690Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(50, 200);  // 50Hz for 200ms
    wait_ms_main_theme(200);
    speaker->play(660, 100);  // 660Hz for 100ms
    wait_ms_main_theme(100);
    speaker->play(880, 100);  // 880Hz for 100ms
    wait_ms_main_theme(100);
    // Silence for 100ms
    speaker->stop();
    wait_ms_main_theme(100);
    speaker->play(650, 300);  // 650Hz for 300ms
    wait_ms_main_theme(300);
    speaker->play(649, 100);  // 649Hz for 100ms
    wait_ms_main_theme(100);
}