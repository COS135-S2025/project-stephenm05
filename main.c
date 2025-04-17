
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
        printf("Error opening file\n");
        exit(1);
    }
    return file;
}

//function to remove trailing whitespaces from the provided string
void trimTrailingSpaces(char* word) {
    //char pointer looking at the char in word immediately preceeding the null terminator
    char* end = word+(strlen(word)-1);
    //while the last regular char in word is a space
    while(isspace(*end)) {
        //set the last char to be the new end of the word
        *end='\0';
        //and move end so it is again looking at the last char in word
        end--;
    }
    return;
}

int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = read_file(argv[1]);

    //create Player structs based on input file
    char line[MAX_LINE_LENGTH];

    //create and shuffle a Deck

    //main gameloop iterates through Players and then questions

    //write final scores to original file once the Deck is all the way cycled through
    

    //close the file
    fclose(file);

    return 0;
}