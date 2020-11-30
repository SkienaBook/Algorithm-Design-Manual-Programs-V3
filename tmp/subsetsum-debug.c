/*	subsetsum.c
	Solve the subset sum problem by dynamic programming

	begun: February 16, 2020
	by: Steven Skiena

	The first dimension of the table will denote the rank of the integer
	being considered, with the second dimension denoting the realizable
	sums.
*/

#include <stdio.h>
#include "bool.h"

#define	MAXN    100    /* largest n */
#define MAXSUM	10000  /* largest sum we will consider */

#define NIL     -1

/* compute whether k can be made as a subset sum from s */

/* [[[ subset_sum_cut */
bool sum[MAXN+1][MAXSUM+1];     /* table of realizable sums */
int parent[MAXN+1][MAXSUM+1];   /* table of parent pointers */

bool subset_sum(int s[], int n, int k) {
    int i, j;                     /* counters */

    sum[0][0] = TRUE;
    parent[0][0] = NIL;

    for (i = 1; i <= k; i++) {
        sum[0][i] = FALSE;
	parent[0][i] = NIL;
    }

    for (i = 1; i <= n; i++) {    /* build table */
        for (j = 0; j <= k; j++) {
		sum[i][j] = sum[i-1][j];
                parent[i][j] = NIL;

	        if ((j >= s[i-1]) && (sum[i-1][j-s[i-1]]==TRUE)) {
            		sum[i][j] = TRUE;
			parent[i][j] = j-s[i-1];
		}
        }
    }

for (i = 0; i <= n; i++) {    
   printf("i=%d  s[i]=%d : ",i,s[i]);
   for (j = 0; j <= k; j++) {
	printf(" %d ",sum[i][j]);
   }
   printf("\n");
}

for (i = 0; i <= n; i++) { 
   printf("i=%d  s[i]=%d : ",i,s[i]);
   for (j = 0; j <= k; j++) {
        printf(" %d ",parent[i][j]);
   }
   printf("\n");
}

    return(sum[n][k]);
}
/* ]]] */

void report_subset(int n, int k) {
   if (k == 0) {
	return;
   }

   if (n < 0) {
	printf("trouble at n=%d k=%d\n",n,k);
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


