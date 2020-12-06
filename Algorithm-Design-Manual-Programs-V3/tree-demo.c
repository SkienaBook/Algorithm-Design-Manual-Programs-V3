/*    tree-demo.c

    Driver for a binary search tree container implementation.
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



#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

tree *parent;    /* last node visited */

tree *init_tree(void) {
    return(NULL);
}

bool empty_tree(tree *t) {
    if (t == NULL) {
        return (true);
    }
    return (false);
}

/* [[[ search_tree_cut */
tree *search_tree(tree *l, item_type x) {
    if (l == NULL) {
        return(NULL);
    }

    if (l->item == x) {
        return(l);
    }

    if (x < l->item) {
        return(search_tree(l->left, x));
    } else {
        return(search_tree(l->right, x));
    }
}
/* ]]] */

/* [[[ insert_tree_cut */
void insert_tree(tree **l, item_type x, tree *parent) {
    tree *p;    /* temporary pointer */

    if (*l == NULL) {
        p = malloc(sizeof(tree));
        p->item = x;
        p->left = p->right = NULL;
        p->parent = parent;
        *l = p;
        return;
    }

    if (x < (*l)->item) {
        insert_tree(&((*l)->left), x, *l);
    } else {
        insert_tree(&((*l)->right), x, *l);
    }
}
/* ]]] */

void print_tree(tree *l) {
    if (l != NULL) {
        print_tree(l->left);
        printf("%d ", l->item);
        print_tree(l->right);
    }
}

/* [[[ sucessor_descd_cut */
tree *successor_descendant(tree *t) {
    tree *succ;                     /* successor pointer */

    if (t->right == NULL) {
        return(NULL);
    }
    succ = t->right;
    while (succ->left != NULL) {
        succ = succ->left;
    }
    return(succ);
}
/* ]]] */

/* [[[ find_minimum_cut */
tree *find_minimum(tree *t) {
    tree *min;    /* pointer to minimum */

    if (t == NULL) {
        return(NULL);
    }

    min = t;
    while (min->left != NULL) {
        min = min->left;
    }
    return(min);
}
/* ]]] */

tree *predecessor_descendant(tree *t) {
    tree *pred;    /* predecessor pointer */

    if (t->left == NULL) {
        return(NULL);
    }

    pred = t->left;
    while (pred->right != NULL) {
        pred = pred->right;
    }
    return(pred);
}

/* [[[ delete_tree_cut */
tree *delete_tree(tree *t, item_type x) {
    tree *d;             /* node with key to delete */
    tree *p;             /* node to be physically deleted */
    item_type new_key;   /* key to overwrite deleted key */
    tree *child;         /* d's only child, if any */

    d = search_tree(t, x);

    if (d == NULL) {
        printf("Warning: key to be deleted %d is not in tree.\n", x);
        return(t);
    }

    if (d->parent == NULL) {    /* if d is the root */
        if ((d->left == NULL) && (d->right == NULL)) {
            free(d);
            return NULL;    /* root-only tree */
        }

        if (d->left != NULL) {    /* find node to physically delete */
            p = predecessor_descendant(d);
        } else { 
            p = successor_descendant(d);
        }
    } else {
        if ((d->left == NULL) || (d->right == NULL)) {
            /* d has <=1 child, so try to find non-null child */
            if (d->left != NULL) {
                child = d->left;
            } else {
                child = d->right;
            }

            if ((d->parent)->left == d) {    /* fill null pointer */
              d->parent->left = child;
            } 
            else {
              d->parent->right = child;
            }
            if (child != NULL) {
                child->parent = d->parent;
            }
            free(d);
            return(t);
        } else {
            p = successor_descendant(d);    /* p has 2 children */
        }
    }

    new_key = p->item;    /* deal with simpler case of deletion */
    delete_tree(t, p->item);
    d->item = new_key;
    return (t);
}
/* ]]] */

void process_item(item_type x) {
    printf("%d", x);
}

/* [[[ traverse_tree_cut */
void traverse_tree(tree *l) {
    if (l != NULL) {
        traverse_tree(l->left);
        process_item(l->item);
        traverse_tree(l->right);
    }
}
/* ]]] */




int main(void) {
    char c;               /* input character */
    item_type d;          /* input item */
    tree *l;              /* tree under construction */
    tree *tmp;            /* returned tree from search */

    l = init_tree();

    while (scanf("%c", &c) != EOF) {
	    if (tolower(c) == 'p') {
		    print_tree(l);
		    printf("\n");
	    }
	    if (tolower(c) == 'i') {
		    scanf("%d", &d);
		    printf("new item: %d\n", d);
		    insert_tree(&l, d, NULL);
	    }
	    if (tolower(c) == 's') {
		    scanf("%d", &d);
		    tmp = search_tree(l, d);
		    if (tmp == NULL) {
		        printf("item %d not found\n",d);
		    } else {
		        printf("item %d found\n",d);
		    }
	    }
	    if (tolower(c) == 'd') {
	        scanf("%d", &d);
	        printf(" deleting item %d\n", d);
	        l = delete_tree(l, d);
	        print_tree(l);
	        printf("\n");
	    }
    }
    return 0;
}
