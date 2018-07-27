#ifndef MENU_H
#define MENU_H

void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
 }

void ajustar_pantalla ()
{
    SetConsoleTitle("Banana Task");
    system("mode con: cols=100 lines=30");


	HWND ConsoleWindow;
	ConsoleWindow=GetForegroundWindow();

	HWND   hwndScreen;
	RECT   rectScreen;
	hwndScreen=GetDesktopWindow ();
	GetWindowRect(hwndScreen,&rectScreen);

	SetWindowPos (ConsoleWindow,NULL,0,0,1000,500, SWP_SHOWWINDOW);

	RECT rConsole;
	GetWindowRect (ConsoleWindow,&rConsole);
	int Width = rConsole.left = rConsole.right;
	int Height = rConsole.bottom - rConsole.top;

	int ConsolePosX;
	int ConsolePosY;
	ConsolePosX = ((rectScreen.right-rectScreen.left)/2-Width/2 );
	ConsolePosY = ((rectScreen.bottom-rectScreen.top)/2- Height/2 );
	SetWindowPos(ConsoleWindow,NULL,ConsolePosX,ConsolePosY, Width, Height, SWP_SHOWWINDOW || SWP_NOSIZE);
}

#endif // MENU_H
