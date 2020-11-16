/*    stack.c

    Implementation of a LIFO stack abstract data type.
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
#include <stdbool.h>

#include "stack.h"

void init_stack(stack *s) {
    s->top = -1;
    s->count = 0;
}


void push(stack *s, int x) {
    if (s->count >= STACKSIZE) {
        printf("Warning: stack overflow push x=%d\n", x);
    } else {
        s->top = s->top + 1;
        s->s[s->top] = x;
        s->count = s->count + 1;
    }
}

int pop(stack *s) {
    int x;

    if (s->count <= 0) printf("Warning: empty stack pop.\n");
    
    x = s->s[s->top];
    s->top = s->top - 1;
    s->count = s->count - 1;

    return(x);
}

int empty_stack(stack *s) {
    return (s->count <= 0);
}

void print_stack(stack *s) {
    int i;    /* counter */

    for (i = (s->count - 1); i >= 0; i--) {
        printf("%d ", s->s[i]);
    }
    printf("\n");
}
