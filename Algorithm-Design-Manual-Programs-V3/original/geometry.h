/*	geometry.h
	Header file for geometric data types

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


#define	PI	3.1415926	/* ratio of circumference to diameter */
#define EPSILON	0.000001	/* a quantity small enough to be zero */

typedef struct {
	double a;		/* x-coefficient */
	double b;		/* y-coefficient */
	double c;		/* constant term */
} line;

#define DIMENSION	2	/* dimension of points */
#define X		0	/* x-coordinate index */
#define	Y		1	/* y-coordinate index */

typedef double point[DIMENSION];

#define MAXPOLY		200	/* maximum number of points in a polygon */

typedef struct {
	int n;			/* number of points in polygon */
	point p[MAXPOLY];	/* array of points in polygon */
} polygon;


typedef struct {
	point p1,p2;		/* endpoints of line segment */
} segment;

typedef point triangle[3];	/* triangle datatype */

typedef struct {
	int n;			/* number of triangles in triangulation */
	int t[MAXPOLY][3];	/* indicies of vertices in triangulation */
} triangulation;

typedef struct {
	point c;		/* center of circle */
	double r;		/* radius of circle */
} circle;


/*	Comparison macros 	*/

#define	max(A, B)		((A) > (B) ? (A) : (B))
#define min(A, B)		((A) < (B) ? (A) : (B))

