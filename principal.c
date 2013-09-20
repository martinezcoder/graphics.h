#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include "interfaz.h"
#include "mouse.h"
#include "matriz.h"
#include "brsenham.h"

typedef struct objeto
{
	int tipo; // 0=linea, 1=circulo
	int color;
	struct punt p1, p2; // Si es circulo, p2.x = radio
};

//Variables globales que contienen el origen de coordenadas
int ejex = 0;
int ejey = 0;

int cx(int x){	return (x + ejex); }
int cy(int y){	return (ejey - y); }


void centrar_origen(int x, int y) //Centra el origen de coordenadas
{
	ejex = x;
	ejey = y;
}


void pinta_origen(int color)
{
	setcolor(color); 

	//trazando eje coordenadas
	//linea horizontal 
	linea( 0 , ejey , getmaxx(), ejey, color ); 
	//linea vertical   
	linea( ejex , 0 , ejex , getmaxy(), color);
}


void inserta_circle_menu(struct punt *p1, int *r, int *color)
{
	limpia();
	printf("Centro x: ");scanf("%d", &p1->x);limpia();
	printf("Centro y: ");scanf("%d", &p1->y);limpia();
	printf("Radio: ");scanf("%d", r);limpia();
	printf("Color: ");scanf("%d", color);limpia();

}


void inserta_eje_coord()
{
	int coordx, coordy;

	limpia();
	printf("Centro x: ");scanf("%d", &coordx);limpia();
	printf("Centro y: ");scanf("%d", &coordy);limpia();

	centrar_origen(cx(coordx),cy(coordy));
}


void inserta_line_menu(struct punt *p1, struct punt *p2, int *color)
{
	limpia();
	printf("X inicial: ");
	scanf("%d", &p1->x);limpia();
	printf("Y inicial: ");
	scanf("%d", &p1->y);limpia();
	printf("X final: ");
	scanf("%d", &p2->x);limpia();
	printf("Y final: ");
	scanf("%d", &p2->y);limpia();
	printf("Color: ");
	scanf("%d", color);limpia();
}	


void nuevoObj(int tipo, struct objeto *obj, struct punt p1, struct punt p2, int color)
{
	obj->tipo = tipo;
	obj->color = color;
	obj->p1.x = p1.x;
	obj->p1.y = p1.y;
	obj->p2.x = p2.x;
	if (tipo == 0)	obj->p2.y = p2.y;
}

void numeraobjeto(struct objeto *obj, int num)
{
	int x,y;
	char n[3];

	setcolor(14);

	sprintf(n, "%d", num);
	x = obj->p1.x;
	y = obj->p1.y;

	if (obj->tipo == 0)
	{
		outtextxy(cx(x), cy(y), n);
	}else{
		outtextxy(cx(x), cy(y), n);
	}
}

int selecciona_objeto(int numobj)
{
	int sel=-1;
	limpia();
	printf("Selecciona un objeto: ");
	scanf("%d", &sel);
	limpia();
	if ((sel < 0) || (sel > numobj)) sel = -1;

	return sel;
}

void busca_punt_intersec(struct punt *p5, struct punt *pr1, struct punt *pr2, struct punt *ps1, struct punt *ps2)
{
	double mr, ms, br, bs;
	int zero;

	if ((pr2->x - pr1->x) == 0)
	{
		mr = 0;
		zero = 1;
	}
	else
	{
		mr = ((((double)(pr2->y - pr1->y)) / ((double)(pr2->x - pr1->x))));
	}
	
	if ((ps2->x - ps1->x) == 0) 
	{
		ms = 0;
		zero = 2;
	}
	else
	{
		ms = ((((double)(ps2->y - ps1->y)) / ((double)(ps2->x - ps1->x))));
	}
	
	br = (((double)(pr1->y)) - (mr * ((double)(pr1->x))));
	bs = (((double)(ps1->y)) - (ms * ((double)(ps1->x))));

	if (zero == 0) 
	{
		p5->x = ((int)((bs - br) / (mr - ms)));
	}
	else
	{
		if (zero == 1)
		{
			p5->x = pr1->x;
			p5->y = ((int)((ms * ((double)(p5->x))) + bs));
		}
		else
		{
			p5->x = ps1->x;
			p5->y = ((int)((mr * ((double)(p5->x))) + br));
		}
	}

	if (zero == 0) p5->y = ((int)((mr * ((double)(p5->x))) + br));
}

