/*    suduku.c

    A backtracking program to solve Seduku
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



#include <stdio.h>
#include <string.h>

#include <stdbool.h>

#define BASED       3                     /* base dimension, 3*3 blocks */
/* [[[ sudoku_objects_cut */
#define DIMENSION   9                     /* 9*9 board */
#define NCELLS      DIMENSION*DIMENSION   /* 81 cells in 9-by-9-board */
#define MAXCANDIDATES   DIMENSION+1       /* max digit choices per cell */

bool finished = false;

typedef struct {
    int x, y;     /* row and column coordinates of square */
} point;

typedef struct {
   int m[DIMENSION+1][DIMENSION+1];    /* board contents */
   int freecount;                      /* open square count */
   point move[NCELLS+1];               /* which cells have we filled? */
} boardtype;
/* ]]] */

extern bool finished;    /* solution found, stop search */

int steps;               /* how many total move insertions? */

bool fast;               /* fast or slow nextmove algorithm? */
bool smart;              /* quickly test for unfillable squares? */

/**********************************************************************/

void possible_values(point p, boardtype *board, bool possible[]) {
    int x, y;          /* square to fill */
    int i, j;          /* counters */
    int xlow, ylow;    /* origin of box with (x,y) */
    bool init;         /* is anything/everthing possible? */

    x = p.x;
    y = p.y;

    if ((board->m[x][y] != 0) || ((x < 0) || (y < 0))) {
        init = false;
    } else {
        init = true;
    }

    for (i = 1; i <= DIMENSION; i++) {
        possible[i] = init;
    }

    for (i = 0; i < DIMENSION; i++) {
        if (board->m[x][i] != 0) {
            possible[board->m[x][i]] = false;
        }
    }

    for (i = 0; i < DIMENSION; i++) {
        if (board->m[i][y] != 0) {
            possible[board->m[i][y]] = false;
        }
    }

    xlow = BASED * ((int) (x / BASED));
    ylow = BASED * ((int) (y / BASED));

    for (i = xlow; i < xlow + BASED; i++) {
        for (j = ylow; j < ylow + BASED; j++) {
            if (board->m[i][j] != 0) {
                possible[board->m[i][j]] = false;
            }
        }
    }
}

void print_possible(bool possible[]) {
    int i;    /* counter */

    for (i = 0; i <= DIMENSION; i++) {
        if (possible[i]) {
            printf(" %d", i);
        }
        printf("\n");
    }
}

int possible_count(int x, int y, boardtype *board) {
    int i;                      /* counter */
    int cnt;                    /* number of open squares */
    bool possible[DIMENSION+1]; /* what is possible for the square */
    point p;

    p.x = x;
    p.y = y;
    possible_values(p, board, possible);
    cnt = 0;
    for (i = 0; i <= DIMENSION; i++) {
        if (possible[i]) {
            cnt++;
        }
    }
    return(cnt);
}

void fill_square(point p, int v, boardtype *board) {
    if (board->m[p.x][p.y] == 0) {
        board->freecount = board->freecount - 1;
    } else {
        printf("Warning: filling already filled square (%d,%d)\n", p.x, p.y);
    }
    board->m[p.x][p.y] = v;
}

void free_square(point p, boardtype *board) {
    if (board->m[p.x][p.y] != 0) {
        board->freecount = board->freecount + 1;
    } else {
        printf("Warning: freeing already empty square (%d,%d)\n", p.x, p.y);
    }
    board->m[p.x][p.y] = 0;
}

void next_square(point *p, boardtype* board) {
    int i, j;               /* counters */
    int bestcnt, newcnt;    /* the best and latest square counts */
    bool doomed;            /* some empty square without moves? */

    bestcnt = DIMENSION + 1;
    doomed = false;
    
    p->x = p->y = -1;

    for (i = 0; i < DIMENSION; i++) {
        for (j = 0; j < DIMENSION; j++) {
            newcnt = possible_count(i, j, board);
            if ((newcnt == 0) && (board->m[i][j] == 0)) {
                doomed = true;
            }
            if (fast) {
                if ((newcnt < bestcnt) && (newcnt >= 1)) {
                    bestcnt = newcnt;
                    p->x = i;
                    p->y = j;
                }
            }
            else {  
                if ((newcnt >= 1) && (board->m[i][j] == 0)) {
                    p->x = i;
                    p->y = j;
                }
            }
        }
    }

    if (doomed && smart) {
        p->x = p->y = -1;    /* initialize to non-position */
    }
}

