#include <stdlib.h>
#include <stdio.h>
#include "..\include\CuTest.h"

#define STRING_INTIAL_SIZE 256

struct Node {
    int vertex;
    struct Node* next;
};

struct AdjList {
    struct Node* head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct Node* createNode( int vertex ) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;

    return newNode;
};

struct Graph* createGraph( int V ) {
    struct Graph* newGraph = (struct Graph*) malloc(sizeof(struct Graph));
    newGraph->V = V;

    newGraph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList*));

    int i;
    for (i = 0; i < V; i++) {
        newGraph->array[i].head = NULL;
    }

    return newGraph;
};

void createEdge( struct Graph* graph, int src, int dest ) {
    //проверяем наличие такого ребра
    struct Node* pCrawl = graph->array[src].head;
    while ( pCrawl ) {
        if ( pCrawl->vertex == dest ) return;
        pCrawl = pCrawl->next;
    }

    //добавляем новый узел в начало списка смежности
    struct Node* destNode = createNode(dest);
    destNode->next = graph->array[src].head;
    graph->array[src].head = destNode;

    struct Node* srcNode = createNode(src);
    srcNode->next = graph->array[dest].head;
    graph->array[dest].head = srcNode;
}

void printGraph( struct Graph* graph, char* path ) {
    FILE* fp = fopen(path, "w");

    int i;
    for (i = 0; i < graph->V; i++) {
        struct Node* pCrawl = graph->array[i].head;
        fprintf(fp, "\n Adjacency list of vertex %d\n head", i);
        while ( pCrawl ) {
            fprintf(fp, "-> %d", pCrawl->vertex);
            pCrawl = pCrawl->next;
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

char* fromFileToString( FILE* fp ) {
    int strSize = STRING_INTIAL_SIZE;
    char* string = (char*) malloc(strSize * sizeof(char));
    int i = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        string[i] = c;
        i++;
        if ( i == strSize ) {
            strSize = strSize * 2;
            string = realloc(string, strSize);
        }
    }
    return string;
}

void testPrintGraph_Basic( CuTest *tc ) {
    struct Graph* graph = createGraph(3);
    createEdge(graph, 0, 1);
    createEdge(graph, 0, 2);
    createEdge(graph, 1, 2);

    char* path = "actualOutput.txt";
    printGraph(graph, path);

    FILE* actualFile = fopen(path, "r");
    char* actualOutput = fromFileToString(actualFile);
    fclose(actualFile);
    remove(path);

    path = "../test_resources/print_test_basic.txt";
    FILE* expectedFile = fopen(path, "r");
    char* expectedOutput = fromFileToString(expectedFile);
    fclose(expectedFile);

    CuAssertStrEquals(tc, expectedOutput, actualOutput);
}

void testPrintGraph_Reversed( CuTest *tc ) {
    struct Graph* graph = createGraph(3);
    createEdge(graph, 1, 0);
    createEdge(graph, 2, 0);
    createEdge(graph, 2, 1);

    char* path = "actualOutput1.txt";
    printGraph(graph, path);

    FILE* actualFile = fopen(path, "r");
    char* actualOutput = fromFileToString(actualFile);
    fclose(actualFile);
    remove(path);

    path = "../test_resources/print_test_reversed.txt";
    FILE* expectedFile = fopen(path, "r");
    char* expectedOutput = fromFileToString(expectedFile);
    fclose(expectedFile);

    CuAssertStrEquals(tc, expectedOutput, actualOutput);
}

void testPrintGraph_Large( CuTest *tc ) {
    struct Graph* graph = createGraph(20);
    createEdge(graph, 0, 19);
    createEdge(graph, 0, 1);
    createEdge(graph, 2, 10);
    createEdge(graph, 15, 16);

    char* path = "actualOutput2.txt";
    printGraph(graph, path);

    FILE* actualFile = fopen(path, "r");
    char* actualOutput = fromFileToString(actualFile);
    fclose(actualFile);
    remove(path);

    path = "../test_resources/print_test_large.txt";
    FILE* expectedFile = fopen(path, "r");
    char* expectedOutput = fromFileToString(expectedFile);
    fclose(expectedFile);

    CuAssertStrEquals(tc, expectedOutput, actualOutput);
}

CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testPrintGraph_Basic);
    SUITE_ADD_TEST(suite, testPrintGraph_Reversed);
    SUITE_ADD_TEST(suite, testPrintGraph_Large);
    return suite;
}