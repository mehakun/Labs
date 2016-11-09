% Реализация стандартных предикатов обработки списков
    
    % Принадлежность элемента списку
    % (элемент, список)
    lismember(X, [X | _]).
    lismember(X, [_ | T]):-lismember(X, T).
    
    % Длина списка
    % (список, длина)
    lislength([], 0).
    lislength([_ | L], N):-lislength(L, M), N is M + 1.
    
    % Конкатинация списков
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
    % (список, элемент, позиция, итератор, результат)
    stdlisinsert(List, Elem, Pos, Res):-same_length([Elem|List], Res), append(Bef,List0, List),length(Bef, Pos), append(Bef,[Elem|List0],Res).
    lisinsert(Elem, 0, List, [Elem|List]).
    lisinsert(Elem, Pos, [El|List], [El|Rest]):-Pos1 is Pos - 1, lisinsert(Elem, Pos1, List, Rest).
    lismaxnum(L, M):-max_member(M, L).
    lismaxnum(e(L), M):-max_member(M, L).

%    lismaximum([L], N):-lismaxnum([L], -25, 0, 0, N).

    
    % Пример совместного использования предикатов
    
