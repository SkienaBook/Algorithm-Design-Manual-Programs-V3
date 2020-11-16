/*	partition.c
	Optimally balance partitions using dynamic programming 

	begun: August 14, 2006
	by: Steven Skiena
*/

#define	MAXN	45		/* largest number of books */
#define MAXK	10		/* largest number of dividers */
#define MAXINT	100000		/* infinity */


max(int a, int b)
{
	return( (a > b) ? a : b );
} 

read_partition(int s[], int *n, int *k)
{
	int i;			/* counter */

	scanf("%d %d\n",n,k);
	for (i=1; i<=*n; i++)
		scanf("%d\n",&(s[i]));
}

print_books(int s[], int start, int end)
{
	int i;			/* counter */

	printf("\{");
	for (i=start; i<=end; i++) printf(" %d ",s[i]);
	printf("}\n");
}

print_matrix(int m[MAXN+1][MAXK+1], int n, int k)
{
	int i,j;		/* counters */


	printf("\n");
	for (i=1; i<=n; i++) {
		for (j=1; j<=k; j++) 
			printf(" %d ",m[i][j]);
		printf("\n");
	}
}

reconstruct_partition(int s[],int d[MAXN+1][MAXK+1], int n, int k)
{
	if (k==1)
		print_books(s,1,n);
	else {
		reconstruct_partition(s,d,d[n][k],k-1);
		print_books(s,d[n][k]+1,n);
	}
}

partition(int s[], int n, int k)
{
	int p[MAXN+1];				/* prefix sums array */
	int m[MAXN+1][MAXK+1];			/* DP table for values */
	int d[MAXN+1][MAXK+1];			/* DP table for dividers */
	int cost;				/* test split cost */
	int i,j,x;				/* counters */

	p[0] = 0;				/* construct prefix sums */
	for (i=1; i<=n; i++) p[i]=p[i-1]+s[i];

	for (i=1; i<=n; i++) m[i][1] = p[i];	/* initialize boundaries */
	for (j=1; j<=k; j++) m[1][j] = s[1];

	for (i=2; i<=n; i++)			/* evaluate main recurrence */
		for (j=2; j<=k; j++) {
			m[i][j] = MAXINT;
			for (x=1; x<=(i-1); x++) {
				cost = max(m[x][j-1], p[i]-p[x]);
				if (m[i][j] > cost) {
					m[i][j] = cost;
					d[i][j] = x;
				}
			}
		}

/*
	print_matrix(m,n,k);
	print_matrix(d,n,k);
*/
	reconstruct_partition(s,d,n,k);		/* print book partition */
}



main()
{
	int s[MAXN+1];			/* book thicknesses to partition */
	int n;				/* how many books? */
	int k;				/* how many partitions? */

	read_partition(s,&n,&k);
	partition(s,n,k);

}

