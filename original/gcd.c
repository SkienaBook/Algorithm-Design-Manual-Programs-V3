/*	gcd.c           

	Compute the greatest common divisor of two integers

	by: Steven Skiena
	begun: July 10, 2002
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


#include<stdio.h>
#include<math.h>


long gcd1(p,q)
long p,q;				/* integers to compute the GCD of */
{
	if (q > p) return(gcd1(q,p));


	if (q == 0) return(p);

	printf(" gcd(%d,%d) &=& gcd(%d \\mod %d, %d) = gcd(%d,%d) \n",p,q,p,q,q,q,p%q);
	return( gcd1(q, p % q) );
}

/*	Find the gcd(p,q) and x,y such that p*x + q*y = gcd(p,q)	*/

long gcd(long p, long q, long *x, long *y)
{
	long x1,y1;			/* previous coefficients */
	long g;				/* value of gcd(p,q) */

        if (q > p) return(gcd(q,p,y,x));

        if (q == 0) {
		*x = 1;
		*y = 0;
		return(p);
	}

        g = gcd(q, p%q, &x1, &y1);
	
	*x = y1;
	*y = (x1 - floor(p/q)*y1);

	return(g);
}



main() {
      long p,q;
      long gcd(), gcd2();
      long x,y,g1,g2;

      while (scanf("%d %d",&p,&q)!=EOF) {

	printf("gcd of p=%d and q=%d = %d\n",p,q,g1=gcd1(p,q));
	printf(" %d*%d + %d*%d = %d\n",p,x,q,y,g2=gcd(p,q,&x,&y));

	if (g1 != g2) printf("ERROR: GCD\n");
	if ((p*x + q*y) != g1) printf("ERROR: DIOPHONINE SOLUTION WRONG!\n");

      }
}

