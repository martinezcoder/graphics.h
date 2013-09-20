#include "mouse.h"

  

union REGS reg;     // variable global para control del mouse 
struct REGPACK res; // variable global para lectura de datos 

  

/********************************/ 

/* Muestra mouse en la pantalla */ 

void mostrar_mouse(){ 

            reg.x.ax = 0x1; 

            int86(0x33, &reg, &reg); 

} 

  

/*******************************/ 

/* Oculta mouse en la pantalla */ 

void ocultar_mouse(){ 

            reg.x.ax = 0x2; 

            int86(0x33, &reg, &reg); 

} 

  

/*******************************************************************/ 

/* Nos retorna el estado actual de la posicion y botones del mouse */ 

/* utilizando punteros                                             */ 

void estado_mouse(int *x,int *y, int *izq, int *der){ 

            res.r_ax = 3; 

            intr(0x33,&res); 

            *izq = res.r_bx & 0x01; 

            *der = res.r_bx & 0x02; 

            *der = *der >> 1; 

            *x = res.r_cx ; 

            *y = res.r_dx; 

} 

  

/***********************************************/ 

/* Inicializa el mouse en la posicion indicada */ 

/* utilizando punteros                         */ 

void inicia_mouse(int x,int y) { 

            reg.x.ax=0; 

            int86(0x33, &reg, &reg); 

            reg.x.ax = 4; 

            reg.x.cx = x; 

            reg.x.dx = y; 

            int86(0x33, &reg, &reg); 
}

