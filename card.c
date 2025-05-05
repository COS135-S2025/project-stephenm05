
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

//define functions declared in header file here

//function to create a Card struct and return its pointer, with s and r representing the suit and rank
Card* makeCard(int s,int r) {
    //reserve space for the Card struct
    Card* c = malloc(sizeof(Card));
    //assign the basic int members
    (c->suit)=s;
    (c->rank)=r;
    //switch statements to set c->name to the appropriate text to describe the card on the form "RANK of SUIT"
    switch(r) {
        case 1:
            strcpy(c->name,"Ace");
            break;
        case 2:
            strcpy(c->name,"Two");
            break;
        case 3:
            strcpy(c->name,"Three");
            break;
        case 4:
            strcpy(c->name,"Four");
            break;
        case 5:
            strcpy(c->name,"Five");
            break;
        case 6:
            strcpy(c->name,"Six");
            break;
        case 7:
            strcpy(c->name,"Seven");
            break;
        case 8:
            strcpy(c->name,"Eight");
            break;
        case 9:
            strcpy(c->name,"Nine");
            break;
        case 10:
            strcpy(c->name,"Ten");
            break;
        case 11:
            strcpy(c->name,"Jack");
            break;
        case 12:
            strcpy(c->name,"Queen");
            break;
        case 13:
            strcpy(c->name,"King");
            break;
    }
    strcat(c->name," of ");
    switch(s) {
        case 1:
            strcat(c->name,"Clubs");
            break;
        case 2:
            strcat(c->name,"Diamonds");
            break;
        case 3:
            strcat(c->name,"Spades");
            break;
        case 4:
            strcat(c->name,"Hearts");
            break;
    }
    //return c so the user can access the Card created
    return c;
}

//function to free a Card struct
//takes a pointer to the Card pointer you actually want to free and set to NULL
void freeCard(Card** p) {
    free(*p);
    (*p)=NULL;
    return;
}

//function to print a card's name in blue if it's spades or clubs and red if it's hearts or diamonds
void printCard(Card* c) {
    if((c->suit)%2==0) {
        printf(C_RED "%s" C_RESET,c->name);
    } else {
        printf(C_BLUE "%s" C_RESET,c->name);
    }
    return;
}
