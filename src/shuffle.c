#include "shuffle.h"

void shuffle_uint_array(unsigned short *arr, unsigned short head)
{
    // rand() needs to have a seed, if we use current time it will be random
    // enough for this use case
    static unsigned short seed_generated = 0;
    if (!seed_generated)
        srand((unsigned short)time(NULL));
    for (unsigned short i = head; i <= head; --i)
    {
        unsigned short target_index = rand() % head;
        unsigned short temp = arr[i];
        arr[i] = arr[target_index];
        arr[target_index] = temp;
    }
}