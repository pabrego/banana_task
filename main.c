#include <stdio.h>
#include <stdlib.h>
#include "Tareas.h"

int main()
{
    int opcion, i;
    RBTree* todoPorFecha = create_RBTree((int(*)(void*, void*))lower_than);
    RBTree** todoPorPrioridad = (RBTree**)malloc(sizeof(RBTree*)*5);
    for(i=0;i<5;i++)
    {
        todoPorPrioridad[i] = create_RBTree((int(*)(void*, void*))lower_than);
    }
    Lista* categorias = createList();
    
    cargar_archivo(categorias, todoPorFecha, todoPorPrioridad);
    menu:
    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|          B A N A N A   T A S K          |\n" );
    printf("|        ELIJA OPERACIÓN A REALIZAR       |\n" );
    printf("|_________________________________________|\n" );
    printf("|                                         |\n" );
    printf("|   1.-  Agregar tarea.                   |\n" );
    printf("|   2.-  Quitar tarea.                    |\n" );
    printf("|   3.-  Mostrar tareas.                  |\n" );
    printf("|   4.-  Editar tarea.                    |\n" );
    printf("|   0.-  Salir.                           |\n" );
    printf("|_________________________________________|\n" );

    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    getchar();
    
    switch(opcion){
    case 1:
        printf("Opcion 1: Agregar tareas.\n");
        agregar_tarea(categorias, todoPorFecha, todoPorPrioridad);
        goto menu;
    case 2:
        printf("Opcion 2: Quitar tareas.\n");
        quitar_tarea(categorias, todoPorFecha, todoPorPrioridad);
        goto menu;
    case 3:
        printf("Opcion 3: Revisar tareas pendientes.\n");
        mostrar_todo(categorias, todoPorFecha, todoPorPrioridad);
        goto menu;
    case 4:
        printf("Opcion 5: Editar tareas.\n");
        editar_tarea(categorias, todoPorFecha, todoPorPrioridad);
        goto menu;
    case 0:
        printf("Opcion 0: Salir.\n");
        guardar_todo(todoPorFecha);
        break;
    default:
        printf("Opcion invalida.\n");
        goto menu;
    }
    return 0;
}
