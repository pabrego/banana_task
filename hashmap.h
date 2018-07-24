#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct nodo hashElem;

typedef struct HashMap HashMap;

long hash(long key, long capac);

void enlarge(HashMap* map);

void H_insert(HashMap* map, long key, void* data);

void* H_search(HashMap* map, long key);

void H_erase(HashMap* map, long key);

void* H_first(HashMap* map);

void* H_next(HashMap* map);

#endif
