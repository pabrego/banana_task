#ifndef TAREAS_H
#define TAREAS_H
#include <string.h>

typedef struct Tarea Tarea;

typedef struct Categoria Categoria;

typedef struct Fecha Fecha;

int lower_than(Tarea*, Tarea*);
Categoria* buscar_categoria(Lista*, char*);
Categoria* crea_n_categoria(char*);
Fecha* crea_fecha();
Tarea* crea_tarea();
void agregar_tarea(Lista*, RBTree*, RBTree**);
void quitar_tarea(Lista*, RBTree*, RBTree**);
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
