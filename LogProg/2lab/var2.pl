    
candidates([X,Y,Z]):-L=["А","Б","В","Г","Д","Е"],member(X,L),member(Y,L),
    not(X=Y),member(Z,L),not(X=Z),not(Y=Z).
    
    older(X,Y,[X,Y,_]).
    older(X,Y,[X,_,Y]).
    older(X,Y,[_,X,Y]).
    
    solve(L):-candidates(L),L=[X,Y,Z],
    (X="Д" ; not(member("А",L))),
    (not(older("Б","В",L)) ; not(member("Б",L))),
    (not(member("Е",L)) ; not(member("Б",L))),
    (not(member("Д",L)) ; not(member("Е",L)) ; not(member("В",L))),
    (not(X="Е"), not(Z="Б") ; not(member("В",L))),
    (not(older("В","Г",L)),not(older("Д","Г",L)); not(member("Г",L))),
    not(Y="Д"),
    (not(member("Г",L)) ; not(Z="Д")),
    (member("Е",L) ; not(member("А",L)) ; not(member("Д",L))),
    (L=["Е",_,_] ; L=["Б",_,_] ; not(member("Е",L))).
    
    solve:- solve([A,B,C]),write("Председатель - "),write(A),
    write(" Заместитель - "),write(B),write(" Секретарь - "),write(C),nl.
