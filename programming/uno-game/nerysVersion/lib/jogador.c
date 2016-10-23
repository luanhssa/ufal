#include"principal.h"

struct _player_{
    int id;
    int qtCards;
    Card* hand;
    Player* nextPlayer;
    Player* previousPlayer;
};

Player* createPlayer(int id, Player* first){
    Player* newPlayer = (Player*) malloc(sizeof(Player));
    newPlayer->id = id;
    newPlayer->hand = NULL;
    newPlayer->nextPlayer = NULL;
    newPlayer->previousPlayer = NULL;
    newPlayer->qtCards = 0;

    if(first != NULL){
        newPlayer->nextPlayer = first->nextPlayer;
        first->nextPlayer = newPlayer;
        newPlayer->previousPlayer = first;
        newPlayer->nextPlayer->previousPlayer = newPlayer;
    }
    else{
        newPlayer->nextPlayer = newPlayer;
        newPlayer->previousPlayer = newPlayer;
    }
    return newPlayer;
}

void pushPlayer(MainPack* pack, Player* newPlayer){
    if(newPlayer->hand != NULL){
        newPlayer->hand = insertCard(pack, newPlayer->hand);
    }
    else{
        newPlayer->hand = popPack(pack);
    }
    newPlayer->qtCards++;
}

Card* getHandPlayer(Player* jogador){
    return jogador->hand;
}

void descartar(Game* game, char symbol, char color){
    register int i=0;
    Player* jogador = getJogadores(game);
    Card* carta = getHandPlayer(jogador);

    for(; i < getQTCards(jogador); i++) {
        if(symbol == peekSymbol(carta) && color == peekColor(carta)){
            jogador->hand = removeCard(carta, jogador->hand);
            jogador->qtCards--;
            setColorTop(game, color);
            setSymbolTop(game, symbol);
            setIdTop(game, getIdCard(carta));
            if(!pushPack(carta, getDescarte(game))){
                exit(1);
            }

            break;
        }
        carta = getNextCard(carta);
    }
    if(color=='D'){
        insertEvent(creatEvent(pegarCorAction),eventsQueue);
        if(symbol=='A'){
            insertEvent(creatEvent(nextPlayerAction),eventsQueue);
            insertEvent(creatEvent(puxar4Action),eventsQueue);
        }
    } else if(symbol=='K'){
        insertEvent(creatEvent(nextPlayerAction),eventsQueue);
        insertEvent(creatEvent(puxar2Action),eventsQueue);
    } else if(symbol=='Q'){
        insertEvent(creatEvent(nextPlayerAction),eventsQueue);
    } else if(symbol=='J'){
        insertEvent(creatEvent(inverterAction),eventsQueue);
    }
    insertEvent(creatEvent(nextPlayerAction),eventsQueue);
}

void printPlayerCards(Player* newPlayer){
    if(newPlayer->hand != NULL){
        printCards(newPlayer->hand);
    }
    else{
        printf("Empty Hand!\n");
    }
}

int getPlayerId(Player* newPlayer){
    return newPlayer->id;
}

int getQTCards(Player* newPlayer){
    return newPlayer->qtCards;
}


void insertPlayer(int id,Player *listPlayers){
    createPlayer(id,listPlayers);
}

Player* getNextPlayer(Player *jogadores){

    return jogadores->nextPlayer;
}

Player* getPreviousPlayer(Player *jogadores){

    return jogadores->previousPlayer;
}

Card* getPlayerCards(Player* player){
    return player->hand;
}
