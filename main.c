#include <stdlib.h>
#include <stdio.h>

extern void translateToGraph ( char* pathIn, char* pathOut );

int main ( int argc, char *args[] ) {
    char path[100];

     if (argc != 3) {
        printf("IllegalArgumentException. InputFileName OutputFileName");
        exit(EXIT_FAILURE);
    }

    translateToGraph(args[1], args[2]);
    exit(EXIT_SUCCESS);
}