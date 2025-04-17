
#ifndef DECK_H
#define DECK_H

typedef struct Deck{
    struct Card* cardOrder[52];
    int timesShuffled;
} Deck;

#endif

