/*	distance.c

	Compute Euclidian distances

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


#define	DIMENSION	3
#include <math.h>

typedef int point[DIMENSION];

main(){
	point a={6,2,3};
	point b={6,3,4};
	double distance();

	printf("distance = %f\n",distance(a,b));
}

double distance(point a, point b)
{
	int i;
	double d=0.0;

	for (i=0; i<DIMENSION; i++)
		d = d + (a[i]-b[i]) * (a[i]-b[i]);

	return( sqrt(d) );
}
