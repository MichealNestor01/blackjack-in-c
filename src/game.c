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
    Player *dealer = &players[8];

    // deal initial two cards
    printf("== Dealing Cards ==\n");
    for (unsigned short card = 0; card < 2; ++card)
    {
        for (unsigned short player_index = 0; player_index < player_count; ++player_index)
            deal_card(deck, &players[player_index]);
        deal_card(deck, dealer); // dealer
        display_hands(players, player_count, 1);
    }

    // peak for dealer blackjack if possible
    unsigned short dealer_first_card_val = dealer->hand[0] % 13;
    if (dealer_first_card_val == 0 || dealer_first_card_val > 9)
    {
        printf("== Peaking at the dealer's hand ==\n");
        if (dealer->hand_score == 21)
        {
            printf("The dealer has blackjack, round over\n");
            for (unsigned short player_index = 0; player_index < player_count; ++player_index)
                score_player(&players[player_index], dealer);
            dealer->hand_head = -1;
            return;
        }
        printf("The dealer does not have blackjack\n");
    }

    // continue to the players turns
    printf("== Player Turns ==\n");
    unsigned short player_not_bust = 0;
    char buff[55];
    for (unsigned short player_index = 0; player_index < player_count; ++player_index)
    {
        unsigned short player_number = player_index + 1;
        Player *player = &players[player_index];
        hand_string_repr(player, buff);
        printf("Player %hu turn! Current hand: %s (%hu).\n", player_number, buff, player->hand_score);
        while (1) // turn loop
        {
            // check for blackjack
            if (player->hand_score == 21)
            {
                if (player->hand_head == 1)
                    printf("Player %hu has blackjack, turn complete.\n", player_number);
                else
                    printf("Player %hu has 21, turn complete.\n", player_number);
                player_not_bust = 1;
                break;
            }

            // get the user's choice
            unsigned short choice = get_player_choice(player_number);
            if (choice == 1)
            {
                deal_card(deck, player);
                hand_string_repr(player, buff);
                printf("!HIT! Updated hand: %s (%hu)\n", buff, player->hand_score);
            }
            else if (choice == 2)
            {
                printf("!STICK! Final hand: %s (%hu)\n", buff, player->hand_score);
                player_not_bust = 1;
                break;
            }

            // bust check
            if (player->hand_score > 21)
            {
                printf("!BUST! Player %hu's turn is over.\n", player_number);
                break;
            }
        }
        deal_card(deck, player);
    }

    // check if all players are bust
    if (!player_not_bust)
    {
        printf("All players are BUST, round complete! All players loose 1 point\n");
        for (unsigned short player_index = 0; player_index < player_count; ++player_index)
            score_player(&players[player_index], dealer);
        return;
    }

    // dealers turn
    printf("== Dealer's Turn ==\n");
    while (1)
    {
        hand_string_repr(dealer, buff);
        printf("Dealer's hand: %s (%hu)\n", buff, dealer->hand_score);
        if (dealer->hand_score > 16)
        {
            printf("!STAND! The dealer's turn is complete\n");
            break;
        }
        else if (dealer->hand_score > 21)
        {
            printf("!BUST! The dealer's turn is complete\n");
            break;
        }
        printf("!HIT! Dealing the dealer another card\n");
        deal_card(deck, dealer);
    }

    // scores at the doors
    printf("== Round Overview ==\n");
    for (unsigned short player_index = 0; player_index < player_count; ++player_index)
    {
        hand_string_repr(&players[player_index], buff);
        score_player(&players[player_index]); // will clear the hand
        printf("Player %hu's hand: %s (%hu)\n", player_index + 1, buff, players[player_index].hand_score);
    }
    hand_string_repr(dealer, buff);
    dealer->hand_head = -1; // clear the dealer's hand
    printf("Dealer's hand: %s (%hu)\n", buff, dealer->hand_score);
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