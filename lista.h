#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

typedef struct Nodo
{
    struct Nodo* prev;
    struct Nodo* next;
    void* data;
} Nodo;

typedef struct Lista
{
    Nodo* first;
    Nodo* last;
    Nodo* current;
} Lista;

Lista* createList();
Nodo* _createNode(void*);
void* first_L(Lista*);
void pushBack(Lista*, void*);
void* last_L(Lista*);
void* next_L(Lista*);
void popCurrent(Lista* );




#endif // LISTA_H
