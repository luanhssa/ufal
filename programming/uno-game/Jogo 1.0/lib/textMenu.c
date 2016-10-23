#include "principal.h"

void drawMainMenu(){
///   FILE *mainMenu = fopen("../text/mainMenu.txt","r");

   al_draw_text(fontTittle, colorYellow,(1366/2)+100,25,ALLEGRO_ALIGN_CENTRE, "Instrucões");
   al_draw_text(font, colorGray, (displayWidht*0.292825), (displayHeigh*0.260416), ALLEGRO_ALIGN_LEFT,
             "O jogador pode jogar apenas uma carta por rodada.");
   //drawButton((displayWidht*0.51244), (displayHeigh*0.91), (displayHeigh*0.0130208),
   //            (displayHeigh*0.03404), (displayWidht*0.093206), colorRed);
   //drawButton((displayWidht*0.51317), (displayHeigh*0.91), (displayHeigh*0.0104166),
   //            (displayHeigh*0.03115), (displayWidht*0.091742), colorDarkRed);
}

void drawOptionMenu(){
   al_draw_text(fontTittle, colorYellow,(1366/2)+100,25,ALLEGRO_ALIGN_CENTRE, "OPCõES");
}

void drawHelpMenu(){
   al_draw_text(fontTittle, colorYellow,(1366/2)+100,25,ALLEGRO_ALIGN_CENTRE, "AJUDA");
}


void optionMenu(float y, int maxMenu){
   al_draw_filled_rectangle(0.5, 0.5, y+0.5, (displayHeigh), colorDarkRed);
   al_draw_filled_rectangle(y+0.5-(displayWidht*0.014641), 0.5, (y+0.5), (displayHeigh), colorRed);

   if(y>=maxMenu){
      al_draw_text(fontMenu, colorResumeMenu, (displayWidht*0.01),
                 (displayHeigh*0.19),ALLEGRO_ALIGN_LEFT, "Resumir");
      al_draw_text(fontMenu, colorMainMenu, (displayWidht*0.01),
                 (displayHeigh*0.32),ALLEGRO_ALIGN_LEFT, "Menu Principal");
      al_draw_text(fontMenu, colormenuHelp, (displayWidht*0.01),
                 (displayHeigh*0.45),ALLEGRO_ALIGN_LEFT, "Ajuda");
      al_draw_text(fontMenu, colorMenuOpcoes, (displayWidht*0.01),
                 (displayHeigh*0.58),ALLEGRO_ALIGN_LEFT, "Opcões");
      al_draw_text(fontMenu, colorMenuSair, (displayWidht*0.01),
                 (displayHeigh*0.71),ALLEGRO_ALIGN_LEFT, "Sair");
   }
}

void drawPlayers(bool carlos, bool jorge, bool leonildo, bool luan, bool maxwell, bool playerONE){

   if(leonildo){
      al_draw_bitmap(leoShadow, (displayWidht/2)-307.5-165, (displayHeigh/2)-163.5,0);
   }
   if(jorge){
      al_draw_bitmap(jorgeShadow, (displayWidht/2)-307.5, (displayHeigh/2)-163.5-153,0);
   }
   if(maxwell){
      al_draw_bitmap(maxShadow, (displayWidht/2)-85.5, (displayHeigh/2)-163.5-184,0);
   }
   if(carlos){
      al_draw_bitmap(neryShadow, (displayWidht/2)+307.5-178, (displayHeigh/2)-163.5-153,0);
   }
   if(luan){
      al_draw_bitmap(luanShadow, (displayWidht/2)+307.5-20, (displayHeigh/2)-163.5,0);
   }
   if(playerONE){
      al_draw_textf(fontMenu, colorLightRed,1129, 67, ALLEGRO_ALIGN_CENTRE, "Sua Vez!");
   }

   al_draw_bitmap(imageLeo, (displayWidht/2)-307.5-165, (displayHeigh/2)-163.5,0);
   al_draw_bitmap(imageJorge, (displayWidht/2)-307.5, (displayHeigh/2)-163.5-153,0);
   al_draw_bitmap(imageMax, (displayWidht/2)-85.5, (displayHeigh/2)-163.5-184,0);
   al_draw_bitmap(imageNery, (displayWidht/2)+307.5-178, (displayHeigh/2)-163.5-153,0);
   al_draw_bitmap(imageLuan, (displayWidht/2)+307.5-20, (displayHeigh/2)-163.5,0);
}
