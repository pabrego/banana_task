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

void mostrar_todo(HashMap* hash_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    int opcion;

    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|        TODAS:                           |\n" );
    printf("|   1.-  Ordenadas por fecha.             |\n" );
    printf("|   2.-  Ordenadas por prioridad.         |\n" );
    printf("|                                         |\n" );
    printf("|   3.-  Revisar categorias.              |\n" );
    printf("|                                         |\n" );
    printf("|   0.-  Volver al menú principal.        |\n" );
    printf("|_________________________________________|\n" );

    switch (opcion)
    {
        case 1: mostrar_arbol(por_fecha);break;
        case 2: mostrar_prioridad(por_prioridad);break;
        case 3: mostrar_categoria(hash_categorias);break;
        case 0: break;
    }

}

void mostrar_prioridad(RBTree** por_prioridad)
{
    int i;
    for(i=0;i<5;i++)
    {
        mostrar_arbol(por_prioridad[i]);
    }
}

void mostrar_categoria(HashMap* hash_categorias)
{

}

void guardar_todo(HashMap* hash_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    FILE* f = fopen();
}

void mostrar_arbol(RBTree* arbol)
{
    Tarea* imprimir = first(arbol);
    int* day = imprimir->fecha->dia;
    int* month = imprimir->fecha->mes;
    int* year = imprimir->fecha->anio;
    char* name = imprimir->nombre;
    int* priority = imprimir->prioridad;
    char* category = imprimir->categoria;
    int* activa = imprimir->estado;
    while(imprimir){
        if(*priority == 1)
        {
            printf("|%d/%d/%d  Baja   %s  %s ",day, month, year, name, category);
        }
        else if(*priority == 2)
        {
            printf("|%d/%d/%d  Media  %s  %s ",day, month, year, name, category);
        }
        else if(*priority == 3)
        {
            printf("|%d/%d/%d  Alta   %s  %s ",day, month, year, name, category);
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
