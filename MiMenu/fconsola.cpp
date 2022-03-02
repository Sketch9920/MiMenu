#include "fconsola.h"
HANDLE hConsole;         //handle de la consola
COORD console_size;

void resizeConBufAndWindow(/*HANDLE hConsole, */SHORT xSize, SHORT ySize);
void cons_Iniciar(short ancho, short alto)
{
   //Abre el canal de Entrada y salida(i/o) de la pantalla de consola
   hConsole = CreateFileA("CONOUT$", GENERIC_WRITE | GENERIC_READ,
                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                   0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);

   //Asignamos el tamño de la consola a 80x25 caracteres
   console_size.X = ancho; //80 de ancho x 25 de alto
   console_size.Y = alto;
   
   HWND consoleWindow = GetConsoleWindow();
   SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

   resizeConBufAndWindow(console_size.X, console_size.Y);
   
   SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

   SetConsoleScreenBufferSize(hConsole, console_size);
   //Asignamos el color del texto a blanco sobre fondo negro
   SetConsoleTextAttribute( hConsole, (WORD)((0 << 4) | 7) );

   //clear_screen();
}
void cons_posxy(int x, int y)
{
	COORD cursor_pos;              //origen en la esquina superior izquierda
	cursor_pos.X = x;// - 1;          //Windows inicia en (0, 0)
	cursor_pos.Y = y;// - 1;          //colocamos en (1, 1)
	SetConsoleCursorPosition(hConsole, cursor_pos);
}
void cons_color(color colorTexto, color colorFondo)
{
/*  0  Negro				8  Gris oscuro
	1  Azul oscuro			9  Azul
	2  Verde oscuro			10 Verde
	3  Celeste oscuro		11 Celeste
	4  Rojo oscuro			12 Rojo
	5  Magenta oscuro		13 Magenta
	6  Cafe					14 Amarillo
	7  Blanco(gris claro)   15 Blanco Claro
*/
	SetConsoleTextAttribute( hConsole, (WORD)((colorFondo << 4) | colorTexto) );
}
void cons_ShowCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void cons_cls(TCHAR fillchar/*HANDLE hConsole*/)
{

	COORD coordScreen = { 0, 0 }; /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize; /* number of character cells in the current buffer */
	/* get the number of character cells in the current buffer */
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * (csbi.dwSize.Y);
	/* fill the entire screen with blanks */
	FillConsoleOutputCharacter(hConsole, fillchar, dwConSize, coordScreen, &cCharsWritten);

	/* get the current text attribute */
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	/* now set the buffer's attributes accordingly */
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	/* put the cursor at (0, 0) */
	SetConsoleCursorPosition(hConsole, coordScreen);

	return;
}
void resizeConBufAndWindow(/*HANDLE hConsole, */SHORT xSize, SHORT ySize)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* hold current console buffer info */
	SMALL_RECT srWindowRect; /* hold the new console size */
	COORD coordScreen;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	/* get the largest size we can size the console window to */
	coordScreen = GetLargestConsoleWindowSize(hConsole);
	/* define the new console window size and scroll position */
	srWindowRect.Right = (SHORT)(min(xSize, coordScreen.X) - 1);
	srWindowRect.Bottom = (SHORT)(min(ySize, coordScreen.Y) - 1);
	srWindowRect.Left = srWindowRect.Top = (SHORT)0;
	/* define the new console buffer size */
	coordScreen.X = xSize;
	coordScreen.Y = ySize;
	/* if the current buffer is larger than what we want, resize the */
	/* console window first, then the buffer */
	if ((DWORD)csbi.dwSize.X * csbi.dwSize.Y > (DWORD)xSize * ySize)
	{
		SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
		SetConsoleScreenBufferSize(hConsole, coordScreen);
	}
	/* if the current buffer is smaller than what we want, resize the */
	/* buffer first, then the console window */
	if ((DWORD)csbi.dwSize.X * csbi.dwSize.Y < (DWORD)xSize * ySize)
	{
		SetConsoleScreenBufferSize(hConsole, coordScreen);
		SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
	}
	/* if the current buffer *is* the size we want, don't do anything! */
	return;
}


void mouse()
{
	DWORD events;
	INPUT_RECORD input_record;

	ReadConsoleInput(hConsole, &input_record, 1, &events);
	int mouseX = input_record.Event.MouseEvent.dwMousePosition.X;
	int mouseY = input_record.Event.MouseEvent.dwMousePosition.Y;
	int buttonState = input_record.Event.MouseEvent.dwButtonState;

	if (input_record.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED) return;

	int keyCode = input_record.Event.KeyEvent.wVirtualKeyCode;

}
void cons_shadow(short x1, short y1, short width, short height)
{
	DWORD dwWritten;
	int iy;
	COORD posShadow = { x1, y1};
	int intensidad = 7; //0 = negro
	for (iy = 0; iy < height; iy++)
		//for (ix = 0; ix < ix + width; ix++)
		{
			FillConsoleOutputAttribute(hConsole, (WORD)(intensidad << 4) | FOREGROUND_INTENSITY, width, posShadow, &dwWritten);
			posShadow.Y++;
		}
}