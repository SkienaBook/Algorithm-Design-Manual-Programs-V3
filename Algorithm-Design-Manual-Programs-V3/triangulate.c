/*    triangulate.c

    Triangulate a polygon via ear-clipping, and compute the area of a polygon.
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



#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "geometry.h"

void add_triangle(triangulation *t, int i, int j, int k, polygon *p) {
    int n;    /* number of triangles in t */

    n = t->n;

    t->t[n][0] = i;
    t->t[n][1] = j;
    t->t[n][2] = k;

    t->n = n + 1;
}

bool point_in_triangle(point p, triangle t) {
    int i;    /* counter */

    for (i = 0; i < 3; i++) {
        if (cw(t[i], t[(i + 1 ) % 3], p)) {
            return(false);
        }
    }

    return(true);
}

bool ear_Q(int i, int j, int k, polygon *p) {
    triangle t;    /* coordinates for points i,j,k */
    int m;         /* counter */

    copy_point(p->p[i], t[0]);
    copy_point(p->p[j], t[1]);
    copy_point(p->p[k], t[2]);

    if (cw(t[0], t[1], t[2])) {
        return(false);
    }

    for (m = 0; m < p->n; m++) {
        if ((m != i) && (m != j) && (m != k)) {
            if (point_in_triangle(p->p[m], t)) {
                return(false);
            }
        }
    }

    return(true);
}

void triangulate(polygon *p, triangulation *t) {
    int l[MAXPOLY], r[MAXPOLY];    /* left/right neighbor indices */
    int i;                         /* counter */

    for (i = 0; i < p->n; i++) {    /* initialization */
        l[i] = ((i - 1) + p->n) % p->n;
        r[i] = ((i + 1) + p->n) % p->n;
    }

    t->n = 0;
    i = p->n-1;
    while (t->n < (p->n - 2)) {
        i = r[i];
        if (ear_Q(l[i], i,r[i], p)) {
            add_triangle(t, l[i], i, r[i], p);
            l[r[i]] = l[i];
            r[l[i]] = r[i];
        }
    }
}

double area_triangulation(polygon *p) {
    triangulation t;                /* output triangulation */
    double total = 0.0;             /* total area so far */
    int i;                          /* counter */

    triangulate(p, &t);
    for (i = 0; i < t.n; i++) {
        total += triangle_area(p->p[t.t[i][0]], 
        	                   p->p[t.t[i][1]], p->p[t.t[i][2]]);
    }

    return(total);
}

double area(polygon *p) {
    double total = 0.0;    /* total area so far */
    int i, j;              /* counters */

    for (i = 0; i < p->n; i++) {
        j = (i + 1) % p->n;
        total += (p->p[i][X] * p->p[j][Y]) - (p->p[j][X] * p->p[i][Y]);
    }

    return(total / 2.0);
}

int main(void) {
    polygon p;           /* input polygon */
    int i;               /* counter */

    scanf("%d", &p.n);
    for (i = 0; i < p.n; i++) { 
        scanf("%lf %lf", &p.p[i][X], &p.p[i][Y]);
    }

    printf(" area via triangulation = %f\n", area_triangulation(&p));
    printf(" area slick = %f\n", area(&p));

    return 0;
}

void print_triangulation(triangulation *t) {
    int i, j;    /* counters */

    for (i = 0; i < t->n; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %d ", t->t[i][j]);
        }
        printf("\n");
    }
}
