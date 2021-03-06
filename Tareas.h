#ifndef TAREAS_H
#define TAREAS_H
#include "lista.h"
#include "rbtree.h"


typedef struct Tarea Tarea;

typedef struct Categoria Categoria;

typedef struct Fecha Fecha;


int lower_than(Tarea*, Tarea*);

void agregar_tarea(Lista*, RBTree*, RBTree**);

void quitar_tarea(Lista*, RBTree*, RBTree**);

void mostrar_todo(Lista* lista_categorias,RBTree* por_fecha, RBTree** por_prioridad);

void editar_tarea(Lista* lista_categorias,RBTree* por_fecha, RBTree** por_prioridad);

void guardar_todo(RBTree* por_fecha);

void cargar_archivo(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad);


#endif // TAREAS_H
