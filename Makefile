#	
#	Makefile for "Algorithm Design Manual" / "Programming Challenges" Programs
#

# Copyright 2003-2020 by Steven S. Skiena; all rights reserved.
# Permission is granted for use in non-commerical applications
# provided this copyright notice remains intact and unchanged.
# 
# These programs appear in my books:
# 
# "The Algorithm Design Manual" by Steven Skiena, second edition, Springer,
# London 2008.  See out website www.algorist.com for additional information
# or https://www.amazon.com/exec/obidos/ASIN/1848000693/thealgorith01-20
# 
# "Programming Challenges: The Programming Contest Training Manual"
# by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.
# See our website www.programming-challenges.com for additional information,
# or http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/


MAKEFILE = Makefile
SOURCES = backtrack.c 8-queens.c permutations.c subsets.c queue.c war.c \
	graph.c random.c sorting.c bfs-dfs.c bfs-demo.c dfs-demo.c \
	connected.c topsort.c wgraph.c prim.c dijkstra.c floyd.c findcycle.c \
	editdistance.c stringedit.c lcs.c substringedit.c geometry.c \
	superman.c convex-hull.c triangulate.c 10055.c distance.c name.c \
	polly.c gcd.c primes.c bignum.c editbrute.c elevator.c order.c \
	plates.c geotest.c cgtest.c netflow.c paths.c sudoku.c annealing.c \
	tsp.c fib.c partition.c  biconnected.c stack.c strong.c topsort1.c \
	bipartite.c priority_queue.c kruskal.c set_union.c list-demo.c \
	tree-demo.c matrix.c binomial.c subsetsum.c tsp-astar.c tsp-pq.c \
	convolve.c countedges.c sentinel.c strong1.c
# criterion_test.c
OBJECTS = backtrack.o 8-queens.o permutations.o subsets.o queue.o war.o \
	graph.o random.o sorting.o bfs-dfs.o bfs-demo.o dfs-demo.o \
	connected.o topsort.o wgraph.o prim.o dijkstra.o floyd.o findcycle.o \
	editdistance.o stringedit.o lcs.o substringedit.o geometry.o \
	superman.o convex-hull.o triangulate.o 10055.c distance.o name.o \
	polly.o gcd.o primes.o bignum.o editbrute.o elevator.o order.o \
	plates.o geotest.o cgtest.o netflow.o paths.o sudoku.o annealing.o \
	tsp.o fib.o partition.o biconnected.o stack.o strong.o topsort1.o \
	bipartite.o priority_queue.o kruskal.o set_union.o list-demo.o \
	tree-demo.o matrix.o binomial.o subsetsum.o tsp-astar.o tsp-pq.o \
	convolve.o countedges.o strong1.o
# criterion_test.o
BINARIES = 8-queens permutations subsets war sorting bfs-demo \
	dfs-demo connected topsort prim dijkstra floyd findcycle stringedit \
	superman editbrute convex-hull triangulate 10055 distance name \
	polly gcd substringedit primes bignum elevator order plates geotest cgtest \
	netflow lcs paths sudoku tsp fib partition biconnected strong topsort \
	bipartite kruskal matrix tree-demo topsort1 list-demo binomial \
	subsetsum tsp-astar convolve countedges sentinel strong1
# criterion_test
INCLUDES = backtrack.h queue.h graph.h editdistance.h \
	   geometry.h annealing.h tsp.h stack.h priority_queue.h set_union.h \
	   list.h tree.h item.h random.h bfs-dfs.h editbrute.h tsp-astar.h tsp-pq.h


CC = gcc
CFLAGS = -ggdb -Wall -std=c99 -pedantic # -O4 -g -DNDEBUG -pg -Wextra
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

kruskal:	kruskal.o set_union.o wgraph.o
		$(CC) -o $@ kruskal.o set_union.o wgraph.o $(LFLAGS)

bipartite:	bipartite.o queue.o graph.o bfs-dfs.o
		$(CC) -o $@ bipartite.o queue.o graph.o bfs-dfs.o $(LFLAGS)

topsort1:	topsort1.o queue.o graph.o stack.o bfs-dfs.o
		$(CC) -o $@ topsort1.o queue.o graph.o stack.o bfs-dfs.o $(LFLAGS)

strong:		strong.o bfs-dfs.o queue.o graph.o stack.o
		$(CC) -o $@ strong.o bfs-dfs.o queue.o graph.o stack.o $(LFLAGS)

biconnected:	biconnected.o bfs-dfs.o queue.o graph.o
		$(CC) -o $@ biconnected.o bfs-dfs.o queue.o graph.o $(LFLAGS)

partition:	partition.c
		$(CC) -o $@ partition.c $(LFLAGS)

fib:		fib.c
		$(CC) -o $@ fib.c $(LFLAGS)

tsp:		annealing.o random.o tsp.o 
		$(CC) -o $@ annealing.o random.o tsp.o $(LFLAGS)

tsp-astar:	tsp-astar.o tsp-pq.o
		$(CC) -o $@ tsp-astar.o tsp-pq.o $(LFLAGS)

