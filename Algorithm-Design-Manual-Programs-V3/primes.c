/*    primes.c        

    Compute the prime factorization of an integer.
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

void prime_factorization(long x) {
    long i;    /* counter */
    long c;    /* remaining product to factor */

    c = x;

    while ((c % 2) == 0) {
        printf("%d\n", 2);
        c = c / 2;
    }

    i = 3;

    while (i <= (sqrt(c) + 1)) {
        if ((c % i) == 0) {
            printf("%ld\n", i);
            c = c / i;
        } else {
            i = i + 2;
        }
    }

    if (c > 1) {
        printf("%ld\n", c);
    }
}

int main(void) {
    long p;

    while (scanf("%ld", &p) != EOF) {
        printf("prime factorization of p=%ld \n", p);
        prime_factorization(p);
    }

    return 0;
}
