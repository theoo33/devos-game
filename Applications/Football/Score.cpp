#include "Score.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>

extern Semaphore* score_sem;

Score::Score(
    int x_pos, 
    int y_pos, 
    int team
) : 
x(x_pos), 
y(y_pos), 
zero_data(zero_data),
one_data(one_data),
two_data(two_data),
three_data(three_data)
{
    count = 0;
    if (team == 1) {
        zero_data = zeroR_data;
        one_data = oneR_data;
        two_data = twoR_data;
        three_data = threeR_data;
    }
    else {
        zero_data = zeroB_data;
        one_data = oneB_data;
        two_data = twoB_data;
        three_data = threeB_data;
    }
}

void Score::increment(){
    score_sem->P();
    count++;
}

unsigned char* Score::show_sprite(){
    switch (count)
    {
    case 0:
        return zero_data;
    case 1:
        return one_data;
    case 2:
        return two_data;
    case 3:
        return three_data;
    }
}