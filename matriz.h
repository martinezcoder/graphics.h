#ifndef _MATRIZ_H__
#define _MATRIZ_H__

#include "Brsenham.h"

#define PI  3.14196

typedef struct punt
{
	int x, y;
};

typedef struct MATRIZ
{
	float v[3][3];
};



void matriz_identidad(struct MATRIZ *m);

void matriz_traslacion(struct MATRIZ *m, float Tx, float Ty);

void matriz_rotacion(struct MATRIZ *m, float angulo);

void matriz_escalado(struct MATRIZ *m, float Ex, float Ey);

void multiplica(struct MATRIZ *puntos, struct MATRIZ *mt, struct MATRIZ *resul, int numpuntos);

void trasl_linea(struct punt *p1, struct punt *p2);

void rota_linea(struct punt *p1, struct punt *p2);

void trasl_circle(struct punt *p1);

void escala_linea(struct punt *p1, struct punt *p2);

#endif