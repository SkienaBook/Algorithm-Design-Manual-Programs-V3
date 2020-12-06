/*	triangulate.c

	Triangulate a polygon via ear-clipping, and compute the area
	of a polygon.

	by: Steven Skiena
	begun: May 7, 2002
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


#include "bool.h"
#include "geometry.h"
#include <math.h>


triangulate(polygon *p, triangulation *t)
{
	int l[MAXPOLY], r[MAXPOLY];	/* left/right neighbor indices */
	int i;				/* counter */

	for (i=0; i<p->n; i++) {	/* initialization */
		l[i] = ((i-1) + p->n) % p->n;
		r[i] = ((i+1) + p->n) % p->n;
	}

	t->n = 0;
	i = p->n-1;
	while (t->n < (p->n-2)) {
		i = r[i];
		if (ear_Q(l[i],i,r[i],p)) {
			add_triangle(t,l[i],i,r[i],p);
			l[ r[i] ] = l[i];
			r[ l[i] ] = r[i];
		}
	}
}

add_triangle(triangulation *t, int i, int j, int k, polygon *p)
{
	int n;				/* number of triangles in t */

	n = t->n;

	t->t[n][0] = i;
	t->t[n][1] = j;
	t->t[n][2] = k;

	t->n = n + 1;
}

bool ear_Q(int i, int j, int k, polygon *p)
{
	triangle t;			/* coordinates for points i,j,k */
	int m;				/* counter */
	bool cw();

	copy_point(p->p[i],t[0]);
	copy_point(p->p[j],t[1]);
	copy_point(p->p[k],t[2]);

	if (cw(t[0],t[1],t[2])) return(FALSE);

	for (m=0; m<p->n; m++) {
		if ((m!=i) && (m!=j) && (m!=k))
			if (point_in_triangle(p->p[m],t)) return(FALSE);
	}

	return(TRUE);
}


bool point_in_triangle(point p, triangle t)
{
	int i;				/* counter */
	bool cw();

	for (i=0; i<3; i++)
		if (cw(t[i],t[(i+1)%3],p)) return(FALSE);

	return(TRUE);
}

double area_triangulation(polygon *p)
{
	triangulation t;                /* output triangulation */
	double total = 0.0;		/* total area so far */
        int i;                          /* counter */
	double triangle_area();

	triangulate(p,&t);
	for (i=0; i<t.n; i++)
		total += triangle_area(p->p[t.t[i][0]],
			p->p[t.t[i][1]], p->p[t.t[i][2]]);

	return(total);
}

double area(polygon *p)
{
	double total = 0.0;		/* total area so far */
	int i, j;			/* counters */

	for (i=0; i<p->n; i++) {
		j = (i+1) % p->n;
		total += (p->p[i][X]*p->p[j][Y]) - (p->p[j][X]*p->p[i][Y]);
	}

	return(total / 2.0);
}



main(){
	polygon p;			/* input polygon */
	triangulation t;		/* output triangulation */
	int i;				/* counter */
	double area(), area_triangulate();

	scanf("%d",&p.n);
	for (i=0; i<p.n; i++) 
		scanf("%lf %lf",&p.p[i][X],&p.p[i][Y]);

/*
	print_polygon(&p);
	triangulate(&p,&t);
	print_triangulation(&t);
*/

	printf(" area via triangulation = %f\n", area_triangulation(&p));
	printf(" area slick = %f\n", area(&p));

}

print_triangulation(triangulation *t)
{
	int i, j;			/* counters */

	for (i=0; i< t->n; i++) {
		for (j=0; j<3; j++)
                        printf(" %d ",t->t[i][j]);
/*
		for (j=0; j<3; j++)
			printf(" (%5.3f,%5.3f)",t->t[i][j][X],t->t[i][j][Y]);
*/
		printf("\n");
	}
}
