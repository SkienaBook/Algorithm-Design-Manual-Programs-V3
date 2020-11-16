/*	tree.h

	Header file for binary search tree implementation
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



#include "item.h"

/* [[[ struct_tree_cut */
typedef struct tree {
    item_type item;         /* data item */
    struct tree *parent;    /* pointer to parent */
    struct tree *left;      /* pointer to left child */
    struct tree *right;     /* pointer to right child */
} tree;
/* ]]] */
