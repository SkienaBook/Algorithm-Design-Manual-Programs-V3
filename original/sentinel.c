/*
	sentinel.c

	Example search program using sentinels

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

#define MAXINT	1000000
int a[100];

main() {
	int i,n, x;

	for (i=1; i<=50; i++) a[i]=i;
	n=50;
	x = -1;

        i = n;
        while ((a[i]>=x) && (i>=1)) {
		a[i] = a[i-1];
		i=i-1;
	}
        a[i+1] = x;

	printf("without sentinel, i=%d a[1]=%d\n",i,a[1]);
	for (i=1; i<=10; i++) printf("%d ",a[i]);
	x = -2;

        i = n;
        a[0] = - MAXINT;
        while (a[i] >= x) {
		a[i] = a[i-1];
		i=i-1;
	}
        a[i+1] = x;

	printf("\nwith sentinel, i=%d a[1]=%d\n",i,a[1]);
        for (i=1; i<=10; i++) printf("%d ",a[i]);


}

