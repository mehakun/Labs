brother(Y,X):-parent(Z,Y),parent(Z,X),sex(Y, m),X<>Y.
brotherInSquare(Y,X):-parent(Z,X),brother(Z,F),parent(F,Y),sex(Y, m).
