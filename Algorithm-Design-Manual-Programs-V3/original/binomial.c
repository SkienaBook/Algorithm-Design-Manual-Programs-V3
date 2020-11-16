/*	binomial.c
	Compute the binomial coefficients using dynamic programming 

	begun: February 10, 2002
	by: Steven Skiena
*/

#define	MAXN	100		/* largest n or m */

long binomial_coefficient(n,m)
int n,m;			/* computer n choose m */
{
	int i,j;		/* counters */
	long bc[MAXN][MAXN];	/* table of binomial coefficient values */

	for (i=0; i<=n; i++) bc[i][0] = 1;

	for (j=0; j<=n; j++) bc[j][j] = 1;


	for (i=1; i<=n; i++)
		for (j=1; j<i; j++)
			bc[i][j] = bc[i-1][j-1] + bc[i-1][j];

	return( bc[n][m] );
}

main()
{
	int a, b;
	long binomial_coefficient();

	while (1) {
		scanf("%d %d",&a,&b);
		printf("%d\n",binomial_coefficient(a,b));
	}
}

