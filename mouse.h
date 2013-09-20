#include <dos.h>
#include <conio.h>
#include <stdio.h> 

/* Muestra mouse en la pantalla */ 
void mostrar_mouse();

/* Oculta mouse en la pantalla */ 
void ocultar_mouse();

/* Nos retorna el estado actual de la posicion y botones del mouse */ 
void estado_mouse(int *x,int *y, int *izq, int *der);

/* Inicializa el mouse en la posicion indicada */ 
void inicia_mouse(int x,int y);