/*	geometry.h
	Header file for geometric data types
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




#include <stdbool.h>

#define	PI      3.1415926   /* ratio of circumference to diameter */
#define EPSILON 0.000001    /* a quantity small enough to be zero */

typedef struct {
    double a;       /* x-coefficient */
    double b;       /* y-coefficient */
    double c;       /* constant term */
} line;

#define DIMENSION  2  /* dimension of points */
#define X          0  /* x-coordinate index */
#define	Y          1  /* y-coordinate index */

typedef double point[DIMENSION];

#define MAXPOLY    200 /* maximum number of points in a polygon */

typedef struct {
    int n;              /* number of points in polygon */
    point p[MAXPOLY];   /* array of points in polygon */
} polygon;

typedef struct {
    point p1, p2;       /* endpoints of line segment */
} segment;

typedef point triangle[3];  /* triangle datatype */

typedef struct {
    int n;              /* number of triangles in triangulation */
    int t[MAXPOLY][3];  /* indicies of vertices in triangulation */
} triangulation;

typedef struct {
    point c;        /* center of circle */
    double r;       /* radius of circle */
} circle;

/*	Comparison macros  */

#define	max(A, B)		((A) > (B) ? (A) : (B))
#define min(A, B)		((A) < (B) ? (A) : (B))

void points_to_line(point p1, point p2, line *l);
void point_and_slope_to_line(point p, double m, line *l);
bool parallelQ(line l1, line l2);
bool same_lineQ(line l1, line l2);
void intersection_point(line l1, line l2, point p);
void closest_point(point p_in, line l, point p_c);
double distance(point a, point b);
void copy_point(point a, point b);
void swap_point(point a, point b);
void points_to_segment(point a, point b, segment *s);
void segment_to_points(segment s, point p1, point p2);
bool point_in_box(point p, point b1, point b2);
bool segments_intersect(segment s1, segment s2);
double signed_triangle_area(point a, point b, point c);
double triangle_area(point a, point b, point c);
bool ccw(point a, point b, point c);
bool cw(point a, point b, point c);
bool collinear(point a, point b, point c);
void print_points(point p[], int n);
void print_polygon(polygon *p);
void print_point(point p);
void print_line(line l);
void print_segment(segment s);
