
/*	superman.c

	Compute Superman's flight path -- geometry example 

	by: Steven Skiena
	begin: April 11, 2002
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


#define	MAXN	100		/* maximum number of circles */

#include "bool.h"
#include "geometry.h"
#include <math.h>

point s;			/* Superman's initial position */
point t;			/* target position */
int ncircles;			/* number of circles */
circle c[MAXN];			/* circles data structure */

superman()
{
	line l;			/* line from start to target position */
	point close;		/* closest point */
	double d;		/* distance from circle-center */
	double xray = 0.0;	/* length of intersection with circles */
	double around = 0.0;	/* length around circular arcs */
	double angle;		/* angle subtended by arc */
	double travel;		/* total travel distance */
	int i;			/* counter */
	double asin(), sqrt();
	double distance();

	points_to_line(s,t,&l);

	for (i=1; i<=ncircles; i++) {
		closest_point(c[i].c,l,close);
		d = distance(c[i].c,close);
		if ((d>=0) && (d < c[i].r) && point_in_box(close,s,t)) {
			xray += 2*sqrt(c[i].r*c[i].r - d*d);
			angle = acos(d/c[i].r);
			around += ((2*angle)/(2*PI)) * (2*PI*c[i].r);
printf("circle %d (%7.3lf,%7.3lf,%7.3lf) is %7.3lf away from l, xray=%7.3lf around=%7.3lf angle=%7.3lf.\n",
i,c[i].c[X],c[i].c[Y],c[i].r,d,xray,around,angle);
		}
	}

	travel = distance(s,t) - xray + around;
	printf("Superman sees through %7.3lf units, and flies %7.3lf units\n",
		xray, travel);
}


main(){
	int i;			/* counter */

	scanf("%lf %lf",&s[X],&s[Y]);
	scanf("%lf %lf",&t[X],&t[Y]);
	scanf("%d",&ncircles);
	for (i=1; i<=ncircles; i++)
		scanf("%lf %lf %lf",&c[i].c[X],&c[i].c[Y],&c[i].r);

        printf("%7.3lf %7.3lf\n",s[X],s[Y]);
        printf("%7.3lf %7.3lf\n",t[X],t[Y]);
        printf("%d\n",ncircles);
        for (i=1; i<=ncircles; i++)
                printf("%7.3lf %7.3lf %7.3lf\n",c[i].c[X],c[i].c[Y],c[i].r);

	superman();
}
