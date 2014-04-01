Hashimoto-Camera-lib
====================

###Biblioteca de rotinas para acesso a camêra

####Sobre
---------------------
O arquivo ```camera.c``` contém a implementação de uma biblioteca que permite o acesso a imagens de câmeras através da plataforma OpenCV. 
Para utilizar essa biblioteca, o arquivo de cabeçalho ```camera.h``` deve ser incluído no código.

```C
#include "camera.h"
```  

Essa inclusão adiciona o tipo de dados camera.
```C
     typedef struct {
       unsigned char ***quadro;
       int largura, altura;
       CvCapture *capture;
} camera;
```

Os campos largura e altura representam a resolução em pixels da imagem de uma câmera. O campo quadro representa essa imagem como uma matriz tridimensional de caracteres sem sinal. São esses três campos que podem ser analisados pelo programa. O campo ```capture``` é auxiliar e deve ser ignorado.

A primeira dimensão da matriz representa a altura, a segunda dimensão representa a largura e a terceira representa os canais vermelho, verde e azul (RGB) de cada pixel. 

Para ilustrar essa definição, considere um apontador ```camera *cam; ```. 

```C
     cam->quadro[5][9][0]
     cam->quadro[5][9][1]
     cam->quadro[5][9][2]
```
Sabemos que os valores representam respectivamente a quantidade de vermelho, verde e azul do pixel na posição vertical 5 e posição horizontal 9. Cabe lembrar que cada quantidade, sendo um caractere sem sinal, está entre 0 e 255.

####Utilização
---------------------

Para utilizar esse tipo de dados apropriadamente, o cabeçalho também adiciona as seguintes funções básicas:

```C 
camera *camera_inicializa(int i);
```

######Aloca, inicializa e devolve o endereço de uma variável do tipo camera. O valor dessa variável representa a i-ésima câmera conectada ao computador. A contagem inicia do zero: i = 0 corresponde à primeira câmera, i = 1 corresponde à segunda câmera e assim em diante.
---------------------

```C 
void camera_finaliza(camera *cam);
```

######Finaliza e libera os recursos utilizados pela câmera representada por cam.
---------------------

```C 
void camera_atualiza(camera *cam);
```

######Atualiza a câmera representada por cam, escrevendo uma nova imagem no campo quadro. A chamada dessa função e a subsequente lógica de visão computacional devem ser executadas imediatamente antes das funções de desenho do Allegro.
---------------------

```C 
void camera_copia(camera *cam, unsigned char ***matriz, ALLEGRO_BITMAP *bitmap);
```

######Copia a imagem representada por matriz para um bitmap do Allegro. Espera-se que as resoluções de ambos sejam iguais à de uma imagem da câmera representada por cam e que a matriz tenha o mesmo formato que o campo quadro, mas a matriz não precisa necessariamente ser esse campo.
---------------------

```C 
unsigned char ***camera_aloca_matriz(camera *cam);
```

######Aloca e devolve o endereço de uma matriz com o mesmo formato do campo quadro de cam.
---------------------
```C 
void camera_libera_matriz(camera *cam, unsigned char ***matriz);
```

######Libera uma matriz com o mesmo formato do campo quadro de cam.
---------------------

####Observação
---------------------
Em algumas versões de sistemas operacionais baseados em
Debian (por exemplo Ubuntu ou elementaryOS), é necessário
modificar o arquivo camera.h. Substitua a primeira linha

```C
     #include <opencv/highgui.h>
```
pela linha
```C
     #include <opencv2/highgui/highgui_c.h>
```

####Créditos
---------------------
[![cv](http://gediscursivos.files.wordpress.com/2012/12/lattes.png?w=869)](http://lattes.cnpq.br/5909154335340519)  [Profº Marcelo Hashimoto](https://www.github.com/mhsenac)

####Links
---------------------

[OpenCV]()

[Allegro5]()

[Instalação do OpenCV e Allegro5 no Linux](https://github.com/senacbcc/OpenCV-Allegro5-InstallScript)

[Instalação do OpenCV e Allegro5 no Windows](https://github.com/ezefranca/BCC-1s14-PI3-Master-Exploder/wiki/Compila%C3%A7%C3%A3o-e-Instala%C3%A7%C3%A3o-Allegro-5-e-OpenCV-no-Windows)
