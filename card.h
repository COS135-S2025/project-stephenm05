
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

//enum representing the possible suits as numerical values
typedef enum Suit{
    CLUBS=1,
    DIAMONDS,
    SPADES,
    HEARTS
} Suit;

typedef struct Card{
    char name[20];
    Suit suit;
    Rank rank;
} Card;

//function to create a Card struct
Card* makeCard(int s,int r);

//function to free a Card struct
void freeCard(Card** p);

//function to print a card
void printCard(Card* c);

#endif

