
#ifndef DECK_H
#define DECK_H

#define DECK_SIZE 52

typedef struct Deck{
    struct Card* cardOrder[DECK_SIZE];
    int timesShuffled;
} Deck;

//function to create a Deck struct
Deck* makeDeck();

//function to free the Deck struct and all its associated Card structs
void freeDeck(Deck** p);

//function to shuffle the Deck
void shuffleDeck(Deck* d);

//function to print the Deck, mostly for debugging
void printDeck(Deck* d);

#endif

