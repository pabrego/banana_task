#include <stdio.h>
#include <stdlib.h>
/*#include <avl-tree.h>
#include <hashmap.h>*/
#include "Tareas.h"

int main()
{
    int opcion, i;
    arbol* todoPorFecha = newRBTree();
    arbol** todoPorPrioridad = (arbol**)malloc(sizeof(arbol*)*5);
    for(i=0;i<5;i++){
        todoPorPrioridad[i] = newRBTree();
    }
    HashMap* categorias = newHashMap();

    cargar_archivo(todoPorFecha, todoPorPrioridad, categorias);

    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|          B A N A N A   T A S K          |\n" );
    printf("|        ELIJA OPERACIÓN A REALIZAR       |\n" );
    printf("|_________________________________________|\n" );
    printf("|                                         |\n" );
    printf("|   1.-  Agregar tarea.                   |\n" );
    printf("|   2.-  Agregar categoria.               |\n" );
    printf("|   3.-  Revisar tareas pendientes.       |\n" );
    printf("|   4.-  Revisar tareas realizadas.       |\n" );
    printf("|   5.-  Editar tarea.                    |\n" );
    printf("|   0.-  Salir.                           |\n" );
    printf("|_________________________________________|\n" );

    menu:  scanf("%d", &opcion);

    switch(opcion){
    case 1:
        printf("Opcion 1: Agregar tareas\n");
        agregar_tarea(todoPorFecha, todoPorPrioridad, categorias);
        break;
    case 2:
        printf("Opcion 2: Agregar categoria\n");
        agregar_categoria(categorias);
        break;
    case 3:
        printf("Opcion 3: Revisar tareas pendientes\n");
        mostrar_todo(todoPorFecha, todoPorPrioridad, categorias);
        break;
    case 4:
        printf("Opcion 4: Revisar tareas realizadas\n");
        mostrar_todo(todoPorFecha, todoPorPrioridad, categorias);
        break;
    case 5:
        printf("Opcion 5: Editar tareas\n");

        break;
    case 0:
        printf("Opcion 0: Salir\n");
        break;
    default:
        printf("Opcion invalida\n");
        goto menu;
    }
    return 0;
}