void print_board(boardtype *board) {
    int i, j;    /* counters */

    printf("\nThere are %d free board positions.\n", board->freecount);


    for (i = 0; i < DIMENSION; i++) {
        for (j = 0; j < DIMENSION; j++) {
            if (board->m[i][j] == 0) {
                printf(" ");
            } else {
                printf("%c", (char) '0' + board->m[i][j]);
            }
            if ((j + 1) % BASED == 0) {
                printf("|");
            }
        }
        printf("\n");
        if ((i + 1) % BASED == 0) {
            for (j = 0; j < (DIMENSION + BASED - 1); j++) {
                printf("-");
            }
            printf("\n");
        }
    }
}

void init_board(boardtype* board) {
    int i, j;    /* counters */

    for (i = 0; i < DIMENSION; i++) {
        for (j = 0; j < DIMENSION; j++) {
            board->m[i][j] = 0;
        }
        board->freecount = DIMENSION * DIMENSION;
    }
}

void read_board(boardtype* board) {
    int i, j;    /* counters */
    char c;
    int value;
    point p;

    init_board(board);

    for (i = 0; i < DIMENSION; i++) {
        for (j = 0; j < DIMENSION; j++) {
            scanf("%c", &c);
            value = (int) (c - '0');
            if (value != 0) {
                p.x = i;
                p.y = j;
                fill_square(p, value, board);
            }
        }
        scanf("\n"); /*newline*/
    }
}

void copy_board(boardtype *a, boardtype *b) {
    int i, j;

    b->freecount = a->freecount;

    for (i = 0; i < DIMENSION; i++) {
        for (j = 0; j < DIMENSION; j++) {
            b->m[i][j] = a->m[i][j];
        }
    }
}

/******************************************************************/
/* [[[ process_solution_sudoku_cut */
void process_solution(int a[], int k, boardtype *board) {
    finished = true;
    printf("process solution\n");
    print_board(board);
}
/* ]]] */

/* [[[ is_a_solution_sudoku_cut */
bool is_a_solution(int a[], int k, boardtype *board) {
    steps = steps + 1;          /* count steps for results table */

    return (board->freecount == 0);
}
/* ]]] */

/* [[[ make_unmake_move_sudoku_cut */
void make_move(int a[], int k, boardtype *board) {
    fill_square(board->move[k], a[k], board);
}

void unmake_move(int a[], int k, boardtype *board) {
    free_square(board->move[k], board);
}
/* ]]] */

/* [[[ construct_candidates_sudoku_cut */
void construct_candidates(int a[], int k, boardtype *board, int c[], int *nc) {
    int i;                       /* counter */
    bool possible[DIMENSION+1];  /* which digits fit in this square */

    next_square(&(board->move[k]), board);  /* pick square to fill next */

    *nc = 0;

    if ((board->move[k].x < 0) && (board->move[k].y < 0)) {
        return;    /* error condition, no moves possible */
    }

    possible_values(board->move[k], board, possible);
    for (i = 1; i <= DIMENSION; i++) {
        if (possible[i]) {
            c[*nc] = i;
            *nc = *nc + 1;
        }
    }
}
/* ]]] */

void backtrack(int a[], int k, boardtype *input) {
    int c[MAXCANDIDATES];           /* candidates for next position */
    int ncandidates;                /* next position candidate count */
    int i;                          /* counter */

    if (is_a_solution(a, k, input)) {
            process_solution(a, k, input);
    } else {
        k = k + 1;
        construct_candidates(a, k, input, c, &ncandidates);
        for (i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            make_move(a, k, input);
            backtrack(a, k, input);
            unmake_move(a, k, input);

            if (finished) {
                return;    /* terminate early */
            }
        }
    }
}

void solve_problem(boardtype *board) {
   int a[DIMENSION * DIMENSION + 1];
   boardtype temp;

   printf("----------------------------------\n");
   steps = 0;
   copy_board(board, &temp);
   finished = false;

   backtrack(a,0, &temp);

   printf("It took %d steps to find this solution ", steps);
   printf("for fast=%d  smart=%d\n", fast, smart);
}

int main(void) {
    boardtype board;              /* Sudoku board structure */

    read_board(&board);
    print_board(&board);

    fast = true;
    smart=true;
    solve_problem(&board);

    fast = true;
    smart=false;
    solve_problem(&board);

    fast = false;
    smart=true;
    solve_problem(&board);

    fast = false;
    smart=false;
    solve_problem(&board);

    return 0 ;
}
