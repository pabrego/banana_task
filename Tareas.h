#ifndef TAREAS_H
#define TAREAS_H
#include <string.h>

typedef struct Tarea{
    char* categoria;
    char* nombre;
    char* descripcion;
    int prioridad;
    struct Fecha* fecha;
    int estado;
}Tarea;

typedef struct Categoria{
    arbol* por_fecha;
    arbol** por_priori;
    char* n_categoria;
}Categoria;

typedef struct Fecha{
    int dia;
    int mes;
    int anio;
}Fecha;

Categoria* crea_n_categoria();
Fecha* crea_fecha();
Tarea* crea_tarea();
void agregar_tarea();
void agregar_categoria();
void mostrar_todo(HashMap* hash_categorias, arbol* por_fecha, arbol** por_prioridad);
void mostrar_arbol();
void mostrar_prioridad();
void mostrar_categoria();
void editar_tarea();
void quitar_tarea();
void realizar_tarea();
void guardar_todo();


#endif // TAREAS_H
