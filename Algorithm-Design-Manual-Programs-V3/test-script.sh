
# test script for "Programming Challenges" programs -q

./distance | diff - datafiles/distance-out -q
./war < datafiles/war-in | diff - datafiles/war-out -q
./name < datafiles/name-in | diff - datafiles/name-out -q
./sorting | diff - datafiles/sorting-out -q
./polly < datafiles/polly-in | diff - datafiles/polly-out -q
./bignum < datafiles/bignum-in | diff - datafiles/bignum-out -q
./gcd < datafiles/gcd-in | diff - datafiles/gcd-out -q
./primes < datafiles/primes-in | diff - datafiles/primes-out -q
./subsets | diff - datafiles/subsets-out -q
./permutations | diff - datafiles/permutations-out -q
./8-queens | diff - datafiles/8-queens-out -q
./bfs-demo < datafiles/grid | diff - datafiles/grid-bfs-demo-out -q
./bfs-demo < datafiles/regular-tree | diff - datafiles/regular-tree-bfs-demo-out -q
./dfs-demo < datafiles/grid | diff - datafiles/grid-dfs-demo-out -q
./dfs-demo < datafiles/regular-tree | diff - datafiles/regular-tree-dfs-demo-out -q
./connected < datafiles/connected-in | diff - datafiles/connected-out -q
./connected < datafiles/grid | diff - datafiles/grid-connected-out -q
./connected < datafiles/separate-comps | diff - datafiles/separate-comps-connected-out -q
./topsort < datafiles/grid | diff - datafiles/grid-topsort-out -q
./topsort < datafiles/simple-acyclic | diff - datafiles/simple-acyclic-topsort-out -q
./prim < datafiles/wgrid | diff - datafiles/wgrid-prim-out -q
./prim < datafiles/simple-wgraph | diff - datafiles/simple-wgraph-prim-out -q
./floyd < datafiles/wgrid | diff - datafiles/wgrid-floyd-out -q
./dijkstra < datafiles/wgrid | diff - datafiles/wgrid-dijkstra-out -q
./dijkstra < datafiles/simple-wgraph | diff - datafiles/simple-wgraph-dijkstra-out -q
./editbrute <datafiles/editbrute-in | diff - datafiles/editbrute-out -q
./stringedit <datafiles/stringedit-in | diff - datafiles/stringedit-out -q
./lcs <datafiles/stringedit-in | diff - datafiles/lcs-out -q
./substringedit < datafiles/substringedit-in | diff - datafiles/substringedit-out -q
./elevator < datafiles/elevator-in | diff - datafiles/elevator-out -q
./order | diff - datafiles/order-out -q
./plates <datafiles/plates1-in | diff - datafiles/plates1-out -q
./plates <datafiles/plates2-in | diff - datafiles/plates2-out -q
./plates <datafiles/plates3-in | diff - datafiles/plates3-out -q
./superman < datafiles/superin1 | diff - datafiles/superin1-out -q
./superman < datafiles/superin2 | diff - datafiles/superin2-out -q
./superman < datafiles/superin3 | diff - datafiles/superin3-out -q
./superman <datafiles/superin4 | diff - datafiles/superin4-out -q
./geotest < datafiles/geotest-in | diff - datafiles/geotest-out -q
./convex-hull < datafiles/chin | diff - datafiles/chin-out -q
./convex-hull < datafiles/chin1 | diff - datafiles/chin1-out -q
./convex-hull < datafiles/i.2 | diff - datafiles/i.2-out -q
./convex-hull < datafiles/i.4 | diff - datafiles/i.4-out -q
./convex-hull < datafiles/i.9 | diff - datafiles/i.9-out -q
./convex-hull < datafiles/i.10 | diff - datafiles/i.10-out -q
./convex-hull < datafiles/i.19 | diff - datafiles/i.19-out -q
./convex-hull < datafiles/convex-bad.10 | diff - datafiles/convex-bad.10-out -q
./convex-hull < datafiles/VDError-uniq.dat | diff - datafiles/VDError-uniq.dat-out -q
./convex-hull < datafiles/VDError.dat | diff - datafiles/VDError-uniq.dat-out -q
./triangulate < datafiles/tri1 | diff - datafiles/tri1-out -q
./triangulate < datafiles/tri2 | diff - datafiles/tri2-out -q
./triangulate < datafiles/tri3 | diff - datafiles/tri3-out -q
./cgtest < datafiles/cgtest-in | diff - datafiles/cgtest-out -q
./netflow < datafiles/netflow1-in | diff - datafiles/netflow1-out -q
./netflow < datafiles/netflow2-in | diff - datafiles/netflow2-out -q
./netflow < datafiles/netflow3-in | diff - datafiles/netflow3-out -q
./paths < datafiles/paths-graph  | diff - datafiles/paths-graph-out -q
# -q
#   Extra cases for "The Algorithm Design Manual" -q
# -q
./partition < datafiles/partition-data1 | diff - datafiles/partition-data1-out -q
./partition < datafiles/partition-data2 | diff - datafiles/partition-data2-out -q
./biconnected < datafiles/grid | diff - datafiles/biconnected-grid -q
./biconnected < datafiles/tree | diff - datafiles/biconnected-tree -q
./biconnected < datafiles/art3 | diff - datafiles/biconnected-art3 -q
./biconnected < datafiles/baase | diff - datafiles/biconnected-baase -q
./biconnected < datafiles/clr-graph | diff - datafiles/biconnected-clr-graph -q
./biconnected < datafiles/bridge-tree | diff - datafiles/biconnected-bridge-tree -q
./biconnected < datafiles/backedge-tree | diff - datafiles/biconnected-backedge-tree -q
./biconnected < datafiles/backedge-parent-tree | diff - datafiles/biconnected-backedge-parent-tree -q
./biconnected < datafiles/complete-4-graph | diff - datafiles/biconnected-complete-4-graph -q
./biconnected < datafiles/biconnected-1 | diff - datafiles/biconnected-1-out -q
./strong < datafiles/g-1 | diff - datafiles/strong-g-1 -q
./strong < datafiles/g-2 | diff - datafiles/strong-g-2 -q
./strong < datafiles/g-3 | diff - datafiles/strong-g-3 -q
./strong < datafiles/g-4 | diff - datafiles/strong-g-4 -q
./strong < datafiles/g-5 | diff - datafiles/strong-g-5 -q
./strong < datafiles/strong-clr | diff - datafiles/strong-clr-out -q
./strong < datafiles/simple-strong | diff - datafiles/simple-strong-strong-out -q
./bipartite < datafiles/grid | diff - datafiles/bipartite-grid -q
./bipartite < datafiles/tree | diff - datafiles/bipartite-tree -q
./bipartite < datafiles/art3 | diff - datafiles/bipartite-art3 -q
./topsort1 < datafiles/grid | diff - datafiles/grid-topsort1-out -q
./topsort1 < datafiles/simple-acyclic | diff - datafiles/simple-acyclic-topsort1-out -q
./matrix < datafiles/matrix-data1 | diff - datafiles/matrix-data1-out -q
./matrix < datafiles/matrix-data2 | diff - datafiles/matrix-data2-out -q
./list-demo < datafiles/list-in | diff - datafiles/list-out -q
./tree-demo < datafiles/list-in | diff - datafiles/treelist-out -q
./tree-demo < datafiles/t1.in | diff - datafiles/t1.out -q
./binomial < datafiles/binomial-in | diff - datafiles/binomial-out
./subsetsum < datafiles/subsetsum-in | diff - datafiles/subsetsum-out
#
./tsp-astar < datafiles/tsp5-in | diff - datafiles/tsp5-out
./tsp-astar < datafiles/tsp6-in | diff - datafiles/tsp6-out
./tsp-astar < datafiles/tsp7-in | diff - datafiles/tsp7-out
./tsp-astar < datafiles/tsp8-in | diff - datafiles/tsp8-out
./tsp-astar < datafiles/tsp9-in | diff - datafiles/tsp9-out
#
./convolve < datafiles/convolve-1 | diff - datafiles/convolve1-out
./convolve < datafiles/convolve-2 | diff - datafiles/convolve2-out
./convolve < datafiles/convolve-3 | diff - datafiles/convolve3-out
./convolve < datafiles/convolve-4 | diff - datafiles/convolve4-out
#
./findcycle < datafiles/grid | diff - datafiles/findcycle-grid-out
./findcycle < datafiles/tree | diff - datafiles/findcycle-tree-out
#
./kruskal < datafiles/wgrid | diff - datafiles/wgrid-kruskal-out -q
./kruskal < datafiles/simple-wgraph | diff - datafiles/simple-wgraph-kruskal-out -q
#
#./sudoku < datafiles/sudoku1 | diff - datafiles/sudoku1-out -q
#./sudoku < datafiles/sudoku2 | diff - datafiles/sudoku2-out -q
./sudoku < datafiles/sudoku3 | diff - datafiles/sudoku3-out -q
#
./tsp < datafiles/tsp-examples/tsp48 | diff - datafiles/tsp48-out
#
./countedges < datafiles/grid | diff - datafiles/countedges-grid
./countedges < datafiles/tree | diff - datafiles/countedges-tree
#
./sentinel | diff - datafiles/sentinel-out -q
#
./strong1 < datafiles/g-1 | diff - datafiles/strong1-g-1 -q
./strong1 < datafiles/g-2 | diff - datafiles/strong1-g-2 -q
./strong1 < datafiles/g-3 | diff - datafiles/strong1-g-3 -q
./strong1 < datafiles/g-4 | diff - datafiles/strong1-g-4 -q
./strong1 < datafiles/g-5 | diff - datafiles/strong1-g-5 -q
./strong1 < datafiles/strong-clr | diff - datafiles/strong1-clr-out -q
./strong1 < datafiles/simple-strong | diff - datafiles/simple-strong1-strong-out -q
#
