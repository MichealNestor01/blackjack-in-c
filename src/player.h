#ifndef PLAYER_H
#define PLAYER_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "deck.h"

typedef struct Player
{
    short score;
    unsigned short hand_score;
    short hand_head;
    unsigned short hand[11];
} Player;

Player init_player(void);
void add_to_hand(Player *player, unsigned short card);
void score_hand(Player *player);
void score_player(Player *player, Player *dealer);
void hand_string_repr(Player *player, char *out);
void hand_string_repr_only_n_shown(Player *player, char *out, unsigned short cards_to_show);

#endif