/*	editbrute.c

	Compute string edit distance *without* dynamic programming!
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
#include <string.h>
#include <stdbool.h>

#include "editdistance.h"

/* [[ cell_instance_cut */
cell m[MAXLEN+1][MAXLEN+1];    /* dynamic programming table */
/* ]] */

/**********************************************************************/
void goal_cell(char *s, char *t, int *i, int *j) {
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}

int match(char c, char d) {
    if (c == d) {
        return(0);
    }
    return(1);
}

int indel(char c) {
    return(1);
}

void row_init(int i, cell m[MAXLEN+1][MAXLEN+1]) {
    m[0][i].cost = i;
    if (i > 0) {
        m[0][i].parent = INSERT;
    } else {
        m[0][i].parent = -1;
    }
}

void column_init(int i, cell m[MAXLEN+1][MAXLEN+1]) {
    m[i][0].cost = i;
    if (i > 0) {
        m[i][0].parent = DELETE;
    } else {
        m[0][i].parent = -1;
    }
}

/**********************************************************************/

void match_out(char *s, char *t, int i, int j) {
    if (s[i] == t[j]) {
        printf("M");
    } else {
        printf("S");
    }
}

void insert_out(char *t, int j) {
    printf("I");
}

void delete_out(char *s, int i) {
    printf("D");
}


int string_compare2(char *s, char *t, int i, int j, cell m[MAXLEN+1][MAXLEN+1]) {
    int k;           /* counter */
    int opt[3];      /* cost of the three options */
    int lowest_cost; /* lowest cost */

    if (i == 0) {    /* indel is the cost of an insertion or deletion  */ 
        return(j * indel(' '));
    }

    if (j == 0) {
        return(i * indel(' '));
    }

    opt[MATCH] = string_compare2(s, t, i-1, j-1, m) + match(s[i], t[j]);
    opt[INSERT] = string_compare2(s, t, i, j-1, m) + indel(t[j]);
    opt[DELETE] = string_compare2(s, t, i-1, j, m) + indel(s[i]);

    lowest_cost = opt[MATCH];
    for (k = INSERT; k <= DELETE; k++) {
        if (opt[k] < lowest_cost) {
            lowest_cost = opt[k];
        }
    }

    m[i][j].cost = lowest_cost;	/* REMOVE FROM PRINTED VERSION */

    return(lowest_cost);
}

/* [[[ string_compare_cut */
int string_compare_r(char *s, char *t, int i, int j) {
    int k;           /* counter */
    int opt[3];      /* cost of the three options */
    int lowest_cost; /* lowest cost */

    if (i == 0) {    /* indel is the cost of an insertion or deletion */ 
        return(j * indel(' '));
    }

    if (j == 0) {
        return(i * indel(' '));
    }
                     /* match is the cost of a match/substitution */

    opt[MATCH]  = string_compare_r(s,t,i-1,j-1) + match(s[i],t[j]);
    opt[INSERT] = string_compare_r(s,t,i,j-1) + indel(t[j]);
    opt[DELETE] = string_compare_r(s,t,i-1,j) + indel(s[i]);

    lowest_cost = opt[MATCH];
    for (k = INSERT; k <= DELETE; k++) {
        if (opt[k] < lowest_cost) {
            lowest_cost = opt[k];
        }
    }

    return(lowest_cost);
}
/* ]]] */

void reconstruct_path(char *s, char *t, int i, int j, cell m[MAXLEN+1][MAXLEN+1]) {
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

void print_matrix(char *s, char *t, bool costQ, cell m[MAXLEN+1][MAXLEN+1]) {
    int i, j;           /* counters */
    int x, y;           /* string lengths */

    x = strlen(s);
    y = strlen(t);

    printf("   ");
    for (i = 0; i < y; i++) {
        printf("  %c", t[i]);
    }

    printf("\n");

    for (i = 0; i < x; i++) {
        printf("%c: ",s[i]);
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

int main(void) {
    int i, j;
    int cost1, cost2;
    char s[MAXLEN], t[MAXLEN];    /* input strings */

    s[0] = t[0] = ' ';

    scanf("%s", &(s[1]));
    scanf("%s", &(t[1]));

    cost1 = string_compare_r(s, t, strlen(s) - 1, strlen(t) - 1);
    printf("matching cost = %d \n", cost2 = string_compare2(s, t, strlen(s) - 1, strlen(t) - 1, m));

    if (cost1 != cost2) printf("Editbrutes do not agree: cost1=%d cost2=%d\n",cost1,cost2);

    print_matrix(s, t, true, m);
    printf("\n");
    print_matrix(s, t, false, m);

    goal_cell(s, t, &i, &j);

    printf("%d %d\n", i, j);

    reconstruct_path(s, t, i, j, m);
    printf("\n");

    return 0;
}
