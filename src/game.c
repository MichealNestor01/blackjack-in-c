#include "game.h"

void play_game(unsigned short player_count, unsigned short deck_count)
{
    printf("== Starting Game ==\n");
    printf("Number of players: %d\n", player_count);
    printf("Number of decks shuffled in: %d\n", deck_count);
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
    printf("== Dealing Cards ==\n");
    for (unsigned short card = 0; card < 2; ++card)
    {
        for (unsigned short player_index = 0; player_index < player_count; ++player_index)
            deal_card(deck, &players[player_index]);
        deal_card(deck, &players[8]); // dealer
        display_hands(players, player_count, 1);
    }

    // peak for dealer blackjack if possible
    unsigned short dealer_first_card_val = players[8].hand[0] % 13;
    if (dealer_first_card_val == 0 || dealer_first_card_val > 9)
    {
        printf("== Peaking at the dealer's hand ==\n");
        if (players[8].hand_score == 21)
        {
            printf("The dealer has blackjack, round over\n");
            for (unsigned short player_index = 0; player_index < player_count; ++player_index)
                udpdate_score(&players[player_index], 21);
            return;
        }
        printf("The dealer does not have blackjack\n");
    }

    // continue to the players turns
    printf("== Player turns ==\n");
    for (unsigned short player_index = 0; player_index < player_count; ++player_index)
    {
        deal_card(deck, &players[player_index]);
    }
}

void deal_card(Deck *deck, Player *player)
{
    unsigned short card = pop_card(deck);
    add_to_hand(player, card);
}

void display_hands(Player *players, unsigned short player_count, unsigned short dealer_cards_to_show)
{
    char buff[55];
    for (unsigned short player = 0; player < player_count; ++player)
    {
        hand_string_repr(&players[player], buff);
        printf("Player %d's hand: %s (%hu)\n", player + 1, buff, players[player].hand_score);
    }
    hand_string_repr_only_n_shown(&players[8], buff, dealer_cards_to_show);
    if (dealer_cards_to_show == 1 && players[8].hand_head != 0)
        printf("Dealer's hand: %s (?)\n", buff);
    else
        printf("Dealer's hand: %s (%hu)\n", buff, players[8].hand_score);
}

unsigned short get_player_choice(unsigned short player_number)
{
    printf("Player %hu, please select your move:\n", player_number);
    printf("\t(1) Hit\n");
    printf("\t(2) Stick\n");
    // printf("\t(3) Double down\n");
    // printf("\t(4) Split\n");
    // printf("\t(5) Surrender\n");
    unsigned short choice = 0;
    while (1)
    {
        printf("What is your your choice?: ");

        if (scanf("%hu", &choice) != 1)
        {
            // Consume invalid input
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("Invalid input, please enter a number between 1 and 2.\n");
            continue;
        }

        if (1 <= choice && choice <= 2)
            return choice;
        printf("Invalid input, please enter a number between 1 and 2.\n");
    }
}