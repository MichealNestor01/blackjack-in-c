#include "shuffle.h"

void shuffle_uint_array(unsigned int *arr, unsigned int head)
{
    for (unsigned int i = head; i <= head; --i)
    {
        unsigned int target_index = rand() % head;
        unsigned int temp = arr[i];
        arr[i] = arr[target_index];
        arr[target_index] = temp;
    }
}