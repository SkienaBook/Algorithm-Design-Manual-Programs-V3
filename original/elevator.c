/*	elevator.c

	Elevator stop optimization via dynamic programming.

	by: Steven Skiena
	begun: April 1, 2002
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


#define	NFLOORS		25	/* the height of the building in floors */
#define MAX_RIDERS	50	/* what is the capacity of the elevator? */

#define MAXINT  100007



int stops[MAX_RIDERS];		/* what floor does everyone get off at? */
int nriders;			/* number of riders */
int nstops;			/* number of allowable stops */

int m[NFLOORS+1][MAX_RIDERS];	/* dynamic programming cost table */
int p[NFLOORS+1][MAX_RIDERS];	/* dynamic programming parent table */



int min(int a, int b)
{
	if (a < b)  return(a); else return(b);
}

/*	m[i][j] denotes the cost of serving all the riders using j stops,
	the last of which is at floor i.  Zero is the originating floor.
*/

int optimize_floors()
{
	int i,j,k;		/* counters */
	int cost;		/* costs placeholder */
	int laststop;		/* the elevator's last stop */

	for (i=0; i<=NFLOORS; i++) {
		m[i][0] = floors_walked(0,MAXINT);
		p[i][0] = -1;
	}

	for (j=1; j<=nstops; j++) 
		for (i=0; i<=NFLOORS; i++) {
			m[i][j] = MAXINT;
			for (k=0; k<=i; k++) {
			     cost = m[k][j-1] - floors_walked(k,MAXINT) +
				floors_walked(k,i) + floors_walked(i,MAXINT);
			     if (cost < m[i][j]) {
			     	m[i][j] = cost;
				p[i][j] = k;
			     }    
			}
		}

	laststop = 0;
	for (i=1; i<=NFLOORS; i++) 
		if (m[i][nstops] < m[laststop][nstops])
			laststop = i;
	
	return(laststop);
}




floors_walked(int previous, int current)
{
	int nsteps=0;		/* total distance traveled */
	int i;			/* counter */

	for (i=1; i<=nriders; i++)
		if ((stops[i] > previous) && (stops[i] <= current))
			nsteps += min(stops[i]-previous, current-stops[i]);

	return(nsteps);
}


reconstruct_path(int lastfloor, int stops_to_go)
{
	if (stops_to_go > 1)
		reconstruct_path( p[lastfloor][stops_to_go], stops_to_go-1);

	printf("%d\n",lastfloor);
}

print_matrix(m)
int m[NFLOORS+1][MAX_RIDERS];
{
	int i,j;                        /* counters */

        for (j=0; j<=nstops; j++) {
                for (i=0; i<=NFLOORS; i++)
                        printf("%3d",m[i][j]);
                printf("\n");
        }
}


main()
{
	int i,j;			/* counters */
	int laststop;

	scanf("%d %d",&nriders,&nstops);


	for (i=1; i<=nriders; i++)
		scanf("%d",&(stops[i]));

        for (i=1; i<=nriders; i++)
                printf("%d\n",stops[i]);

	laststop = optimize_floors();

	print_matrix(&m);
	printf("\n");
	print_matrix(&p);

	printf("cost = %d\n",m[laststop][nstops]);

	reconstruct_path(laststop,nstops);

}
