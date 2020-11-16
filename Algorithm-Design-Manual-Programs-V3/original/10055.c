
#include<stdio.h>

int main() {
      long p,q,r;

      while (scanf("%ld %ld",&p,&q)
		!=EOF) {
 	if (q>p) r=q-p;
        else r=p-q;

        printf("%ld\n",r);
      }
}

