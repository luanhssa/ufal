% Definir sexo dos objetos do BD

pessoa(X) :- 
	feminino(X); 
	masculino(X).
	
feminino(maria).
feminino(ana).
feminino(íris).
feminino(júlia).
masculino(joão).
masculino(josé).
masculino(jorge).

% Sexo definido BD criado

progenitor(maria, josé). 
progenitor(joão, josé).
progenitor(joão, ana).
progenitor(josé, júlia).
progenitor(josé, íris).
progenitor(íris, jorge).

% Para mostrar todos usar: ";"

pai(X, Y) :- 
	progenitor(X, Y), 
	masculino(X).

mãe(X, Y) :- 
	progenitor(X, Y), 
	feminino(X).
	
avô(X, Y):-
	pai(X, Z),
	progenitor(Z, Y).
	
avó(X, Y):-
	mãe(X, Z),
	progenitor(Z, Y).
	
irmão(X, Y):-
	masculino(X),
	progenitor(Z, X),
	progenitor(Z, Y),
	not(X=Y).

irmã(X, Y):-
	feminino(X),
	progenitor(Z, X),
	progenitor(Z, Y),
	not(X=Y).
