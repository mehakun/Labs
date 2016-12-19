% БД слов
article(a).
article(the).

item(book).
item(computer).
item(disk).
item(pen).
item(bottle).
item(table).

color(red).
color(green).
color(blue).
color(white).
color(black).

size(little).
size(medium).
size(big).

% Расположение
location(in, X, in(X)).
location(on, X, on(X)).
location(under, X, under(X)).
location(behind, X, behind(X)).
location(before, X, before(X)).
location(after, X, after(X)).
% Обработка списка слов
sentence([H], s(H)).
sentence([A, B], s(A, B)).
    
sentence([Art, Size, Item | T], Res):-
    article(Art),
    size(Size),
    item(Item),
    sentence([object(Item, size(Size)) | T], Res).

sentence([Art, Color, Item | T], Res):-
	  article(Art),
	  color(Color),
	  item(Item),
	  sentence([object(Item, color(Color)) | T], Res).

sentence([object(Item, size(Size)), is, X, Y, Z | T], Res):-
	  article(Y),
	  item(Z),
	  location(X, Z, Loc),
	  sentence([location(object(Item, size(Size)), Loc) | T], Res).

sentence([object(Item, color(Color)), is, X, Y, Z | T], Res):-
	  article(Y),
	  item(Z),
	  location(X, Z, Loc),
	  sentence([location(object(Item, color(Color)), Loc) | T], Res).

sentence([object(Item, size(Size)), is, X | T], Res):-
	  color(X),
	  sentence([object(Item, size(Size)), color(X) | T], Res).

sentence([object(Item, color(Color)), is, X | T], Res):-
	  size(X),
	  sentence([object(Item, color(Color)), size(X) | T], Res).

