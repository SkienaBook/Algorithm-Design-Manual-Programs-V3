(*	Steven Skiena
	Output Combinatorica graphs in Programming Challenges format
	July 12, 2002

*)

g = SetEdgeWeights[GridGraph[5,5], {WeightingFunction->RandomInteger,
	WeightRange->{1,10000}} ]

Edges[g,EdgeWeight]

OutGraph[g_Graph] :=
	Module[{},
		Print[V[g], " ", M[g]];
		Map[(Print[#[[1,1]], " ", #[[1,2]], " ", #[[2]] ])&,
			Edges[g,EdgeWeight]];
	]

DoubleOutGraph[g_Graph,name_] :=
        Module[{f},
		f=OpenWrite[name];
                Write[f,V[g], " ", 2*M[g]];
                Map[(Write[f,#[[1,1]], " ", #[[1,2]], " ", #[[2]] ]; Write[f,#[[1,2]], " ", #[[1,1]], " ", #[[2]] ];)&,
                        Edges[g,EdgeWeight]];
        ]


DoubleOutGraph[g,"file-test"]


(* To prove the validity of dijkstra 

n[34]:= g >> /tmp/wgrid.m

In[35]:= Dijkstra[g,1,25]

Out[35]= Dijkstra[-Graph:<40, 25, Undirected>-, 1, 25]

In[36]:= ?ShortestPath
ShortestPath[g, start, end] finds a shortest path between vertices start and
   end in graph g. An option Algorithm, that takes on the values Automatic,
   Dijkstra or BellmanFord, is provided. This allows a choice between using
   Dijkstra's algorithm and the Bellman-Ford algorithm. The default is
   Algorithm -> Automatic. In this case, depending on whether edges have
   negative weights and depending on the density of the graph the algorithm
   chooses between Bellman-Ford and Dijkstra.

In[37]:= ShortestPath[g,1,25]

Out[37]= {1, 6, 11, 16, 17, 22, 23, 24, 25}

In[38]:= Table[ ShortestPath[g,1,i], {i,1,25}]

Out[38]= {{1}, {1, 2}, {1, 2, 3}, {1, 2, 3, 4}, {1, 2, 3, 4, 5}, {1, 6}, 
 
>    {1, 2, 7}, {1, 2, 3, 8}, {1, 2, 3, 8, 9}, {1, 2, 3, 8, 9, 10}, 
 
>    {1, 6, 11}, {1, 6, 11, 12}, {1, 2, 3, 8, 13}, {1, 2, 3, 8, 13, 14}, 
 
>    {1, 2, 3, 8, 9, 10, 15}, {1, 6, 11, 16}, {1, 6, 11, 16, 17}, 
 
>    {1, 6, 11, 16, 17, 18}, {1, 6, 11, 16, 17, 18, 19}, 
 
>    {1, 2, 3, 8, 9, 10, 15, 20}, {1, 6, 11, 16, 21}, {1, 6, 11, 16, 17, 22}, 
 
>    {1, 6, 11, 16, 17, 22, 23}, {1, 6, 11, 16, 17, 22, 23, 24}, 
 
>    {1, 6, 11, 16, 17, 22, 23, 24, 25}}

*)
