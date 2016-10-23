pessoa(paulo).
pessoa(pedro).
cidade(maceió).
cidade(recife).
estado(pernambuco).
estado(alagoas).

nasceu(paulo, maceió).
nasceu(pedro, recife).

fica(maceió, alagoas).
fica(recife, pernambuco).

alagoano(X) :-
	nasceu(X, Y),
	fica(Y, alagoas).
