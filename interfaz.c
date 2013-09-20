#include <graphics.h>
#include "interfaz.h"

void box(int startx, int starty, int endx, int endy, int color)
{
	linea(startx, starty, startx, endy, color);
	linea(startx, starty, endx, starty, color);
	linea(endx, starty, endx, endy, color);
	linea(endx, endy, startx, endy, color);
}

void inicia_interfaz()
{
	inicia_mouse(0,0);
	mostrar_mouse();
}

void pantalla_completa()
{
	setviewport(0,0,getmaxx(),getmaxy(),1);  // iniciamos con ventana pantalla completa
}

void onfocus(int xi,int yi,int xf,int yf)
{
	signed int size;
	void *buf;

	size=imagesize(xi,yi,xf,yf);
	buf = (char *)malloc(size);
	getimage(xi,yi,xf,yf,buf);
	putimage(xi,yi,buf,NOT_PUT);
	free(buf);
}

void restaura(void *antes, int focus[])
{
	int i;

	if (antes != NULL)
	{
		i = 0;
		while (focus[i]!=1) i++;
		
		switch (i)
		{
		case 0: putimage(10,35,antes,COPY_PUT);
			break;
		case 1: putimage(10,55,antes,COPY_PUT);
			break;
		case 2: putimage(10,75,antes,COPY_PUT);
			break;
		case 3: putimage(10,95,antes,COPY_PUT);
			break;
		case 4: putimage(10,115,antes,COPY_PUT);
			break;
		}
		focus[i] = 0;
	}
}

int bucle_botones(int num)
{
	int x, y, izq, der;
	int i, ret, pulsado = 0;
	int focus[10];
	void *antes;

	antes = NULL;
	for (i=0; i<10; i++) focus[i] = 0; //Inicializa a cero

	while (!pulsado)
	{
		estado_mouse(&x, &y, &izq, &der);

		if ((x > 10) && (x < 90) && (num >= 1))
		{ 
			if ((y > 50) && (y < 65))
			{
				if (focus[0] == 0)
				{
					ocultar_mouse();
					restaura(antes, focus);free(antes);
					antes = (void *)malloc(imagesize(10,35,80,50)); getimage(10,35,80,50,antes);
					onfocus(10,35,80,50);focus[0] = 1;
					mostrar_mouse();
				}
				if (izq)
				{
					ret = 1; pulsado = 1;
				}
			}
			if ((y > 70) && (y < 85) && (num >= 2))
			{
				if (focus[1] == 0)
				{
					ocultar_mouse();
					restaura(antes, focus);free(antes);
					antes = (void *)malloc(imagesize(10,55,80,70)); getimage(10,55,80,70,antes);
					onfocus(10,55,80,70);focus[1] = 1;
					mostrar_mouse();
				}
				if (izq)
				{
					ret = 2; pulsado = 1;
				}
			}
			if ((y > 90) && (y < 105) && (num >= 3))
			{
				if (focus[2] == 0)
				{
					ocultar_mouse();
					restaura(antes, focus);free(antes);
					antes = (void *)malloc(imagesize(10,75,80,90)); getimage(10,75,80,90,antes);
					onfocus(10,75,80,90);focus[2] = 1;
					mostrar_mouse();
				}
				if (izq)
				{
					ret = 3; pulsado = 1;
				}
			}
			if ((y > 110) && (y < 125) && (num >= 4))
			{
				if (focus[3] == 0)
				{
					ocultar_mouse();
					restaura(antes, focus);free(antes);
					antes = (void *)malloc(imagesize(10,95,80,110)); getimage(10,95,80,110,antes);
					onfocus(10,95,80,110);focus[3] = 1;
					mostrar_mouse();
				}
				if (izq)
				{
					ret = 4; 
					if (num == 4) ret = '0';
					pulsado = 1;
				}
			}
			if ((y > 130) && (y < 145) && (num >= 5))
			{
				if (focus[4] == 0)
				{
					ocultar_mouse();
					restaura(antes, focus);free(antes);
					antes = (void *)malloc(imagesize(10,95,80,130)); getimage(10,115,80,130,antes);
					onfocus(10,115,80,130);focus[4] = 1;
					mostrar_mouse();				
				}
				if (izq)
				{
					ret = 5;
					if (num == 5) ret = '0'; 
					pulsado = 1;
				}
			}
		}
		if (kbhit())
		{
			ret = getch();
			if (ret == '0') pulsado = 1;
		}
	}
	free(antes);
	return ret;
}

int menu(struct vp *coord, char *opcion[], int num)
{
	int i, selec;

	pantalla_completa();

	setviewport(coord->vpxi, coord->vpyi, coord->vpxf, coord->vpyf, 1); clearviewport();
	setfillstyle(1,1); floodfill(1,1,3); // pinta el fondo de la ventana	
	box(0, 0, coord->vpxf - coord->vpxi, coord->vpyf - coord->vpyi, 3); // Marco de la ventana
	
	setcolor(BLACK); outtextxy(25,10, opcion[0]);
			
	setcolor(7);
	outtextxy(5, 40 + ((num - 2) * 20), opcion[1]);

	for (i=2; i<num; i++) outtextxy(5, 40+((i-2)*20),opcion[i]);
	
	inicia_interfaz();

	selec = bucle_botones(num-1); // -1 pq el titulo está incluido en num

	pantalla_completa();
	
	return selec;
}

void puerto_vision(int xi, int yi, int xf, int yf)
{
	pantalla_completa();
	setviewport(xi, yi, xf, yf, 1);
}

void limpia()
{
	gotoxy(1,1); printf("                                                 ");
	gotoxy(1,1);
}