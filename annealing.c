/*	Simulated Annealing Implementation

	These routines provide a fairly generic implementation of
	simulated annealing, starting from my older code to optimize
	selective assembly.
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


#include <stdio.h>
#include <stdbool.h>

#include "annealing.h"      /* type declarations for SA */
#include "random.h"

int solution_count;         /* how many solutions evaluated */


/***********************************************************************/

void solution_count_update(tsp_solution *s, tsp_instance *t) {
    solution_count = solution_count+1;
    if ((solution_count==1) ||((solution_count % PRINT_FREQUENCY) == 0)) {
        printf("%d %7.1f\n", solution_count, solution_cost(s, t));
    }
}

/*  Use random sampling to provide a heuristic solution to a given
    optimization problem.
*/
/* [[[ random_sampling_cut */
void random_sampling(tsp_instance *t, int nsamples, tsp_solution *s) {
    tsp_solution s_now;             /* current tsp solution */
    double best_cost;               /* best cost so far */
    double cost_now;                /* current cost */
    int i;                          /* counter */

    initialize_solution(t->n, &s_now);
    best_cost = solution_cost(&s_now, t);
    copy_solution(&s_now, s);

    for (i = 1; i <= nsamples; i++) {
        random_solution(&s_now);
        cost_now = solution_cost(&s_now, t);

        if (cost_now < best_cost) {
            best_cost = cost_now;
            copy_solution(&s_now, s);
        }

        solution_count_update(&s_now, t);
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
        stuck = true;
        for (i = 1; i < t->n; i++) {
            for (j = i + 1; j <= t->n; j++) {
                delta = transition(s, t, i, j);
                if (delta < 0) {
                    stuck = false;
                    cost = cost + delta;
                } else {
                    transition(s, t, j, i);
                }
                solution_count_update(s, t);
            }
        }
    } while (stuck);
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
    int x, y;                       /* pair of items to swap */
    int i, j;                       /* counters */
    bool accept_win, accept_loss;   /* conditions to accept transition */
    double temperature;             /* the current system temp */
    double current_value;           /* value of current state */
    double start_value;             /* value at start of loop */
    double delta;                   /* value after swap */
    double exponent;                /* exponent for energy funct */

    temperature = INITIAL_TEMPERATURE;

    initialize_solution(t->n, s);
    current_value = solution_cost(s, t);

    for (i = 1; i <= COOLING_STEPS; i++) {
        temperature *= COOLING_FRACTION;

        start_value = current_value;		

        for (j = 1; j <= STEPS_PER_TEMP; j++) {
            /* pick indices of elements to swap */
            x = random_int(1, t->n);
            y = random_int(1, t->n);

            delta = transition(s, t, x, y);
            accept_win = (delta < 0);       /* did swap reduce cost? */

            exponent = (-delta / current_value) / (K * temperature);
            accept_loss = (exp(exponent) > random_float(0,1));

            if (accept_win || accept_loss) {
                current_value += delta;
            } else {
                transition(s, t, x, y);     /* reverse transition */
            }
            solution_count_update(s, t);
        }

        if (current_value < start_value) {  /* rerun at this temp */
            temperature /= COOLING_FRACTION;
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
