brother(Y,X):-parents(Z,Y),parents(Z,X),sex(Y, m),X<>Y.
brotherInSquare(Y,X):-parents(Z,X),brother(Z,F),parents(F,Y),sex(Y, m).
