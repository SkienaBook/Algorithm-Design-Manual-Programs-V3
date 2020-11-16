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


#define NMAX    1001    /* maximum number of points */

typedef struct {
    int x, y;    /* x and y coordinates of point */
} point;

typedef struct {
   int n;              /* how many points in problem? */
   point p[NMAX+1];    /* array of points */
} tsp_instance;

typedef struct {
   double cost;      /* lower bound on full cost solution */
   int n;            /* how many elements in permutation? */    
   int p[NMAX+1];    /* array of indices */
} tsp_solution;

double solution_cost(tsp_solution *s, tsp_instance *t);
void initialize_solution(int n, tsp_solution *s);
void copy_solution(tsp_solution *s, tsp_solution *t);
void random_solution(tsp_solution *s);
double transition(tsp_solution *s, tsp_instance *t, int i, int j);
