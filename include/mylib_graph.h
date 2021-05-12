// mylib_graph.h

#ifndef MYLIB_TRANS_H_
#define MYLIB_TRANS_H_

struct Node;
struct AdjList;
struct Graph;

// Функции библиотеки mylib_graph
extern struct Node* createNode( int vertex );
extern struct Graph* createGraph( int V );
extern void createEdge( struct Graph* graph, int src, int dest );
extern void printGraph( struct Graph* graph, char* path );
extern void translateToGraph( char* pathIn, char* pathOut );
extern char* fromFileToString( FILE* fp );

#endif  // MYLIB_TRANS_H_