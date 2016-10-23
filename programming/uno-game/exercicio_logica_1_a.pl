% Definir sexo dos objetos do BD

pessoa(X) :- 
	feminino(X); 
	masculino(X).
	
feminino(maria).
feminino(ana).
feminino(�ris).
feminino(j�lia).
masculino(jo�o).
masculino(jos�).
masculino(jorge).

% Sexo definido BD criado

progenitor(maria, jos�). 
progenitor(jo�o, jos�).
progenitor(jo�o, ana).
progenitor(jos�, j�lia).
progenitor(jos�, �ris).
progenitor(�ris, jorge).

% Para mostrar todos usar: ";"

pai(X, Y) :- 
	progenitor(X, Y), 
	masculino(X).

m�e(X, Y) :- 
	progenitor(X, Y), 
	feminino(X).
	
av�(X, Y):-
	pai(X, Z),
	progenitor(Z, Y).
	
av�(X, Y):-
	m�e(X, Z),
	progenitor(Z, Y).
	
irm�o(X, Y):-
	masculino(X),
	progenitor(Z, X),
	progenitor(Z, Y),
	not(X=Y).

irm�(X, Y):-
	feminino(X),
	progenitor(Z, X),
	progenitor(Z, Y),
	not(X=Y).
