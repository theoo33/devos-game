#include "HalfManager.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <sextant/ordonnancements/preemptif/thread.h>
#include <drivers/EcranBochs.h>

HalfManager::HalfManager(EcranBochs* vga) : vga(vga) {
}

void HalfManager::half_logic() {
    half_time_sem->P();
    // TODO : Prepare screen for the pause
}

void HalfManager::match_end_logic() {
    half_time_sem->P();
    // TODO : Prepare screen for the end of the match
}

void HalfManager::run() {
    half_time_sem->P();
    while(true){
        if (!half_passed){
            half_logic();
            half_passed = true;
        }
        else match_end_logic();
        thread_yield();
    }
}
