#include <graphics.h>
#include <math.h>
#include "brsenham.h"

int Bressenham(int X_act, int Y_act, int X_fin, int Y_fin, int Pi, int caso, int color)
{
	int increX, increY;

	increX = X_fin - X_act;
	increY = Y_fin - Y_act;	

	if ((caso==5)||(caso==6)||(caso==7)||(caso==8))
	{
		putpixel(Y_act, X_act, color);
		putpixel(Y_fin, X_fin, color);
	}
	else
	{
		putpixel(X_act, Y_act, color);
		putpixel(X_fin, Y_fin, color);
	}

	while (X_act != X_fin)
	{
		if (Pi < 0)
		{
			if ((caso == 7)||(caso == 8)) X_act--;
			else X_act++;

			Pi = Pi + (2 * abs(increY));
		}
		else
		{
			if ((caso == 7)||(caso == 8)) X_act--;
			else X_act++;
			
			if ((caso == 3)||(caso == 4))
				Y_act--;
			else
				Y_act++;

			Pi = Pi + ( 2 * (abs(increY) - abs(increX)));
		}
		
		if ((caso == 5)||(caso == 6)||(caso == 7)||(caso == 8))
			putpixel(Y_act, X_act, color);
		else
			putpixel(X_act, Y_act, color);
	}
	return 0;
}

int linea(int X_ini, int Y_ini, int X_fin, int Y_fin, int color)
{
	int increY, increX, Pi;

	increX = X_fin - X_ini;
	increY = Y_fin - Y_ini;

	if ( abs(increX) >= abs(increY) )
	{
		if (increX > 0)
		{
			if (increY >= 0)
			{
				///////////////////////////CASO1
				Pi = (2 * abs(increY)) - abs(increX);
				Bressenham(X_ini, Y_ini, X_fin, Y_fin, Pi, 1, color);
			}
			else
			{
				///////////////////////////CASO4
				Pi = (2 * abs(increY)) - abs(increX);
				Bressenham(X_ini, Y_ini, X_fin, Y_fin, Pi, 4, color);
				//incremento X, decremento Y 
			}
		}
		else
		{
			if (increY <= 0)
			{
				///////////////////////////CASO2
				Pi = (2 * abs(increY)) - abs(increX);
				Bressenham(X_fin, Y_fin, X_ini, Y_ini, Pi, 2, color);
			}
			else
			{
				///////////////////////////CASO3
				Pi = (2 * abs(increY)) - abs(increX);
				Bressenham(X_fin, Y_fin, X_ini, Y_ini, Pi, 3, color);
			}
		}
	}
	else
	{
		if (increY > 0)
		{
			if (increX >= 0) 
			{
				///////////////////////////CASO5
				Pi = (2 * abs(increX)) - abs(increY);
				Bressenham(Y_ini, X_ini, Y_fin, X_fin, Pi, 5, color);
			}
			else
			{
				///////////////////////////CASO 8
				Pi = (2 * abs(increX)) - abs(increY);
				Bressenham(Y_fin, X_fin, Y_ini, X_ini, Pi, 8, color);
			}
		}
		else
		{
			if (increX <= 0)
			{
				///////////////////////////CASO6
				Pi = (2 * abs(increX)) - abs(increY);
				Bressenham(Y_fin, X_fin, Y_ini, X_ini, Pi, 6, color);
			}
			else
			{
				///////////////////////////CASO 7
				Pi = (2 * abs(increX)) - abs(increY);
				Bressenham(Y_ini, X_ini, Y_fin, X_fin, Pi, 7, color);
			}
		}
	}
	return 0;
}


void circulo(int r, int cx, int cy, int color) //radio, centro y relacion de aspecto
{
  int Pi = 1-r;//3 - (2 * r);  // valor de testing
  int x;
  int y = r;
  	
  for (x = 0; x <= y; x++)  // Ciclo Pal. Bresenham
    {
    	putpixel(cx+x, cy+y, color);
	putpixel(cx+x, cy-y, color);
	putpixel(cx-x, cy+y, color);
	putpixel(cx-x, cy-y, color);
	putpixel(cx+y, cy+x, color);
	putpixel(cx+y, cy-x, color);
	putpixel(cx-y, cy+x, color);
	putpixel(cx-y, cy-x, color);

        if (Pi < 0)
        {
            Pi = Pi + (4 * x + 6);         // A la derecha
        }
        else
        {
            Pi = Pi + (4 * (x - y) + 10);
            y = y - 1;                     // A la derecha y abajo
        }
   }
}

