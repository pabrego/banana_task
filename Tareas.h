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
    RBTree* por_fecha;
    RBTree** por_priori;
    char* n_categoria;
}Categoria;

typedef struct Fecha{
    int dia;
    int mes;
    int anio;
}Fecha;

int lower_than(Tarea*, Tarea*);
int buscar_categoria(char*, Lista*);
Categoria* crea_n_categoria(char*);
Fecha* crea_fecha();
Tarea* crea_tarea();
void agregar_tarea(HashMap*, Lista*, RBTree*, RBTree**);
void quitar_tarea(HashMap*, Lista*, RBTree*, RBTree**);
void mostrar_todo(HashMap* hash_categorias, RBTree* por_fecha, RBTree** por_prioridad);
void mostrar_arbol();
void mostrar_prioridad();
void mostrar_categoria();
void editar_tarea();
void quitar_tarea();
void realizar_tarea();
void guardar_todo(RBTree* por_fecha);
void cargar_archivo(HashMap* hash_categorias, RBTree* por_fecha, RBTree** por_prioridad);

#endif // TAREAS_H
