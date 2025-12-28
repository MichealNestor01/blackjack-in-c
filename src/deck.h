#ifndef DECK_H
#define DECK_H

#include "stdlib.h"
#include "stdio.h"
#include "shuffle.h"

typedef struct Deck
{
    unsigned int total;
    unsigned int head;
    unsigned int *cards;
} Deck;

Deck init_shuffled_deck(unsigned int deck_count);
Deck init_sorted_deck(unsigned int deck_count);
unsigned int pop_card(Deck *deck);
void card_string_repr(unsigned int card, char *out);

#endif