#include "game.h"

void play_game(unsigned int player_count, unsigned int deck_count)
{
    // setup the player objects and the shuffled deck
    Player players[9];
    for (unsigned int player_index = 0; player_index < player_count; ++player_index)
        players[player_index] = init_player();
    players[8] = init_player(); // players[8] is used as the dealer
    Deck deck = init_shuffled_deck(deck_count);
    unsigned int round = 1;
    while (1)
    { // main loop
        play_round(players, player_count, &deck);
        ++round;
        break;
    }
}

void play_round(Player *players, unsigned int player_count, Deck *deck)
{
    // deal initial two cards
    for (unsigned int card = 0; card < 2; ++card)
    {
        for (unsigned int player_index; player_index < player_count; ++player_count)
            deal_card(deck, &players[player_index]);
        deal_card(deck, &players[8]); // dealer
    }
    // peak for dealer blackjack
    if (players[8].hand_score == 21)
    {
    }
}

void deal_card(Deck *deck, Player *player)
{
    unsigned int card = pop_card(deck);
    add_to_hand(player, card);
}