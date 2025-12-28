#include "deck.h"

Deck init_shuffled_deck(unsigned short deck_count)
{
    Deck new_deck = init_sorted_deck(deck_count);
    shuffle_uint_array(new_deck.cards, new_deck.head);
    return new_deck;
}

Deck init_sorted_deck(unsigned short deck_count)
{
    Deck new_deck;
    new_deck.total = (deck_count * 52);
    new_deck.head = new_deck.total - 1;
    new_deck.cards = malloc(deck_count * 52 * sizeof *new_deck.cards);
    for (unsigned short d = 0; d < deck_count; ++d)
        for (unsigned short c = 0; c < 52; ++c)
            new_deck.cards[c + d * 52] = c;
    return new_deck;
}

void card_string_repr(unsigned short card, char *out)
{
    if (card > 51)
    {
        fprintf(stderr, "ERROR: %u > 51 and can't be converted to a card\n", card);
        exit(1);
    }

    static const char *suits[] = {"S", "H", "C", "D"};
    static const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    unsigned short suit = card / 13;
    unsigned short rank = card % 13;

    snprintf(out, 4, "%s%s", ranks[rank], suits[suit]);
}

unsigned short pop_card(Deck *deck)
{
    if (deck->head >= deck->total)
    {
        fprintf(stderr, "ERROR: Can't pop from deck, deck empty\n");
        exit(1);
    }
    return deck->cards[deck->head--];
}

void shuffle_deck(Deck *deck)
{
    deck->head = deck->total - 1;
    shuffle_uint_array(deck->cards, deck->head);
}