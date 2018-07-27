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

#endif // MENU_H
