#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

Game* createGame();

    /**  getNextPlayer
    *
    *   Retorna o próximo jogador
    *
    *   Parâmetros:
    *              Lista de jogadores
    *   Retorno:
    *               Proximo nó da lista
    */
MainPack* getBaralho(Game* game);

    /**  getNextPlayer
    *
    *   Retorna o próximo jogador
    *
    *   Parâmetros:
    *              Lista de jogadores
    *   Retorno:
    *               Proximo nó da lista
    */
MainPack* getDescarte(Game* game);

Player* getJogadores(Game* game);

Player* getJogadorPrincipal(Player* gamePlayer);

Player* getJogador(Player* gamePlayer, int id);

char getColorTop(Game* game);

char getSymbolTop(Game* game);

int getIdTop(Game* game);

int getSentido(Game* game);

//funções de alterar COR e SIMBOLO
void setColorTop(Game* game,char newColor);

void setSymbolTop(Game* game,char newSymbol);

void setIdTop(Game* game, int id);

void changeSentido(Game* game);

void nextPlayer(Game* jogo);

#endif // JOGO_H_INCLUDED
