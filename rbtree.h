#ifndef RBTREE_H
#define RBTREE_H
#include "Tareas.h"

typedef struct rbtree RBTree;

RBTree* create_RBTree(lower_than);

// Inserta un nuevo "data" al arbol con su respectiva "key".
void RB_insert(RBTree* T, void* key, void* data);

// Elimina un "data" del arbol mediante su "key".
void RB_delete(RBTree* T, void* key);

// Retorna un "data" del arbol mediante su "key".
void* RB_search(RBTree* T, void* key);

// Retorna el "data" raiz del arbol.
void* RB_first(RBTree* T);

// Retorna el "data" siguiente al actual.
void* RB_next(RBTree* T);

#endif // RBTREE_H
