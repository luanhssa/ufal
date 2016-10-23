#ifndef BARALHO_H_INCLUDED
#define BARALHO_H_INCLUDED
// -------  ACREDITO QUE A FUNÇÃO DO BARALHO ESTEJA ERRADA!!!!!
   /**  createMainPack
    *
    *   Cria um baralho com todas as cartas embaralhadas
    *
    *   Parâmetros:
    *               vazio
    *   Retorno:
    *               baralho (MainPack)
    */
MainPack* createMainPack();

   /**  createEmptyPack
    *
    *   Aloca memoria de um baralho
    *
    *   Parâmetros:
    *               vazio
    *   Retorno:
    *               retorna o baralho vazio
    */
MainPack* createEmptyPack();

   /**  createPackStack
    *
    *   Cria uma pilha de cartas para o baralho
    *
    *   Parâmetros:
    *               vazio
    *   Retorno:
    *               uma carta com a primeira posição
    */
Card** createPackStack();

   /**  popPack
    *
    *   Remove a carta do topo do baralho
    *
    *   Parâmetros:
    *               baralho (pack)
    *   Retorno:
    *               a carta que foi removida
    */
Card* popPack(MainPack* pack);

   /**  pushPack
    *
    *   Insere uma carta (newCard) em um baralho (pack)
    *
    *   Parâmetros:
    *               uma carta
    *               um baralho
    *   Retorno:
    *               booleano
    */
int pushPack(Card* newCard, MainPack* pack);

Card** shufleCards(Card** cards, int qntcartas);

int getSizePack(MainPack* pack);

void pushMainPack(MainPack* pack, MainPack* descarte);

Card** getPack(MainPack* pack);

#endif // BARALHO_H_INCLUDED
