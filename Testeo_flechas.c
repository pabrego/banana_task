#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
 }
int main()
{
    char c;
    int y = 1;

 ini:   printf("Banana Task (Early access 0.0.1)\n");

    printf("\t1. Agregar tareas\n");
    printf("\t2. Mostrar tareas\n");
    printf("\t3. Editar tareas\n");
    printf("\t4. Salir\n");

    gotoxy(0,y);
    printf("=>");
    while(1)
    {
        c = getch();
        if(c == -32)
        {
            gotoxy(0, y);
            printf("  ");
            c = getch();
            if(c == 72)
            {
                y--;
                if(y<1)
                {
                    y = 4;
                }
            }
            else if(c == 80)
            {
                y++;
                if(y>4)
                {
                    y = 1;
                }
            }
            printf("  ");
            gotoxy(0,y);
            printf("=>");
        }
        else if (c == 13)
        {
            if(y == 1)
            {
                gotoxy(0,5);
                printf("Agregar tarea\n");
                gotoxy(0,0);
            }
            else if (y == 2)
            {
                gotoxy(0,5);
                printf("Mostrar tarea\n");
                gotoxy(0,0);
            }
            else if (y == 3)
            {
                gotoxy(0,5);
                printf("Editar tareas\n");
                gotoxy(0,0);
            }
            else if (y == 4)
            {
                gotoxy(0,5);
                printf("Salir         \n");
                break;
            }
            goto ini;
        }
    }
    return 0;
}
