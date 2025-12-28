#include "stdio.h"
#include "stdlib.h"
#include "deck.h"
#include "time.h"
#include "game.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("USAGE: %s players decks\n", argv[0]);
        exit(0);
    }

    int players = atoi(argv[1]);
    if (players < 1 || players > 10)
    {
        printf("USAGE: must select between 1 and 10 players\n");
        exit(0);
    }

    int decks = atoi(argv[2]);
    if (decks < 1 || decks > 8)
    {
        printf("USAGE: must select between 1 and 8 decks to play with\n");
        exit(0);
    }

    char yes_or_no[2];
    while (1)
    {
        play_game(players, decks);

        // clear stdin
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        // check if the user wants to play again
        printf("Play another game with the same configuration? (Y/N): ");
        fgets(yes_or_no, sizeof(yes_or_no), stdin);
        if (!(yes_or_no[0] == 'Y' || yes_or_no[0] == 'y'))
        {
            printf("Closing program\n");
            return 0;
        }
    }

    return 0;
}