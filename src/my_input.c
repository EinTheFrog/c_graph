#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "mylib_graph.h"
#include "CuTest.h"

void translateToGraph( char* pathIn, char* pathOut ) {
    FILE *fp;
    char* rawData;
    int c, i, v, j;

    fp = fopen(pathIn, "r");

    c = fgetc(fp);
    i = 0;
    rawData = fromFileToString(fp);
    fclose(fp);

    i = 1; // т.к. 1-ая скобка внешняя и не считается
    v = 0; 
    //все string кончаются на 0 ('\0')
    while (rawData[i] != 0) {
        if (rawData[i] == '{') {
            v++;
        }
        i++;
    }
    struct Graph* graph = createGraph(v);

    i = 1;
    j = 0;
    int src, dest; 
    //все string кончаются на 0 ('\0')
    while (rawData[i] != 0) {
        if (rawData[i] == '{') {
            src = j;
            while (rawData[i] != '}') {
                if (isdigit(rawData[i])) {
                    dest = 0;
                    while (isdigit(rawData[i])) {
                        dest = dest * 10 + (rawData[i] - '0');
                        i++;
                    }
                    createEdge(graph, src, dest);                    
                } else {
                    i++;
                }
            }
            j++;
        }
        i++;
    }

    printGraph(graph, pathOut);
}