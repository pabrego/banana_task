#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
 }

void ajustar_pantalla()
{
    SetConsoleTitle("Banana Task");
    system("mode con: cols=100 lines=30");

    //Get the window console handle(isn't the right code but works for these sample
	HWND ConsoleWindow;
	ConsoleWindow=GetForegroundWindow();

	//Getting the desktop hadle and rectangule
	HWND   hwndScreen;
	RECT   rectScreen;
	hwndScreen=GetDesktopWindow ();
	GetWindowRect(hwndScreen,&rectScreen);

	//Set windows size(see the width problem)
	SetWindowPos (ConsoleWindow,NULL,0,0,1000,500, SWP_SHOWWINDOW);

	// Get the current width and height of the console
	RECT rConsole;
	GetWindowRect (ConsoleWindow,&rConsole);
	int Width = rConsole.left = rConsole.right;
	int Height = rConsole.bottom - rConsole.top;

	//caculate the window console to center of the screen
	int ConsolePosX;
	int ConsolePosY;
	ConsolePosX = ((rectScreen.right-rectScreen.left)/2-Width/2 );
	ConsolePosY = ((rectScreen.bottom-rectScreen.top)/2- Height/2 );
	SetWindowPos(ConsoleWindow,NULL,ConsolePosX,ConsolePosY, Width, Height, SWP_SHOWWINDOW || SWP_NOSIZE);
}

void bordes_menu()
{
   int i;
   printf("%c", 201);       //De aqui se empieza a imprimir el borde...
   for(i=0; i<118; i++)
   {
       if((i == 49) || (i == 69))
       {
           printf("%c", 203);
       }
       else
       {
        printf("%c", 205);
       }
   }
   printf("%c\n", 187);

   for(i=0; i<24; i++)
   {
       gotoxy(0,(i+1));
       printf("%c", 186);
       gotoxy(119, (i+1));
       printf("%c", 186);
   }
   gotoxy(0,25);
   printf("%c",200);
   for(i=0; i<118;i++)
   {
       printf("%c", 205);
   }
   printf("%c\n", 188);
   gotoxy(50,1);
   printf("%c", 186);
   gotoxy(70,1);
   printf("%c", 186);
   gotoxy(50,2);
   printf("%c", 200);
   for(i=0; i<20; i++)
   {
       printf("%c", 205);
   }
   gotoxy(70,2);
   printf("%c", 188); //... Hasta acá
   gotoxy(55, 1);
   printf("Banana Task");
}

void menu_principal()
{
    int i;
    gotoxy(53, 9);
    printf("Agregar Tarea");
    gotoxy(53, 11);
    printf("Quitar tarea");
    gotoxy(53, 13);
    printf("Mostrar Tarea");
    gotoxy(53, 15);
    printf("Editar Tarea");
    gotoxy(53, 17);
    printf("Salir");

    gotoxy(44,7);
    printf("%c", 201); //Esquina superior izquierda
    for(i=0; i<30; i++)
    {
        printf("%c",205); //Barra horizaontal superior
    }
    printf("%c", 187); //Esquina superior derecha
    gotoxy(44,19);
    printf("%c", 200);//Esquina inferior izquierda
    gotoxy(75,19);
    printf("%c", 188);//Esquina inferior derecha
    gotoxy(45,19);
    for(i=0; i<30; i++)
    {
        printf("%c",205); //Barra horizontal inferior
    }
    i = 0;
    for(i=8; i<19; i++) //Barras verticales
    {
        gotoxy(44, i);
        printf("%c", 186);
        gotoxy(75, i);
        printf("%c", 186);

    }

}
/*void menu_funciones()
{
    int i;
    gotoxy(53, 9);
    printf("Agregar Tarea");
    gotoxy(53, 11);
    printf("Quitar tarea");
    gotoxy(53, 13);
    printf("Mostrar Tarea");
    gotoxy(53, 15);
    printf("Editar Tarea");
    gotoxy(53, 17);
    printf("Salir");

    gotoxy(44,7);
    printf("%c", 201); //Esquina superior izquierda
    for(i=0; i<30; i++)
    {
        printf("%c",205); //Barra horizaontal superior
    }
    printf("%c", 187); //Esquina superior derecha
    gotoxy(44,19);
    printf("%c", 200);//Esquina inferior izquierda
    gotoxy(75,19);
    printf("%c", 188);//Esquina inferior derecha
    gotoxy(45,19);
    for(i=0; i<30; i++)
    {
        printf("%c",205); //Barra horizontal inferior
    }
    i = 0;
    for(i=8; i<19; i++) //Barras verticales
    {
        gotoxy(44, i);
        printf("%c", 186);
        gotoxy(75, i);
        printf("%c", 186);
    }*/
