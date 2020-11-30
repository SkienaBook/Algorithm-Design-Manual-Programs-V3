/*    war.c

    Simulation of the children's card game War 

    cards with format value, suit, e.g. 4h ranked by orders 23456789TJQKA and cdhs
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



#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include "queue.h"
#include "random.h"

#define NGAMES    50
#define MAXSTEPS  100000
#define NCARDS    52    /* number of cards */
#define NSUITS    4     /* number of suits */

char values[] = "23456789TJQKA";
char suits[] = "cdhs";

/*    Return the suit and value of the given card.     */

char suit(int card) {
    return(suits[card % NSUITS]);
}

char value(int card) {
    return(values[card/NSUITS]);
}

void print_card_queue(queue *q) {
    int i;

    i = q->first;

    while (i != q->last) {
        printf("%c%c ", value(q->q[i]), suit(q->q[i]));
        i = (i + 1) % QUEUESIZE;
    }

    printf("%2d ", q->q[i]);
    printf("\n");
}

/*     Rank the card with given value and suit.    */

int rank_card(char value, char suit) {
    int i, j;    /* counters */

    for (i = 0; i < (NCARDS / NSUITS); i++) {
        if (values[i] == value) {
            for (j = 0; j < NSUITS; j++) {
                if (suits[j] == suit) {
                    return(i * NSUITS + j);
                }
            }
        }
    }

    printf("Warning: bad input value=%d, suit=%d\n", value, suit);
    return -1;
}


void testcards(void) {
    int i;                   /* counter */

    for (i = 0; i < NCARDS; i++) {
        printf(" i=%d card[i]=%c%c rank=%d\n", i, value(i),
                 suit(i), rank_card(value(i), suit(i)) );
    }
}

/************************************************************/

void random_init_decks(queue *a, queue *b) {
    int i;    /* counter */
    int perm[NCARDS+1];

    for (i = 0; i < NCARDS; i = i+1) {
        perm[i] = i;
    }

    random_permutation(perm, NCARDS);

    init_queue(a);
    init_queue(b);

    for (i = 0; i < NCARDS / 2; i = i+1) {
        enqueue(a, perm[2 * i]);
        enqueue(b, perm[2 * i + 1]);
    }

    print_card_queue(a);
    print_card_queue(b);
}

void clear_queue(queue *a, queue *b) {
    while (!empty_queue(a)) {
        enqueue(b, dequeue(a));
    }
}

void war(queue *a, queue *b) {
    int steps=0;    /* step counter */
    int x,y;        /* top cards */
    queue c;        /* cards involved in the war */
    bool inwar;     /* are we involved in a war? */

    inwar = false;
    init_queue(&c);

    while ((!empty_queue(a)) && (!empty_queue(b) && (steps < MAXSTEPS))) {
	    steps = steps + 1;
	    x = dequeue(a);
	    y = dequeue(b);
	    enqueue(&c, x);
	    enqueue(&c, y);
	    if (inwar) {
	        inwar = false;
	    } else {
	        if (value(x) > value(y)) {
	            clear_queue(&c,a);
	        } else if  (value(x) < value(y)) {
	            clear_queue(&c,b);
	        } else if (value(y) == value(x)) {
	            inwar = true;
	        }
	    }
    }

    if (!empty_queue(a) && empty_queue(b)) {
        printf("a wins in %d steps \n", steps);
    } else if (empty_queue(a) && !empty_queue(b)) {
        printf("b wins in %d steps \n", steps);
    } else if (!empty_queue(a) && !empty_queue(b)) {
        printf("game tied after %d steps, |a|=%d |b|=%d \n",
                steps, a->count, b->count);
    } else {
        printf("a and b tie in %d steps \n", steps);
    }
}

int old_main(void) {
    queue a, b;
    int i;

    for (i = 1; i <= NGAMES; i++) {
        random_init_decks(&a, &b);
        war(&a, &b);
    }
    return 0;
}

int main(void) {
    queue decks[2];       /* player's decks */
    char value, suit, c;  /* input characters */
    int i;                /* deck counter */

    while (true) {
        for (i = 0; i <= 1; i++) {
           init_queue(&decks[i]);

            while ((c = getchar()) != '\n') {
                if (c == EOF) {
                    return -1;
                }
                if (c != ' ') {
                    value = c;
                    suit = getchar();
                    enqueue(&decks[i], rank_card(value, suit));
                }
            }
        }
        war(&decks[0], &decks[1]);
    }
    return 0;
}
