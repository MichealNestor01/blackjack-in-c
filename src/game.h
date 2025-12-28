#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "deck.h"

void play_game(unsigned int players, unsigned int decks);
void play_round(Player *players, unsigned int player_count, Deck *deck);
void deal_card(Deck *deck, Player *player);

#endif