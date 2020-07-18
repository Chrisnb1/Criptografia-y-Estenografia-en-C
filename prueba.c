#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "imagen.h"
#include "crypt.h"

void readMsj(bmpInfoHeader *info, unsigned char *img){
    int i;
    int j=0;
    double mensaje[7];
    //Recorro hasta tener todo el mensaje.
    for(i=0; i<7; i++){
        mensaje[i]=img[j];
        j=j+3; 
    } 
    Decryption(mensaje);
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

int main(){
    
    bmpInfoHeader info;
    unsigned char *img;
    bmpFileHeader fileHeader;

    img=LoadBMP("paisaje2.bmp", &info, &fileHeader);
    readMsj(&info, img);
    return 0;
} 






