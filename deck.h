
#ifndef DECK_H
#define DECK_H

typedef struct Deck{
    struct Card* cardOrder[52];
    int timesShuffled;
} Deck;

//function to create a Deck struct
Deck* makeDeck();

//function to free the Deck struct and all its associated Card structs
void freeDeck(Deck** p);

//function to shuffle the Deck
void shuffleDeck(Deck* d);

#endif

