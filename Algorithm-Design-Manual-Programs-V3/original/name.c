/*	name.c
	Corporate name changing program -- string example

	by:Steven Skiena
	begun: January 28, 2002
	revised: July 3, 2002
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


#include <stdio.h>
#include <string.h>

#define	MAXLEN		1001	/* longest possible string */
#define MAXCHANGES	101	/* maximum number of name changes */

typedef char string[MAXLEN];

string mergers[MAXCHANGES][2];	/* store before/after corporate names */
int nmergers;			/* the number of different name changes */

read_changes()
{
	int i;			/* counter */

	scanf("%d\n",&nmergers);
	for (i=0; i<nmergers; i++) {
		read_quoted_string(&(mergers[i][0]));
		read_quoted_string(&(mergers[i][1]));
		/*printf("%s to %s\n",mergers[i][0], mergers[i][1]);*/
	}
}

read_quoted_string(char *s)
{
	int i=0;		/* counter */
	char c;			/* latest character */

	while ((c=getchar()) != '\"') ;

	while ((c=getchar()) != '\"') {
		s[i] = c;
		i = i+1;
	}

	s[i] = '\0';
}

main()
{
	string s;		/* input string */
	char c;			/* input character */
	int nlines;		/* number of lines in text */
	int i,j;		/* counters */
	int pos;		/* position of pattern in string */

	read_changes();
	scanf("%d\n",&nlines);

	for (i=1; i<=nlines; i=i+1) {
		/* read text line */
		j=0;
		while ((c=getchar()) != '\n') {
                	s[j] = c;
                	j = j+1;
        	}
		s[j] = '\0';

		for (j=0; j<nmergers; j=j+1) 
			while ((pos=findmatch(mergers[j][0],s)) != -1) {
			   replace_x_with_y(s, pos,
				strlen(mergers[j][0]), mergers[j][1]);
			   /*printf("PARTIAL: %s\n",s);*/
			}
	
		printf("%s\n",s);
	}
}


/*	Return the position of the first occurrence of the pattern p
	in the text t, and -1 if it does not occur.
*/

int findmatch(char *p, char *t)
{
	int i,j;			/* counters */
	int plen, tlen;			/* string lengths */

	plen = strlen(p);
	tlen = strlen(t);

	for (i=0; i<=(tlen-plen); i=i+1) {
		j=0;
		while ((j<plen) && (t[i+j]==p[j]))
			j = j+1;
		if (j == plen) return(i);
	}

	return(-1);
}


/*	Replace the substring of length xlen starting at position pos in
	string s with the contents of string y.
*/

replace_x_with_y(char *s, int pos, int xlen, char *y)
{
	int i;				/* counter */
	int slen,ylen;			/* lengths of relevant strings */

	slen = strlen(s);
	ylen = strlen(y);

	if (xlen >= ylen)
		for (i=(pos+xlen); i<=slen; i++) s[i+(ylen-xlen)] = s[i]; 
	else
		for (i=slen; i>=(pos+xlen); i--) s[i+(ylen-xlen)] = s[i];

	for (i=0; i<ylen; i++) s[pos+i] = y[i];
}

