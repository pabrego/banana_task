#include <stdio.h>
#include <stdlib.h>

#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct nodo hashElem;

typedef struct HashMap HashMap;

long hash(long key, long capac);

void enlarge(HashMap* map);

void insert(HashMap* map, long key, void* data);

void* search(HashMap* map, long key);

void erase(HashMap* map, long key);

void* first(HashMap* map);

void* next(HashMap* map);

#endif
