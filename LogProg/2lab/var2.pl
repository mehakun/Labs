
older(A, B):-pred(A), zam(B).
older(A, B):-pred(A), sec(B).
older(A, B):-zam(A), sec(B).
zam(A):-not(pred(A)), not(sec(A)).
pred(A):-not(zam(A)), not(sec(A)).
sec(A):-not(zam(A)), not(pred(A)).
any(A):-pred(A); zam(A); sec(A).

solve(A, B, V, G, D, E, Pred, Zam, Sec):-
    (zam(A); sec(A)), pred(D),
    (zam(B); sec(B)), older(V, B),
    not(any(B)), any(E),
    not(any(V)), any(D), any(E),
    not(any(V)), (pred(E); sec(B)),
    not(any(G)), (older(V, G); older(D, G)),
    any(D), not(zam(D)),
    not(sec(D)), older(G, D),
    not(any(D)), any(A), not(zam(E)), not(pred(E)),
    any(E), (pred(E); pred(B)).
             
    
              
