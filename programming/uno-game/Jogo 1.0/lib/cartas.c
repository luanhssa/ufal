#include"principal.h"

struct _card_{
    char color;
    char symbol;
    Card* nextCard;
    Card* previousCard;
    int id;
};

char peekColor(Card* pCard){
    return pCard->color;
}

char peekSymbol(Card* pCard){
    return pCard->symbol;
}

int getIdCard(Card* pCard){
        return pCard->id;
}

Card* createCard(char color, char symbol, int id){
    Card* newCard = (Card*)malloc(sizeof(Card));
    newCard->color = color;
    newCard->symbol = symbol;
    newCard->id = id;
    newCard->previousCard = NULL;
    newCard->nextCard = NULL;
    return newCard;
}

Card* createEmptyCard(){
    Card* card = (Card*)malloc(sizeof(Card));
    return card;
}

void printCards(Card* newCard){
    if(newCard != NULL){
        printf("Carta: (%c, %c)\n", peekColor(newCard), peekSymbol(newCard));
        printCards(getNextCard(newCard));
    }
}

Card* insertCard(MainPack* pack, Card* cardList){
    Card* newCard = (Card*)malloc(sizeof(Card));
    newCard = popPack(pack);
    if(cardList != NULL){
        cardList->previousCard = newCard;
        newCard->nextCard = cardList;
    }
    if(newCard == NULL) {
        return cardList;
    }
    else {
        return newCard;
    }
}
Card* getNextCard(Card *first){
    return first->nextCard;
}

Card* removeCard(Card* carta, Card* list){
    if(list == NULL){
        return NULL;
    }
    if(carta->previousCard == NULL){
        list = carta->nextCard;
        carta->nextCard->previousCard = NULL;
    }
    else if(carta->nextCard == NULL){
        carta->previousCard->nextCard = NULL;

    }
    else{
        carta->previousCard->nextCard = carta->nextCard;
        carta->nextCard->previousCard = carta->previousCard;
    }
    carta->nextCard = NULL;
    carta->previousCard = NULL;
    return list;
}