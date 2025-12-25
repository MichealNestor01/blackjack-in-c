#ifndef DECK_H
#define DECK_H

#include "stdlib.h"
#include "stdio.h"
#include "shuffle.h"

typedef struct Deck
{
    unsigned int head;
    unsigned int *cards;
} Deck;

Deck init_shuffled_deck();
Deck init_sorted_deck();
void card_string_repr(unsigned int card, char *out);

#endif