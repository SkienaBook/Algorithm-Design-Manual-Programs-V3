/*	netflow.c

	Network flow implementation -- Ford-Fulkerson augmenting path algorithm.

	by: Steven Skiena
	begun: September 19, 2002

	This algorithm requires its own special graph type, to allow for
	flows and residual flow fields.
*/

/*
Copyright 2003 by Steven S. Skiena; all rights reserved. 

Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.

This book can be ordered from Amazon.com at

http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/

*/


#include "bool.h"
#include "queue.h"
#include <stdio.h>
#include "geometry.h"


#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */


typedef struct {
	int v;				/* neighboring vertex */
	int capacity;			/* capacity of edge */
	int flow;			/* flow through edge */
	int residual;			/* residual capacity of edge */
} edge;

typedef struct {
	edge edges[MAXV][MAXDEGREE];	/* adjacency info */
	int degree[MAXV];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} flow_graph;



main()
{
	flow_graph g;			/* graph to analyze */
	int source, sink;		/* source and sink vertices */
	int flow;			/* total flow */
	int i;				/* counter */

	scanf("%d %d",&source,&sink);
	read_flow_graph(&g,TRUE);

	netflow(&g,source,sink);

	print_flow_graph(&g);

	flow = 0;
	for (i=0; i<g.nvertices; i++)
		flow += g.edges[source][i].flow;

	printf("total flow = %d\n",flow);
}



initialize_graph(g)
flow_graph *g;				/* graph to initialize */
{
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;

	for (i=0; i<MAXV; i++) g->degree[i] = 0;
}

read_flow_graph(g,directed)
flow_graph *g;				/* graph to initialize */
bool directed;				/* is this graph directed? */
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x,y,w;			/* placeholder for edge and weight */

	initialize_graph(g);

	scanf("%d %d\n",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d %d\n",&x,&y,&w);
		insert_flow_edge(g,x,y,directed,w);
	}
}

insert_flow_edge(flow_graph *g, int x, int y, bool directed, int w)
{
	if (g->degree[x] > MAXDEGREE)
		printf("Warning: insertion(%d,%d) exceeds degree bound\n",x,y);

	g->edges[x][g->degree[x]].v = y;
	g->edges[x][g->degree[x]].capacity = w;
	g->edges[x][g->degree[x]].flow = 0;
	g->edges[x][g->degree[x]].residual = w;
	g->degree[x] ++;

	if (directed == FALSE)
		insert_flow_edge(g,y,x,TRUE,w);
	else
		g->nedges ++;
}


edge *find_edge(flow_graph *g, int x, int y)
{
	int i;				/* counter */

	for (i=0; i<g->degree[x]; i++) 
		if (g->edges[x][i].v == y) 
			return( &g->edges[x][i] );

	return(NULL);
}


add_residual_edges(flow_graph *g)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) 
		for (j=0; j<g->degree[i]; j++)
			if (find_edge(g,g->edges[i][j].v,i) == NULL)
				insert_flow_edge(g,g->edges[i][j].v,i,TRUE,0);
}


print_flow_graph(flow_graph *g)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		for (j=0; j<g->degree[i]; j++)
			printf(" %d(%d,%d,%d)",g->edges[i][j].v,
				g->edges[i][j].capacity,
				g->edges[i][j].flow,
				g->edges[i][j].residual);
		printf("\n");
	}
}

bool processed[MAXV];		/* which vertices have been processed */
bool discovered[MAXV];          /* which vertices have been found */
int parent[MAXV];		/* discovery relation */

bool finished = FALSE;          /* if true, cut off search immediately */


initialize_search(g)
flow_graph *g;				/* graph to traverse */
{
        int i;                          /* counter */

        for (i=1; i<=g->nvertices; i++) {
                processed[i] = FALSE;
                discovered[i] = FALSE;
                parent[i] = -1;
        }
}


bfs(flow_graph *g, int start)
{
	queue q;			/* queue of vertices to visit */
	int v;				/* current vertex */
	int i;				/* counter */

	init_queue(&q);
	enqueue(&q,start);
	discovered[start] = TRUE;

	while (empty(&q) == FALSE) {
		v = dequeue(&q);
		process_vertex_early(v);
		processed[v] = TRUE;
		for (i=0; i<g->degree[v]; i++) 
		    if (valid_edge(g->edges[v][i]) == TRUE) {
			if (discovered[g->edges[v][i].v] == FALSE) {
				enqueue(&q,g->edges[v][i].v);
				discovered[g->edges[v][i].v] = TRUE;
				parent[g->edges[v][i].v] = v;
			}
			if (processed[g->edges[v][i].v] == FALSE) 
				process_edge(v,g->edges[v][i].v);
		    }
		process_vertex_late(v);
	}
}


bool valid_edge(edge e)
{
	if (e.residual > 0) return (TRUE);
	else return(FALSE);
}

process_vertex_early(v)
int v;					/* vertex to process */
{
}

process_vertex_late(v)
int v;                                  /* vertex to process */
{
}

process_edge(x,y)
int x,y;                                /* edge to process */
{
}




find_path(start,end,parents)
int start;				/* first vertex on path */
int end;				/* last vertex on path */
int parents[];				/* array of parent pointers */
{
	if ((start == end) || (end == -1))
		printf("\n%d",start);
	else {
		find_path(start,parents[end],parents);
		printf(" %d",end);
	}
}

int path_volume(flow_graph *g, int start, int end, int parents[])
{
	edge *e;			/* edge in question */
	edge *find_edge();

	if (parents[end] == -1) return(0);

	e = find_edge(g,parents[end],end);

	if (start == parents[end])
		return(e->residual);
	else
		return( min(path_volume(g,start,parents[end],parents), e->residual) );
}


augment_path(flow_graph *g, int start, int end, int parents[], int volume)
{
	edge *e;			/* edge in question */
	edge *find_edge();

	if (start == end) return;

	e = find_edge(g,parents[end],end);
	e->flow += volume;
	e->residual -= volume;
	
	e = find_edge(g,end,parents[end]);
	e->residual += volume;

	augment_path(g,start,parents[end],parents,volume);
}


netflow(flow_graph *g, int source, int sink)
{
	int volume;			/* weight of the augmenting path */

	add_residual_edges(g);

	initialize_search(g);
	bfs(g,source);

	volume = path_volume(g, source, sink, parent);

	while (volume > 0) {
		augment_path(g,source,sink,parent,volume);
		initialize_search(g);
		bfs(g,source);
		volume = path_volume(g, source, sink, parent);
	}
}
