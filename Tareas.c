#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tareas.h"

Categoria* crea_n_categoria(){
    Categoria* nodo = (Categoria*) malloc(sizeof(Categoria));
    nodo->n_categoria = (char*) malloc(sizeof(char)*16);
  /*nodo->por_cate = create_treeMap();
    nodo->por_fecha = create_treeMap();*/
    return nodo;
}

Fecha* crea_fecha(){
    Fecha* nodo = (Fecha*) malloc(sizeof(Fecha));
    nodo->anio = 0;
    nodo->mes = 0;
    nodo->dia = 0;
    return nodo;
}

Tarea* crea_tarea(){
    Tarea* nodo = (Tarea*) malloc(sizeof(Tarea));
    nodo->nombre = (char*) malloc(sizeof(char)*31);
    nodo->descripcion = (char*) malloc(sizeof(char)*141);
    nodo->categoria = (char*) malloc(sizeof(char)*16);
    nodo->prioridad = 0;
    nodo->estado = 0;
    nodo->fecha = crea_fecha();
    return nodo;
}

void mostrar_todo(){
    int opcion;

    /*menú preguntando opciones de muestra*/

    switch (opcion) {
        case 1: mostrar_por_fecha();break;
        case 2: mostrar_por_prioridad();break;
        case 3: mostrar_categoria();
    }

}

void mostrar_arbol(arbol* arbol)
{
    Tarea* imprimir = first(arbol);
    int* day = imprimir->fecha->dia;
    int* month = imprimir->fecha->mes;
    int* year = imprimir->fecha->anio;
    char* name = imprimir->nombre;
    int* prio = imprimir->prioridad;
    char* cate = imprimir->categoria;
    int* activa = imprimir->estado;
    while(imprimir){
        if(*prio == 1)
        {
            printf("|%d/%d/%d  Baja   %s  %s ",day, month, year, name, cate);
        }
        else if(*prio == 2)
        {
            printf("|%d/%d/%d  Media  %s  %s ",day, month, year, name, cate);
        }
        else if(*prio == 3)
        {
            printf("|%d/%d/%d  Alta   %s  %s ",day, month, year, name, cate);
        }
        if(activa)
        {
            printf("   Activa  \n");
        }
        else
        {
            printf(" Realizada \n");
        }
        imprimir = next(arbol);
    }


}
