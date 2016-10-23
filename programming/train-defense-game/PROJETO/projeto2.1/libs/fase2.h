#ifndef FASE2_H_INCLUDED
#define FASE2_H_INCLUDED

/*
enum MYKEYS {
KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
*/

int fase2_player1(void)
{
   const int imagem_player1_SIZE = 32;
   int cont_tempo=0,    // contador do tempo
         qnt_vidas=5,   // quantidade máxima de imagem_vidas
         cont_vidas=0, // contador de vidas
         cont_fundo=0, // contador para passar a imagem de fundo e os trilhos
         cont_nuvem=1280, // contador para passar as nuvens
         cont_trem=0, //contador para passar as imagens do trem
         cont_ini=0, // contador para passar as imagens dos inimigos
         ATIVOS=0, /// booleano que serve para identificar se todos os inimigos estão ativos para que o boss entre
         BOSS_DEAD=EST_INATIVO, /// variavel que identifica a morte do boss e faz com que a estacao apareça
         cont_vida_boss=10,   /// contador de vidas para o boss
         opcao=0,
         inimigo_delay=0,
         i, j, k;       // auxiliares

   ALLEGRO_DISPLAY *janela_fase2 = NULL;

   ALLEGRO_EVENT_QUEUE *event_queue = NULL;

   ALLEGRO_TIMER *timer = NULL;


   al_init_font_addon();   // initialize the font addon
   al_init_ttf_addon();    // initialize the ttf (True Type Font) addon
   ALLEGRO_FONT *font_tempo = al_load_ttf_font("fonts/GringoNights.ttf",24,0);
   ALLEGRO_FONT *font_vidas = al_load_ttf_font("fonts/GringoNights.ttf",20,0);
   ALLEGRO_FONT *font_score = al_load_ttf_font("fonts/GringoNights.ttf",18,0);
   ALLEGRO_FONT *font_fase = al_load_ttf_font("fonts/GringoNights.ttf",46,0);
   ALLEGRO_FONT *font_gameover = al_load_ttf_font("fonts/GringoNights.ttf",72,0);

   ALLEGRO_BITMAP *imagem_player1 = NULL;
   ALLEGRO_BITMAP *imagem_vidas = NULL;
   ALLEGRO_BITMAP *imagem_vidas_cinza = NULL;
   ALLEGRO_BITMAP *imagem_ceu = NULL;
   ALLEGRO_BITMAP *imagem_nuvem = NULL;
   ALLEGRO_BITMAP *imagem_fundo_fase1 = NULL;
   ALLEGRO_BITMAP *imagem_trem[8] = {NULL};
   ALLEGRO_BITMAP *imagem_inimigo[4] = {NULL};
   ALLEGRO_BITMAP *imagem_arvore[4] = {NULL};
   ALLEGRO_BITMAP *imagem_boss[4] = {NULL};
   ALLEGRO_BITMAP *soltador = NULL;
   ALLEGRO_BITMAP *imagem_tiro = NULL;
   ALLEGRO_BITMAP *imagem_estacao = NULL;
   ALLEGRO_BITMAP *vida_boss_canto1 = NULL;
   ALLEGRO_BITMAP *vida_boos_meio1 = NULL;
   ALLEGRO_BITMAP *vida_boss_canto2 = NULL;
   ALLEGRO_BITMAP *vida_boos_meio2 = NULL;
   ALLEGRO_BITMAP *imagem_tiro_boss1 = NULL;
   ALLEGRO_BITMAP *imagem_tiro_boss2 = NULL;
   ALLEGRO_BITMAP *imagem_tiro_boss3 = NULL;

   ALLEGRO_SAMPLE *musica_fundo=NULL;
   ALLEGRO_SAMPLE *som_tiro=NULL;
   ALLEGRO_SAMPLE *som_boss=NULL;


   OBJETO_MOVEL inimigo[10];
   OBJETO_MOVEL arvore[12];
   OBJETO_MOVEL boss;
   OBJETO_MOVEL estacao;

   boss.estado = EST_INATIVO;
   boss.x = -150;
   boss.y = 200;

   estacao.estado = EST_INATIVO;
   estacao.x = 1500;
   estacao.y = 250;

   for(i=0;i<12;i++)
   {
      arvore[i].estado=EST_INATIVO;
   }
   for(i=0;i<TIROS;i++)
   {
      tiro[i].estado = EST_INATIVO;
      tiro_ini[i].estado = EST_INATIVO;
   }

   for(i=0;i<10;i++)
   {
      inimigo[i].estado = EST_INATIVO;
      inimigo[i].x = -50;
   }

   float player1_x = SCREEN_X / 2.0 - imagem_player1_SIZE / 2.0;
   float player1_y = SCREEN_Y / 2.0 - imagem_player1_SIZE / 2.0;

   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   bool game_over = false;
   bool next_level = false;

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
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

   if (!al_reserve_samples(3)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }

   janela_fase2 = al_create_display(SCREEN_X, SCREEN_Y);
   if(!janela_fase2) {
      fprintf(stderr, "failed to create janela_fase2!\n");
      al_destroy_timer(timer);
      return -1;
   }
   imagem_player1 = al_create_bitmap(imagem_player1_SIZE, imagem_player1_SIZE);
   if(!imagem_player1) {
      fprintf(stderr, "failed to create imagem_player1 bitmap!\n");
      al_destroy_display(janela_fase2);
      al_destroy_timer(timer);
      return -1;
   }
   al_set_target_bitmap(imagem_player1);

   al_init_image_addon();

   al_clear_to_color(al_map_rgb(255, 0, 255));

   al_set_target_bitmap(al_get_backbuffer(janela_fase2));

   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(imagem_player1);
      al_destroy_display(janela_fase2);
      al_destroy_timer(timer);
      return -1;
   }

   al_register_event_source(event_queue, al_get_display_event_source(janela_fase2));

   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_clear_to_color(al_map_rgb(0,0,0));

   musica_fundo = al_load_sample( "audio/footstep2.wav" );
   som_tiro = al_load_sample("audio/tiro.wav");
   som_boss = al_load_sample("audio/tiro_boss.wav");

