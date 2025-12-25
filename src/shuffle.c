#include "shuffle.h"

void shuffle_uint_array(unsigned int *arr, unsigned int head)
{
    // rand() needs to have a seed, if we use current time it will be random
    // enough for this use case
    static unsigned int seed_generated = 0;
    if (!seed_generated)
        srand((unsigned int)time(NULL));
    for (unsigned int i = head; i <= head; --i)
    {
        unsigned int target_index = rand() % head;
        unsigned int temp = arr[i];
        arr[i] = arr[target_index];
        arr[target_index] = temp;
    }
}