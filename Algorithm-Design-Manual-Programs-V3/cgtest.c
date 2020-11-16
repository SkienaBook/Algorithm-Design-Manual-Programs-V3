/*	cgtest.c        
	Driver program for computational geometry routines; give the
	basic geometric primatives a workout.
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
or http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/
*/


#include <math.h>
#include <stdio.h>

#include "geometry.h"


int main(void) {
    point p1, p2, q1, q2, i;
    line l1, l2;
    segment s1, s2;

    while (scanf("%lf %lf", &p1[X], &p1[Y]) != EOF ) {
        scanf("%lf %lf", &p2[X], &p2[Y]);
        scanf("%lf %lf", &q1[X], &q1[Y]);
        scanf("%lf %lf", &q2[X], &q2[Y]);

        points_to_segment(p1, p2, &s1);
        points_to_segment(q1, q2, &s2);

        points_to_line(p1, p2, &l1);
        points_to_line(q1, q2, &l2);

        print_segment(s1);
        print_segment(s2);

        printf("segments_intersect test\n");
        printf("%d\n", segments_intersect(s1, s2));

        printf("intersection point\n");
        intersection_point(l1, l2, i);
        print_point(i);

        printf("--------------------------------\n");
    }
    
    return 0;
}
