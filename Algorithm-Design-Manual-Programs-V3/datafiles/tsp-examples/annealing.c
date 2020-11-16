/*	Steven Skiena
	8/7/06
	Simulated Annealing Implementation

	These routines provide a fairly generic implementation of
	simulated annealing, starting from my older code to optimize
	selective assembly.

*/
#include <stdio.h>

#include "annealing.h"      /* type declarations for SA */
#include "bool.h"
#include "random.h"

int solution_count;         /* how many solutions evaluated */


/***********************************************************************/

void solution_count_update(tsp_solution *s, tsp_instance *t) {
    solution_count = solution_count+1;
    if ((solution_count % PRINT_FREQUENCY) == 0) {
        printf("%d %7.1f\n", solution_count, solution_cost(s, t));
    }
}

/*  Use random sampling to provide a heuristic solution to a given
    optimization problem.
*/
/* [[[ random_sampling_cut */
void random_sampling(tsp_instance *t, int nsamples, tsp_solution *bestsol) {
    tsp_solution s;                 /* current tsp solution */
    double best_cost;               /* best cost so far */
    double cost_now;                /* current cost */
    int i;                          /* counter */

    initialize_solution(t->n, &s);
    best_cost = solution_cost(&s, t);
    copy_solution(&s, bestsol);

    for (i = 1; i <= nsamples; i++) {
        random_solution(&s);
        cost_now = solution_cost(&s, t);

        if (cost_now < best_cost) {
            best_cost = cost_now;
            copy_solution(&s, bestsol);
        }

        solution_count_update(&s, t);
    }
}
/* ]]] */

/*  Use hill climbing to provide a heuristic solution to a given
    optimization problem.
*/

/* [[[ hill_climbing_cut */
void hill_climbing(tsp_instance *t, tsp_solution *s) {
    double cost;            /* best cost so far */
    double delta;           /* swap cost */
    int i, j;               /* counters */
    bool stuck;             /* did I get a better solution? */

    initialize_solution(t->n, s);
    random_solution(s);
    cost = solution_cost(s, t);

    do {
        stuck = TRUE;
        for (i = 1; i < t->n; i++) {
            for (j = i + 1; j <= t->n; j++) {
                delta = transition(s, t, i, j);
                if (delta < 0) {
                    stuck = FALSE;
                    cost = cost + delta;
                } else {
                    transition(s, t, j, i);
                }
                solution_count_update(s, t);
            }
        }
    } while (stuck == TRUE);

}
/* ]]] */

void repeated_hill_climbing(tsp_instance *t, int nsamples, tsp_solution *bestsol) {
    tsp_solution s;                 /* current tsp solution */
    double best_cost;               /* best cost so far */
    double cost_now;                /* current cost */
    int i;                          /* counter */

    initialize_solution(t->n, &s);
    best_cost = solution_cost(&s, t);
    copy_solution(&s, bestsol);

    for (i = 1; i <= nsamples; i++) {
        hill_climbing(t, &s);
        cost_now = solution_cost(&s, t);
        if (cost_now < best_cost) {
            best_cost = cost_now;
            copy_solution(&s, bestsol);
        }
    }
}

/*	These routines implement simulated annealing.  Pairs of components
	of the same type will be swapped at random, and the new arrangment
	accepted either if (1) it is an improvement, or (2) the penalty is
	less than a random number, which is a function of the temperature
	of the system.

	We are seeking to *minimize* the current_value.
*/

/* [[[ anneal_cut */
void anneal(tsp_instance *t, tsp_solution *s) {
    int i1, i2;                 /* pair of items to swap */
    int i, j;                   /* counters */
    double temperature;         /* the current system temp */
    double current_value;       /* value of current state */
    double start_value;         /* value at start of loop */
    double delta;               /* value after swap */
    double merit, flip;         /* hold swap accept conditions */
    double exponent;            /* exponent for energy funct */

    temperature = INITIAL_TEMPERATURE;

    initialize_solution(t->n, s);
    current_value = solution_cost(s, t);

    for (i = 1; i <= COOLING_STEPS; i++) {
        temperature *= COOLING_FRACTION;

        start_value = current_value;		

        for (j = 1; j <= STEPS_PER_TEMP; j++) {
            /* pick indices of elements to swap */
            i1 = random_int(1, t->n);
            i2 = random_int(1, t->n);

            delta = transition(s, t, i1, i2);

            flip = random_float(0, 1);
            exponent = (-delta / current_value) / (K * temperature);
            merit = pow(E, exponent);

            if (delta < 0) {            /*ACCEPT-WIN*/
                current_value = current_value + delta;

                if (TRACE_OUTPUT == TRUE) {
                    printf("swap WIN %d--%d value %f  temp=%f i=%d j=%d\n",
                    i1, i2, current_value, temperature, i, j);
                }
            } else { 
                if (merit > flip) {     /*ACCEPT-LOSS*/
                    current_value = current_value + delta;
                    if (TRACE_OUTPUT == TRUE) {
                        printf("swap LOSS %d--%d value %f merit=%f flip=%f i=%d j=%d\n",
                        i1, i2, current_value, merit, flip, i, j);
                    }
                } else {                /* REJECT */
                    transition(s, t, i1, i2);
                } 
            }
            solution_count_update(s, t);
        }
        if ((current_value-start_value) < 0.0) { /* rerun at this temp */
            temperature /= COOLING_FRACTION;
            if (TRACE_OUTPUT == TRUE) {
                printf("rerun at temperature %f\n", temperature);
            }
        }
    }
}
/* ]]] */

void repeated_annealing(tsp_instance *t, int nsamples, tsp_solution *bestsol) {
    tsp_solution s;                 /* current tsp solution */
    double best_cost;               /* best cost so far */
    double cost_now;                /* current cost */
    int i;                          /* counter */

    initialize_solution(t->n, &s);
    best_cost = solution_cost(&s, t);
    copy_solution(&s, bestsol);

    for (i = 1; i <= nsamples; i++) {
        anneal(t, &s);
        cost_now = solution_cost(&s, t);
        if (cost_now < best_cost) {
            best_cost = cost_now;
            copy_solution(&s, bestsol);
        }
    }
}
