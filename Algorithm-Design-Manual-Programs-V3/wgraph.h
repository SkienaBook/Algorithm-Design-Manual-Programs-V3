/*    wgraph.h

    Header file for pointer-less weighted graph type from Skiena-Revilla
*/

/* Copyright 2003-2020 by Steven S. Skiena; all rights reserved.
Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

These programs appear in my books:

"The Algorithm Design Manual" by Steven Skiena, second edition, Springer,
London 2008.  See out website www.algorist.com for additional information
or https://www.amazon.com/exec/obidos/ASIN/1848000693/thealgorith01-20

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.
See our website www.programming-challenges.com for additional information,
or https://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/
*/




#define MAXV         100   /* maximum number of vertices */
#define MAXDEGREE    50    /* maximum outdegree of a vertex */

typedef struct {
    int v;         /* neighboring vertex */
    int weight;    /* edge weight */
} edge;

typedef struct {
    edge edges[MAXV+1][MAXDEGREE];    /* adjacency info */
    int degree[MAXV+1];               /* outdegree of each vertex */
    int nvertices;                    /* number of vertices in the graph */
    int nedges;                       /* number of edges in the graph */
    int directed;                     /* is the graph directed? */
} graph;