/******************************* LOAD IMAGES ***********************************************/

   imagem_fundo_fase1 = al_load_bitmap("imagens/fundo_game_2.png");
   imagem_ceu=al_load_bitmap("imagens/ceu_game_1.png");
   imagem_nuvem=al_load_bitmap("imagens/nuvem.png");
   imagem_vidas = al_load_bitmap("imagens/vida.png");
   imagem_vidas_cinza = al_load_bitmap("imagens/vida_cinza.png");
   imagem_trem[0] = al_load_bitmap("imagens/trem1.png");
   imagem_trem[1] = al_load_bitmap("imagens/trem2.png");
   imagem_trem[2] = al_load_bitmap("imagens/trem3.png");
   imagem_trem[3] = al_load_bitmap("imagens/trem4.png");
   imagem_trem[4] = al_load_bitmap("imagens/trem5.png");
   imagem_trem[5] = al_load_bitmap("imagens/trem6.png");
   imagem_trem[6] = al_load_bitmap("imagens/trem7.png");
   imagem_trem[7] = al_load_bitmap("imagens/trem8.png");
   imagem_player1 = al_load_bitmap("imagens/player_1.png");
   imagem_inimigo[0] = al_load_bitmap("imagens/inimigo1.png");
   imagem_inimigo[1] = al_load_bitmap("imagens/inimigo2.png");
   imagem_inimigo[2] = al_load_bitmap("imagens/inimigo3.png");
   imagem_inimigo[3] = al_load_bitmap("imagens/inimigo4.png");
   imagem_boss[0] = al_load_bitmap("imagens/boss1.png");
   imagem_boss[1] = al_load_bitmap("imagens/boss2.png");
   imagem_boss[2] = al_load_bitmap("imagens/boss3.png");
   imagem_boss[3] = al_load_bitmap("imagens/boss4.png");
   imagem_arvore[0] = al_load_bitmap("imagens/arvore1.png");
   imagem_arvore[1] = al_load_bitmap("imagens/arvore2.png");
   imagem_arvore[2] = al_load_bitmap("imagens/arvore3.png");
   imagem_arvore[3] = al_load_bitmap("imagens/arvore4.png");
   soltador = al_load_bitmap("imagens/vida_cinza.png");
   imagem_tiro = al_load_bitmap("imagens/bala.png");
   imagem_estacao = al_load_bitmap("imagens/estacao_de_trem.png");
   vida_boos_meio1 = al_load_bitmap("imagens/life_boss_neutro2.png");
   vida_boss_canto1 = al_load_bitmap("imagens/life_boss_neutro1.png");
   vida_boos_meio2 = al_load_bitmap("imagens/life_boss_active2.png");
   vida_boss_canto2 = al_load_bitmap("imagens/life_boss_active1.png");
   imagem_tiro_boss1 = al_load_bitmap("imagens/tiro_boss1.png");
   imagem_tiro_boss2 = al_load_bitmap("imagens/tiro_boss2.png");
   imagem_tiro_boss3 = al_load_bitmap("imagens/tiro_boss3.png");

