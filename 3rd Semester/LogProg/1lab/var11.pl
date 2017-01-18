% Реализация стандартных предикатов обработки списков
    
    % Принадлежность элемента списку
    % (элемент, список)
    lismember(X, [X | _]).
    lismember(X, [_ | T]):-lismember(X, T).
    
    % Длина списка
    % (список, длина)
    lislength([], 0).
    lislength([_ | L], N):-lislength(L, M), N is M + 1.
    
    % Конкатенация списков
    % (список1, список2, список1+2)
    lisappend([], L, L).
    lisappend([X | L1], L2, [X | L3]):-lisappend(L1, L2, L3).
    
    % Удаление элемента из списка
    % (элемент, список, список без элемента)
    lisdelete(X, [X | T], T).
    lisdelete(X, [Y | T], [Y | Z]):-lisdelete(X, T, Z).

    % Перестановки элементов в списке
    % (список, перестановка)
    lispermutation([], []).
    lispermutation(L, [X | T]):-lisdelete(X, L, Y), lispermutation(Y, T).
    
    % Подсписки списка
    % (подсписок, список)
    lissubl(S, L):-lisappend(_, L1, L), lisappend(S, _, L1).

    % Вставка элемента в список на указанную позицию
    % (список, элемент, позиция, результат)
    stdlisinsert(List, Elem, Pos, Res):-same_length([Elem|List], Res), append(Bef,List0, List), length(Bef, Pos), append(Bef,[Elem|List0],Res).
    lisinsert(List, Elem, 0, [Elem|List]).
    lisinsert([El|List], Elem, Pos, [El|Rest]):-Pos1 is Pos - 1, lisinsert(List, Elem, Pos1, Rest).

    % Нахождение максимального элемента в списке
    % (список, элемент)
    lismaxnum([], R, R).
    lismaxnum([X|Xs], WK, R):- X >  WK, lismaxnum(Xs, X, R).
    lismaxnum([X|Xs], WK, R):- X =< WK, lismaxnum(Xs, WK, R).
    lismaxnume([], R, R).
    lismaxnume([e(X,Y)|Xs], e(WK,WY), R):- Y > WY, lismaxnume(Xs, e(X,Y), R).
    lismaxnume([e(X,Y)|Xs], e(WK,WY), R):- Y=<WY, lismaxnume(Xs, e(WK,WY), R).
    lismaxnum([X|Xs], R):- lismaxnum(Xs, X, R).
    lismaxnume([e(X,Y)|Xs], R):- lismaxnume(Xs, e(X,Y), R).
    
    % Пример совместного использования предикатов
    % Вставка максимального элемента из Списка1 в Список2 на Pos позицию
    % (список1, список2, позиция, результат)
    lisinsertmax(List1, List2, Pos, Res):-lismaxnum(List1, Elem), stdlisinsert(List2, Elem, Pos, Res).
