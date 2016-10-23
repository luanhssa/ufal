#include "lib/principal.h"

int main(){
    if(!iniciaAllegro()){      ///** Inicializa as funções para o Allegro funcionar corretamente.
        return -1;
    }

    if(!iniciaVariable()){    ///** Inicializa variáveis (fonte, cor, tempo, display, evento).
        return -1;
    }

    ALLEGRO_BITMAP *image = al_load_bitmap("image/teste.png"),
    *buttonImage = al_load_bitmap("image/button.png");

    int button = 0;

    Game* jogo = createGame();

    while(!doexit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if(getMouseX() >= 0.5 && getMouseY() >= (displayHeigh*0.29)
            && getMouseX() <= (displayWidht*0.20) && getMouseY() <= (displayHeigh*0.38)){
                menuMainMenu = true;
                menuHelp = false;
                menuOpcoes = false;
            }
            else if(getMouseX() >= 0.5 && getMouseY() >= (displayHeigh*0.41)
                && getMouseX() <= (displayWidht*0.20) && getMouseY() <= (displayHeigh*0.51)){
                menuHelp = true;
                menuMainMenu = false;
                menuOpcoes = false;
            }
            else if(getMouseX() >= 0.5 && getMouseY() >= (displayHeigh*0.54)
                && getMouseX() <= (displayWidht*0.20) && getMouseY() <= (displayHeigh*0.64)){
                menuOpcoes = true;
                menuMainMenu = false;
                menuHelp = false;
            }
            if(getMouseX() >= 0.5 && getMouseY() >= (displayHeigh*0.67)
                && getMouseX() <= (displayWidht*0.20) && getMouseY() <= (displayHeigh*0.77)){

                doexit = true;
                return 0;
            }
            if(getMouseX() >= (displayWidht*0.51244) && getMouseY() >= (displayHeigh*0.91)
                && getMouseX() <= ((displayWidht*0.51244)+208) && getMouseY() <= ((displayHeigh*0.91)+44)){
                if(button == 2){
                    button = 0;
                }else{
                    button = 2;
                }
            }
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            posMouse = pushMouse(posMouse, ev.mouse.x, ev.mouse.y);
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
        mouseHover(0.5, (displayHeigh*0.29), (displayWidht*0.20), (displayHeigh*0.38), &colorMainMenu, menuMainMenu);
        mouseHover(0.5, (displayHeigh*0.41), (displayWidht*0.20), (displayHeigh*0.51), &colormenuHelp, menuHelp);
        mouseHover(0.5, (displayHeigh*0.54), (displayWidht*0.20), (displayHeigh*0.64), &colorMenuOpcoes, menuOpcoes);
        mouseHover(0.5, (displayHeigh*0.67), (displayWidht*0.20), (displayHeigh*0.77), &colorMenuSair, 0);

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(colorBlack);

            drawMenu(fontMenu, colorMainMenu, colorMenuNovoJogo,
            colormenuHelp, colorMenuOpcoes, colorMenuSair);

            al_draw_bitmap(image,25,45,0);

            if(menuMainMenu){
                drawMainMenu();
                al_draw_bitmap(buttonImage, (displayWidht*0.51244), (displayHeigh*0.91), button);
                al_draw_textf(font, colorYellow, (displayWidht*0.51244)+104, (displayHeigh*0.91)+8,
                ALLEGRO_ALIGN_CENTRE, "JOGAR!");
            }
            else if(menuHelp){
                drawHelpMenu();
            }
            else if(menuOpcoes){
                drawOptionMenu();
            }

            al_draw_textf(fontMenu, colorWhite, 5.0, 10.0,ALLEGRO_ALIGN_LEFT,
            "Mouse(x):%d - Mouse(y):%d", getMouseX(), getMouseY());

            al_draw_textf(fontMenu, colorWhite, 805.0, 10.0,ALLEGRO_ALIGN_LEFT,
            "Heigh:%d - Widht:%d", displayHeigh, displayWidht);

            al_flip_display();

            if(button == 2){
                menuMainMenu = false;
                al_rest(0.5);
                button = 0;
                al_flip_display();
                game(jogo);
            }
        }
    }

    destroyVariable();

    return 0;
}
