#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

const float FPS = 60;
const int SCREEN_X = 1280;
const int SCREEN_Y = 720;

int seconds = 0;


int cont_score=0;  // contador da pontuação

#include "libs/tiros.h"
#include "libs/soltador.h"
#include "libs/boss.h"
#include "libs/fase1.h"
#include "libs/fase2.h"

int loopMenu(void)
{
    ALLEGRO_DISPLAY *janela_menu = NULL;
    ALLEGRO_EVENT_QUEUE *evento = NULL;
    ALLEGRO_TIMER *tempo = NULL;
    ALLEGRO_BITMAP *fundo_menu = NULL;
    ALLEGRO_BITMAP *botao[4];

   ALLEGRO_SAMPLE *som_menu=NULL;

   int i;
   int j;

   int mouse_posX = 0;
   int mouse_posY = 0;
   bool redraw = true;
   int opcao = 0;


   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }

   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }

   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }

   tempo = al_create_timer(1.0 / FPS);
   if(!tempo) {
      fprintf(stderr, "failed to create tempo!\n");
      return -1;
   }

   janela_menu = al_create_display(SCREEN_X, SCREEN_Y);
   if(!janela_menu) {
      fprintf(stderr, "failed to create janela_menu!\n");
      al_destroy_timer(tempo);
      return -1;
   }

    al_init_image_addon();

    al_clear_to_color(al_map_rgb(255, 0, 255));

    al_set_target_bitmap(al_get_backbuffer(janela_menu));

    evento = al_create_event_queue();
    if(!evento)
    {
        fprintf(stderr, "failed to create evento!\n");
        al_destroy_display(janela_menu);
        al_destroy_timer(tempo);
        return -1;
    }

   al_register_event_source(evento, al_get_display_event_source(janela_menu));

   al_register_event_source(evento, al_get_timer_event_source(tempo));

   al_register_event_source(evento, al_get_mouse_event_source());

   al_register_event_source(evento, al_get_keyboard_event_source());

   al_clear_to_color(al_map_rgb(0,0,0));

   al_flip_display();

   al_start_timer(tempo);

    fundo_menu = al_load_bitmap("imagens/FundoMenuPrincipal.png");
    botao[0] = al_load_bitmap("imagens/botao1pA.png");
    botao[1] = al_load_bitmap("imagens/botao1pB.png");
    botao[2] = al_load_bitmap("imagens/botao2pA.png");
    botao[3] = al_load_bitmap("imagens/botao2pB.png");
    i=0;
    j=2;

   som_menu = al_load_sample("audio/som_menu.wav");

   al_play_sample(som_menu, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
   while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(evento, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                                 break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
         mouse_posX = ev.mouse.x;
         mouse_posY = ev.mouse.y;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        if(i==1)
        {
            al_destroy_timer(tempo);
            al_destroy_display(janela_menu);
            al_destroy_event_queue(evento);
            al_destroy_sample(som_menu);
            return 1;
        }
        else if(j==3)
        {
            al_destroy_timer(tempo);
            al_destroy_display(janela_menu);
            al_destroy_event_queue(evento);
            al_destroy_sample(som_menu);
            return 2;
        }
      }
      if(mouse_posX>340&&mouse_posX<340+139&&mouse_posY>420&&mouse_posY<481)
      {
            i=1;
      }
      else if(i==1)
      {
            i=0;
      }/*
      if(mouse_posX>772&&mouse_posX<772+139&&mouse_posY>420&&mouse_posY<481)
      {
            j=3;
      }
      else if(j==3)
      {
            j=2;
      }*/
      if(redraw && al_is_event_queue_empty(evento)) {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));
         al_draw_bitmap(fundo_menu,0,0,0);
         al_draw_bitmap(botao[i],340,420,0);
         //al_draw_bitmap(botao[j],772,420,0);

         al_flip_display();
      }
    }
    al_destroy_timer(tempo);
    al_destroy_display(janela_menu);
    al_destroy_event_queue(evento);
    al_destroy_sample(som_menu);

   return opcao;
}

int main(void)
{
    iniciar();
    int fase;
    int opcao=1;
   loopMENU:
    cont_score=0;
    opcao = loopMenu();
    if(opcao == 1)
    {
        fase = 1;
        if(fase==1)
        {
            fase = fase1_player1();
            if(fase==1)    /// apertou esc e volta pra o menu
            {
               goto loopMENU;
            }
            else if(fase==2)  /// proxima fase
            {
               fase = fase2_player1();
               if(fase==1)
               {
                   goto loopMENU;
               }
               else if(fase==3)
               {
                   //fase = fase3_player1();
               }
            }
        }
    }
    else if(opcao == 2)
    {
        //fase=loopGameA2();
    }
    return fase;
}
