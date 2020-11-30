/*	suduku.c

	A backtracking program to solve Seduku

	by:Steven Skiena
	begun: August 2, 2006
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


#include <string.h>
#include "bool.h"

#define	BASED	   3			/* base dimension, 3*3 blocks */
#define DIMENSION  BASED*BASED		/* 9*9 board */
#define NCELLS     DIMENSION*DIMENSION  /* 81 cells in a 9*9 problem */

typedef struct {
	int x, y;			/* x and y coordinates of point */
} point;

typedef struct {
   int m[DIMENSION+1][DIMENSION+1];	/* matrix of board contents */
   int freecount;			/* how many open squares remain? */

   point move[NCELLS+1];
} boardtype;

extern bool finished;			/* solution found, stop search */

int steps;				/* how many total move insertions? */

bool fast;				/* fast or slow nextmove algorithm? */
bool smart;				/* quickly test for unfillable squares?*/

/**********************************************************************/

possible_values(int x, int y, boardtype *board, bool possible[])
{
        int i,j;			/* counters */
	int xlow,ylow;			/* origin of box with (x,y) */
	bool init;			/* is anything/everthing possible? */

	if ((board->m[x][y] != 0) || ((x<0)||(y<0)))
		init = FALSE;
	else
		init = TRUE;

        for (i=1; i<=DIMENSION; i++) possible[i] = init;

	for (i=0; i<DIMENSION; i++)
		if (board->m[x][i] != 0) possible[ board->m[x][i] ] = FALSE;

	for (i=0; i<DIMENSION; i++)
		if (board->m[i][y] != 0) possible[ board->m[i][y] ] = FALSE;

	xlow = BASED * ((int) (x / BASED));
	ylow = BASED * ((int) (y / BASED));

	for (i=xlow; i<xlow+BASED; i++)
		for (j=ylow; j<ylow+BASED; j++)
		     if (board->m[i][j] != 0) possible[ board->m[i][j] ] = FALSE;
}

print_possible(bool possible[])
{
	int i;				/* counter */

	for (i=0; i<=DIMENSION; i++)
		if (possible[i] == TRUE) printf(" %d",i);
	printf("\n");
}

int possible_count(int x, int y, boardtype *board)
{
	int i;				/* counter */
	int cnt;			/* number of open squares */
	bool possible[DIMENSION+1];     /* what is possible for the square */

	possible_values(x,y,board,possible);
	cnt = 0;
	for (i=0; i<=DIMENSION; i++)
		if (possible[i] == TRUE) cnt++;
	return(cnt);
}

fill_square(int x, int y, int v, boardtype *board)
{
	if (board->m[x][y] == 0)
		board->freecount=board->freecount-1;
	else
		printf("Warning: filling already filled square (%d,%d)\n",x,y);

	board->m[x][y] = v;
}

free_square(int x, int y, boardtype *board)
{
	if (board->m[x][y] != 0)
		board->freecount=board->freecount+1;
	else
		printf("Warning: freeing already empty square (%d,%d)\n",x,y);

	board->m[x][y] = 0;
}
	

next_square(int *x, int *y, boardtype* board)
{
	int i,j;			/* counters */
	int bestcnt, newcnt;		/* the best and latest square counts */
	bool doomed;			/* some empty square without moves? */

	bestcnt = DIMENSION + 1;
	doomed = FALSE;
	
	*x = *y = -1;

	for (i=0; i<DIMENSION; i++) {
		for (j=0; j<DIMENSION; j++) {
			newcnt = possible_count(i,j,board);
			if ((newcnt==0) && (board->m[i][j]==0))
				doomed = TRUE;
		    if (fast) {
			if ((newcnt < bestcnt) && (newcnt >= 1)) {
				bestcnt = newcnt;
				*x = i;
				*y = j;
			}
		    }
		    if (!fast) {  
			if ((newcnt >= 1) && (board->m[i][j] == 0)) {
				*x = i;
				*y = j;
			}
		    }
		}
	}

	if (doomed && smart) {
		*x = *y = -1;		/* initialize to non-position */
	}
}


print_board(boardtype *board)
{
	int i,j;			/* counters */

	printf("\nThere are %d free board positions.\n",board->freecount);


	for (i=0; i<DIMENSION; i++) {
		for (j=0; j<DIMENSION; j++) {
			if (board->m[i][j] == 0)
				printf(" ");
			else
				printf("%c",(char) '0'+board->m[i][j]);
			if ((j+1)%BASED == 0)
				printf("|");
		}
		printf("\n");
		if ((i+1)%BASED == 0) {
			for (j=0; j<(DIMENSION+BASED-1); j++)
				printf("-");
			printf("\n");
		}
	}
}

init_board(boardtype* board)
{
	int i,j;			/* counters */

	for (i=0; i<DIMENSION; i++)
		for (j=0; j<DIMENSION; j++)
			board->m[i][j] = 0;
	board->freecount = DIMENSION*DIMENSION;
}

read_board(boardtype* board)
{
	int i,j;			/* counters */
	char c;
	int value;

	init_board(board);

	for (i=0; i<DIMENSION; i++) {
                for (j=0; j<DIMENSION; j++) {
			scanf("%c",&c);
			value = (int) (c - '0');
			if (value != 0)
				fill_square(i,j,value,board);
		}
		scanf("\n"); /*newline*/
	}
}

copy_board(boardtype *a, boardtype *b)
{
	int i,j;

	b->freecount = a->freecount;

	for (i=0; i<DIMENSION; i++)
		for (j=0; j<DIMENSION; j++)
			b->m[i][j] = a->m[i][j];
}
	

/******************************************************************/

process_solution(int a[], int k, boardtype *board)
{
	finished = TRUE;
printf("process solution\n");
	print_board(board);
}

is_a_solution(int a[], int k, boardtype *board)
{
steps = steps+1;

	if (board->freecount == 0) {
		return (TRUE);
	}
	else
		return(FALSE);

}

make_move(int a[], int k, boardtype *board)
{
	fill_square(board->move[k].x,board->move[k].y,a[k],board);
}


unmake_move(int a[], int k, boardtype *board)
{
	free_square(board->move[k].x,board->move[k].y,board);
}

construct_candidates(int a[], int k, boardtype *board, int c[], int *ncandidates)
{
	int x,y;			/* position of next move */
	int i;				/* counter */
	bool possible[DIMENSION+1];     /* what is possible for the square */

	next_square(&x,&y,board);	/* which square should we fill next? */

	board->move[k].x = x;		/* store our choice of next position */
	board->move[k].y = y;

	*ncandidates = 0;

	if ((x<0) && (y<0)) return;	/* error condition, no moves possible */

	possible_values(x,y,board,possible);
	for (i=1; i<=DIMENSION; i++)
                if (possible[i] == TRUE) {
			c[*ncandidates] = i;
			*ncandidates = *ncandidates + 1;
		}
}

main()
{
	int i,j;			/* counters */
	int a[DIMENSION*DIMENSION+1];
	boardtype board;		/* Seduko board structure */
	boardtype temp;

	read_board(&board);
	print_board(&board);
	copy_board(&board,&temp);


	for (fast=TRUE; fast>=FALSE; fast--) 
		for (smart=TRUE; smart>=FALSE; smart--) {

			printf("----------------------------------\n");
			steps = 0;
			copy_board(&temp,&board);
			finished = FALSE;
		
			backtrack(a,0,&board);
			/*print_board(&board);*/

			printf("It took %d steps to find this solution ",steps);
			printf("for fast=%d  smart=%d\n",fast,smart);


		}
}

