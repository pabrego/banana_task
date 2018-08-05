#include <stdio.h>
#include <stdlib.h>
#include "Tareas.h"
#include "menu.h"

int main()
{
    ajustar_pantalla();
    bordes_menu();
    system("color 06");
    RBTree* todoPorFecha = create_RBTree((int(*)(void*, void*))(lower_than));
    RBTree** todoPorPrioridad = (RBTree**) malloc(sizeof(RBTree*)*5);
    Lista* Categorias = createList();
    char c;
    int y = 9, i;
    for(i=0; i<5; i++)
    {
        todoPorPrioridad[i] = create_RBTree((int(*)(void*, void*))(lower_than));
    }

    cargar_archivo(Categorias, todoPorFecha, todoPorPrioridad);
    menu_principal();
    gotoxy(47,y);
    printf(">>");
    while(1)
    {
        c = getch();
        if(c == -32)
        {
            gotoxy(47, y);
            printf("  ");
            c = getch();
            if(c == 72)
            {
                y = y-2;
                if(y<9)
                {
                    y = 17;
                }
            }
            else if(c == 80)
            {
                y = y+2;
                if(y>17)
                {
                    y = 9;
                }
            }
            printf("  ");
            gotoxy(47,y);
            printf(">>");
        }
        else if (c == 13)
        {
            if(y == 9)
            {
                agregar_tarea(Categorias, todoPorFecha, todoPorPrioridad);
                bordes_menu();
                menu_principal();
                gotoxy(47,y);
                printf(">>");
            }
            else if(y == 11)
            {

                quitar_tarea(Categorias, todoPorFecha, todoPorPrioridad);
                bordes_menu();
                menu_principal();
                gotoxy(47,y);
                printf(">>");
            }
            else if(y == 13)
            {
                system("color ");
                mostrar_todo(Categorias, todoPorFecha, todoPorPrioridad);
                system("color 06");
                bordes_menu();
                menu_principal();
                gotoxy(47,y);
                printf(">>");
            }
            else if(y == 15)
            {
                gotoxy(53, 20);
                editar_tarea(Categorias, todoPorFecha, todoPorPrioridad);
                bordes_menu();
                menu_principal();
                gotoxy(47,y);
                printf(">>");
            }
            else
            {
                gotoxy(45,20);
                guardar_todo(todoPorFecha);
                printf("Gracias por usar Banana Task");
                gotoxy(0,26);
                break;
            }
        }
    }
    return 0;
}
