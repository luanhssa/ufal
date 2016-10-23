#include"principal.h"

struct _game_{
    MainPack* baralho;
    MainPack* descarte;
    Player* jogadores;
    char colorTop;
    char symbolTop;
    int idTop;
    int sentido;
};

Game* createGame(){
    Game* newGame = (Game*) malloc(sizeof(Game));
    register int i;//auxiliar

    newGame->baralho = createMainPack();

    newGame->descarte = createEmptyPack();

    newGame->jogadores = createPlayer(1,NULL);

    newGame->sentido = 1;

    Card* firstCard = popPack(newGame->baralho);
    newGame->colorTop = peekColor(firstCard);
    newGame->symbolTop = peekSymbol(firstCard);
    newGame->idTop = getIdCard(firstCard);
    pushPack(firstCard, newGame->descarte);

    for(i=2;i<7;i++){
        insertPlayer(i,newGame->jogadores);
    }
    for(i=0;i<102;i++){
        pushPlayer(newGame->baralho, newGame->jogadores);
        newGame->jogadores = getPreviousPlayer(newGame->jogadores);
    }
    return newGame;
}

MainPack* getBaralho(Game* game){
    return game->baralho;
}

MainPack* getDescarte(Game* game){
    return game->descarte;
}

Player* getJogadores(Game* game){
    return game->jogadores;
}
char getColorTop(Game* game){
    return game->colorTop;
}
int getIdTop(Game* game){
    return game->idTop;
}
char getSymbolTop(Game* game){
    return game->symbolTop;
}
int getSentido(Game* game){
    return game->sentido;
}

//funções de alterar COR e SIMBOLO
void setColorTop(Game* game,char newColor){
    game->colorTop = newColor;
}
void setSymbolTop(Game* game,char newSymbol){
    game->symbolTop = newSymbol;
}

void setIdTop(Game* game, int id){
    game->idTop = id;
}

void changeSentido(Game* game){
    game->sentido = (getSentido(game)? 0 : 1);
}

Player* getJogadorPrincipal(Player* gamePlayer){
    if(getPlayerId(gamePlayer)== 1){
        return gamePlayer;
    }else{
        return getJogadorPrincipal(getPreviousPlayer(gamePlayer));
    }
}

Player* getJogador(Player* gamePlayer, int id){
    if(getPlayerId(gamePlayer)== id){
        return gamePlayer;
    }else{
        return getJogador(getPreviousPlayer(gamePlayer), id);
    }
}

void nextPlayer(Game* jogo){
    if(jogo->sentido){
        jogo->jogadores = jogo->jogadores->nextPlayer;
    }else{
        jogo->jogadores = jogo->jogadores->previousPlayer;
    }
}
