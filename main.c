
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "card.h"
#include "player.h"
#include "deck.h"


//reads a file and returns a pointer to it
FILE* readFile(char *filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("ERROR: Specified file does not exist\n");
        exit(1);
    }
    return file;
}

//function to remove trailing whitespaces from the provided string
void trimSpaces(char* word) {
    //char pointer looking at the char in word immediately preceeding the null terminator
    char* end = word+(strlen(word)-1);
    //keep moving end back until it's on a non-space char
    while(isspace(*end)) {
        end--;
    }
    //then terminate word on the char after end
    *(end+1)='\0';

    //this while loop is essentially the same as above but reversed
    char* start=word;
    while(isspace(*start)) {
        start++;
    }
    //and instead of ending the word, once we find where the actual chars start we just copy the string starting there into word
    strcpy(word,start);
    return;
}

int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = readFile(argv[1]);

    //create Player structs based on input file
    //buffer to store lines from input file
    char line[MAX_LINE_LENGTH];
    //set line to the first line in the input file, terminating the program if there is no first line bc then we can't make the Player structs we need
    if(fgets(line,MAX_LINE_LENGTH,file)==NULL) {
        printf("ERROR: The specified file is empty");
        return 2;
    }
    trimSpaces(line);
    //create the first Player and record it's pointer. the first Player we create will be the last to go for coding simplicity
    Player* lastPlayer = makeFirstPlayer(line);
    Player* playerPointer=lastPlayer;
    int playerCount=1;
    //once we have our first Player we can loop through the rest using the regular makePlayer() function to get most of them linked together
    while(fgets(line,MAX_LINE_LENGTH,file)!=NULL) {
        trimSpaces(line);
        //creates a new Player struct from the current name who will play before the last Player we created
        playerPointer = makePlayer(line,playerPointer);
        playerCount++;
    }
    //this loop concludes with playerPointer pointing to the Player who will go first
    //update lastPlayer->nextPlayer so the first Player goes after lastPlayer for a complete turn loop
    (lastPlayer->nextPlayer)=playerPointer;
    
    printf("Order of play is as follows:\n");
    for(int i=1;i<=playerCount;i++) {
        printf("%d. %s\n",i,(playerPointer->name));
        playerPointer = (playerPointer->nextPlayer);
    }
    

    //create and shuffle a Deck
    Deck* deck = makeDeck();
    shuffleDeck(deck);
    printf("\n*shuffling noises*\n\n");

    printf("To play this game, guess the answer to the question asked about your next card, inputting your answer using the number specified.\n\n");

    //main gameloop iterates through Players and then questions
    //set up pointer to iterate through the deck
    Card** drawPointer = (deck->cardOrder);
    //vars tracking which question to ask and if the player was right
    int qType = 0;
    int isRight = 0;
    //runs while there are undrawn cards in the deck
    while(drawPointer<((deck->cardOrder)+DECK_SIZE)) {
        //ask the appropriate question to the Player pointed to by playerPointer
        switch(qType) {
            //red or black?
            case 0:
                printf("%s, red (0) or black (1)?\n",(playerPointer->name));
                fgets(line,MAX_LINE_LENGTH,stdin);
                //suit % 2 is 0 if the suit is red or 1 if it's black
                if(atoi(line)==((nextCard->suit)%2)) {
                    isRight=1;
                } else {
                    isRight=0; }
                break;
            //higher or lower?
            case 1:
                break;
            //inside or outside?
            case 2:
                break;
            //suit?
            case 3:
                break;
        }
    }

    //write final scores to original file once the Deck is all the way cycled through
    

    //close the file
    fclose(file);

    return 0;
}