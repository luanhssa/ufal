#ifndef PRINCIPAL_H_INCLUDED
#define PRINCIPAL_H_INCLUDED
   /**  struct baralho (MainPack)
    *
    *   possui uma pilha de cartas
    *   e um inteiro indicando a quantidade de cartas na pilha
    */
typedef struct _mainPack_ MainPack;

   /**  struct carta (Card)
    *
    *   possui um caracter com a cor (color) da carta
    *   possui um caracter com o simbolo (symbol) da carta
    *   possui um inteiro com o Id da imagem da carta
    *   um ponteiro para a próxima carta
    *   um ponteiro para a carta anterior
    */
typedef struct _card_ Card;

   /**  struct jogador (Player)
    *
    *   possui um inteiro com a identificação (id) do jogador
    *   um ponteiro para a primeira carta
    *   um ponteiro para o próximo jogador
    *   um ponteiro para o jogador anterior
    */
typedef struct _player_ Player;

   /**  struct _game_ (Game)
    *
    *   possui um inteiro com o sentido do jogo
    *   um caracter com a cor da carta do topo
    *   um caracter com o simbolo da carta do topo
    *   um pilha de cartas (baralho principal)
    *   um pilha de cartas (baralho de descarte)
    *   uma lista (duplamente encadeada circular) de jogadores
    */
typedef struct _game_ Game;


   /**
    *   Struct com a posição do mouse.
    */
typedef struct mouse Mouse;

typedef struct _event_ Event;

typedef struct _queue_ Queue;


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "iniciaAllegro.h"
#include "game.h"
#include "textMenu.h"
#include "baralho.h"
#include "cartas.h"
#include "jogador.h"
#include "jogo.h"
#include "graphics.h"
#include "action.h"
#include "ai.h"

#define offset 0.5;
#define MAX_STACK_SIZE 108


#define nextPlayerAction 'n'
#define puxar2Action '2'
#define puxar4Action '4'
#define pegarCorAction 'c'
#define inverterAction 'i'

int FPS;
int   displayHeigh,
      displayWidht;
bool key[4];
bool redraw;
bool doexit;
bool  menuMainMenu,
      menuNovoJogo,
      menuHelp,
      menuOpcoes,
      changeColor,
      gamePaused,
      menuResumeMenu,
      leave;

Queue                   *eventsQueue;

ALLEGRO_DISPLAY         *display;

ALLEGRO_DISPLAY_MODE    disp_data;

ALLEGRO_EVENT_QUEUE     *event_queue;

ALLEGRO_TIMER           *timer;

ALLEGRO_COLOR           colorMenu,
                        colorMenuNovoJogo,
                        colormenuHelp,
                        colorMenuOpcoes,
                        colorMenuSair,
                        colorMainMenu,
                        colorBlack,
                        colorWhite,
                        colorRed,
                        colorDarkRed,
                        colorLightRed,
                        colorYellow,
                        colorGray,
                        colorResumeMenu;

ALLEGRO_FONT            *font,
                        *fontMenu,
                        *fontTittle,
                        *fontPlayers;

ALLEGRO_BITMAP          *leoShadow,
                        *luanShadow,
                        *neryShadow,
                        *jorgeShadow,
                        *maxShadow,
                        *imageLeo,
                        *imageLuan,
                        *imageNery,
                        *imageJorge,
                        *imageMax,
                        *piso,
                        *table,
                        *imageSentido,
                        *imageQnt,
                        *imageBDiscard,
                        *imageBaralho,
                        *imageGetCor,
                        *amarelo,
                        *azul,
                        *verde,
                        *vermelho;

ALLEGRO_BITMAP          **cartasImagens;
/*
                        *carta0Amarela,//0
                        *carta0Azul,//1
                        *carta0Verde,//2
                        *carta0Vermelho,//3
                        *carta1Amarelo,//4
                        *carta1Azul,//5
                        *carta1Verde,//6
                        *carta1Vermelho,//7
                        *carta2Amarelo,//8
                        *carta2Azul,//9
                        *carta2Verde,//10
                        *carta2Vermelho,//...
                        *carta3Amarelo,
                        *carta3Azul,
                        *carta3Verde,
                        *carta3Vermelho,
                        *carta4Amarelo,
                        *carta4Azul,
                        *carta4Verde,
                        *carta4Vermelho,
                        *carta5Amarelo,
                        *carta5Azul,
                        *carta5Verde,
                        *carta5Vermelho,
                        *carta6Amarelo,
                        *carta6Azul,
                        *carta6Verde,
                        *carta6Vermelho,
                        *carta7Amarelo,
                        *carta7Azul,
                        *carta7Verde,
                        *carta7Vermelho,
                        *carta8Amarelo,
                        *carta8Azul,
                        *carta8Verde,
                        *carta8Vermelho,
                        *carta9Amarelo,
                        *carta9Azul,
                        *carta9Verde,
                        *carta9Vermelho,
                        *cartaInverterAmarelo,
                        *cartaInverterAzul,
                        *cartaInverterVerde,
                        *cartaInverterVermelho,
                        *cartaBloqueioAmarelo,
                        *cartaBloqueioAzul,
                        *cartaBloqueioVerde,
                        *cartaBloqueioVermelho,
                        *cartaMais4,
                        *cartaMais2Amarelo,
                        *cartaMais2Azul,
                        *cartaMais2Verde,
                        *cartaMais2Vermelho,
                        *cartaCoringa;
*/

enum MYKEYS {
            KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

   /**
    * color: cor da carta;
    * id: tipo da carta 0-9 ou cartas especiais (+4, +2, 0, inverte, cor)
    ******************** BEGIN Color
    * Amarelo = 'Y'
    * Azul = 'B'
    * Verde = 'G'
    * Vermelho = 'R'
    * Dark = 'D'
    ******************** END Color
    ******************** BEGIN ID's
    * 0 = '0'
    * 1 = '1'
    * 2 = '2'
    * 3 = '3'
    * 4 = '4'
    * 5 = '5'
    * 6 = '6'
    * 7 = '7'
    * 8 = '8'
    * 9 = '9'
    * +4 = 'A'
    * +2 = 'K'
    * Pular = 'Q'
    * Reverte = 'J'
    * Coringa = 'C'
    ******************** END ID's
    ******************** BEGIN Distribuição
    * 2 (1-9) de cada cor (x4)      = 72
    * 1 (0) de cada cor (x4)        = 4
    * 2 reverter de cada cor (x4)   = 8
    * 2 pular de cada cor (x4)      = 8
    * 2 (+2) de cada cor (x4)       = 8
    * 4 (+4)                        = 4
    * 4 Curinga                     = 4
    * -----------------------------------
    * TOTAL                         = 108
    ******************** END Distribuição
    */

#endif // PRINCIPAL_H_INCLUDED
