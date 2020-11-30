/*	matrix.c

	Multiply two matrices.
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
#include <stdlib.h>

/************************************************************/

#define	MAXV        100     /* maximum number of vertices */
#define MAXDEGREE   50      /* maximum outdegree of a vertex */
#define MAXINT      100007

typedef struct {
    int m[MAXV+1][MAXV+1];  /* adjacency/weight info */
    int rows;               /* number of rows */
    int columns;            /* number of columns */
} matrix;

void initialize_matrix(matrix *m) {
    int i, j;    /* counters */

    for (i = 1; i <= m->rows; i++) {
        for (j = 1; j <= m->columns; j++) {
            m->m[i][j] = 0;
        }
    }
}

void read_matrix(matrix *m) {
    int i, j;    /* counters */

    scanf("%d %d\n", &(m->rows), &(m->columns));

    for (i = 1; i <= m->rows; i++) {
        for (j = 1; j <= m->columns; j++) {
            scanf("%d", &m->m[i][j]);
        }
    }
}

void print_matrix(matrix *g) {
    int i, j;    /* counters */

    for (i = 1; i <= g->rows; i++) {
        for (j = 1; j <= g->columns; j++) {
            printf(" %d",g->m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiply(matrix *a, matrix *b, matrix *c) {
    int i, j, k;    /* dimension counters */

    if (a->columns != b->rows) {
        printf("Error: bounds dont match!\n");
        return;
    }

    c->rows = a->rows;
    c->columns = b->columns;
/* [[[ matrix_cut */
    for (i = 1; i <= a->rows; i++) {
        for (j = 1; j <= b->columns; j++) {
            c->m[i][j] = 0;
            for (k = 1; k <= b->rows; k++) {
                c->m[i][j] += a->m[i][k] * b->m[k][j];
            }
        }
    }
/* ]]] */
}

int main(void) {
    matrix a, b, c;

    read_matrix(&a);
    print_matrix(&a);

    read_matrix(&b);
    print_matrix(&b);

    multiply(&a, &b, &c);

    print_matrix(&c);

    return 0;
}
