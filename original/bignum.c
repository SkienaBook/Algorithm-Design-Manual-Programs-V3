/*	bignum.c
	Implementation of large integer arithmetic: addition, subtraction,
		multiplication, and division.

	begun: February 7, 2002
	by: Steven Skiena
*/

/*
Copyright 2003 by Steven S. Skiena; all rights reserved. 

Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.

This book can be ordered from Amazon.com at

http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/

*/


#include <stdio.h>

#define	MAXDIGITS	100		/* maximum length bignum */ 

#define PLUS		1		/* positive sign bit */
#define MINUS		-1		/* negative sign bit */

typedef struct {
        char digits[MAXDIGITS];         /* represent the number */
	int signbit;			/* 1 if positive, -1 if negative */ 
        int lastdigit;			/* index of high-order digit */
} bignum;


print_bignum(bignum *n)
{
	int i;

	if (n->signbit == MINUS) printf("- ");
	for (i=n->lastdigit; i>=0; i--)
		printf("%c",'0'+ n->digits[i]);

	printf("\n");
}

int_to_bignum(int s, bignum *n)
{
	int i;				/* counter */
	int t;				/* int to work with */

	if (s >= 0) n->signbit = PLUS;
	else n->signbit = MINUS;

	for (i=0; i<MAXDIGITS; i++) n->digits[i] = (char) 0;

	n->lastdigit = -1;

	t = abs(s);

	while (t > 0) {
		n->lastdigit ++;
		n->digits[ n->lastdigit ] = (t % 10);
		t = t / 10;
	}

	if (s == 0) n->lastdigit = 0;
}

initialize_bignum(bignum *n)
{
	int_to_bignum(0,n);
}


int max(int a, int b)
{
	if (a > b) return(a); else return(b);
}

/*	c = a +-/* b;	*/

add_bignum(bignum *a, bignum *b, bignum *c)
{
	int carry;			/* carry digit */
	int i;				/* counter */

	initialize_bignum(c);

	if (a->signbit == b->signbit) c->signbit = a->signbit;
	else {
		if (a->signbit == MINUS) {
			a->signbit = PLUS;
			subtract_bignum(b,a,c);
			a->signbit = MINUS;
		} else {
                        b->signbit = PLUS;
                        subtract_bignum(a,b,c);
                        b->signbit = MINUS;
		}
		return;
	}

	c->lastdigit = max(a->lastdigit,b->lastdigit)+1;
	carry = 0;

	for (i=0; i<=(c->lastdigit); i++) {
		c->digits[i] = (char) (carry+a->digits[i]+b->digits[i]) % 10;
		carry = (carry + a->digits[i] + b->digits[i]) / 10;
	}

	zero_justify(c);
}


subtract_bignum(bignum *a, bignum *b, bignum *c)
{
	int borrow;			/* has anything been borrowed? */
	int v;				/* placeholder digit */
	int i;				/* counter */

	initialize_bignum(c);

	if ((a->signbit == MINUS) || (b->signbit == MINUS)) {
                b->signbit = -1 * b->signbit;
                add_bignum(a,b,c);
                b->signbit = -1 * b->signbit;
		return;
        }

	if (compare_bignum(a,b) == PLUS) {
		subtract_bignum(b,a,c);
		c->signbit = MINUS;
		return;
	}

        c->lastdigit = max(a->lastdigit,b->lastdigit);
        borrow = 0;

        for (i=0; i<=(c->lastdigit); i++) {
		v = (a->digits[i] - borrow - b->digits[i]);
		if (a->digits[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}

                c->digits[i] = (char) v % 10;
        }

	zero_justify(c);
}

compare_bignum(bignum *a, bignum *b)
{
	int i;				/* counter */

	if ((a->signbit == MINUS) && (b->signbit == PLUS)) return(PLUS);
	if ((a->signbit == PLUS) && (b->signbit == MINUS)) return(MINUS);

	if (b->lastdigit > a->lastdigit) return (PLUS * a->signbit);
	if (a->lastdigit > b->lastdigit) return (MINUS * a->signbit);

	for (i = a->lastdigit; i>=0; i--) {
		if (a->digits[i] > b->digits[i]) return(MINUS * a->signbit);
		if (b->digits[i] > a->digits[i]) return(PLUS * a->signbit);
	}

	return(0);
}

zero_justify(bignum *n)
{
	while ((n->lastdigit > 0) && (n->digits[ n->lastdigit ] == 0))
		n->lastdigit --;

        if ((n->lastdigit == 0) && (n->digits[0] == 0))
		n->signbit = PLUS;	/* hack to avoid -0 */
}


digit_shift(bignum *n, int d)		/* multiply n by 10^d */
{
	int i;				/* counter */

	if ((n->lastdigit == 0) && (n->digits[0] == 0)) return;

	for (i=n->lastdigit; i>=0; i--)
		n->digits[i+d] = n->digits[i];

	for (i=0; i<d; i++) n->digits[i] = 0;

	n->lastdigit = n->lastdigit + d;
}



multiply_bignum(bignum *a, bignum *b, bignum *c)
{
	bignum row;			/* represent shifted row */
	bignum tmp;			/* placeholder bignum */
	int i,j;			/* counters */

	initialize_bignum(c);

	row = *a;

	for (i=0; i<=b->lastdigit; i++) {
		for (j=1; j<=b->digits[i]; j++) {
			add_bignum(c,&row,&tmp);
			*c = tmp;
		}
		digit_shift(&row,1);
	}

	c->signbit = a->signbit * b->signbit;

	zero_justify(c);
}


divide_bignum(bignum *a, bignum *b, bignum *c)
{
        bignum row;                     /* represent shifted row */
        bignum tmp;                     /* placeholder bignum */
	int asign, bsign;		/* temporary signs */
        int i,j;                        /* counters */

	initialize_bignum(c);

	c->signbit = a->signbit * b->signbit;

	asign = a->signbit;
	bsign = b->signbit;

	a->signbit = PLUS;
        b->signbit = PLUS;

	initialize_bignum(&row);
	initialize_bignum(&tmp);

	c->lastdigit = a->lastdigit;

	for (i=a->lastdigit; i>=0; i--) {
		digit_shift(&row,1);
		row.digits[0] = a->digits[i];
		c->digits[i] = 0;
		while (compare_bignum(&row,b) != PLUS) {
			c->digits[i] ++;
			subtract_bignum(&row,b,&tmp);
			row = tmp;
		}
	}

	zero_justify(c);

	a->signbit = asign;
	b->signbit = bsign;
}



main()
{
	int a,b;
	bignum n1,n2,n3,zero;

	while (scanf("%d %d\n",&a,&b) != EOF) {
		printf("a = %d    b = %d\n",a,b);
		int_to_bignum(a,&n1);
		int_to_bignum(b,&n2);

		add_bignum(&n1,&n2,&n3);
		printf("addition -- ");
		print_bignum(&n3);

		printf("compare_bignum a ? b = %d\n",compare_bignum(&n1, &n2));

		subtract_bignum(&n1,&n2,&n3);
		printf("subtraction -- ");
		print_bignum(&n3);

                multiply_bignum(&n1,&n2,&n3);
		printf("multiplication -- ");
                print_bignum(&n3);

		int_to_bignum(0,&zero);
		if (compare_bignum(&zero, &n2) == 0)
			printf("division -- NaN \n");
                else {
			divide_bignum(&n1,&n2,&n3);
			printf("division -- ");
                	print_bignum(&n3);
		}
		printf("--------------------------\n");
	}
}

