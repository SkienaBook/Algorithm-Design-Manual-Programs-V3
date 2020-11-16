/*    subsets.c

    Construct all subsets via backtracking.
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



#include <stdio.h>
#include <stdbool.h>

bool finished = false;
#define MAXCANDIDATES   100    /* max possible next extensions */
#define NMAX            100    /* maximum solution size */

/* [[[ process_solution_cut */
void process_solution(int a[], int k, int input) {
    int i;    /* counter */
    
    printf("{");
    for (i = 1; i <= k; i++) {
        if (a[i] == true) {
            printf(" %d", i);
        }
    }

    printf(" }\n");
}
/* ]]] */

void make_move(int a[], int k, int n) {

}

void unmake_move(int a[], int k, int n) {

}

/*    What are possible elements of the next slot in the permutation?  */


/* [[[ subset_part_cut */
/* [[[ is_a_solution_cut */
int is_a_solution(int a[], int k, int n) {
    return (k == n);
}
/* ]]] */

/* [[[ construct_candidates_cut */
void construct_candidates(int a[], int k, int n, int c[], int *nc) {
    c[0] = true;
    c[1] = false;
    *nc = 2;
}
/* ]]] */
/* ]]] */

void backtrack(int a[], int k, int input) {
    int c[MAXCANDIDATES];           /* candidates for next position */
    int ncandidates;                /* next position candidate count */
    int i;                          /* counter */

    if (is_a_solution(a, k, input)) {
        process_solution(a, k, input);
    } else {
        k = k + 1;
        construct_candidates(a, k, input, c, &ncandidates);
        for (i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            make_move(a, k, input);
            backtrack(a, k, input);
            unmake_move(a, k, input);

            if (finished) {
                return;    /* terminate early */
            }
        }
    }
}

/* [[[ generate_subsets_cut */
void generate_subsets(int n) {
    int a[NMAX];                    /* solution vector */

    backtrack(a, 0, n);
}
/* ]]] */

int main(void) {
    generate_subsets(3);
    return 0;
}
