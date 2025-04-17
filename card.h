
#ifndef CARD_H
#define CARD_H

//enum to store the numerical value of the 13 possible card ranks
typedef enum Rank{
    ACE=1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
} Rank;

typedef struct Card{
    char name[10];
    char suit[10];
    Rank rank;
} Card;

#endif

