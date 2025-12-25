#include "deck.h"
#include "stdio.h"
#include "time.h"

int main()
{
    printf("hello world\n");

    Deck deck = init_shuffled_deck(1);
    char card[4];
    for (unsigned int i = 0; i <= deck.head; ++i)
    {
        card_string_repr(deck.cards[i], card);
        printf("Card %d: %s (%d)\n", i, card, deck.cards[i]);
    }

    return 0;
}