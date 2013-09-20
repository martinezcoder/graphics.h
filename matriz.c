// MATRICES DE TRANSFORMACION 2D
#include <math.h>
#include "matriz.h"


void matriz_identidad(struct MATRIZ *m)
{
	int i, j;
	
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			if (i == j) m->v[i][j] = 1.0;
			else m->v[i][j] = 0.0;
		}
	}
}


void matriz_traslacion(struct MATRIZ *m, float Tx, float Ty)
{
 matriz_identidad(m);
 m->v[2][0] = Tx;
 m->v[2][1] = Ty;
}


void matriz_rotacion(struct MATRIZ *m, float angulo)
{
 float  tmpsin, tmpcos;

 if (angulo == 0) angulo = 360;

 angulo = 180 / angulo;
 tmpsin = sin(PI / angulo);  // la funcion sin y cos utiliza angulos en radianes
 tmpcos = cos(PI / angulo);

 matriz_identidad(m);

 m->v[0][0] =  tmpcos;
 m->v[0][1] =  tmpsin;
 m->v[1][0] = -tmpsin;
 m->v[1][1] =  tmpcos;
}


void matriz_escalado(struct MATRIZ *m, float Ex, float Ey)
{
 matriz_identidad(m);
 m->v[0][0] = Ex;
 m->v[1][1] = Ey;
}


void multiplica(struct MATRIZ *punto, struct MATRIZ *mt, struct MATRIZ *resul, int numpuntos)
{
 int i, j, k;

 for (i=0; i < numpuntos; i++) {
	for (j=0; j<3; j++) {
		resul->v[i][j] = 0.0;
		for (k=0; k<3; k++)
			resul->v[i][j] = resul->v[i][j] + (punto->v[i][k] * mt->v[k][j]);
		}
	}
}


void trasl_linea(struct punt *p1, struct punt *p2)
{
	struct MATRIZ m, trasl, resul;
	float Tx, Ty;

	limpia();	printf("Traslacion en X: ");
	scanf("%f", &Tx);
	limpia();	printf("Traslacion en Y: ");
	scanf("%f", &Ty);
	limpia();

	m.v[0][0] = (float)p1->x;  
	m.v[0][1] = (float)p1->y;
	m.v[0][2] = 1.0;
	m.v[1][0] = (float)p2->x;
	m.v[1][1] = (float)p2->y;
	m.v[1][2] = 1.0;
	
	matriz_traslacion(&trasl, Tx, Ty);

	multiplica(&m, &trasl, &resul, 2);
	
	p1->x = (int)resul.v[0][0]; p1->y = (int)resul.v[0][1];
	p2->x = (int)resul.v[1][0]; p2->y = (int)resul.v[1][1];

}


void rota_linea(struct punt *p1, struct punt *p2)
{
	struct MATRIZ m, trasl, rota, resul;
	float angulo;

	limpia();	printf("angulo de rotacion: ");
	scanf("%f", &angulo);
	limpia();
	

	m.v[0][0] = (float)p1->x;  
	m.v[0][1] = (float)p1->y;
	m.v[0][2] = 1.0;
	m.v[1][0] = (float)p2->x;
	m.v[1][1] = (float)p2->y;
	m.v[1][2] = 1.0;

//traslacio al origen
	matriz_traslacion(&trasl, -(p1->x), -(p1->y));

	multiplica(&m, &trasl, &resul, 2);
	
	m.v[0][0] = resul.v[0][0]; 
	m.v[0][1] = resul.v[0][1];
	m.v[0][2] = 1.0; //resul.v[0][2];
	m.v[1][0] = resul.v[1][0]; 
	m.v[1][1] = resul.v[1][1];
	m.v[1][2] = 1.0; //resul.v[1][2];

//rotació
	matriz_rotacion(&rota, angulo);

	multiplica(&m, &rota, &resul, 2);

	m.v[0][0] = resul.v[0][0]; 
	m.v[0][1] = resul.v[0][1];
	m.v[0][2] = resul.v[0][2];
	m.v[1][0] = resul.v[1][0]; 
	m.v[1][1] = resul.v[1][1];
	m.v[1][2] = resul.v[1][2];

//traslació a on estaba	
	matriz_traslacion(&trasl, p1->x, p1->y);

	multiplica(&m, &trasl, &resul, 2);

	p1->x = (int)resul.v[0][0]; p1->y = (int)resul.v[0][1];
	p2->x = (int)resul.v[1][0]; p2->y = (int)resul.v[1][1];
}

void trasl_circle(struct punt *p1)
{
	struct MATRIZ m, trasl, resul;
	float Tx, Ty;

	limpia();	printf("Traslacion en X: ");
	scanf("%f", &Tx);
	limpia();	printf("Traslacion en Y: ");
	scanf("%f", &Ty);
	limpia();

	m.v[0][0] = (float)p1->x;  
	m.v[0][1] = (float)p1->y;
	m.v[0][2] = 1.0;
	
	matriz_traslacion(&trasl, Tx, Ty);

	multiplica(&m, &trasl, &resul, 1);
	
	p1->x = (int)resul.v[0][0]; p1->y = (int)resul.v[0][1];
}


void escala_linea(struct punt *p1, struct punt *p2)
{
	struct MATRIZ m, escala, resul;
	float Ex, Ey;

	limpia();	printf("Factor escala en X: ");
	scanf("%f", &Ex);
	limpia();	printf("Factor escala en Y: ");
	scanf("%f", &Ey);
	limpia();

	m.v[0][0] = (float)p1->x;  
	m.v[0][1] = (float)p1->y;
	m.v[0][2] = 1.0;
	m.v[1][0] = (float)p2->x;
	m.v[1][1] = (float)p2->y;
	m.v[1][2] = 1.0;
	
	matriz_escalado(&escala, Ex, Ey);

	multiplica(&m, &escala, &resul, 2);
	
	p1->x = (int)resul.v[0][0]; p1->y = (int)resul.v[0][1];
	p2->x = (int)resul.v[1][0]; p2->y = (int)resul.v[1][1];

}