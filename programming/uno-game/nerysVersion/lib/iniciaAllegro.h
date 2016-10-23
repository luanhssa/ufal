#ifndef INICIAALLEGRO_H_INCLUDED
#define INICIAALLEGRO_H_INCLUDED

/**
  *   Função que inicia funções do ALLEGRO5.
  *   Esta função foi criada para ajudar e não precisar inicializar as funções.
  */
bool iniciaAllegro();
 /**
   *     Inicializa variáveis (fonte, cor, tempo, display, evento, imagens).
   */
bool iniciaVariable();

 /**
   *     Destroi variáveis que foram inicializadas.
   */
void destroyVariable();

#endif // INICIAALLEGRO_H_INCLUDED
