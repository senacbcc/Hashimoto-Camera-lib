#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "camera.h"



#define FPS 60



void erro(char *mensagem) {
  fputs(mensagem, stderr);

  exit(EXIT_FAILURE);
}


int main() {
  camera *cam = camera_inicializa(0);
  if(!cam)
    erro("erro na inicializacao da camera\n");

  int largura = cam->largura;
  int altura = cam->altura;

  if(!al_init())
    erro("erro na inicializacao do allegro\n");

  if(!al_init_image_addon())
    erro("erro na inicializacao do adicional de imagem\n");

  if(!al_init_primitives_addon())
    erro("erro na inicializacao do adicional de primitivas\n");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
  if(!timer)
    erro("erro na criacao do relogio\n");

  ALLEGRO_DISPLAY *display = al_create_display(2 * largura, altura);
  if(!display)
    erro("erro na criacao da janela\n");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  if(!queue)
    erro("erro na criacao da fila\n");

  al_register_event_source(queue, al_get_timer_event_source(timer));
  al_register_event_source(queue, al_get_display_event_source(display));

  al_start_timer(timer);

  /**********/

  unsigned char ***matriz = camera_aloca_matriz(cam);

  ALLEGRO_COLOR cor = al_map_rgb_f(0, 0, 1);

  ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);

  ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, largura, altura);

  ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, largura, 0, largura, altura);

  /**********/

  int desenhar = 0;
  int terminar = 0;

  while(1) {
    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      desenhar = 1;
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      terminar = 1;
      break;
    default:
      printf("evento desconhecido\n");
    }

    if(terminar)
      break;

    if(desenhar && al_is_event_queue_empty(queue)) {
      desenhar = 0;
      camera_atualiza(cam);

      /**********/

      float cy = 0;
      float cx = 0;
      int cn = 0;

      for(int y = 0; y < altura; y++)
	for(int x = 0; x < largura; x++) {
	  int r = cam->quadro[y][x][0];
	  int g = cam->quadro[y][x][1];
	  int b = cam->quadro[y][x][2];

	  if(r > g + b) {
	    cy += y;
	    cx += x;
	    cn++;

	    matriz[y][x][0] = 255;
	    matriz[y][x][1] = 255;
	    matriz[y][x][2] = 255;
	  }
	  else {
	    matriz[y][x][0] = 0;
	    matriz[y][x][1] = 0;
	    matriz[y][x][2] = 0;
	  }
	}

      /**********/

      camera_copia(cam, cam->quadro, esquerda);

      if(cn > 0)
	al_draw_circle(cx / cn, cy / cn, 100, cor, 1);

      camera_copia(cam, matriz, direita);

      /**********/

      al_flip_display();
    }
  }

  /**********/

  al_destroy_bitmap(direita);

  al_destroy_bitmap(esquerda);

  camera_libera_matriz(cam, matriz);

  /**********/

  al_stop_timer(timer);

  al_unregister_event_source(queue, al_get_display_event_source(display));
  al_unregister_event_source(queue, al_get_timer_event_source(timer));

  al_destroy_event_queue(queue);
  al_destroy_display(display);
  al_destroy_timer(timer);

  al_shutdown_primitives_addon();
  al_shutdown_image_addon();
  al_uninstall_system();

  camera_finaliza(cam);

  return EXIT_SUCCESS;
}
