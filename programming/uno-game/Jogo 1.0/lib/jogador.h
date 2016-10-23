#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED

   /**  createPlayer
    *
    *   Cria uma lista de Jogadores
    *
    *   Parâmetros:
    *               inteiro que é a identificação do jogador
    *               ponteiro para o primeiro jogador
    *   Retorno:
    *               retorna a lista jogador
    */
Player* createPlayer(int id, Player* first);

   /**  pushPlayer
    *
    *   Remove a carta do topo do baralho e coloca na mão do jogador
    *
    *   Parâmetros:
    *               baralho
    *               jogador
    */
void pushPlayer(MainPack* pack, Player* player);

   /**  getPlayerCards
    *
    *   retorna o ID do jogador
    *
    *   Parâmetros:
    *               jogador
    *
    *   Retorno:
    *               vazio
    */
void printPlayerCards(Player* player);

   /**  printPlayerId
    *
    *   imprime a identificação do jogador
    *
    *   Parâmetros:
    *               jogador
    *
    *   Retorno:
    *               vazio
    */
int getPlayerId(Player* newPlayer);

   /**  insertPlayer
    *
    *   Insere jogadores na lista duplamente encadeada.( Lista de jogadores)
    *
    *   Parâmetros:
    *               Id do jogador(Int)
    *               jogador (É um nó de uma lista)
    *   Retorno:
    *               vazio
    */
void insertPlayer(int id,Player *listPlayers);

    /**  getNextPlayer
    *
    *   Retorna o próximo jogador
    *
    *   Parâmetros:
    *              Lista de jogadores
    *   Retorno:
    *               Proximo nó da lista
    */
Player* getNextPlayer(Player *jogadores);

    /**  getPreviousPlayer
    *
    *   Retorna o jogador anterior
    *
    *   Parâmetros:
    *              Lista de jogadores
    *   Retorno:
    *               Anterior nó da lista
    */
Player* getPreviousPlayer(Player *jogadores);

int getQTCards(Player* newPlayer);

Card* getPlayerCards(Player* player);

void descartar(Game* game, char symbol, char color);

Card* getHandPlayer(Player* jogador);

#endif // JOGADOR_H_INCLUDED
