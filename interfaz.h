#ifndef _INTERFAZ_H__
#define _INTERFAZ_H__


#include "mouse.h"

typedef struct vp   //coordenadas de un viewport
{
	int vpxi, vpyi;
	int vpxf, vpyf;
};


void box(int startx, int starty, int endx, int endy, int color);

void inicia_interfaz(); // incia mouse

void pantalla_completa(); // viewport completo

void onfocus(int xi, int yi, int xf, int yf); // Color inverso al la zona especificada

void restaura(void *antes, int focus[]); // restaura el color inverso al original

int bucle_botones(int num); // bucle de las opciones de los botones


// Coordenadas de la ventana, opciones y nº de opciones
int menu(struct vp *coord, char *opcion[], int num); 

void puerto_vision(int xi, int yi, int xf, int yf); // selecciona un viewport

void limpia();  // limpia la linea de entrada de datos (linea 1)

#endif