#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Nodo* _createNode(void *data)
{
    Nodo *newn;
    newn = (Nodo*)malloc(sizeof(Nodo));
    newn->data = data;
    newn->next = NULL;
    newn->prev = NULL;
    return newn; /* Retornamos dirección del elemento insertado */
}

Lista* createList()
{
   Lista* list=(Lista*) malloc (sizeof(Lista));
   list->first=NULL;
   list->current=NULL;
   list->last=NULL;
   return list;
}

void pushBack(Lista* list, void* data)
{
     Nodo* N = _createNode(data);
     if(list->first == NULL)
     {
        list->first = N;
        list->last = N;
        list->current = N;
     }
     else
     {
        list->current->next = N;
        N->prev = list->current;
        list->last = N;
        list->current = N;
     }
}

void* last_L(Lista* list)
{
    void* ptr;
    if (list->last != NULL){
    ptr = list->last->data;
    return ptr;
    list->current = list->last;
    }
    else
    {
        return NULL;
    }
}

void* first_L(Lista* list)
{
    void* ptr;
    if (list->first != NULL){
    ptr = list->first->data;
    list->current = list->first;
    return ptr;
    }
    else
    {
        return NULL;
    }
}
void* next_L(Lista *list)
{
    void* ptr;
    if (list->current->next != NULL){
    ptr = list->current->next->data;
    list->current = list->current->next;
    return ptr;
    }
    else
    {
        return NULL;
    }
}
void popCurrent(Lista* list)
{
    Nodo* n;
    if (list->first == list->last)
    {
        list->first = NULL;
        list->last = NULL;
        free(list->current->data);
        free(list->current);
    }
    else if(list->current == list->last)
    {
        list->last = list->current->prev;
        list->current->prev = NULL;
        list->last->next = NULL;
        free(list->current->data);
        free(list->current);
        list->current = list->last;
    }
    else if(list->current == list->first)
    {
        list->first = list->current->next;
        list->current->prev = NULL;
        list->current->next = NULL;
        free(list->current->data);
        free(list->current);
        list->current = list->first;
    }
    else
    {
        n = list->current->next;
        list->current->prev->next = n;
        list->current->next->prev = list->current->prev;
        list->current->next = NULL;
        list->current->prev = NULL;
        free(list->current->data);
        free(list->current);
        list->current = n;
    }
}
