#include "principal.h"

struct mouse{
   int x;
   int y;
};
Mouse* addMouse(int posX, int posY){
   Mouse *newMouse = (Mouse*) malloc(sizeof(Mouse));
   newMouse->x = posX;
   newMouse->y = posY;

   return newMouse;
}
int getMouseX(){
   return posMouse->x;
}
int getMouseY(){
   return posMouse->y;
}
Mouse* pushMouse(Mouse *newMouse, int newX, int newY){
   posMouse->x = newX;
   posMouse->y = newY;
   return posMouse;
}

void drawMenu(ALLEGRO_FONT *fontMenu, ALLEGRO_COLOR colorMainMenu,
              ALLEGRO_COLOR colorMenuNovoJogo, ALLEGRO_COLOR colormenuHelp,
              ALLEGRO_COLOR colorMenuOpcoes, ALLEGRO_COLOR colorMenuSair){
   al_draw_filled_rectangle(0.5, 0.5, (displayWidht*0.22), displayHeigh, colorRed);
   al_draw_filled_rectangle((displayWidht*0.20), 0.5, (displayWidht*0.22),
                             displayHeigh, colorDarkRed);
   if(menuMainMenu){
      al_draw_filled_rectangle(0.5, (displayHeigh*0.29),
                                (displayWidht*0.20), (displayHeigh*0.38), colorDarkRed);
   }else if(menuHelp){
      al_draw_filled_rectangle(0.5, (displayHeigh*0.41),
                                (displayWidht*0.20), (displayHeigh*0.51), colorDarkRed);
   }else if(menuOpcoes){
      al_draw_filled_rectangle(0.5, (displayHeigh*0.54),
                                (displayWidht*0.20), (displayHeigh*0.64), colorDarkRed);
   }
   al_draw_text(fontMenu, colorMainMenu, (displayWidht*0.01),
                 (displayHeigh*0.32),ALLEGRO_ALIGN_LEFT, "Menu Principal");
   al_draw_text(fontMenu, colormenuHelp, (displayWidht*0.01),
                 (displayHeigh*0.45),ALLEGRO_ALIGN_LEFT, "Ajuda");
   al_draw_text(fontMenu, colorMenuOpcoes, (displayWidht*0.01),
                 (displayHeigh*0.58),ALLEGRO_ALIGN_LEFT, "Opcões");
   al_draw_text(fontMenu, colorMenuSair, (displayWidht*0.01),
                 (displayHeigh*0.71),ALLEGRO_ALIGN_LEFT, "Sair");
}

void mouseHover(float posX1, float posY1, float posX2, float posY2, ALLEGRO_COLOR *color, bool ativo){
   if(ativo){
      *color = colorBlack;
   }
   else if((posMouse->x >= posX1 && posMouse->x <= posX2) && (posMouse->y >= posY1 && posMouse->y <= posY2)){
      *color = colorBlack;
   }
   else{
      *color = colorWhite;
   }
}

void drawButton(float x, float y, float rx, float height, float width, ALLEGRO_COLOR color){
   al_draw_filled_ellipse(x, y, rx, height, color);
   al_draw_filled_ellipse(x+width, y, rx, height, color);
   al_draw_filled_rectangle(x+0.5, y-height+0.5, x+width+0.5, y+height+0.5, color);
}

int playerCards(Player* jogador){
    int qtd, esp, posx, espCards;

    qtd = getQTCards(jogador);
    esp = ((displayWidht*0.745)-(displayWidht*0.178))/2;
    if(qtd !=0) {
        espCards = 40*qtd + (126-40);
        posx = (displayWidht*0.178)+esp - espCards/2;
        return posx;
    }
    else {
        return esp;
    }

}

void drawPlayerCards(Player* jogador, int carta, int posx){
    Card* cartas = getPlayerCards(jogador);
    int i;
    int posy = (displayHeigh*0.716);
    for(i = 1;cartas!=NULL; cartas = getNextCard(cartas), i++){
        if(i == carta){
            //printf("%d\n",carta);
            drawCard(getIdCard(cartas), posx, posy-100);
            posx += 40;
        }else{
            drawCard(getIdCard(cartas), posx, posy);
            posx += 40;
        }
    }
}

void drawCard(int id, int posx, int posy){
    al_draw_bitmap(cartasImagens[id], posx, posy, 4);
}

void drawDescarte(int id){
    al_draw_bitmap(cartasImagens[id], (displayWidht*0.486), (displayHeigh*0.403), 0);
}

void drawBaralho(){
    al_draw_bitmap(imageBaralho, (displayWidht*0.387), (displayHeigh*0.410), 0);
}

void mudarCor(Game* game){
    bool escolhendo = true;

    while(escolhendo){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(getMouseX() >= (displayWidht/2)-205 && getMouseY() >= (displayHeigh/2)-205
               && getMouseX() <= (displayWidht/2) && getMouseY() <= (displayHeigh/2)){
                   setColorTop(game, 'Y');
                   escolhendo = false;
            }
            else if(getMouseX() >= (displayWidht/2)-205 && getMouseY() >= (displayHeigh/2)
               && getMouseX() <= (displayWidht/2) && getMouseY() <= (displayHeigh/2)+205){
                   setColorTop(game, 'R');
                   escolhendo = false;
            }
            else if(getMouseX() >= (displayWidht/2) && getMouseY() >= (displayHeigh/2)-205
               && getMouseX() <= (displayWidht/2)+205 && getMouseY() <= (displayHeigh/2)){
                   setColorTop(game, 'B');
                   escolhendo = false;
            }
            else if(getMouseX() >= (displayWidht/2) && getMouseY() >= (displayHeigh/2)
               && getMouseX() <= (displayWidht/2)+205 && getMouseY() <= (displayHeigh/2)+205){
                   setColorTop(game, 'G');
                   escolhendo = false;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            posMouse = pushMouse(posMouse, ev.mouse.x, ev.mouse.y);
        }
        al_draw_bitmap(imageGetCor, (displayWidht/2)-205, (displayHeigh/2)-205, 0);
        al_flip_display();
    }
}
