#ifndef GAME_H
#define GAME_H

#include "stdio.h"
#include "player.h"
#include "deck.h"

void play_game(unsigned short players, unsigned short decks);
void play_round(Player *players, unsigned short player_count, Deck *deck);
void deal_card(Deck *deck, Player *player);
void display_hands(Player *players, unsigned short player_count, unsigned short show_dealer);
unsigned short get_player_choice(unsigned short player_number);

#endif