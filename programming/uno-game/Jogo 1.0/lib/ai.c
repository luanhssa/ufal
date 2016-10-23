#include "principal.h"

void artificialInteligence(Game* game){
	char color;
	char symbol;
	Player *jogador = getJogadores(game);
	Card *carta;
	bool escolheu = false;
	int	red = 0,
		blue = 0,
		green = 0,
		yellow = 0;

	for(carta = getHandPlayer(jogador) ; carta != NULL ; carta = getNextCard(carta)){
		if(getColorTop(game) == peekColor(carta) || getSymbolTop(game) == peekSymbol(carta)){
			color = peekColor(carta);
			symbol = peekSymbol(carta);
			escolheu = true;
			break;
		}
		if(peekColor(carta) == 'R'){
			red++;
		}
		else if(peekColor(carta) == 'B'){
			blue++;
		}
		else if(peekColor(carta) == 'G'){
			green++;
		}
		else if(peekColor(carta) == 'Y'){
			yellow++;
		}
	}
	if(!escolheu){
		for(carta = getHandPlayer(jogador) ; carta!=NULL ; carta = getNextCard(carta)){
			if('D' == peekColor(carta)){
				symbol = peekSymbol(carta);
				color = peekColor(carta);
				escolheu = true;
				break;
			}
		}
		if(!escolheu){
			pushPlayer(getBaralho(game), jogador);
			carta = getHandPlayer(jogador);
			if(getColorTop(game) == peekColor(carta) || getSymbolTop(game) == peekSymbol(carta) || 'D' == peekColor(carta)){
				color = peekColor(carta);
				symbol = peekSymbol(carta);
				escolheu = true;
			}
		}
	}
	if(escolheu){
		descartar(game, symbol, color);
		if(peekColor(carta) == 'D'){
            setColorTop(game, getBiggestColor(red, blue, green, yellow));
		}
	}
	else{
//		empilhar next player;
        insertEvent(creatEvent(nextPlayerAction), eventsQueue);
	}
}

char getBiggestColor(int red, int blue, int green, int yellow){
    if(red >= green){
        if(red >= blue){
            if(red >= yellow){
                return 'R';
            }
        }
    }
    if(green >= red){
        if(green >= blue){
            if(green >= yellow){
                return 'G';
            }
        }
    }
    if(blue >= red){
        if(blue >= green){
            if(blue >= yellow){
                return 'B';
            }
        }
    }
    return 'Y';
}