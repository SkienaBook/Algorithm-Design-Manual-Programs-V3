/*  sentinel.c

    Example search program using sentinels
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

#define MAXINT 1000000

int a[100];

int main(void) {
    int i, n, x;

    for (i = 1; i <= 20; i++) {
        a[i] = i;
    }
    n = 20;
    x = -1;

    i = n;
    while ((a[i] >= x) && (i >= 1)) {
        a[i + 1] = a[i];
        i = i - 1;
    }
    a[i + 1] = x;

    printf("without sentinel, i=%d a[1]=%d\n", i, a[1]);
    for (i = 1; i <= 25; i++) {
        printf("%d ", a[i]);
    }
    x = -2;

    n = 21;
    i = n;
    a[0] = - MAXINT;
    while (a[i] >= x) {
        a[i + 1] = a[i];
        i = i - 1;
    }
    a[i + 1] = x;

    printf("\nwith sentinel, i=%d a[1]=%d\n", i, a[1]);
    for (i = 1; i <= 25; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
