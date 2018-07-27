#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "menu.h"
#include "conio.h"
#include "Tareas.h"

int main()
{
    ajustar_pantalla();
    RBTree* todoPorFecha = create_RBTree((int(*)(void*, void*))(lower_than));
    RBTree** todoPorPrioridad = (RBTree**) malloc(sizeof(RBTree*)*5);
    Lista* Categorias = createList();
    char c;
    int y = 1, i;
    for(i=0; i<5; i++)
    {
        todoPorPrioridad[i] = create_RBTree((int(*)(void*, void*))(lower_than));
    }

 ini:   printf("Banana Task (Early access 0.0.1)\n");

    printf("\t1. Agregar tareas\n");
    printf("\t2. Quitar tareas\n");
    printf("\t3. Mostrar tareas\n");
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
                agregar_tarea(Categorias, todoPorFecha, todoPorPrioridad);
                gotoxy(0,0);
            }
            else if (y == 2)
            {
                gotoxy(0,5);
                printf("Quitar tarea\n");
                quitar_tarea(Categorias, todoPorFecha, todoPorPrioridad);
                gotoxy(0,0);
            }
            else if (y == 3)
            {
                gotoxy(0,5);
                printf("Mostrar tareas\n");
                mostrar_todo(Categorias, todoPorFecha, todoPorPrioridad);
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
