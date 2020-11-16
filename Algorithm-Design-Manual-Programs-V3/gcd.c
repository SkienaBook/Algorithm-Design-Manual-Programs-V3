/*	gcd.c           

	Compute the greatest common divisor of two integers
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



#include <math.h>
#include <stdio.h>

/* integers to compute the GCD of */

long gcd1(long p, long q) {
    if (q > p) {
        return(gcd1(q, p));
    }

    if (q == 0) {
        return(p);
    }

    printf(" gcd(%ld,%ld) &=& gcd(%ld \\mod %ld, %ld) = gcd(%ld,%ld) \n",
            p, q, p, q, q, q, p % q);

    return(gcd1(q, p % q));
}

/*	Find the gcd(p,q) and x,y such that p*x + q*y = gcd(p,q)	*/

long gcd(long p, long q, long *x, long *y) {
    long x1, y1;        /* previous coefficients */
    long g;             /* value of gcd(p,q) */

    if (q > p) {
        return(gcd(q, p, y, x));
    }

    if (q == 0) {
        *x = 1;
        *y = 0;
        return(p);
    }

    g = gcd(q, p%q, &x1, &y1);
	
    *x = y1;
    *y = (x1 - floor(p/q)*y1);

    return(g);
}

int main(void) {
    long p, q;
    long x, y, g1, g2;

    while (scanf("%ld %ld", &p, &q) != EOF) {
        g1 = gcd1(p, q);
        g2 = gcd(p, q, &x, &y);

        printf("gcd of p=%ld and q=%ld = %ld\n", p, q, g1);
        printf(" %ld*%ld + %ld*%ld = %ld\n", p, x, q, y, g2);

        if (g1 != g2) {
            printf("ERROR: GCD\n");
        }
        
        if ((p*x + q*y) != g1) {
            printf("ERROR: DIOPHONINE SOLUTION WRONG!\n");
        }
    }

    return 0;
}
