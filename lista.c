#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

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
    int size;
} Lista;

Nodo* _createNode(void* data)
{
    Nodo* newn;
    newn = (Nodo*)malloc(sizeof(Nodo));
    newn->data = data;
    newn->next = NULL;
    newn->prev = NULL;
    return newn; /* Retornamos direccion del elemento insertado */
}

Lista* createList()
{
   Lista* L = (Lista*) malloc(sizeof(Lista));
   L->first = NULL;
   L->current = NULL;
   L->last = NULL;
   L->size = 0;
   return L;
}

void L_pushBack(Lista* L, void* data)
{
     Nodo* N = _createNode(data);
     L->size++;
     if(L->first == NULL)
     {
        L->first = N;
        L->last = N;
        L->current = N;
     }
     else
     {
        L->current->next = N;
        N->prev = L->current;
        L->last = N;
        L->current = N;
     }
}

void* L_last(Lista* L)
{
    void* ptr;
    if (L->last != NULL)
    {
        ptr = L->last->data;
        L->current = L->last;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

void* L_first(Lista* L)
{
    void* ptr;
    if (L->first != NULL)
    {
        ptr = L->first->data;
        L->current = L->first;
        return ptr;
    }
    else
    {
        return NULL;
    }
}
void* L_next(Lista *L)
{
    void* ptr;
    if (L->current->next != NULL)
    {
        ptr = L->current->next->data;
        L->current = L->current->next;
        return ptr;
    }
    else
    {
        return NULL;
    }
}
void L_popCurrent(Lista* L)
{
    Nodo* n;
    L->size--;
    if (L->first == L->last)
    {
        L->first = NULL;
        L->last = NULL;
        L->size--;
        free(L->current->data);
        free(L->current);
    }
    else if(L->current == L->last)
    {
        L->last = L->current->prev;
        L->current->prev = NULL;
        L->last->next = NULL;
        free(L->current->data);
        free(L->current);
        L->current = L->last;
    }
    else if(L->current == L->first)
    {
        L->first = L->current->next;
        L->current->prev = NULL;
        L->current->next = NULL;
        free(L->current->data);
        free(L->current);
        L->current = L->first;
    }
    else
    {
        n = L->current->next;
        L->current->prev->next = n;
        L->current->next->prev = L->current->prev;
        L->current->next = NULL;
        L->current->prev = NULL;
        free(L->current->data);
        free(L->current);
        L->current = n;
    }
}

int L_get_size(Lista* L)
{
    return L->size;
}
