/*    sorting.c

    Implementations of primary sorting algorithms 
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
#include <stdlib.h>
#include <stdbool.h>

#include "priority_queue.h"
#include "queue.h"
#include "random.h"

#define NELEM        100 /* size of test arrays */
#define LESS_THAN    -1
#define EQUAL_TO     0
#define GREATER_THAN 1

bool compare(item_type a, item_type b) {
    if (a < b) {
        return(LESS_THAN);
    }

    if (a > b) {
        return(GREATER_THAN);
    }

    return(EQUAL_TO);
}

/*    Swap the ith and jth elements of array s.    */

void newswap(item_type s[], int i, int j) {
    item_type tmp;    /* placeholder */

    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}

/* [[[ insertion_cut */
void insertion_sort(item_type s[], int n) {
    int i, j;    /* counters */

/* [[[ insertion_inner_cut */
    for (i = 1; i < n; i++) {
        j = i;
        while ((j > 0) && (s[j] < s[j - 1])) {
            swap(&s[j], &s[j - 1]);
            j = j-1;
        }
    }
/* ]]] */
}
/* ]]] */

/* [[[ selection_cut */
void selection_sort(item_type s[], int n) {
    int i, j;   /* counters */
    int min;    /* index of minimum */

    for (i = 0; i < n; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (s[j] < s[min]) {
                min = j;
            }
        }
        swap(&s[i], &s[min]);
    }
}
/* ]]] */

/* [[[ partition_cut */
int partition(item_type s[], int l, int h) {
    int i;          /* counter */
    int p;          /* pivot element index */
    int firsthigh;  /* divider position for pivot element */

    p = h;          /* select last element as pivot */
    firsthigh = l;
    for (i = l; i < h; i++) { 
        if (s[i] < s[p]) {
            swap(&s[i], &s[firsthigh]);
            firsthigh++;
        }
    }
    swap(&s[p], &s[firsthigh]);

    return(firsthigh);
}
/* ]]] */

/*    quicksort array s from the index l to index h.    */
/* [[[ quicksort_cut */
void quicksort(item_type s[], int l, int h) {
    int p;    /* index of partition */

    if (l < h) {
        p = partition(s, l, h);
        quicksort(s, l, p - 1);
        quicksort(s, p + 1, h);
    }
}
/* ]]] */

/* [[[ heapsort_cut */
void heapsort_(item_type s[], int n) {
    int i;               /* counters */
    priority_queue q;    /* heap for heapsort */

    make_heap(&q, s, n);

    for (i = 0; i < n; i++) {
        s[i] = extract_min(&q);
    }
}
/* ]]] */

/* [[[ binary_search_cut */
int binary_search(item_type s[], item_type key, int low, int high) {
    int middle;    /* index of middle element */

    if (low > high) {
        return (-1);    /* key not found */
    }

    middle = (low + high) / 2;

    if (s[middle] == key) {
        return(middle);
    }
    
    if (s[middle] > key) {
        return(binary_search(s, key, low, middle - 1));
    } else {
        return(binary_search(s, key, middle + 1, high));
    }
}
/* ]]] */

/* [[[ merge_cut */
void merge(item_type s[], int low, int middle, int high) {
    int i;                  /* counter */
    queue buffer1, buffer2; /* buffers to hold elements for merging */

    init_queue(&buffer1);
    init_queue(&buffer2);

    for (i = low; i <= middle; i++) enqueue(&buffer1, s[i]);
    for (i = middle + 1; i <= high; i++) enqueue(&buffer2, s[i]);

    i = low;
    while (!(empty_queue(&buffer1) || empty_queue(&buffer2))) {
        if (headq(&buffer1) <= headq(&buffer2)) {
            s[i++] = dequeue(&buffer1);
        } else {
            s[i++] = dequeue(&buffer2);
        }
    }

    while (!empty_queue(&buffer1)) {
        s[i++] = dequeue(&buffer1);
    }

    while (!empty_queue(&buffer2)) {
        s[i++] = dequeue(&buffer2);
    }
}
/* ]]] */

/* [[[ mergesort_cut */
void merge_sort(item_type s[], int low, int high) {
    int middle;    /* index of middle element */

    if (low < high) {
        middle = (low + high) / 2;
        merge_sort(s, low, middle);
        merge_sort(s, middle + 1, high);

        merge(s, low, middle, high);
    }
}
/* ]]] */

int main(void) {
    int s[NELEM+2];
    int i;         /* counter */

    for (i = 0; i < NELEM; i++) {
        s[i] = NELEM - i;
    }
    random_permutation(s, NELEM);

    insertion_sort(s, NELEM);

    printf("\n\nInsertion sort: \n");
    for (i = 0; i < NELEM; i++) {
        printf("%d ", s[i]);
    }

    for (i = 0; i < NELEM; i++) {
        s[i] = NELEM - i;
    }
    random_permutation(s, NELEM);

    selection_sort(s, NELEM);

    printf("\n\nSelection sort: \n");
    for (i = 0; i < NELEM; i++) {
        printf("%d ", s[i]);
    }

    for (i = 0; i < NELEM; i++) {
        s[i] = NELEM - i;
    }
    random_permutation(s, NELEM);

    quicksort(s, 0, NELEM - 1);

    printf("\n\nQuicksort: \n");
    for (i = 0; i < NELEM; i++) {
        printf("%d ", s[i]);
    }

    for (i = 0; i < NELEM; i++) {
        s[i] = NELEM - i;
    }
    random_permutation(s, NELEM);

    heapsort_(s, NELEM);

    printf("\n\nHeapsort sort: \n");
    for (i = 0; i < NELEM; i++) {
        printf("%d ", s[i]);
    }

    for (i = 0; i < NELEM; i++) {
        s[i] = NELEM - i;
    }
    random_permutation(s, NELEM);

    merge_sort(s, 0, NELEM - 1);
    printf("\n\nMergesort: \n");
    for (i = 0; i < NELEM; i++) {
        printf("%d ", s[i]);
    }
    printf("\n");

    printf("\n");

    // /* test binary search */
    printf("Binary Search: \n");
    for (i = 0; i < NELEM; i++) {
        s[i] = 2 * (NELEM - i);
    }
    random_permutation(s, NELEM);

    heapsort_(s, NELEM);
    for (i = 2; i < 2 * NELEM + 1; i += 2) {
        printf("%d found in %d\n", i, binary_search(s, i, 0, NELEM - 1));
    }

    return 0;
}
