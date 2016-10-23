#ifndef CARTAS_H_INCLUDED
#define CARTAS_H_INCLUDED

Card* colocarCarta(MainPack* baralho, Card* maoJogador);

   /**  peekColor
    *
    *   Olha a cor da carta
    *
    *   Parâmetros:
    *               uma carta
    *   Retorno:
    *               um caracter com a cor da carta
    *               caracter | significado
    *                    'Y' = Yellow
    *                    'G' = Green
    *                    'B' = Blue
    *                    'R' = Red
    *                    'D' = Dark
    */
char peekColor(Card *pCard);

   /**  peekSymbol
    *
    *   Olha o simbolo da carta
    *
    *   Parâmetros:
    *               uma carta
    *   Retorno:
    *               um caracter com o simbolo da carta
    *               caracter | significado
    *                    '0' = 0
    *                    '1' = 1
    *                    '2' = 2
    *                    '3' = 3
    *                    '4' = 4
    *                    '5' = 5
    *                    '6' = 6
    *                    '7' = 7
    *                    '8' = 8
    *                    '9' = 9
    *                    'A' = +4
    *                    'K' = +2
    *                    'Q' = Pular
    *                    'J' = Reverte
    *                    'C' = Coringa
    */
char peekSymbol(Card *pCarta);

   /**  createCard
    *
    *   Cria uma carta
    *
    *   Parâmetros:
    *               um caracter com a cor da carta
    *               um caracter com o simbolo da carta
    *   Retorno:
    *               a carta criada
    */
Card* createCard(char color, char symbol, int id);

   /**  printCards
    *
    *   Imprime cartas (linked list)
    *
    *   Parâmetros:
    *               uma carta
    *   Retorno:
    *               vazio
    */
void printCards(Card* newCard);

   /**  printCards
    *
    *   Remove a carta do baralho (pack) e coloca em uma lista de cartas
    *   A inserção é feita no começo da lista
    *
    *   Parâmetros:
    *               um baralho (pack)
    *               uma carta ou NULL
    *   Retorno:
    *               a lista de cartas
    */
Card* insertCard(MainPack* pack, Card* cardList);

   /**  getNextCard
    *
    *   Vai para a próxima carta da mão do jogador
    *
    *   Parâmetros:
    *               Primeira carta
    *   Retorno:
    *               a lista de cartas
    */

Card* getNextCard(Card *first);

int getIdCard(Card* pCard);

Card* createEmptyCard();

Card* removeCard(Card* carta, Card* list);

#endif // CARTAS_H_INCLUDED
