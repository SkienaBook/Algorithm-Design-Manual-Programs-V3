/*	editdistance.c

	A generic implementation of string comparison via dynamic programming
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
#include <string.h>
#include <stdbool.h>

#include "editdistance.h"

/**********************************************************************/
/* [[[ string_comp2_cut */
int string_compare(char *s, char *t, cell m[MAXLEN+1][MAXLEN+1]) {
    int i, j, k;     /* counters */
    int opt[3];      /* cost of the three options */

    for (i = 0; i <= MAXLEN; i++) {
        row_init(i, m);
        column_init(i, m);
    }


    for (i = 1; i < strlen(s); i++) {
        for (j = 1; j < strlen(t); j++) {
            opt[MATCH] = m[i-1][j-1].cost + match(s[i], t[j]);
            opt[INSERT] = m[i][j-1].cost + indel(t[j]);
            opt[DELETE] = m[i-1][j].cost + indel(s[i]);

            m[i][j].cost = opt[MATCH];
            m[i][j].parent = MATCH;
            for (k = INSERT; k <= DELETE; k++) {
                if (opt[k] < m[i][j].cost) {
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                }
            }
        }
    }

    goal_cell(s, t, &i, &j);
    return(m[i][j].cost);
}
/* ]]] */

/* [[[ reconstruct_path_ed_cut */
void reconstruct_path(char *s, char *t, int i, int j,
                               cell m[MAXLEN+1][MAXLEN+1]) {
    if (m[i][j].parent == -1) {
        return;
    }

    if (m[i][j].parent == MATCH) {
        reconstruct_path(s, t, i-1, j-1, m);
        match_out(s, t, i, j);
        return;
    }

    if (m[i][j].parent == INSERT) {
        reconstruct_path(s, t, i, j-1, m);
        insert_out(t, j);
        return;
    }

    if (m[i][j].parent == DELETE) {
        reconstruct_path(s, t, i-1, j, m);
        delete_out(s, i);
        return;
    }
}
/* ]]] */

void print_matrix(char *s, char *t, bool costQ, cell m[MAXLEN+1][MAXLEN+1]) {
    int i, j;           /* counters */
	int x,y;            /* string lengths */

    x = strlen(s);
    y = strlen(t);

    printf("   ");
    for (i = 0; i < y; i++) {
         printf("  %c", t[i]);
    }
    printf("\n");

    for (i = 0; i < x; i++) {
        printf("%c: ", s[i]);
        for (j = 0; j < y; j++) {
            if (costQ) {
                printf(" %2d", m[i][j].cost);
            } else {
                printf(" %2d", m[i][j].parent);
            }
        }
        printf("\n");
    }
}
