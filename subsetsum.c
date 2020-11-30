/*	subsetsum.c

	Solve the subset sum problem by dynamic programming

	Note: the first dimension of the table will denote the rank of the integer
	being considered, with the second dimension denoting the realizable sums.
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



#include <stdio.h>
#include <stdbool.h>

#define	MAXN    100    /* largest n */
#define MAXSUM	10000  /* largest sum we will consider */

#define NIL     -1

/* compute whether k can be made as a subset sum from s */

/* [[[ subset_sum_cut */
bool sum[MAXN+1][MAXSUM+1];     /* table of realizable sums */
int parent[MAXN+1][MAXSUM+1];   /* table of parent pointers */

bool subset_sum(int s[], int n, int k) {
    int i, j;                     /* counters */

    sum[0][0] = true;
    parent[0][0] = NIL;

    for (i = 1; i <= k; i++) {
        sum[0][i] = false;
	parent[0][i] = NIL;
    }

    for (i = 1; i <= n; i++) {    /* build table */
        for (j = 0; j <= k; j++) {
	    sum[i][j] = sum[i-1][j];
            parent[i][j] = NIL;

	    if ((j >= s[i-1]) && (sum[i-1][j-s[i-1]]==true)) {
		sum[i][j] = true;
		parent[i][j] = j-s[i-1];
	    }
        }
    }

    return(sum[n][k]);
}
/* ]]] */


/* [[[ subset_sum_report_cut */
void report_subset(int n, int k) {
   if (k == 0) {
	return;
   }

   if (parent[n][k] == NIL) {
	report_subset(n-1,k);
   }
   else {
	report_subset(n-1,parent[n][k]);
   	printf(" %d ",k-parent[n][k]);
   }
}
/* ]]] */

int main(void) {
    int r, n, k, i, s[MAXN+1], m, j;

    scanf("%d",&m);

    for (j=0; j<m; j++) {
    
    	scanf("%d %d", &n, &k);
        printf("n=%d  k=%d \n",n,k);

    	for (i=0; i<n; i++) {
        	scanf("%d", &s[i]);
		printf(" %d ",s[i]);
    	}


    	printf("\n Is %d realizable: %d\n", k, r=subset_sum(s,n,k));

    	if (r) report_subset(n,k);
    	printf("\n\n");

    }

    return 0;
}


