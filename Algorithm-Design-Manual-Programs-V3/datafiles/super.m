(*	Steven Skiena
	July 23, 2002
	Superman input viewer

*)

Superman[f_] :=
	Module[{s,n,i,p1,p2,c,g},
		s = OpenRead[f];
		p1 = Read[s,{Real,Real}];
		p2 = Read[s,{Real,Real}];
		g = {Line[{p1,p2}]};
		Print[p1, p2];
		n = First[ Round[ Read[s,{Real}] ] ];
		Print[n];
		Table[
			(c = Read[s,{Real,Real,Real}];
			AppendTo[g, Circle[{c[[1]],c[[2]]},c[[3]]]];
			Print[g];), {n}
		];
		Show[ Graphics[g] ];
	]


Superman["superin1"]
Superman["superin2"]
Superman["superin3"]

