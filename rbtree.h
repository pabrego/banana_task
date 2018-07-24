#ifndef RBTREE_H
#define RBTREE_H


typedef struct rbtree RBTree;

RBTree* create_RBTree(int(*lower_than)(void* key1, void* key2));

// Inserta un nuevo "data" al arbol con su respectiva "key".
void RB_insert(RBTree* T, void* key, void* data);

// Elimina un "data" del arbol mediante su "key".
void RB_delete(RBTree* T, void* key);

// Retorna un "data" del arbol mediante su "key".
void* RB_search(RBTree* T, void* key);

// Retorna el "data" raiz del arbol.
void* RB_first(RBTree* T);

// Retorna el "data" al final del arbol.
void* RB_last(RBTree* T);

// Retorna el "data" siguiente al actual.
void* RB_next(RBTree* T);

// Retorna el "data" anterior al actual.
void* RB_prev(RBTree* T);


#endif // RBTREE_H
