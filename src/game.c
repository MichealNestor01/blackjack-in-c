#include "game.h"

void play_game(unsigned short player_count, unsigned short deck_count)
{
    // setup the player objects and the shuffled deck
    Player players[9];
    for (unsigned short player_index = 0; player_index < player_count; ++player_index)
        players[player_index] = init_player();
    players[8] = init_player(); // players[8] is used as the dealer
    Deck deck = init_shuffled_deck(deck_count);
    unsigned short round = 1;
    while (1)
    { // main loop
        play_round(players, player_count, &deck);
        ++round;
        break;
    }
}

void play_round(Player *players, unsigned short player_count, Deck *deck)
{
    // deal initial two cards
    printf("Dealing cards\n");
    for (unsigned short card = 0; card < 2; ++card)
    {
        for (unsigned short player_index; player_index < player_count; ++player_count)
            deal_card(deck, &players[player_index]);
        deal_card(deck, &players[8]); // dealer
        display_hands(players, player_count);
    }
    // peak for dealer blackjack
    if (players[8].hand_score == 21)
    {
        // score_players(players, player_count);
    }
}

void deal_card(Deck *deck, Player *player)
{
    unsigned short card = pop_card(deck);
    add_to_hand(player, card);
}

void display_hands(Player *players, unsigned short player_count)
{
    char buff[55];
    for (unsigned short player = 0; player < player_count; ++player)
    {
        hand_string_repr(&players[player], buff);
        printf("Player %d's hand: %S", player + 1, buff);
    }
}