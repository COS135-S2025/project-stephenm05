
#ifndef PLAYER_H
#define PLAYER_H

#define MAX_LINE_LENGTH 200

typedef struct Player Player;

struct Player{
    char name[MAX_LINE_LENGTH];
    //pointer to an array of Card pointers
    struct Card** draws;
    int wrongGuesses;
    Player* nextPlayer;
    int drawCount;
    int maxDraws;
};

//function to make a Player
Player* makePlayer(char* n,Player* np);

//function to make the first Player struct (since for the first one we won't have a Player* argument to put in)
Player* makeFirstPlayer(char* n);

//function to free a Player struct
//takes a pointer to the Player pointer you actually want to free and set to NULL
Player* freePlayer(Player** p);

//function to add the Card pointed to by c to p->draws, expanding the latter as needed
int drawCard(Player* p,struct Card* c);

#endif

