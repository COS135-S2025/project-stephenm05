
#ifndef PLAYER_H
#define PLAYER_H

#define MAX_LINE_LENGTH 200

typedef struct Player Player;

struct Player{
    char name[MAX_LINE_LENGTH];
    struct Card* cards;
    int wrongGuesses;
    Player* nextPlayer;
};

#endif

