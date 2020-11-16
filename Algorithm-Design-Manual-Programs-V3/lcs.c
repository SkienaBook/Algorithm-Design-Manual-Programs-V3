/*	lcs.c

	Longest common subsequence of two strings.
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

#include "editdistance.h"
#include <stdbool.h>

cell m[MAXLEN+1][MAXLEN+1];    /* dynamic programming table */

/******************************************************************/

/*	For normal edit distance computation  */

/* [[[ goal_cell_ed_cut */
void goal_cell(char *s, char *t, int *i, int *j) {
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}
/* ]]] */

/* [[[ match_ed_cut */
int match(char c, char d) {
    if (c == d) {
        return(0);
    }
    return(MAXLEN);
}
/* ]]] */

int indel(char c) {
    return(1);
}

/* [[[ row_init_ed_cut */
void row_init(int i, cell m[MAXLEN+1][MAXLEN+1]) {
    m[0][i].cost = i;
    if (i > 0) {
        m[0][i].parent =  INSERT;
    } else {
        m[0][i].parent = -1;
    }
}
/* ]]] */

void column_init(int i, cell m[MAXLEN+1][MAXLEN+1]) {
    m[i][0].cost = i;
    if (i > 0) {
        m[i][0].parent = DELETE;
    } else {
        m[0][i].parent = -1;
    }
}

/**********************************************************************/
/* [[[ mid_out_ed_cut */
void match_out(char *s, char *t, int i, int j) {
    if (s[i] == t[j]) {
        printf("%c", s[i]);
    }
}
/* ]]] */

void insert_out(char *t, int j) {

}

void delete_out(char *s, int i) {

}

/**********************************************************************/

int main(void) {
    int i, j;
    int lcslen, complen;
    char s[MAXLEN],t[MAXLEN];    /* input strings */

    s[0] = t[0] = ' ';

    scanf("%s", &(s[1]));
    scanf("%s", &(t[1]));

    complen = string_compare(s, t, m);
    lcslen = (strlen(s) + strlen(t) - 2 - complen) / 2;

    printf("length of longest common subsequence = %d\n", lcslen);

    goal_cell(s, t, &i, &j);

    reconstruct_path(s, t, i, j, m);
    printf("\n");

    return 0;
}
