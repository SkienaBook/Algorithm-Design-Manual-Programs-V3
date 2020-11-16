/*	sorting.c
	Implementations of primary sorting algorithms 

	by: Steven Skiena
	begun: February 5, 2002

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

#define NELEM	100		/* size of test arrays */

/*	Swap the ith and jth elements of array s.	*/

newswap(int s[], int i, int j)
{
	int tmp;		/* placeholder */

	tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}

insertion_sort(int s[], int n)
{
	int i,j;		/* counters */

	for (i=1; i<n; i++) {
		j=i;
		while ((j>0) && (s[j] < s[j-1])) {
			swap(&s[j],&s[j-1]);
			j = j-1;
		}
	}
}


selection_sort(int s[], int n)
{
        int i,j;                /* counters */
	int min;		/* index of minimum */

        for (i=0; i<n; i++) {
                min=i;
		for (j=i+1; j<n; j++) 
			if (s[j] < s[min]) min=j;
		swap(&s[i],&s[min]);
        }
}

/*	quicksort array s from the index l to index h.	*/

quicksort(int s[], int l, int h)
{
	int p;			/* index of partition */

	if ((h-l)>0) {
		p = partition(s,l,h);
		quicksort(s,l,p-1);
		quicksort(s,p+1,h);
	}
}

int partition(int s[], int l, int h)
{
	int i;			/* counter */
	int p;			/* pivot element index */
	int firsthigh;		/* divider position for pivot element */

	p = h;
	firsthigh = l;
	for (i=l; i<h; i++) 
		if (s[i] < s[p]) {
			swap(&s[i],&s[firsthigh]);
			firsthigh ++;
		}
	swap(&s[p],&s[firsthigh]);

	return(firsthigh);
}



main()
{
	int s[NELEM+2];
	int n;
	int i,j;			/* counters */

	for (i=0; i<NELEM; i++) s[i] = i;
	random_permutation(s,NELEM);

/*
	for (i=0; i<NELEM; i++) printf("%d ",s[i]);
	printf("\n");
*/

	insertion_sort(s,NELEM);

        for (i=0; i<NELEM; i++) printf("%d ",s[i]);
        printf("\n");

        for (i=0; i<NELEM; i++) s[i] = i;
        random_permutation(s,NELEM);

/*
        for (i=0; i<NELEM; i++) printf("%d ",s[i]);
        printf("\n");
*/

	selection_sort(s,NELEM);

        for (i=0; i<NELEM; i++) printf("%d ",s[i]);
        printf("\n");

        for (i=0; i<NELEM; i++) s[i] = i;
        random_permutation(s,NELEM);

/*
        for (i=0; i<NELEM; i++) printf("%d ",s[i]);
        printf("\n");
*/

	quicksort(s,0,NELEM-1);

	for (i=0; i<NELEM; i++) printf("%d ",s[i]);
        printf("\n");

}

