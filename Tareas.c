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
