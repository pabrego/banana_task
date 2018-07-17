#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tareas.h"
#include "hashmap.h"
#include "avl-tree.h"

typedef struct Tarea{
    char* categoria;
    char* nombre;
    char* descripcion;
    int prioridad;
    Fecha* fecha;
    int estado;
}Tarea;

typedef struct Categoria{
    TreeMap* por_fecha;
    TreeMap* por_cate;
    char* nombre;
}Categoria;

typedef struct Fecha{
    int dia;
    int mes;
    int anio;
}Fecha*

void agregar_tarea(){

}

void crear_categoria(){

}

void mostrar_todo(){

}

void editar_tarea(){

}

void quitar_tarea(){

}

void realizar_tarea(){

}

void guardar_todo(){

}
