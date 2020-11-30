/*    order.c

      Demonstrate traversal orders on a grid.
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

#include "geometry.h"

void process(int i, int j) {
    printf("(%d,%d)\n", i, j);
}

void row_major(int n, int m) {
    int i, j;    /* counters */

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            process(i, j);
        }
    }
}

void column_major(int n, int m) {
    int i, j;    /* counters */

    for (j = 1; j <= m; j++) {
        for (i = 1; i <= n; i++) {
            process(i, j);
        }
    }
}

void snake_order(int n, int m) {
    int i, j;    /* counters */

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            process(i, j + (m+1-2*j) * ((i+1) % 2));
        }
    }
}

void diagonal_order(int n, int m) {
    int d, j;      /* diagonal and point counters */
    int pcount;    /* points on diagonal */
    int height;    /* row of lowest point */

    for (d = 1; d <= (m + n - 1); d++) {
        height = 1 + max(0, d - m);
        pcount = min(d, (n - height + 1));
        for (j = 0; j < pcount; j++) {
            process(min(m , d) - j, height + j);
        }
    }
}

int main(void) {
    printf("row_major\n");
    row_major(5, 5);

    printf("\ncolumn_major\n");
    column_major(3, 3);

    printf("\nsnake_order\n");
    snake_order(5, 5);

    printf("\ndiagonal_order\n");
    diagonal_order(3, 4);

    printf("\ndiagonal_order\n");
    diagonal_order(4, 3);

    return 0;
}
