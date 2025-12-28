#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player
{
    unsigned int score;
    unsigned int hand_score;
    unsigned int hand_head;
    unsigned int hand[11];
} Player;

Player init_player();
void add_to_hand(Player *player, unsigned int card);
void score_hand(Player *player);

#endif