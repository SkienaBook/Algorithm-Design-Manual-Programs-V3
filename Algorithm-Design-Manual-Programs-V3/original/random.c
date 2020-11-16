/*
	random.c

	Compute random numbers within given ranges

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
#include <math.h>
#include <stdlib.h>


/**************************************************************************/

/*      These functions generate random numbers in the designated ranges */

random_int(low,high)
int low,high;                                   /*lower/upper bounds on numb*/
{
        int rand();
        int i,j,r;                                      /*random number*/

        i = RAND_MAX / (high-low+1);
        i *= (high-low+1);
        while ((j = rand()) >=i) continue;
        r = (j % (high-low+1)) + low;
/*printf("rand=%d RAND_MAX=%d \n",r,RAND_MAX);*/
/*printf("rand=%d low=%d high=%d \n",r,low,high);*/
        if ((r < low) || (r > high))
                printf("Error: random integer %d out of range [%d,%d]\n",
                        r,low,high);

        return(r);
}
/*      Construct a random permutation of the $n$ elements of the
        given array.
*/

random_permutation(a,n)
int a[];
int n;
{
        int i;

        for (i=n; i>1; i--) 
                swap(&a[i-1],&a[random_int(0,i-1)]);
}

swap(a,b)
int *a,*b;
{
        int x;

        x = *a;
        *a = *b;
        *b = x;
}


double random_float(low,high)
int low,high;                                   /*lower/upper bounds on numb*/
{
        int rand();
        double i,j;                             /* avoid arithmetic trouble */
        double r;                                  /*random number*/

        i = RAND_MAX / (high-low);
        i *= (high-low);
        while ((j = rand()) >=i) continue;
        r = (j/i) * (high-low) + low;

        if ((r < low) || (r > high))
                printf("ERROR: random real %f out of range [%d,%d]\n",
                        r,low,high);

        return(r);

}

