/*    stringedit.c

    Compute the optimal alignment matching two strings
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

/******************************************************************/

/*    For normal edit distance computation  */

cell m[MAXLEN+1][MAXLEN+1];

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

void row_init(int i, cell m[MAXLEN+1][MAXLEN+1]) {    /* what is m[0][i]? */
    m[0][i].cost = i;
    if (i > 0) {
        m[0][i].parent =  INSERT;
    } else {
        m[0][i].parent = -1;
    }
}

void column_init(int i, cell m[MAXLEN+1][MAXLEN+1])    { /* what is m[i][0]? */
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

/**********************************************************************/

int main(void){
    int i, j;
    char s[MAXLEN], t[MAXLEN];    /* input strings */

    s[0] = t[0] = ' ';

    scanf("%s", &(s[1]));
    scanf("%s", &(t[1]));

    printf("matching cost = %d \n", string_compare(s, t, m));

    print_matrix(s, t, true, m);
    printf("\n");
    print_matrix(s, t, false, m);

    goal_cell(s, t, &i, &j);

    printf("%d %d\n", i, j);

    reconstruct_path(s, t, i, j, m);
    printf("\n");

    return 0;
}
