/*	stack.h

	Header file for queue implementation
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



#define STACKSIZE 1000

typedef struct {
    int s[STACKSIZE+1];     /* body of queue */
    int top;                /* position of top element */
    int count;              /* number of stack elements */
} stack;

void init_stack(stack *s);
void push(stack *s, int x);
int pop(stack *s);
void print_stack(stack *s);
int empty_stack(stack *s);

