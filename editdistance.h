/*	editdistance.h

	Header file for string comparison
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

#define MAXLEN     101     /* longest possible string */

/* [[[ editdistance_mid_cut */
#define MATCH      0       /* enumerated type symbol for match */
#define INSERT     1       /* enumerated type symbol for insert */
#define DELETE     2       /* enumerated type symbol for delete */
/* ]]] */

/* [[[ editdistance_cell_struct_cut */
typedef struct {
    int cost;               /* cost of reaching this cell */
    int parent;             /* parent cell */
} cell;
/* ]]] */

void row_init(int i, cell m[MAXLEN+1][MAXLEN+1]);
void column_init(int i, cell m[MAXLEN+1][MAXLEN+1]);
int match(char c, char d);
int indel(char c);
void goal_cell(char *s, char *t, int *i, int *j);
void delete_out(char *s, int i);
void insert_out(char *t, int j);
void match_out(char *s, char *t, int i, int j);
int string_compare(char *s, char *t, cell m[MAXLEN+1][MAXLEN+1]);
int string_compare_r(char *s, char *t, int i, int j);
void reconstruct_path(char *s, char *t, int i, int j, cell m[MAXLEN+1][MAXLEN+1]);
void print_matrix(char *s, char *t, bool costQ, cell m[MAXLEN+1][MAXLEN+1]);