/***************************** END LOAD IMAGES *********************************************/

   al_flip_display();

   al_start_timer(timer);

   al_play_sample(musica_fundo, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

   while(!doexit && opcao==0) {

      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
         cont_tempo++;

         if(key[KEY_LEFT] && player1_x >= 24.0) {
            player1_x -= 3.0;
         }
         if(key[KEY_RIGHT] && player1_x <= SCREEN_X - imagem_player1_SIZE - 30.0) {
            player1_x += 3.0;
         }
         if(key[KEY_UP]&&delayTiro) {
            for(i=0;i<TIROS;i++)
            {
               if(tiro[i].estado == EST_INATIVO)
               {
                  tiro[i].x = player1_x+8;
                  tiro[i].y = 415;
                  tiro[i].estado = EST_ATIVO;
                  delayTiro=0;
                  al_play_sample(som_tiro, 0.3, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                  break;
               }
            }
         }
         redraw = true;
/************************************************************************************////

                 if(cont_nuvem<-2560)
                 {
                  cont_nuvem=-1;
                 }
                 else
                 {
                    cont_nuvem--;
                 }
                 if(estacao.x>500)
                 {
                    if(cont_fundo<-2560)
                    {
                     cont_fundo=-2;
                    }
                    else
                    {
                       cont_fundo-=2;
                    }
                    if(cont_tempo%5==0)
                    {
                      cont_trem++;
                      cont_ini++;
                    }
                    if(cont_ini==4)
                    {
                       cont_ini=0;
                    }
                    if(cont_trem==8)
                    {
                      cont_trem=0;
                      delayTiro=1;
                    }
                 }
                if(cont_tempo%100==0 && boss.estado==EST_ATIVO)
                {
                    delayTiro1=1;
                    delayTiro2=1;
                    delayTiro3=1;
                }
                 if(estacao.estado==EST_ATIVO)
                {
                   estacao.x-=1;
                }
        //////////////////////////////////////////////////////////////////////
                 for(i=0;i<TIROS;i++) /// deixa inativo os tiros do personagem que sairam da tela
                 {
                    if(tiro[i].estado == EST_ATIVO)
                    {
                       tiro[i].y -= TIRO_VEL;
                       if(tiro[i].y < 5)
                       {
                          tiro[i].estado = EST_INATIVO;
                       }
                    }
                 }
                 for(i=0;i<TIROS;i++) /// colisão do tiro com o boss
                 {
                    if(tiro[i].estado==EST_ATIVO && boss.estado==EST_ATIVO)
                    {
                       if(tiro[i].x>boss.x&&tiro[i].y>boss.y&&
                          tiro[i].x<boss.x+96&&tiro[i].y<boss.y+54)
                       {
                          cont_vida_boss--;
                          tiro[i].estado=EST_INATIVO;
                          if(cont_vida_boss==0)
                          {
                             boss.estado=EST_INATIVO;
                             boss.x=-500;
                             cont_score+=100;
                             BOSS_DEAD=EST_ATIVO;
                          }
                       }
                    }
                 }
                 for(i=0;i<10;i++) /// colisão do tiro com o inimigo
                 {
                    if(inimigo[i].estado==EST_ATIVO)
                    {
                       for(j=0;j<TIROS;j++)
                       {
                          if(tiro[j].estado == EST_ATIVO)
                          {
                             if(tiro[j].x>inimigo[i].x&&tiro[j].y>inimigo[i].y&&
                                tiro[j].x<inimigo[i].x+46&&tiro[j].y<inimigo[i].y+36)
                             {
                                inimigo[i].estado = EST_INATIVO;
                                tiro[j].estado = EST_INATIVO;
                                inimigo[i].x = -200;
                                inimigo[i].y = 200;
                                cont_score+=5;
                             }
                          }
                       }
                    }
                 }
                 for(i=0;i<TIROS;i++) /// colisao da bala com o personagem
                 {
                    if(tiro_ini[i].estado==EST_ATIVO)
                    {
                       if(boss.estado){
                          if(i==2){
                             if((tiro_ini[i].x < player1_x && tiro_ini[i].y+4 > 415 &&
                               tiro_ini[i].x+24 > player1_x+16 && tiro_ini[i].y+4 < 415+24)
                                ||
                                (tiro_ini[i].x < player1_x+16 && tiro_ini[i].y+4 > 415 &&
                               tiro_ini[i].x+24 > player1_x && tiro_ini[i].y+4 < 415+24))
                            {
                               tiro_ini[i].estado = EST_INATIVO;
                               player1_x = 1200;
                               cont_vidas++;
                            }
                         }
                         else if(tiro_ini[i].x > player1_x && tiro_ini[i].y+4 > 415 &&
                          tiro_ini[i].x < player1_x+16 && tiro_ini[i].y+4 < 415+24)
                         {
                            tiro_ini[i].estado = EST_INATIVO;
                            player1_x = 1200;
                            cont_vidas++;
                         }

                       }
                       else if(tiro_ini[i].x > player1_x && tiro_ini[i].y+4 > 415 &&
                          tiro_ini[i].x < player1_x+16 && tiro_ini[i].y+4 < 415+24)
                         {
                            tiro_ini[i].estado = EST_INATIVO;
                            player1_x = 1200;
                            cont_vidas++;
                         }
                    }
                 }
                 if(cont_tempo<10800)/*10800)*/ /// vai se mexer pra cima do personagem enquanto o tempo for menor que 3min
                 {
                    for(i=0;i<10;i++) /// movimento X do inimigo
                    {
                       if(inimigo[i].estado==EST_ATIVO)
                       {
                          MOVIMENTOX(player1_x,i,inimigo,10,tiro,TIROS); /// movimento do inimigo
                       }
                    }
                 }
                 else /// qndo tempo menor que 3min eles saem da tela e ficam inativos
                 {
                    for(i=0;i<10;i++)
                    {
                       if(inimigo[i].estado==EST_ATIVO)
                       {
                          inimigo[i].x -= 1;
                       }
                       if(inimigo[i].x<-40)
                       {
                          inimigo[i].estado = EST_INATIVO;
                       }
                    }
                 }
                 for(i=0;i<10;i++) /// movimento Y do inimigo
                 {
                    inimigo[i].y+=MOVIMENTOY(player1_x,i,inimigo,10);
                 }
                 if(boss.estado==EST_ATIVO) /// movimento e tiro do boss
                 {
                        if(tiro_ini[2].y>=431)
                        {
                            tiro_ini[2].estado=EST_INATIVO;
                        }
                        if(tiro_ini[1].y>=431)
                        {
                            tiro_ini[1].estado=EST_INATIVO;
                        }
                        if(tiro_ini[3].y>=431)
                        {
                            tiro_ini[3].estado=EST_INATIVO;
                        }
                    if(tiro_ini[1].estado==EST_INATIVO && delayTiro1){

                        tiro_ini[1].estado=EST_ATIVO;
                        tiro_ini[1].x=boss.x-1;//+(96/2);
                        tiro_ini[1].y=boss.y+(54/2);
                        delayTiro1=0;
                    }
                    if(tiro_ini[1].estado==EST_ATIVO){

                        tiro_ini[1].x-=1;
                        tiro_ini[1].y+=5;

                    }

                    if(tiro_ini[2].estado==EST_INATIVO && delayTiro2){

                        tiro_ini[2].estado=EST_ATIVO;
                        tiro_ini[2].x=boss.x+(20/2);
                        tiro_ini[2].y=boss.y+(54);
                        delayTiro2=0;
                    }
                    if(tiro_ini[2].estado==EST_ATIVO)
                    {

                        tiro_ini[2].y+=5;

                    }

                    if(tiro_ini[3].estado==EST_INATIVO && delayTiro3){

                        tiro_ini[3].estado=EST_ATIVO;
                        tiro_ini[3].x=boss.x+55;//+(96/2);
                        tiro_ini[3].y=boss.y+26;
                        delayTiro3=0;
                    }
                    if(tiro_ini[3].estado==EST_ATIVO){

                        tiro_ini[3].x+=1;
                        tiro_ini[3].y+=5;

                    }
                    MOVIMENTOX_BOSS(player1_x,0,&boss,1,tiro,TIROS);
                    boss.y+=MOVIMENTOY_BOSS(player1_x,0,&boss,1);
                    //MOVIMENTO_BOSS_X(player1_x,boss,tiro,TIROS);
                    //boss.y+=MOVIMENTO_BOSS_Y(player1_x,boss);
                 }
        //////////////////////////////////////////////////////////////////////

                 for(i=0;i<12;i++) /// DEIXA INATIVO OS arvoreS QUE SAIRAM DA TELA
                 {
                    if(arvore[i].estado == EST_ATIVO)
                    {
                       if(arvore[i].x<-20)
                       {
                          arvore[i].estado==EST_INATIVO;
                       }
                       else
                       {
                          arvore[i].x-=2;
                       }
                    }
                 }

                 if(cont_tempo%1==0 && estacao.estado==EST_INATIVO)
                 {
                    //for(i=0;i<5;i++)
                    //{
                       MEXESOLTA(1);  /// MEXE OS ARVORES
                    //}
                 }
                 if(cont_tempo%250==0 && estacao.estado==EST_INATIVO)   /// SOLTADOR DE ARVORES
                 {
                    for(i=0;i<12;i++)
                    {
                       if(i<11)
                       {	srand ( time(NULL) );
                          if (arvore[i].estado==EST_INATIVO && rand()%2 ==0)
                          {
                              arvore[i].x=soltaObjetos[1].x;
                              arvore[i].y=soltaObjetos[1].y;
                              arvore[i].estado=EST_ATIVO;
                              i = 12;
                          }
                       }
                    }
                 }
                 if(cont_tempo%200==0 && cont_tempo<10800)/*10800)*/   /// soltador de inimigos só solta qndo for menor que 3min.
                 {
                    if(inimigo_delay==0)
                    {
                       for(i=0;i<10;i++)
                       {
                          if(inimigo[i].estado==EST_INATIVO)
                          {
                             inimigo[i].estado = EST_ATIVO;
                             inimigo[i].y = soltaObjetos[1].y;
                             i=10;
                             inimigo_delay=0;
                          }
                       }
                    }
                    else
                    {
                       inimigo_delay=0;
                    }
                 }
                 for(i=0;i<10;i++) /// tiro do inimigo contra o personagem 1
                 {
                    if(inimigo[i].estado == EST_ATIVO && inimigo[i].x+23 == player1_x+5)
                    {
                       tiro_ini[i].estado = EST_ATIVO;
                       tiro_ini[i].x = inimigo[i].x+25;
                       tiro_ini[i].y = inimigo[i].y+36;
                       delayTiro1 = 0;
                       al_play_sample(som_tiro, 0.3, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                       break;
                    }/*
                    if(inimigo[i].estado == EST_ATIVO && (415-inimigo[i].y)==
                       abs(inimigo[i].x+23 - player1_x+5))
                    {
                       tiro_ini[i].estado = EST_ATIVO;
                       tiro_ini[i].x = inimigo[i].x+25;
                       tiro_ini[i].y = inimigo[i].y+36;
                       delayTiro1 = 0;
                       break;
                    }*/
                 }
                 for(i=0;i<TIROS;i++) /// tiro do inimigo
                 {
                    if(tiro_ini[i].estado == EST_ATIVO && delayTiro1)
                    {
                       tiro_ini[i].y += TIRO_VEL;
                       if(tiro_ini[i].y > 460)
                       {
                          tiro_ini[i].estado = EST_INATIVO;
                       }
                    }
                 }
                 if(cont_tempo>10800 && boss.estado==EST_INATIVO && BOSS_DEAD==EST_ATIVO)
                 {
                    estacao.estado = EST_ATIVO;
                 }
                 if(cont_tempo>10800 && estacao.estado==EST_INATIVO)//10800)
                 {
                    for(i=0;i<10;i++)
                    {
                       if(inimigo[i].estado==EST_INATIVO) /// verifica se todos os inimigos estão ativos
                       {
                          ATIVOS=0; /// todos inativos
                       }
                       else
                       {
                          ATIVOS=1; /// tem pelo menos 1 ativo e o boss não pode entrar ainda
                          break;
                       }
                    }
                    if(ATIVOS==0 && BOSS_DEAD!=EST_ATIVO)
                    {
                       boss.estado = EST_ATIVO;
                    }
                 }
/************************************************************************************////
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                                 key[KEY_UP] = true;
                                 break;
            case ALLEGRO_KEY_DOWN:
                                 key[KEY_DOWN] = true;
                                 break;
            case ALLEGRO_KEY_LEFT:
                                 key[KEY_LEFT] = true;
                                 break;
            case ALLEGRO_KEY_RIGHT:
                                 key[KEY_RIGHT] = true;
                                 break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                                 key[KEY_UP] = false;
                                 break;
            case ALLEGRO_KEY_DOWN:
                                 key[KEY_DOWN] = false;
                                 break;
            case ALLEGRO_KEY_LEFT:
                                 key[KEY_LEFT] = false;
                                 break;
            case ALLEGRO_KEY_RIGHT:
                                 key[KEY_RIGHT] = false;
                                 break;
            case ALLEGRO_KEY_ESCAPE:
                                 doexit = true;
                                 break;
         }
      }
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
/// ----------------------------- COMEÇA A DESENHAR --------------------------------------------- ///
         al_clear_to_color(al_map_rgb(255,255,255));
         al_draw_bitmap(imagem_ceu,0,0,0);                        /// desenha o ceu
         al_draw_bitmap(imagem_nuvem,cont_nuvem,0,0);             /// desenha as nuvens
         al_draw_bitmap(imagem_fundo_fase1,cont_fundo,0,0);     /// desenha o fundo
         if(BOSS_DEAD==EST_ATIVO)
         {
             //estacao.y=200;
             if(estacao.x>500)
             {
                 estacao.x--;
             }
            al_draw_bitmap(imagem_estacao,estacao.x,estacao.y,0);
         }
/// --------------------------------------COMEÇA A DESENHAR OS TIROS DO BOSS-------------------------///
        if(boss.estado==EST_ATIVO){
            if(tiro_ini[1].estado==EST_ATIVO){

                al_draw_bitmap(imagem_tiro_boss1,tiro_ini[1].x,tiro_ini[1].y,0);
            }
            if(tiro_ini[2].estado==EST_ATIVO){

                al_draw_bitmap(imagem_tiro_boss2,tiro_ini[2].x,tiro_ini[2].y,0);
            }
            if(tiro_ini[3].estado==EST_ATIVO){

                al_draw_bitmap(imagem_tiro_boss3,tiro_ini[3].x,tiro_ini[3].y,0);
            }

        }
/// --------------------------------------PARA DE DESENHAR OS TIROS DO BOSS-------------------------///
         al_draw_bitmap(imagem_trem[cont_trem],0,431,4);        /// desenha o trem
         if(cont_vidas!=qnt_vidas)
         {
            al_draw_bitmap(imagem_player1,player1_x,415,0);       /// desenha o personagem1
         }
////////////// VIDA DO BOSS
         if(boss.estado==EST_ATIVO && BOSS_DEAD==EST_INATIVO)
         {
            for(i=0;i<10;i++) /// desenha a caixa onde vai ficar o life do boss
            {
               if(i==0)
               {
                  al_draw_bitmap(vida_boss_canto1, boss.x-2-55, boss.y-2-100, 0);
               }
               else if(i==9)
               {
                  al_draw_bitmap(vida_boss_canto1, (boss.x-2+(i*20)+2-55), boss.y-2-100, 3);
               }
               else
               {
                  al_draw_bitmap(vida_boos_meio1, (boss.x-2+(i*20)+2-55), boss.y-2-100, 3);
               }
            }
            for(i=0;i<cont_vida_boss;i++) /// desenha o life do boss
            {
               if(i==0)
               {
                  al_draw_bitmap(vida_boss_canto2, boss.x-55, boss.y-100, 0);
               }
               else if(i==9)
               {
                  al_draw_bitmap(vida_boss_canto2, (boss.x+(i*20)-55), boss.y-100, 3);
               }
               else
               {
                  al_draw_bitmap(vida_boos_meio2, (boss.x+(i*20)-55), boss.y-100, 3);
               }
            }
         }
////////////// END VIDA DO BOSS
         //al_draw_bitmap(soltador,1240,soltaObjetos[1].y,0); /// soltador
//////////// BOSS
         if(boss.estado==EST_ATIVO && BOSS_DEAD!=EST_ATIVO)
         {
            al_draw_bitmap(imagem_boss[cont_ini],boss.x,boss.y,0); /// desenha o boss
         }
//////////// END BOSS
////////////////// INIMIGO
         //al_draw_bitmap(imagem_inimigo[cont_ini],200,300,0);
         for(i=0;i<10;i++)
         {
            if(inimigo[i].estado==EST_ATIVO)
            {
               al_draw_bitmap(imagem_inimigo[cont_ini],inimigo[i].x,inimigo[i].y,0); ///desenha o inimigo
            }
         }
////////////////// END INIMIGO
////////////////// TIROS
         for(i=0;i<5;i++)
         {
            if(tiro[i].estado==EST_ATIVO)
            {
               al_draw_bitmap(imagem_tiro,tiro[i].x,tiro[i].y,0); /// desenha o tiro do personagem
            }
            if(tiro_ini[i].estado == EST_ATIVO)
            {
               al_draw_bitmap(imagem_tiro,tiro_ini[i].x,tiro_ini[i].y,3); /// desenha o tiro do inimigo
            }
         }
////////////////// END TIROS
////////////////// ARVORE
         for(i=0;i<12;i++)
         {
            if(arvore[i].estado==EST_ATIVO)
            {
               if(i==0 || i==4 || i==8)
               {
                  al_draw_bitmap(imagem_arvore[0],arvore[i].x,arvore[i].y,0); /// desenha as arvores ativos
               }
               if(i==1 || i==5 || i==9)
               {
                  al_draw_bitmap(imagem_arvore[1],arvore[i].x,arvore[i].y,0); /// desenha os arvores ativos
               }
               if(i==2 || i==6 || i==10)
               {
                  al_draw_bitmap(imagem_arvore[2],arvore[i].x,arvore[i].y,0); /// desenha os arvores ativos
               }
               if(i==3 || i==7 || i==11)
               {
                  al_draw_bitmap(imagem_arvore[3],arvore[i].x,arvore[i].y,0); /// desenha os arvores ativos
               }
            }
         }
////////////////// END ARVORE
////////////////// FASE 1
         if(cont_tempo>30 && cont_tempo<200)
         {
            al_draw_textf(font_fase,al_map_rgb(0,0,0),545,360,ALLEGRO_ALIGN_LEFT,"F");
         }
         if(cont_tempo>40 && cont_tempo<200)
         {
            al_draw_textf(font_fase,al_map_rgb(0,0,0),560,360,ALLEGRO_ALIGN_LEFT,"A");
         }
         if(cont_tempo>50 && cont_tempo<200)
         {
            al_draw_textf(font_fase,al_map_rgb(0,0,0),580,360,ALLEGRO_ALIGN_LEFT,"S");
         }
         if(cont_tempo>60 && cont_tempo<200)
         {
            al_draw_textf(font_fase,al_map_rgb(0,0,0),600,360,ALLEGRO_ALIGN_LEFT,"E");
         }
         if(cont_tempo>70 && cont_tempo<200)
         {
            al_draw_textf(font_fase,al_map_rgb(0,0,0),640,360,ALLEGRO_ALIGN_LEFT,"2");
         }
////////////////// END FASE 1
////////////////// imagem_vidas
         for(i=0;i<qnt_vidas;i++)
         {
            al_draw_bitmap(imagem_vidas,(1245-(i*35)),10,0); /// desenha as imagem_vidas
         }if(tiro_ini[i].x > player1_x && tiro_ini[i].y+4 > 415 &&
                          tiro_ini[i].x < player1_x+16 && tiro_ini[i].y+4 < 415+24)
                         {
                            tiro_ini[i].estado = EST_INATIVO;
                            player1_x = 1200;

                            cont_vidas++;
                         }

         for(i=0;i<cont_vidas;i++)
         {
            al_draw_bitmap(imagem_vidas_cinza,(1245-(i*35)),10,0); /// desenha as imagem_vidas
         }
////////////////// END imagem_vidas
////////////////// FONTS
         al_draw_textf(font_tempo, al_map_rgb(0,0,0), 5.0, 10.0,ALLEGRO_ALIGN_LEFT,
                        "Tempo: %d%d:%d%d", (cont_tempo/3600)/10,(cont_tempo/3600)%10,
                        ((cont_tempo/60)%60)/10,((cont_tempo/60)%60)%10);  /// desenha o tempo
         al_draw_textf(font_tempo, al_map_rgb(0,0,0),570.0,10.0,ALLEGRO_ALIGN_LEFT,
                        "Score: %2d.%1d%1d%1d", (cont_score/100)/10,((cont_score/10)/10)%10,
                        (cont_score/10)%10,(cont_score%10));               /// desenha a pontuação
         al_draw_textf(font_vidas, al_map_rgb(0,0,0), 1100, 15,ALLEGRO_ALIGN_RIGHT,
                        "vidas:");                                         /// desenha "imagem_vidas:"

////////////////// END FONTS
        if(boss.estado!=EST_ATIVO)
        {
            delayTiro1=1;
        }
////////////////// GAME OVER
         if(cont_vidas==qnt_vidas)
         {
            al_draw_textf(font_gameover, al_map_rgb(0,0,0), 800, 350,ALLEGRO_ALIGN_RIGHT,
                        "game over");                                      /// desenha o GAME OVER
            game_over=true;
            doexit=true;
         }
////////////////// END GAME OVER
//////////////// NEXT LEVEL
         if(estacao.x<530)
         {
            al_draw_textf(font_gameover, al_map_rgb(0,0,0), 875, 350,ALLEGRO_ALIGN_RIGHT,
                        "CONGRATULATIONS");                                      /// desenha congratulations e vai pra proxima fase
            next_level=true;
            doexit=true;
            opcao=3;
            al_rest(3);
         }
//////////////// END NEXT LEVEL
         al_flip_display();
      }
   }

   if(game_over==true || next_level==true)
   {
      al_rest(5.0); /// deixa a tela aberta por alguns segundos para que ele veja o game over
   }

   al_destroy_bitmap(imagem_player1);
   al_destroy_timer(timer);
   al_destroy_display(janela_fase2);
   al_destroy_event_queue(event_queue);
   al_destroy_sample(musica_fundo);
   al_destroy_sample(som_boss);
   al_destroy_sample(som_tiro);

   if(game_over==true)
   {
      return 0;      /// game over e volta para o menu
   }
   else
   {
      return opcao;      /// avança para a segunda fase
   }
   //return 1;
}

#endif // FASE2_H_INCLUDED
