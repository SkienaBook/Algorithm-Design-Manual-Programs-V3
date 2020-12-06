/*	cgtest.c        

	Driver program for computational geometry routines; give the
	basic geometric primatives a workout.

	begun: July 23, 2002
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


#include "bool.h"
#include "geometry.h"
#include <math.h>
#include <stdio.h>



main()
{
	point p1,p2,q1,q2,i;
	line l1,l2;
	segment s1,s2,s3,s4;

	while ( scanf("%lf %lf",&p1[X],&p1[Y]) != EOF ) {
        	scanf("%lf %lf",&p2[X],&p2[Y]);
		scanf("%lf %lf",&q1[X],&q1[Y]);
		scanf("%lf %lf",&q2[X],&q2[Y]);

/*
	        print_point(p1);
		print_point(p2);
		print_point(q1);
		print_point(q2);
*/

		points_to_segment(p1,p2,&s1);
		points_to_segment(q1,q2,&s2);

                points_to_line(p1,p2,&l1);
                points_to_line(q1,q2,&l2);

		print_segment(s1);
		print_segment(s2);
		
/*
		printf("slope and line tests\n");
		point_and_slope_to_line(p1,-l1.a,&l3);
		print_line(l3);
                point_and_slope_to_line(p2,-l1.a,&l3);
                print_line(l3);
                point_and_slope_to_line(q1,-l2.a,&l3);
                print_line(l3);
                point_and_slope_to_line(q2,-l2.a,&l3);
                print_line(l3);
*/

		printf("segments_intersect test\n");
		printf("%d\n", segments_intersect(s1,s2));

		printf("intersection point\n");
		intersection_point(l1,l2,i);
		print_point(i);

/*
		printf("closest point\n");
		closest_point(p1,l1,i);
		print_point(i);
                closest_point(p2,l1,i);
                print_point(i);
                closest_point(q1,l1,i);
                print_point(i);
                closest_point(q2,l1,i);
                print_point(i);
                closest_point(p1,l2,i);
                print_point(i);
                closest_point(p2,l2,i);
                print_point(i);
                closest_point(q1,l2,i);
                print_point(i);
                closest_point(q2,l2,i);
                print_point(i);
*/


		printf("--------------------------------\n");
	}


}
