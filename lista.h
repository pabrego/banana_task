#ifndef LISTA_H
#define LISTA_H


typedef struct Lista Lista;

Lista* createList();

void L_pushBack(Lista* L, void* data);

void L_popCurrent(Lista* L);

void* L_first(Lista* L);

void* L_last(Lista* L);

void* L_next(Lista* L);

int L_get_size(Lista* L);


#endif // LISTA_H
