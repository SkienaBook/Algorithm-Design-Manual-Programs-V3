/*	Header for Simulated Annealing Package

	These are the global variables needed for the system.
	The parameters which are most likely to be needed to
	modify in adapting it to another problem are at the top
	of the file.
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
#include <stdlib.h>

#include "tsp.h"

#define TRACE_OUTPUT    FALSE        /* print the swaps as they happen */
#define PRINT_FREQUENCY 10000        /* how often we report progress */


/**************** Simulated Annealing Constants **************************/

#define REPEAT_COUNT        1	/* how many solution attempts do you
                                   want?  More than 1 enables you to
                                   eyeball the output and pick the
                                   best.  If you are getting stuck in
                                   local optima, this good to try. */

#define	INITIAL_TEMPERATURE	1   /* start temperature -- probably
                                   leave intact */

#define COOLING_STEPS       1000   /* how many times do we cool -- make
                                   higher to improve quality, lower to
                                   speed the program up.  Move in
                                   tandem with the COOLING_FRACTION */

#define COOLING_FRACTION    0.998 /* how much to cool each time -- make
                                    higher to improve quality, lower to
                                    speed the program up. */

#define STEPS_PER_TEMP      1000 /* lower makes it faster, higher makes
                                    it potentially better. */

#define E                   2.718/* number e -- probably leave intact*/

#define K                   0.01 /* problem specific Boltzman's constant
                                    May have to adjust if your global
                                    value function changes the sizes
                                    of the numbers it produces.  It is
                                    important that jumps seem random at
                                    the begining of the run, and rare
                                    at the end of a run, and this is
                                    a knob to tweak that. */

/*=========================================================================*/

/*  The stuff below is less likely to change in adapting to new 
    problems, but look for yourself before leaping.
*/

#define ERROR       "ERROR" /* string denoting error id */
#define ERROR_VALUE	0.0	    /* float denoting error value */

void repeated_annealing(tsp_instance *t, int nsamples, tsp_solution *bestsol);
void repeated_hill_climbing(tsp_instance *t, int nsamples, tsp_solution *bestsol);
void random_sampling(tsp_instance *t, int nsamples, tsp_solution *bestsol);
