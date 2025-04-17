
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "card.h"

//define functions declared in header file here

//function to make a Player
Player* makePlayer(char* n,Player* np) {
    //allocate space for the Player struct
    Player* p = malloc(sizeof(Player));
    //set int members to their initial values
    (p->wrongGuesses)=0;
    (p->drawCount)=0;
    (p->maxDraws)=1;
    //indicate the address of the Player who goes next
    (p->nextPlayer)=np;
    //allocate space for the Card* array
    (p->draws)=malloc(sizeof(Card*)*(p->maxDraws));
    //return a pointer to the Player created so the user can access it
    return p;
}

//function to make the first Player struct (since for the first one we won't have a Player* argument to put in)
Player* makeFirstPlayer(char* n) {
    //allocate space for the Player struct
    Player* p = malloc(sizeof(Player));
    //set int members to their initial values
    (p->wrongGuesses)=0;
    (p->drawCount)=0;
    (p->maxDraws)=1;
    //allocate space for the Card* array
    (p->draws)=malloc(sizeof(Card*)*(p->maxDraws));
    //return a pointer to the Player created so the user can access it
    return p;
}

//function to free a Player struct
//takes a pointer to the Player pointer you actually want to free and set to NULL
void freePlayer(Player** p);

//function to add the Card pointed to by c to p->draws, expanding the latter as needed
//returns 0 if no expansion was needed and 1 otherwise
int drawCard(Player* p,Card* c) {
    int wasExpanded=0;
    //expand p->draws if needed
    if((p->drawCount)>=(p->maxDraws)) {
        (p->maxDraws)++;
        (p->draws)=realloc((p->draws),sizeof(Card*)*(p->maxDraws));
        wasExpanded=1;
    }
    //set the earliest unused space in p->draws equal to the provided Card pointer
    (p->draws)[p->drawCount]=c;
    return wasExpanded;
}