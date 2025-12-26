#include "stdio.h"
#include "stdlib.h"
#include "deck.h"
#include "time.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("USAGE: %s players decks\n", argv[0]);
        exit(0);
    }

    int players = atoi(argv[1]);
    if (players < 1 || players > 10)
    {
        printf("USAGE: must select between 1 and 10 players\n");
        exit(0);
    }

    int decks = atoi(argv[2]);
    if (decks < 1 || decks > 8)
    {
        printf("USAGE: must select between 1 and 8 decks to play with\n");
        exit(0);
    }

    Deck deck = init_shuffled_deck(1);
    char card[4];
    for (unsigned int i = 0; i <= deck.head; ++i)
    {
        card_string_repr(deck.cards[i], card);
        printf("Card %d: %s (%d)\n", i, card, deck.cards[i]);
    }

    return 0;
}