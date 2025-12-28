#include "player.h"
#include "stdio.h"

Player init_player(void)
{
    Player new_player = {0, 0, -1, {}};
    return new_player;
}

void add_to_hand(Player *player, unsigned int card)
{
    player->hand[++player->hand_head] = card;
    score_hand(player);
}

void score_hand(Player *player)
{
    // count aces last
    unsigned int ace_count = 0;
    player->hand_score = 0;
    // add the cards face values to the hand score first
    for (int card = 0; card <= player->hand_head; ++card)
    {
        unsigned int card_val = (player->hand[card] % 12) + 1;
        if (card_val == 1)
            ++ace_count;
        else if (card_val > 10)
            player->hand_score += 10;
        else
            player->hand_score += card_val;
    }
    // then count aces
    for (unsigned int i = 0; i < ace_count; ++i)
    {
        if (player->hand_score <= 10)
            player->hand_score += 11;
        else
            player->hand_score += 1;
    }
}

void hand_string_repr(Player *player, char *out)
{
    out[0] = '\0';
    char buff[4];

    for (int i = 0; i <= player->hand_head; ++i)
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