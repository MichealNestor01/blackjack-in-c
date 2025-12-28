#ifndef DECK_H
#define DECK_H

#include "stdlib.h"
#include "stdio.h"
#include "shuffle.h"

typedef struct Deck
{
    unsigned short total;
    unsigned short head;
    unsigned short *cards;
} Deck;

Deck init_shuffled_deck(unsigned short deck_count);
Deck init_sorted_deck(unsigned short deck_count);
unsigned short pop_card(Deck *deck);
void card_string_repr(unsigned short card, char *out);

#endif