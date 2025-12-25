#include "deck.h"

Deck init_shuffled_deck(unsigned int deck_count)
{
    Deck new_deck = init_sorted_deck(deck_count);
    shuffle_uint_array(new_deck.cards, new_deck.head);
    return new_deck;
}

Deck init_sorted_deck(unsigned int deck_count)
{
    Deck new_deck;
    new_deck.head = (deck_count * 52) - 1;
    new_deck.cards = malloc(deck_count * 52 * sizeof *new_deck.cards);
    for (unsigned int d = 0; d < deck_count; ++d)
        for (unsigned int c = 0; c < 52; ++c)
            new_deck.cards[c + d * 52] = c;
    return new_deck;
}