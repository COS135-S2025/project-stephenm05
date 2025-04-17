
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card.h"

//define functions declared in header file here

//function to create a Card struct
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
void freeCard(Card** p);

//function to print a card
void printCard(Card* c);