#ifndef HALFMANAGER_H
#define HALFMANAGER_H

#include <sextant/Activite/Threads.h>
#include <sextant/Synchronisation/Semaphore/Semaphore.h>
#include <drivers/EcranBochs.h>

class HalfManager : public Threads {
    public:
        HalfManager(EcranBochs* vga);
        void run();
        void stop() {Exit();};
        Semaphore* half_time_sem = new Semaphore(1);
        bool half_passed = false;
    private:
        EcranBochs* vga;
        void half_logic();
        void match_end_logic();
};

#endif