void menu_principal()
{
	int selec=1, selec2=1, menu_pral=1, entra=1;
	char *opcion[10];
	struct objeto obj[50]; //maximo 50 objetos
	int i, obj_act=0, aux, ret;
	int numobj=-1;
	struct vp menuop;   // Ventana del menu de opciones
	struct vp grafic;   // Ventana con el eje de coordenadas
	struct punt p1, p2, p5; 
	int r;
	int color;
	float factor;
	double incre1, incre2;


	menuop.vpxi = 0; menuop.vpyi = 16;
	menuop.vpxf = 100; menuop.vpyf = 340;

	grafic.vpxi = 105; grafic.vpyi = 15;
	grafic.vpxf = getmaxx(); grafic.vpyf = getmaxy();
	
	puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);  // Lo que me queda de pantalla
	centrar_origen((grafic.vpxf-grafic.vpxi)/2, (grafic.vpyf-grafic.vpyi)/2);	

	pinta_origen(10);

	while (selec != '0')
	{
		if (menu_pral)
		{
			if (entra)
			{
				opcion[0] = (char *)malloc(sizeof("MENU")); strcpy(opcion[0], "MENU");
				opcion[1] = (char *)malloc(sizeof("  Salir")); strcpy(opcion[1], "  Salir");
				opcion[2] = (char *)malloc(sizeof("  Origen")); strcpy(opcion[2], "  Origen");
				opcion[3] = (char *)malloc(sizeof("  Recta")); strcpy(opcion[3], "  Recta");
				opcion[4] = (char *)malloc(sizeof("  Circulo")); strcpy(opcion[4], "  Circulo");
				opcion[5] = (char *)malloc(sizeof("  Objeto")); strcpy(opcion[5], "  Objeto" );


				entra=0;
			}

			selec = menu(&menuop, opcion, 6);

			switch (selec)
			{
			case 1: inserta_eje_coord();
					menu_pral = 0; entra = 1;
				break;
			case 2: inserta_line_menu(&p1, &p2, &color);
					numobj++; obj_act = numobj;
					nuevoObj(0, &obj[numobj], p1, p2, color);
					menu_pral = 0; entra = 1;
				break;
			case 3: inserta_circle_menu(&p1, &r, &color);
					numobj++; obj_act = numobj; p2.x = r;
					nuevoObj(1, &obj[numobj], p1, p2, color);
					menu_pral = 0; entra = 1;
				break;
			case 4: puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);  // Lo que me queda de pantalla
				    for (i=0;i<=numobj;i++) numeraobjeto(&obj[i], i);
					obj_act = selecciona_objeto(numobj);
					if (obj_act != -1)
					{
						p1.x = obj[obj_act].p1.x;
						p1.y = obj[obj_act].p1.y;
						p2.x = obj[obj_act].p2.x;
						p2.y = obj[obj_act].p2.y;
						r = obj[obj_act].p2.x;
						color = obj[obj_act].color;
						if (obj[obj_act].tipo == 0) selec = 2;
						if (obj[obj_act].tipo == 1) selec = 3;
						menu_pral = 0; entra = 1;
					}
				break;
			case '0': ; //Salir
				break;
			}
		}
		else	// Submenu
		{
			//se borra la pantalla
			system("cls");
			//se selecciona el viewport de la grafica
			puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);
			//se pinta el origen de coordenadas
			pinta_origen(10);
			//Recorre los objetos volviendo a pintar todo
			for (i=0; i<=numobj; i++)
			{
				setcolor(obj[i].color);
				if (obj[i].tipo == 0)
				{
					linea(cx(obj[i].p1.x), cy(obj[i].p1.y), cx(obj[i].p2.x), cy(obj[i].p2.y), obj[i].color);
				}else{
					circulo(obj[i].p2.x, cx(obj[i].p1.x), cy(obj[i].p1.y), obj[i].color);
				}
			}

			//se dibuja el menú secundario

			if (entra)
			{
				free(opcion[0]);free(opcion[1]);free(opcion[2]);free(opcion[3]);free(opcion[4]);free(opcion[5]);
				opcion[0] = (char *)malloc(sizeof("MENU objeto")); strcpy(opcion[0], "MENU obj");
				opcion[1] = (char *)malloc(sizeof(" <-Volver")); strcpy(opcion[1], " <-Volver");
				opcion[2] = (char *)malloc(sizeof(" Traslado")); strcpy(opcion[2], " Traslado");
				opcion[3] = (char *)malloc(sizeof(" Rotar")); strcpy(opcion[3], " Rotar");
				opcion[4] = (char *)malloc(sizeof(" Escalar")); strcpy(opcion[4], " Escalar");
				opcion[5] = (char *)malloc(sizeof(" Alargar")); strcpy(opcion[5], " Alargar");

				entra=0;
			}
			
			selec2 = menu(&menuop, opcion, 6);

			switch (selec2)
			{
			case 1: // TRASLACIONS
				if (selec == 2)	// traslacio de linea
				{
					puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);
					trasl_linea(&p1, &p2);
					linea(cx(p1.x), cy(p1.y), cx(p2.x), cy(p2.y), color);
					nuevoObj(0, &obj[obj_act], p1, p2, color);
				}
				else
				{
					if (selec == 3) //traslacio de cercle
					{
						puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);
						trasl_circle(&p1);
						circulo(r, cx(p1.x), cy(p1.y), color);
						p2.x = r;
						nuevoObj(1, &obj[obj_act], p1, p2, color);
					}
				}
				break;
			case 2: // ROTACIONS
				if (selec == 2) // rotacio de linea
				{
					puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);
					rota_linea(&p1, &p2);
					linea(cx(p1.x), cy(p1.y), cx(p2.x), cy(p2.y), color);
					nuevoObj(0, &obj[obj_act], p1, p2, color);
				}
				else
				{
					if (selec == 3)  // rotacio de cercle
					{
						// No val la pena rotar un cercle pq quedaria igual
					}
				}
				
				break;
			case 3: // ESCALADOS
				if (selec == 2)	// escalat de linea
				{
					puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);
					escala_linea(&p1, &p2);
					linea(cx(p1.x), cy(p1.y), cx(p2.x), cy(p2.y), color);
					nuevoObj(0, &obj[obj_act], p1, p2, color);
				}
				else
				{
					if (selec == 3)  // escalat de cercle
					{
						puerto_vision(grafic.vpxi, grafic.vpyi, grafic.vpxf, grafic.vpyf);
						limpia();printf("factor escala:");scanf("%d",&factor);limpia();
						r = r * factor;
						circulo(r, cx(p1.x), cy(p1.y), color);
						p2.x = r;
						nuevoObj(1, &obj[obj_act], p1, p2, color);
					}
				}
				break;
			case 4: // ALLARGAMENT DE RECTES
				if ((selec == 2)&&(numobj > 0)) //Si es una recta i hi ha mes d'un objecte
				{
					i = 0; ret = 0;
					while ((i <= numobj)&&(ret == 0))
					{
						if ((i != obj_act)&&(obj[i].tipo == 0))
						{
							busca_punt_intersec(&p5, &p1, &p2, &obj[i].p1, &obj[i].p2);
							if ((p5.x >= min(p1.x, p2.x))&&(p5.x >= max(p1.x, p2.x)))
							{
								if ((p5.x >= min(obj[i].p1.x, obj[i].p2.x))&&(p5.x <= max(obj[i].p1.x, obj[i].p2.x)))
								{
									ret = 1;
								}
							}
							if ((p5.x <= min(p1.x, p2.x))&&(p5.x <= max(p1.x, p2.x)))
							{
								if ((p5.x >= min(obj[i].p1.x, obj[i].p2.x))&&(p5.x <= max(obj[i].p1.x, obj[i].p2.x)))
								{
									ret = 1;
								}
							}
						}
						i++;
					}
					
					if (ret==1)
					{ 
						incre1 = sqrt( (double)(((p1.x - p5.x) * (p1.x - p5.x)) + ((p1.y - p5.y) * (p1.y - p5.y))) );
						incre2 = sqrt( (double)(((p2.x - p5.x) * (p2.x - p5.x)) + ((p2.y - p5.y) * (p2.y - p5.y))) );

						if (incre1 > incre2)
						{
							p2.x = p5.x;
							p2.y = p5.y;
						}
						else
						{
							p1.x = p5.x;
							p1.y = p5.y;
						}
						linea(cx(p1.x), cy(p1.y), cx(p2.x), cy(p2.y), color);
						nuevoObj(0, &obj[obj_act], p1, p2, color);
					}
					else
					{
						limpia();printf("No hay intersecciones!");getch();
					}
				}
				else
				{
					limpia();printf("No hay intersecciones!");getch();
				}
				break;
			case '0': menu_pral = 1; entra = 1; 
					  free(opcion[0]);free(opcion[1]);free(opcion[2]);free(opcion[3]);free(opcion[4]);free(opcion[5]);
				break;
			}
		}
	}
	free(opcion[0]);free(opcion[1]);free(opcion[2]);free(opcion[3]);free(opcion[4]);free(opcion[5]);
}


void main()
{
	int driver, mode;

	driver = DETECT;

	initgraph(&driver, &mode, "");

	if (graphresult() != grOk)
	{
		printf("ERROR EN EL MODO GRAFICO");
		exit(0);	
	}

	mode = getgraphmode();
	
	cleardevice();	setbkcolor(0);

	menu_principal();

	restorecrtmode();

	closegraph();
}