#include "player.h"

Player init_player(void)
{
    Player new_player = {0, 0, -1, {}};
    return new_player;
}

void add_to_hand(Player *player, unsigned short card)
{
    player->hand[++player->hand_head] = card;
    score_hand(player);
}

void score_hand(Player *player)
{
    // count aces last
    unsigned short ace_count = 0;
    player->hand_score = 0;
    // add the cards face values to the hand score first
    for (int card = 0; card <= player->hand_head; ++card)
    {
        unsigned short card_val = (player->hand[card] % 13) + 1;
        if (card_val == 1)
            ++ace_count;
        else if (card_val > 10)
            player->hand_score += 10;
        else
            player->hand_score += card_val;
    }
    // then count aces
    for (unsigned short i = 0; i < ace_count; ++i)
    {
        if (player->hand_score <= 10)
            player->hand_score += 11;
        else
            player->hand_score += 1;
    }
}

void score_player(Player *player, Player *dealer)
{
    // score the player -1 if worse than dealer, 0 if match the dealer, 1 if better
    // first check if they player is bust, loose no matter wat
    if (player->hand_score > 21)
    {
        player->score -= 1;
        player->hand_head = -1;
        return;
    }

    // deal with blackjacks
    unsigned short player_has_blackjack = player->hand_score == 21 && player->hand_head == 1;
    unsigned short dealer_has_blackjack = dealer->hand_score == 21 && dealer->hand_head == 1;

    if (player_has_blackjack && !dealer_has_blackjack)
        player->score += 1;
    else if (dealer_has_blackjack && !player_has_blackjack)
        player->score -= 1;
    else if (!player_has_blackjack && !dealer_has_blackjack)
    {
        if (player->hand_score > dealer->hand_score)
            player->score += 1;
        else if (player->hand_score < dealer->hand_score)
            player->score -= 1;
    }
    player->hand_head = -1;
}

void hand_string_repr(Player *player, char *out)
{
    out[0] = '\0';
    char buff[4];

    for (short i = 0; i <= player->hand_head; ++i)
    {
        card_string_repr(player->hand[i], buff);
        if (i)
        { // add a space between cards
            size_t len = strlen(out);
            out[len] = ' ';
            out[len + 1] = '\0';
        }
        strncat(out, buff, 3);
    }
}

void hand_string_repr_only_n_shown(Player *player, char *out, unsigned short cards_to_show)
{
    out[0] = '\0';
    char buff[4];

    for (short i = 0; i <= player->hand_head; ++i)
    {
        if (i < cards_to_show)
            card_string_repr(player->hand[i], buff);
        else if (i == cards_to_show)
        {
            buff[0] = '?';
            buff[1] = '\0';
        }
        if (i)
        { // add a space between cards
            size_t len = strlen(out);
            out[len] = ' ';
            out[len + 1] = '\0';
        }
        strncat(out, buff, 3);
    }
}