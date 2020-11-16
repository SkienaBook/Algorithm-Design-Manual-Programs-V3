/*	convolve.c
	Compute the convolution function of two sequences
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

#define	MAXN    100      /* largest n or m */

int max(int x, int y) {
    if (x > y) return(x); else return(y);
}

int min(int x, int y) {
    if (x < y) return(x); else return(y);
}

int main(void) {
    int i, j;                       /* counters */
    int a[MAXN],b[MAXN],c[MAXN];    /* sequences */
    int n, m;                       /* sequence lengths */

    for (i = 0; i < MAXN; i++) {
        a[i] = b[i] = c[i] = 0;
    }

    scanf("%d",&m);
    for (i=0; i < m; i++) {
	scanf("%d",&a[i]);
    }

    scanf("%d",&n);
    for (i=0; i < n; i++) {
        scanf("%d",&b[i]);
    }

/* [[[ convolve_cut */
    for (i = 0; i < n+m-1; i++) {
        for (j = max(0,i-(n-1)); j <= min(m-1,i); j++) {
	    c[i] = c[i] + a[j] * b[i-j];
	}
    }
/* ]]] */

for (i=0; i < m+n-1; i++) {
	printf("%d ",c[i]);
}

printf("\n");

    return 0;
}
