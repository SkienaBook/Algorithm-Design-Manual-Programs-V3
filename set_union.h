/*	set_union.h

	Header file for union-find data structure implementation
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



#include <stdbool.h>

#define SET_SIZE 1000

/* [[[ set_union_cut */
typedef struct {
    int p[SET_SIZE+1];      /* parent element */
    int size[SET_SIZE+1];   /* number of elements in subtree i */
    int n;                  /* number of elements in set */
} union_find;
/* ]]] */

void union_find_init(union_find *s, int n);
void union_sets(union_find *s, int s1, int s2);
bool same_component(union_find *s, int s1, int s2);
void print_union_find(union_find *s);
