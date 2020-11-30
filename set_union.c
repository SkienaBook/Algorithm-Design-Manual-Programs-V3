/*    set_union.c

    Implementation of a heap / priority queue abstract data type.
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

#include "set_union.h"

/* [[[ set_union_init_cut */
void union_find_init(union_find *s, int n) {
    int i;    /* counter */

    for (i = 1; i <= n; i++) {
        s->p[i] = i;
        s->size[i] = 1;
    }
    s->n = n;
}
/* ]]] */

/* [[[ set_union_find_cut */
int find(union_find *s, int x) {
    if (s->p[x] == x) {
        return(x);
    }
    return(find(s, s->p[x]));
}
/* ]]] */

/* [[[ set_union_union_sets_cut */
void union_sets(union_find *s, int s1, int s2) {
    int r1, r2;    /* roots of sets */

    r1 = find(s, s1);
    r2 = find(s, s2);

    if (r1 == r2) {
        return;    /* already in same set */
    }

    if (s->size[r1] >= s->size[r2]) {
        s->size[r1] = s->size[r1] + s->size[r2];
        s->p[r2] = r1;
    } else {
        s->size[r2] = s->size[r1] + s->size[r2];
        s->p[r1] = r2;
    }
}
/* ]]] */

/* [[[ same_component_cut */
bool same_component(union_find *s, int s1, int s2) {
    return (find(s, s1) == find(s, s2));
}
/* ]]] */

void print_union_find(union_find *s) {
    int i;    /* counter */

    for (i = 1; i <= s->n; i++) {
        printf("%i  set=%d size=%d \n", i, s->p[i], s->size[i]);
    }
    printf("\n");
}
