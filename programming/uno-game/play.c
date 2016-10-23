#include <stdlib.h>
#include <stdio.h>
#include "play.c"
#include "cards.c"

///Estrutura jogador
struct play {
    int id;
    Card *cards;
    struct play *prev, *next;
};

typedef struct play Play;

//Cria a lista vazia
Play* createListPlay() {
	return NULL;
}

//Inicializa os atributos de um jogador
Play* initPlay() {
    Play *new = (Play*) malloc(sizeof(Play));
    new->id = 0;
    new->cards = NULL;
    new->prev = new;
    new->next = new;
    return new;
}

void insertPlay(Play* oldPlay, int id) {
	Play* new = (Play*) malloc(sizeof(Play));
	new->id = id;
	new->prev = oldPlay;
	new->next = oldPlay->next;
	oldPlay->next->prev = new;
	oldPlay->next = new;
}

