#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player
{
    unsigned int score;
    unsigned int hand_score;
    int hand_head;
    unsigned int hand[11];
} Player;

Player init_player(void);
void add_to_hand(Player *player, unsigned int card);
void score_hand(Player *player);
void hand_string_repr(Player *player, char *out);

#endif