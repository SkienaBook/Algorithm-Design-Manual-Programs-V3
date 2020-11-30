
#define	NMAX	1000			/* maximum number of points */

typedef struct {
	int x, y;			/* x and y coordinates of point */
} point;

typedef struct {
   int n;				/* how many points in problem? */
   point p[NMAX+1];			/* array of points */
} tsp_instance;

typedef struct {
   int n;				/* how many elements in permutation? */	
   int p[NMAX+1];			/* array if indices */
} tsp_solution;

