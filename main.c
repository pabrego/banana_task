#include <stdio.h>
#include <stdlib.h>
/*#include <avl-tree.h>
#include <hashmap.h>*/
#include "Tareas.h"

int main()
{
    int opcion;

    printf("Banana Task (Alpha 0.0.1)\n");

    printf("1. Agregar tareas\n");
    printf("2. Mostrar tareas\n");
    printf("3. Editar tareas\n");
    printf("4. Salir\n");

    menu:  scanf("%d", &opcion);

    switch(opcion){
    case 1:
        printf("Opcion 1: Agregar tareas\n");
        break;
    case 2:
        printf("Opcion 2: Mostrar tareas\n");
        break;
    case 3:
        printf("Opcion 3: Editar tareas\n");
        break;
    case 4:
        printf("Opcion 4: Salir\n");
        break;
    default:
        printf("Opcion invalida\n");
        goto menu;
    }
    return 0;
}
