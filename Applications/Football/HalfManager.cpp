#include "HalfManager.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <sextant/ordonnancements/preemptif/thread.h>

Semaphore* half_time_sem = new Semaphore(1);
Semaphore* end_match_sem = new Semaphore(1);

HalfManager::HalfManager(int half_time_duration_seconds) 
    : half_time_duration_seconds(half_time_duration_seconds) {
}

void half_logic() {
    int i = 0;
    half_time_sem->P();
}

void match_end_logic() {
    int i = 0;
    end_match_sem->P();
}

void HalfManager::run() {
    while(true){
        half_logic();
        match_end_logic();
        thread_yield();
    }
}
