
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

    //close the file
    fclose(file);
    
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

        //vars to reduce the amount of member accessing and dereferencing needed
        Card* nextCard = *drawPointer;
        Card** draws = (playerPointer->draws);
        int drawCount = (playerPointer->drawCount);
        int lcr, tcbr,lowBorder, highBorder;
        if(drawCount > 0){lcr = draws[drawCount-1]->rank;} //last card's rank, only initialized if there is a last card
        if(drawCount > 1) {
            tcbr = draws[drawCount-2]->rank; //two cards back's rank, only initialized if there are two previous cards
            (lcr>tcbr) ? (highBorder=lcr, lowBorder=tcbr):(highBorder=tcbr,lowBorder=lcr); //sets high and lowBorder equal to the respective rankings of the last two drawn cards
        }


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
                printf("%s, higher (0) or lower (1)?\n",playerPointer->name);
                printf("Your last card was the ");
                printCard(draws[drawCount-1]);
                printf(".\n");
                fgets(line,MAX_LINE_LENGTH,stdin);
                if(((nextCard->rank)>=lcr && atoi(line)==0) || ((nextCard->rank)<=lcr && atoi(line)==1)) {
                    isRight=1;
                } else {
                    isRight=0; }
                break;
            //inside or outside?
            case 2:
                printf("%s, inside (0) or outside (1)?\n",playerPointer->name);
                printf("Your last two cards were the ");
                printCard(draws[drawCount-1]);
                printf(" and the ");
                printCard(draws[drawCount-2]);
                printf(".\n");
                fgets(line,MAX_LINE_LENGTH,stdin);
                if((atoi(line)==0 && (nextCard->rank)<=highBorder && (nextCard->rank)>=lowBorder) || (atoi(line)==1 && ((nextCard->rank)>=highBorder || (nextCard->rank)<=lowBorder))) {
                    isRight = 1;
                } else {
                    isRight = 0; }
                break;
            //suit?
            case 3:
                printf("%s, clubs (0), diamonds (1), spades (2), or hearts (3)?\n",playerPointer->name);
                fgets(line,MAX_LINE_LENGTH,stdin);
                if((atoi(line)+1)==(nextCard->suit)) {
                    isRight = 1;
                } else {isRight=0;}
                break;
        }

        //once the question has been asked and answered, add nextCard to the Player's draws, tell them whether they were right or wrong, and adjust their score as needed
        drawCard(playerPointer,nextCard);
        printf("*%s draws the ",playerPointer->name);printCard(nextCard);printf("*\n");
        (isRight==1) ? (printf("Congrats, you were right!\n\n")): (printf("Sorry, you were incorrect.\n\n"),(playerPointer->wrongGuesses)++);

        //prepare for the next iteration
        //if we just dealt the last player, increment qType to go to the next question, wrapping as needed
        if(playerPointer==lastPlayer) {
            qType++;
            if(qType>=4) {
                //wrapping code
                qType=0;
                //code to check if the players want to stop at the end of each group of questions
                printf("\nWould you like to keep playing (1) or stop (0)?\n");
                fgets(line,MAX_LINE_LENGTH,stdin);
                //if the players choose to stop, break the while loop condition so the game ends
                if(atoi(line)==0) {
                    drawPointer=(deck->cardOrder)+DECK_SIZE-1;
                    printf("Stopping game...\n\n");
                } else {
                    printf("Play will continue!\n\n");
                }
            }
        }
        
        //go to the next Player
        playerPointer = playerPointer->nextPlayer;

        //increment drawPointer to go to the next Card
        drawPointer++;
    }

    //write final scores to original file once the Deck is all the way cycled through
    file = fopen(argv[1],"w");
    for(int i=0;i<playerCount;i++) {
        fprintf(file,"%s: -%d\n",playerPointer->name,playerPointer->wrongGuesses);
        playerPointer = playerPointer->nextPlayer;
    }
    fclose(file);
    printf("The players' scores have been recorded in %s.\n\n", argv[1]);

    //free everything
    for(int i=0;i<playerCount;i++) {
        //frees the Player the pointer is currently looking at, then sets the pointer to the next Player
        playerPointer = freePlayer(&playerPointer);
    }
    freeDeck(&deck);

    printf("Ending the program. Thanks for playing!");

    return 0;
}