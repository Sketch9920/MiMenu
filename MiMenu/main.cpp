#include"fconsola.h"
#include <iostream>
#include <conio.h>       //para uso de kbhit(), getche()
#include <math.h>
using namespace std;
/*-------------------------------------------------------*/
struct MENU_DATA
{
	char text[128];
	int x;
	int y;
};
MENU_DATA Menu[20];

int SeleccionMainMenu;
bool Terminado=false;
void DrawBox(int x, int y, int width, int height);

TCHAR asciichar = L'▓';

int MenuMain();
void SubMenuAcercaDe();
void SubMenuAgregar();
void SubMenuSalir();
void PrintChar(int length, char val);
int MenuProg(MENU_DATA *menu, int SeleccionActual,int MaxMenu);



int main()
{
	cons_Iniciar(80,30);//Inicializando las propiedades de la consola
	//char* str = "string";

	SeleccionMainMenu = 1;
	cons_ShowCursor(false);
	cons_color(CN_BLANCO, CN_AZUL);
	cons_cls(asciichar);// Limpia la pantalla asignando el caracter deseado
	while (!Terminado)
	
	{
		SeleccionMainMenu = MenuMain();
		cons_color(CN_BLANCO, CN_AZUL);
		cons_cls(asciichar);
		switch (SeleccionMainMenu)
		{
		case 1:
			SubMenuAgregar();
			break;
		case 2:
			SubMenuAcercaDe();
			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:
			SubMenuSalir();
				
			break;
		}
		cons_color(CN_BLANCO, CN_AZUL);
		cons_cls(asciichar);
	}
}


int MenuProg(MENU_DATA *menu, int SeleccionActual,int MaxMenu)
{
	int Actual = SeleccionActual;
	
	cons_color(CN_BLANCO, CN_NEGRO);
	DrawBox(menu[1].x-1 , menu[1].y-1 , strlen(menu[1].text)+2, MaxMenu + 2);
	//set_color(C_BLANCO, C_NEGRO);

	for (int a = 1;a<=MaxMenu;a++)
	{
		cons_posxy(menu[a].x,menu[a].y);
		cout << menu[a].text;
	}

	bool ok=false;
	while (!ok)
	{
		
		//imprime en pantalla la seleccion
		cons_color(CN_AMARILLO, CN_ROJO);
		cons_posxy(menu[Actual].x,menu[Actual].y);
		cout << menu[Actual].text;

		//lee las teclas extendidas del teclado
		int k = _getch();
		if (k == 0 || k == 0xE0) k = _getch();//leer una vez mas para el codigo extendido del teclado

		//borra de la pantalla la seleccion anterior
		cons_color(CN_BLANCO, CN_NEGRO);
		cons_posxy(menu[Actual].x,menu[Actual].y);
		cout << menu[Actual].text;
		
		switch(k)
		{
		case 72: //Arriba
			{
                Actual = (Actual + MaxMenu - 2) % MaxMenu + 1;
			}
			break;
		case 80: //Abajo
			{
				Actual = (Actual) % MaxMenu + 1;
			}
			break;
		case 13: //enter
			ok=true;
			break;
		case 27: //ESC
			Actual=0;
			ok=true;
			break;
		}

	}
	return Actual;
}

int MenuMain()
{
	cons_color(CN_NEGRO, CN_BLANCO_CLARO);
	//DrawBox(0, 0, 5, 2);
	DrawBox(22, 4, 35, 3);
	//cons_color(CN_ROJO, CN_BLANCO_CLARO);
	cons_posxy(23, 5);
	//cons_posxy(0, 0);
	cout << "******Mi Menu principal 1.0******";
	
	strcpy_s(Menu[1].text, "   Empezar juego       ");
	strcpy_s(Menu[2].text, "   Acerca de....       ");
	strcpy_s(Menu[3].text, "   Configurar grafico  ");
	strcpy_s(Menu[4].text, "   Configurar juego    ");
	strcpy_s(Menu[5].text, "   Opciones avanzadas  ");
	strcpy_s(Menu[6].text, "   Musica              ");
	strcpy_s(Menu[7].text, "   >> Terminar <<      ");
	

	Menu[1].x = 25; Menu[1].y = 10;
	Menu[2].x = 25; Menu[2].y = 11;
	Menu[3].x = 25; Menu[3].y = 12;
	Menu[4].x = 25; Menu[4].y = 13;
	Menu[5].x = 25; Menu[5].y = 14;
	Menu[6].x = 25; Menu[6].y = 15;
	Menu[7].x = 25; Menu[7].y = 16;
	
	int MenuSeleccion;
	do
	{
		MenuSeleccion = MenuProg(Menu, SeleccionMainMenu, 7);
	} while (MenuSeleccion == 0);

	return MenuSeleccion;
}

void SubMenuAgregar()
{

	int indexMenu;
	strcpy_s(Menu[1].text, "     Agregar 1    ");
	strcpy_s(Menu[2].text, "     Agregar 2    ");
	strcpy_s(Menu[3].text, "   **Regresar**   ");

	Menu[1].x = 30; Menu[1].y = 10;
	Menu[2].x = 30; Menu[2].y = 11;
	Menu[3].x = 30; Menu[3].y = 12;

	indexMenu = MenuProg(Menu, 1, 3);

	switch (indexMenu)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}
void SubMenuAcercaDe()
{

	int indexMenu;
	strcpy_s(Menu[1].text, "Todos los derechos reservados a mi");
	
	Menu[1].x = 25; Menu[1].y = 11;

	indexMenu = MenuProg(Menu, 1, 1);

	switch (indexMenu)
	{
	case 1:
		break;
	}
}
void SubMenuSalir()
{
	int indexMenu;
	strcpy_s(Menu[1].text, "ENTER para terminar, ESC para cancelar     ");

	Menu[1].x = 20; Menu[1].y = 11;

	indexMenu = MenuProg(Menu, 1, 1);
	
	switch (indexMenu)
	{
	case 1:
		Terminado=true;
		break;
	}
}
//Imprime un caracter repetidas veces
void PrintChar(int length, char val)
{
	int i;
	for (i = 0; i < length; i++)
	{
		cout << val;
	}
}
void DrawBox(int x, int y, int width, int height)
{
	cons_posxy(x, y);
	PrintChar(1, char(218)); PrintChar(width-2, char(196));  PrintChar(1, char(191));
	
	int i;
	for (i = y+1; i < y + height-1; i++)
	{
		cons_posxy(x, i);
		PrintChar(1, char(179)); PrintChar(width-2, char(32));  PrintChar(1, char(179));
	}
	cons_posxy(x, y+height-1);
	PrintChar(1, char(192)); PrintChar(width-2, char(196));  PrintChar(1, char(217));
	cons_shadow(x+1, y + height, width, 1);
	cons_shadow(x+ width , y+1 , 1, height-1);
	//cons_shadow(x, 0 , 5, 1);
}