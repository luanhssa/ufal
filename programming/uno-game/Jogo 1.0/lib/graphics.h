#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

   Mouse *posMouse;

    /**
      *  Função que adiciona um mouse dada as posições x e y.
      */
   Mouse* addMouse(int posX, int posY);

    /**
      *  Retorna o valor do X e do Y respectivamente.
      */
   int getMouseX();
   int getMouseY();

    /**
      *  Retorna o novo mouse.
      */
   Mouse* pushMouse(Mouse *newMouse, int newX, int newY);

    /**
      *    Função draw() criada para facilitar o entendimento.
      */
   void drawMenu(ALLEGRO_FONT *fontMenu, ALLEGRO_COLOR colorMainMenu,
              ALLEGRO_COLOR colorMenuNovoJogo, ALLEGRO_COLOR colormenuHelp,
              ALLEGRO_COLOR colorMenuExtras, ALLEGRO_COLOR colorMenuSair);

    /**
      *  Função que deixar a fonte na cor preto ao passar o mouse por cima da palavra.
      *  A Cor normal é branco.
      */
   void mouseHover(float posX1, float posY1, float posX2, float posY2, ALLEGRO_COLOR *color, bool ativo);

    /**
      *  Função que desenha um botão nas coordenadas x e y.
      *  rx = o raio do arredondamento do botão (em pixels).
      *  height = a altura do botão (em pixels).
      *  color = a cor do botão (ex: al_rgb_(255,255,255) -> cor branca).
      *  width = a largura do botão (em pixels).
      */
   void drawButton(float x, float y, float rx, float height, float width,ALLEGRO_COLOR color);

   void drawPlayerCards(Player* jogador, int carta, int posx);

   int playerCards(Player* jogador);

   void drawCard(int id, int posx, int posy);

   void drawDescarte(int id);

   void drawBaralho();

   void mudarCor(Game* game);

#endif // GRAPHICS_H_INCLUDED
