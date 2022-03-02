#ifndef _INC_WCONSOLE    //don't let this file be included
#define _INC_WCONSOLE    //twice in the same source file

#include <windows.h>     //funciones para la consola en windows

#include <math.h>        //para funciones sin, cos

enum color
{
   CN_NEGRO			= 0,
   CN_AZUL_OSCURO	= 1,
   CN_VERDE_OSCURO	= 2,
   CN_CELESTE_OSCURO	= 3, 
   CN_ROJO_OSCURO	= 4,
   CN_MAGENTA_OSCURO	= 5,
   CN_CAFE			= 6,
   CN_BLANCO			= 7,
   CN_GRIS			= 8,
   CN_AZUL			= 9,
   CN_VERDE			= 10,
   CN_CELESTE		= 11, 
   CN_ROJO			= 12,
   CN_MAGENTA		= 13,
   CN_AMARILLO		= 14,
   CN_BLANCO_CLARO	= 15
};
//--------------------------------------------------------------

void cons_Iniciar(short ancho, short alto);
void cons_posxy(int x, int y);
void cons_color(color texto = CN_BLANCO, color fondo = CN_NEGRO);
void cons_ShowCursor(bool showFlag);
void cons_cls(/*HANDLE hConsole*/TCHAR fillchar = ' ');
void cons_shadow(short x1, short y1, short width, short height);
#endif /* _INC_WCONSOLE */