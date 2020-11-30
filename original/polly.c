/*	polly.c

	Rank the desirability of suitors -- sorting example.

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


#define NAMELENGTH	30		/* maximum length of name */
#define NSUITORS	100		/* maximum number of suitors */

#define BESTHEIGHT	180		/* best height in centimeters */
#define BESTWEIGHT	75		/* best weight in kilograms */

#include <stdio.h>
#include <string.h>

typedef struct {
	char first[NAMELENGTH];		/* suitor's first name */
	char last[NAMELENGTH];          /* suitor's last name */
	int height;			/* suitor's height */
	int weight;			/* suitor's weight */
} suitor;


suitor suitors[NSUITORS];		/* database of suitors */
int nsuitors;				/* number of suitors */

read_suitors()
{
	char first[NAMELENGTH], last[NAMELENGTH];
	int height, weight;

	nsuitors = 0;

	while (scanf("%s %s %d %d\n",suitors[nsuitors].first,
		suitors[nsuitors].last,&height,&weight) != EOF) {
			
		suitors[nsuitors].height = abs(height - BESTHEIGHT);
		if (weight > BESTWEIGHT)
			suitors[nsuitors].weight = weight - BESTWEIGHT;
		else
			suitors[nsuitors].weight = - weight;

		nsuitors ++;
	}
}


main()
{
	int i;				/* counter */
	int suitor_compare();

	read_suitors();

	qsort(suitors, nsuitors, sizeof(suitor), suitor_compare);

	for (i=0; i<nsuitors; i++) 
		printf("%s, %s\n",suitors[i].last, suitors[i].first);
}

int suitor_compare(suitor *a, suitor *b)
{
	int result;			/* result of comparsion */

        if (a->height < b->height) return(-1);
        if (a->height > b->height) return(1);

	if (a->weight < b->weight) return(-1);
	if (a->weight > b->weight) return(1);

	if ((result=strcmp(a->last,b->last)) != 0) return result;

	return(strcmp(a->first,b->first));
}

