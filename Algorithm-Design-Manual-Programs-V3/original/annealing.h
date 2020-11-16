/*	Steven Skiena
	Header for Simulated Annealing Package

	These are the global variables needed for the system.
	The parameters which are most likely to be needed to
	modify in adapting it to another problem are at the top
	of the file.
*/

	

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define TRACE_OUTPUT	FALSE		/* print the swaps as they happen */

#define PRINT_FREQUENCY 10000             /* how often we report progress */



/**************** Simulated Annealing Constants **************************/

#define REPEAT_COUNT		1	/* how many solution attempts do you
					   want?  More than 1 enables you to
					   eyeball the output and pick the
					   best.  If you are getting stuck in
					   local optima, this good to try. */

#define	INITIAL_TEMPERATURE	1	/* start temperature -- probably
					   leave intact */

#define COOLING_STEPS		500	/* how many times do we cool -- make
					   higher to improve quality, lower to
					   speed the program up.  Move in
					   tandem with the COOLING_FRACTION */

#define COOLING_FRACTION	0.97	/* how much to cool each time -- make
					   higher to improve quality, lower to
					   speed the program up. */

#define STEPS_PER_TEMP		1000	/* lower makes it faster, higher makes
					   it potentially better. */

#define E			2.718	/* number e -- probably leave intact*/

#define K			0.01	/* problem specific Boltzman's constant
					   May have to adjust if your global
					   value function changes the sizes
					   of the numbers it produces.  It is
					   important that jumps seem random at
					   the begining of the run, and rare
					   at the end of a run, and this is
					   a knob to tweak that. */

/*=========================================================================*/

/*	The stuff below is less likely to change in adapting to new 
	problems, but look for yourself before leaping.
*/

#define ERROR		"ERROR"		/* string denoting error id */
#define ERROR_VALUE	0.0		/* float denoting error value */


