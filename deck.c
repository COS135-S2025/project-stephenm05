
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"
#include "card.h"

//define functions declared in header file here

//function to create a Deck struct
Deck* makeDeck() {
    //allocate space for the Deck struct
    Deck* d = malloc(sizeof(Deck));
    //set simple initial member values
    (d->timesShuffled)=0;
    //create a full deck's worth of Card structs and add their pointers to d->cardOrder
    //outer loop goes through the suits and inner loop goes through the ranks, so the starting order is all clubs, then all diamonds, all spades, and all hearts in ascending order
    int index=0;
    for(int s=1;s<=4;s++) {
        for(int r=1;r<=13;r++) {
            (d->cardOrder)[index]=makeCard(s,r);
            index++;
        }
    }
    //return a pointer to the Deck created so the user can interact with it
    return d;
}

//function to free the Deck struct and all its associated Card structs
void freeDeck(Deck** p) {
    //create a variable for the actual Deck pointer for ease of use
    Deck* d = *p;
    //iterate through d->cardOrder and free all of the Card structs referenced
    for(int i=0;i<DECK_SIZE;i++) {
        freeCard(&((d->cardOrder)[i]));
    }
    //free the Deck pointer itself and set it to NULL
    free(*p);
    (*p)=NULL;

    return;
}

//function to shuffle the Deck
void shuffleDeck(Deck* d);