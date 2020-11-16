/*	primes.c        

	Compute the prime factorization of an integer.

	by: Steven Skiena
	begun: February 18, 2002
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


prime_factorization(long x)
{
	long i;			/* counter */
	long c;			/* remaining product to factor */

	c = x;

	while ((c % 2) == 0) {
		printf("%ld\n",2);
		c = c / 2;
	}

	i = 3;

	while (i <= (sqrt(c)+1)) {
		if ((c % i) == 0) {
			printf("%ld\n",i);
			c = c / i;
		}
		else
			i = i + 2;
	}

	if (c > 1) printf("%ld\n",c);
}



main() {
      long p;

      while (scanf("%ld",&p)!=EOF) {

	printf("prime factorization of p=%ld \n",p);
	prime_factorization(p);

      }
}

