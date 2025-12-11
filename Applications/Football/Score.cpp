#include "Score.h"
#include <sextant/Synchronisation/Semaphore/Semaphore.h>

extern Semaphore* score_sem;

Score::Score(
    int x_pos, 
    int y_pos, 
    unsigned char* zero_data,
    unsigned char* one_data,
    unsigned char* two_data,
    unsigned char* three_data
) : 
x(x_pos), 
y(y_pos), 
zero_data(zero_data),
one_data(one_data),
two_data(two_data),
three_data(three_data)
{
    count = 0;
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