/*	binomial.c
	Compute the binomial coefficients using dynamic programming 
	by: Steven Skiena
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

#define	MAXN    100    /* largest n or k */

/* compute n choose k */

/* [[[ binomial_coeff_cut */
long binomial_coefficient(int n, int k) {
    int i, j;                   /* counters */
    long bc[MAXN+1][MAXN+1];    /* binomial coefficient table */

    for (i = 0; i <= n; i++) {
        bc[i][0] = 1;
    }

    for (j = 0; j <= n; j++) {
        bc[j][j] = 1;
    }

    for (i = 2; i <= n; i++) {
        for (j = 1; j < i; j++) {
            bc[i][j] = bc[i-1][j-1] + bc[i-1][j];
        }
    }

    return(bc[n][k]);
}
/* ]]] */

int main(void) {
    int a, b, n, i;

    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%d %d", &a, &b);
        printf("%d choose %d = %ld\n", a, b, binomial_coefficient(a, b));
    }

    return 0;
}
