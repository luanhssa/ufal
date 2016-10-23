pessoa(paulo).
pessoa(pedro).
cidade(macei�).
cidade(recife).
estado(pernambuco).
estado(alagoas).

nasceu(paulo, macei�).
nasceu(pedro, recife).

fica(macei�, alagoas).
fica(recife, pernambuco).

alagoano(X) :-
	nasceu(X, Y),
	fica(Y, alagoas).
