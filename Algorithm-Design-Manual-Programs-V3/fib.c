/*	binomial.c
	Compute the binomial coefficients using dynamic programming 
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

/* [[[ fib_const_cut */
#define MAXN    92      /* largest n for which F(n) fits in a long */
#define UNKNOWN -1      /* contents denote an empty cell */
long f[MAXN+1];         /* array for caching fib values */
/* ]]] */

/* computer n choose m */

long binomial_coefficient(int n, int m) {
    int i, j;               /* counters */
    long bc[MAXN][MAXN];    /* table of binomial coefficient values */

    for (i = 0; i <= n; i++) {
        bc[i][0] = 1;
    }

    for (j = 0; j <= n; j++) {
        bc[j][j] = 1;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j < i; j++) {
            bc[i][j] = bc[i-1][j-1] + bc[i-1][j];
        }
    }

    return(bc[n][m]);
}

/* [[[ fib_r_cut */
long fib_r(int n) {
    if (n == 0) {
        return(0);
    }

    if (n == 1) {
        return(1);
    }

    return(fib_r(n-1) + fib_r(n-2));
}
/* ]]] */

/* [[[ fib_c_cut */
long fib_c(int n) {
    if (f[n] == UNKNOWN) { 
        f[n] = fib_c(n-1) + fib_c(n-2);
    }

    return(f[n]);
}
/* ]]] */

/* [[[ fib_c_driver_cut */
long fib_c_driver(int n) {
    int i;      /* counter */

    f[0] = 0;
    f[1] = 1;
	
    for (i = 2; i <= n; i++) {
        f[i] = UNKNOWN;
    }

    return(fib_c(n));
}
/* ]]] */

/* [[[ fib_dp_cut */
long fib_dp(int n) {
    int i;                    /* counter */
    long f[MAXN+1];           /* array for caching values */

    f[0] = 0;
    f[1] = 1;

    for (i = 2; i <= n; i++) {
        f[i] = f[i-1] + f[i-2];
    }

    return(f[n]);
}
/* ]]] */

/* [[[ fib_ult_cut */
long fib_ultimate(int n)
{
        int i;                  /* counter */
        long back2=0, back1=1;  /* last two values of f[n] */
        long next;              /* placeholder for sum */

        if (n == 0) return (0);

        for (i=2; i<n; i++) {
                next = back1+back2;
                back2 = back1;
                back1 = next;
        }
        return(back1+back2);
}
/* ]]] */

int main(void) {
    int i;
    int ntest=92;

    for (i = 0; i <= ntest; i++) {
        printf("fib_c(%d) = %ld\n",i, fib_c_driver(i));
    }

    for (i = 0; i <= ntest; i++) {
        printf("fib_dp(%d) = %ld\n",i, fib_dp(i));
    }

    for (i = 0; i <= ntest; i++) {
        printf("fib_dp2(%d) = %ld\n",i, fib_ultimate(i));
    }

/*
    for (i = 0; i <= ntest; i++) {
        printf("fib(%d) = %ld\n",i, fib_r(i));
    }
*/

    return 0;
}
