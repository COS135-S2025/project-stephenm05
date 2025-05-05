
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "card.h"

//define functions declared in header file here

//function to make a Player from the name string and a pointer to the next Player in the rotation
Player* makePlayer(char* n,Player* np) {
    //allocate space for the Player struct
    Player* p = malloc(sizeof(Player));
    //set int members to their initial values
    (p->wrongGuesses)=0;
    (p->drawCount)=0;
    (p->maxDraws)=1;
    //set the name member to the one specified
    strcpy(p->name,n);
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
    //set the name member to the one specified
    strcpy(p->name,n);
    //allocate space for the Card* array
    (p->draws)=malloc(sizeof(Card*)*(p->maxDraws));
    //return a pointer to the Player created so the user can access it
    return p;
}

//function to free a Player struct
//takes a pointer to the Player pointer you actually want to free and set to NULL
//returns a pointer to the next Player in the rotation so it can be freed as well
Player* freePlayer(Player** dp) {
    //creates a variable of the actual Player pointer for ease of use
    Player* p = *dp;
    //all the actual Card structs will be freed when the main deck is freed, so I don't need to do that here
    //this (maybe unneccessarily) sets all of the Card pointers in p->draws to NULL, and then frees p->draws and sets its root pointer to NULL
    for(int i=0;i<(p->drawCount);i++) {
        (p->draws)[i]=NULL;
    }
    free(p->draws);
    (p->draws)=NULL;
    //save p->nextPlayer to be returned so that that Player can also be freed
    Player* np = p->nextPlayer;
    (p->nextPlayer)=NULL;
    //finally, free the Player pointer and set it to NULL
    free(*dp);
    (*dp)=NULL;

    return np;
}

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
    //set the earliest unused space in p->draws equal to the provided Card pointer and increment p->drawCount
    (p->draws)[p->drawCount]=c;
    (p->drawCount)++;

    return wasExpanded;
}