sudoku:		sudoku.o
		$(CC) -o $@ sudoku.o $(LFLAGS)

8-queens:	8-queens.o
		$(CC) -o $@ 8-queens.o $(LFLAGS)

paths:		paths.o graph.o
		$(CC) -o $@ paths.o graph.o $(LFLAGS)

permutations:	permutations.o
		$(CC) -o $@ permutations.o $(LFLAGS)

subsets:	subsets.o
		$(CC) -o $@ subsets.o $(LFLAGS)

sorting:	random.o queue.o priority_queue.o sorting.o
		$(CC) -o $@ random.o queue.o priority_queue.o sorting.o $(LFLAGS)

war:		queue.o random.o war.o
		$(CC) -o $@ queue.o random.o war.o $(LFLAGS)

bignum:		bignum.o
		$(CC) -o $@ bignum.o $(LFLAGS)

bfs-demo:	queue.o graph.o bfs-dfs.o bfs-demo.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o bfs-demo.o $(LFLAGS)

dfs-demo:	queue.o graph.o bfs-dfs.o dfs-demo.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o dfs-demo.o $(LFLAGS)

connected:	queue.o graph.o bfs-dfs.o connected.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o connected.o $(LFLAGS)

topsort:	queue.o graph.o topsort.o
		$(CC) -o $@ queue.o graph.o topsort.o $(LFLAGS)

findcycle:	queue.o graph.o bfs-dfs.o findcycle.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o findcycle.o $(LFLAGS)

prim:		wgraph.o prim.o
		$(CC) -o $@ wgraph.o prim.o $(LFLAGS)

dijkstra:	wgraph.o dijkstra.o
		$(CC) -o $@ wgraph.o dijkstra.o $(LFLAGS)

floyd:		floyd.o
		$(CC) -o $@ floyd.o $(LFLAGS)

editbrute:	editbrute.o
		$(CC) -o $@ editbrute.o $(LFLAGS)

stringedit:	editdistance.o stringedit.o
		$(CC) -o $@ editdistance.o stringedit.o $(LFLAGS)

lcs:		editdistance.o lcs.o
		$(CC) -o $@ editdistance.o lcs.o $(LFLAGS)

substringedit:	editdistance.o substringedit.o
		$(CC) -o $@ editdistance.o substringedit.o $(LFLAGS)

superman:	geometry.o superman.o
		$(CC) -o $@ geometry.o superman.o $(LFLAGS)

convex-hull:	geometry.o convex-hull.o
		$(CC) -o $@ geometry.o convex-hull.o $(LFLAGS)

triangulate:	geometry.o triangulate.o
		$(CC) -o $@ geometry.o triangulate.o $(LFLAGS)

10055:		10055.o
		$(CC) -o $@ 10055.o $(LFLAGS)

distance:	distance.o
		$(CC) -o $@ distance.o -lm

name:		name.o
		$(CC) -o $@ name.o $(LFLAGS)

polly:		polly.o
		$(CC) -o $@ polly.o $(LFLAGS)

gcd:		gcd.o
		$(CC) -o $@ gcd.o $(LFLAGS)

primes:		primes.o
		$(CC) -o $@ primes.o $(LFLAGS)

elevator:	elevator.o
		$(CC) -o $@ elevator.o $(LFLAGS)

plates:		plates.o
		$(CC) -o $@ plates.o $(LFLAGS)

order:		order.o
		$(CC) -o $@ order.o $(LFLAGS)

geotest:	geometry.o geotest.o
		$(CC) -o $@ geometry.o geotest.o $(LFLAGS)

cgtest:		geometry.o cgtest.o
		$(CC) -o $@ geometry.o cgtest.o $(LFLAGS)

netflow:	netflow.o queue.o
		$(CC) -o $@ netflow.o queue.o $(LFLAGS)

matrix:		matrix.o
		$(CC) -o $@ matrix.o $(LFLAGS)

list-demo:	list-demo.o
		$(CC) -o $@ list-demo.o $(LFLAGS)

tree-demo:	tree-demo.o
		$(CC) -o $@ tree-demo.o $(LFLAGS)

convolve:	convolve.o
		$(CC) -o $@ convolve.o $(LFLAGS)

countedges:	countedges.o
		$(CC) -o $@ queue.o graph.o countedges.o bfs-dfs.o $(LFLAGS)

sentinel:	sentinel.o
		$(CC) -o $@ sentinel.o $(LFLAGS)

strong1:	strong1.o bfs-dfs.o queue.o graph.o stack.o
		$(CC) -o $@ strong1.o bfs-dfs.o queue.o graph.o stack.o $(LFLAGS)

#criterion_test:		criterion_test.o
#		$(CC) -o $@ criterion_test.o $(LFLAGS) -lcriterion

lint:	
	lint -h $(SOURCES)

backup:	$(SOURCES) $(INCLUDES)
	cp $(SOURCES) backup
	cp $(INCLUDES) backup
 
clean: 	
	rm -f core *.o a.out $(BINARIES)
	rm -f ./tests/*.o

tar:	
	make clean
	tar cvf /tmp/bookprograms.tar .

