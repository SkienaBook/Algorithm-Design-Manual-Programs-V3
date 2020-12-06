/*    permutations.c

    Construct all permutations via backtracking.
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

#define MAXCANDIDATES   100    /* max possible next extensions */
#define NMAX            100    /* maximum solution size */

bool finished = false;

/* [[[ process_solution_perms_cut */
void process_solution(int a[], int k, int input) {
    int i;    /* counter */

    for (i = 1; i <= k; i++) {
        printf(" %d", a[i]);
    }
    printf("\n");
}
/* ]]] */

/* [[[ is_a_solution_perms_cut */
int is_a_solution(int a[], int k, int n) {
    return (k == n);
}
/* ]]] */

void make_move(int a[], int k, int n) {

}

void unmake_move(int a[], int k, int n){

}

/*    What are possible elements of the next slot in the permutation?  */
/* [[[ construct_candidates_perms_cut */
void construct_candidates(int a[], int k, int n, int c[], int *nc) {
    int i;                 /* counter */
    bool in_perm[NMAX];    /* what is now in the permutation? */

    for (i = 1; i < NMAX; i++) {
        in_perm[i] = false;
    }

    for (i = 1; i < k; i++) {
        in_perm[a[i]] = true;
    }

    *nc = 0;
    for (i = 1; i <= n; i++) { 
        if (!in_perm[i]) {
            c[ *nc ] = i;
            *nc = *nc + 1;
        }
    }
}
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

/* [[[ generate_perms_cut */
void generate_permutations(int n) {
    int a[NMAX];                    /* solution vector */

    backtrack(a, 0, n);
}
/* ]]] */

int main(void) {
    generate_permutations(0);
    generate_permutations(1);
    generate_permutations(2);
    generate_permutations(3);

    return 0;
}
