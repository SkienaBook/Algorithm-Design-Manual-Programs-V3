/*	backtrack.c
    	A generic backtracking implementation
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
or http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/
*/


#include <stdio.h>

#include "backtrack.h"
#include "bool.h"

/* [[[ backtrack_boolean_cut */
bool finished = FALSE;                  /* found all solutions yet? */
/* ]]] */

void process_solution(int a[], int k, data input);
void construct_candidates(int a[], int k, data input, int c[], int *nc);
void make_move(int a[], int k, data input);
void unmake_move(int a[], int k, data input);
int is_a_solution(int a[], int k, data input);

/* [[[ backtrack_cut */
void backtrack(int a[], int k, data input) {
    int c[MAXCANDIDATES];      /* candidates for next position */
    int nc;                    /* next position candidate count */
    int i;                     /* counter */

    if (is_a_solution(a, k, input)) {
        process_solution(a, k,input);
    } else {
        k = k + 1;
        construct_candidates(a, k, input, c, &nc);
        for (i = 0; i < nc; i++) {
            a[k] = c[i];
            make_move(a, k, input);
            backtrack(a, k, input);
            unmake_move(a, k, input);

            if (finished) {
                return;	/* terminate early */
            }
        }
    }
}
/* ]]] */
