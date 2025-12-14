#ifndef HALFMANAGER_H
#define HALFMANAGER_H

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>

extern Semaphore* half_time_sem;
extern Semaphore* end_match_sem;

class HalfManager : public Threads {
    public:
        HalfManager(int half_time_duration_seconds);
        void run();
    private:
        int half_time_duration_seconds;
};

#endif