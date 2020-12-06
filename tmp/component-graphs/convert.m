
(*	
	Format Data Files for Bandwidth Programming Assignment
*)

OutSCC[n_Integer,p_:0.2,i_Integer] :=
	Block[{g},
		g = RandomGraph[n,p,Directed];
		PutOut[g,ToString[i],Directed];
		StronglyConnectedComponents[g]
	]

OutPath[n_Integer] :=
	PutOut[ InduceSubgraph[ Path[n], RandomPermutation[n] ], "p"]

OutTree[n_Integer] :=
	PutOut[ InduceSubgraph[ RandomTree[n], RandomPermutation[n] ], "t"]

OutK[n_Integer] := PutOut[ K[n], "k"]

OutRandom[n_Integer,p_:0.25] := PutOut[ RandomGraph[n,p], "r"]
OutRandom[n_Integer,p_:0.25,Directed] :=
	PutOut[ RandomGraph[n,p,Directed], "r", Directed]


BinaryTree[n_Integer] :=
	MakeGraph[
		Range[n],
		((#1==2*#2) || (#2==2*#1) || (#1==2*#1+1) || (#2==2*#1+1))&
	]

OutBinaryTree[n_Integer] :=
	PutOut[ MakeUndirected[ BinaryTree[n] ], "bt"]

OutGridGraph[n_Integer,m_Integer] :=
	PutOut[ InduceSubgraph[ GridGraph[n,m], RandomPermutation[n*m] ], "gg"]


PutOut[g_Graph,char_,Directed] :=
        Block[{l,i,s},
                s = StringJoin["g-",ToString[char]];
                Open[s];
                Write[s, V[g], M[g] ];
                l = ToOrderedPairs[g];
                Do [
                        WriteString[s, StringJoin[ ToString[ First[l[[i]]] ],
                                "    ", ToString[ Last[l[[i]]]] ], "\n"],
                        {i,1,Length[l]}
                ];
                Close[s]
        ]


PutOut[g_Graph,char_] :=
	Block[{l,i,s},
		s = StringJoin["g-",ToString[char],"-",ToString[V[g]],"-",
				ToString[2*M[g]]];
		Open[s];
		Write[s, V[g], M[g] ];
		l = ToUnorderedPairs[g];
		Do [
			WriteString[s, StringJoin[ ToString[ First[l[[i]]] ],
				"    ", ToString[ Last[l[[i]]]] ], "\n"],
			{i,1,Length[l]}
		];
		Close[s]
	]
