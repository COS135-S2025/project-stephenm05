/*
The main file that will execute the code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

/*
String parser and file reader, do not touch
*/
//reads a file and returns a pointer to it
FILE* readFile(char *filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    return file;
}

int main(int argc, char** argv){
    if (argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = read_file(argv[1]);
    

    //close the file
    fclose(file);

    return 0;
}