#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "imagen.h"
#include "crypt.h"

int main()
{
  bmpInfoHeader info;
  unsigned char *img;
  unsigned char *img2;
  bmpFileHeader fileHeader;

  img=LoadBMP("paisaje.bmp", &info, &fileHeader);
  img2=EditImage(&info, img);
  WriteBMP("paisaje2.bmp", &info, img2, &fileHeader);
  //DisplayInfo(&info); 

  return 0;
}

unsigned char *EditImage(bmpInfoHeader *info, unsigned char *img){
  unsigned char *img2;
  int i;
  int j=0;
  double *mensaje;
  mensaje=Encryption();
  img2=img;

  //Introduzco el mensaje.
  for(i=0; i<7; i++){
    img2[j]=mensaje[i];
    j=j+3;
  }
  return img2;
}

unsigned char *LoadBMP(char *filename, bmpInfoHeader *bInfoHeader, bmpFileHeader *fileHeader)
{

  FILE *f;
  unsigned char *imgdata;   /* datos de imagen */
  uint16_t type;        /* 2 bytes identificativos */

  f=fopen (filename, "r");
  if (!f)
    return NULL;        /* Si no podemos leer, no hay imagen*/

  /* Leemos los dos primeros bytes */
  fread(&type, sizeof(uint16_t), 1, f);
  if (type !=0x4D42)        /* Comprobamos el formato */
    {
      fclose(f);
      return NULL;
    }

  /* Leemos la cabecera de fichero completa */

  fread(fileHeader, sizeof(bmpFileHeader), 1, f);

  /* Leemos la cabecera de información completa */
  fread(bInfoHeader, sizeof(bmpInfoHeader), 1, f);

  /* Reservamos memoria para la imagen, ¿cuánta?
     Tanto como indique imgsize */
  imgdata=(unsigned char*)malloc(bInfoHeader->imgsize);

  /* Nos situamos en el sitio donde empiezan los datos de imagen,
   nos lo indica el offset de la cabecera de fichero*/
  fseek(f, fileHeader->offset, SEEK_SET);

  /* Leemos los datos de imagen, tantos bytes como imgsize */
  fread(imgdata, bInfoHeader->imgsize,1, f);

  /* Cerramos */
  fclose(f);

  /* Devolvemos la imagen */
  return imgdata;
}


void *WriteBMP(char *filename, bmpInfoHeader *bInfoHeader, unsigned char *image, bmpFileHeader *fileHeader)
{

  FILE *f;
  unsigned char *imgdata;   /* datos de imagen */
  uint16_t type;        /* 2 bytes identificativos */

  f=fopen (filename, "w");
  if (!f)
    return NULL;        /* Si no podemos leer, no hay imagen*/

  /* Escribimos los dos primeros bytes */
  type=0x4D42;
  fwrite(&type, sizeof(uint16_t), 1, f);

  /* Escribimos la cabecera de fichero completa */
  fwrite(fileHeader, sizeof(bmpFileHeader), 1, f);


  /* Escribimos la cabecera de información completa */
  fwrite(bInfoHeader, sizeof(bmpInfoHeader), 1, f);


  /* Nos situamos en el sitio donde empiezan los datos de imagen,
   nos lo indica el offset de la cabecera de fichero*/
  fseek(f, fileHeader->offset, SEEK_SET);


  /* Escribimos los datos de imagen, tantos bytes como imgsize */
  fwrite(image, bInfoHeader->imgsize,1, f);

  /* Cerramos */
  fclose(f);

  /* Devolvemos la imagen */
  return 0;
}

void DisplayInfo(bmpInfoHeader *info)
{
  printf("Tamaño de la cabecera: %u\n", info->headersize);
  printf("Anchura: %d\n", info->width);
  printf("Altura: %d\n", info->height);
  printf("Planos (1): %d\n", info->planes);
  printf("Bits por pixel: %d\n", info->bpp);
  printf("Compresión: %d\n", info->compress);
  printf("Tamaño de datos de imagen: %u\n", info->imgsize);
  printf("Resolucón horizontal: %u\n", info->bpmx);
  printf("Resolucón vertical: %u\n", info->bpmy);
  printf("Colores en paleta: %d\n", info->colors);
  printf("Colores importantes: %d\n", info->imxtcolors);
}

