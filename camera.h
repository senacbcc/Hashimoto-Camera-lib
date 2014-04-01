#include <opencv/highgui.h>

#include <allegro5/allegro.h>



typedef struct {
  unsigned char ***quadro;
  int largura, altura;
  CvCapture *capture;
} camera;



camera *camera_inicializa(int i);
void camera_finaliza(camera *cam);

void camera_atualiza(camera *cam);
void camera_copia(camera *cam, unsigned char ***matriz, ALLEGRO_BITMAP *bitmap);

unsigned char ***camera_aloca_matriz(camera *cam);
void camera_libera_matriz(camera *cam, unsigned char ***matriz);
