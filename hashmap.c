#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

typedef struct nodo{
    long key;
    void* data;
}hashElem;

typedef struct HashMap{
    hashElem** hashArray;
    int current;
    int size; //cant. elementos no nulos
    int capac; //Dimension tabla
}HashMap;

HashMap* createHashMap(int capac){
    int i;
    HashMap* map=(HashMap*) malloc(sizeof(HashMap));
    map->capac=capac;
    map->size=0;
    map->current = 0;
    map->hashArray = malloc(sizeof(hashElem*)*map->capac);
    for(i=0;i<map->capac;i++)
        map->hashArray[i]=NULL;
    return map;
}

long hash (long key, long capac){
  float A = 0.6180334;
  float B = (float) key*A - (float) ((int)((float)key*A));
  return capac * B;
}

void enlarge(HashMap* map){
    hashElem **old_array=map->hashArray;
    int old_capac=map->capac;

    //se reinicializan las variables de la tabla con el nuevo tamaño
    int i;
    map->capac*=2;
    map->size=0;
    map->current=0;
    map->hashArray = malloc(sizeof(hashElem*)*map->capac);
    for(i=0;i<map->capac;i++) map->hashArray[i]=NULL;

    //se reasingnan los elementos de la tabla antigua a la nueva
    for(i=0;i<old_capac;i++){
       if(old_array[i]){
           if(old_array[i]->data)
              H_insert(map, old_array[i]->key, old_array[i]->data);
           free(old_array[i]);
       }

    }

    free(old_array);
}

void H_insert(HashMap* map, long key, void* data){
   int hvalue=hash(key,map->capac);
   if(map->hashArray[hvalue]){ //se busca una casilla disponible a partir de hvalue
       int new_hvalue=-1, i;
       for(i=1;i<map->capac;i++){
          new_hvalue=(hvalue+i)%map->capac;
          if(!map->hashArray[new_hvalue] || !map->hashArray[new_hvalue]->data){
             hvalue=new_hvalue;
             break;
          }
       }
   }

   if(!map->hashArray[hvalue]) map->hashArray[hvalue]=(hashElem*) malloc(sizeof(hashElem));
   map->hashArray[hvalue]->data=data;
   map->hashArray[hvalue]->key=key;
   map->size++;
   if((double)map->size/(double)map->capac > 0.7) enlarge(map); //agranda la tabla
}

void* H_search(HashMap* map, long key){
    int i;
    int hvalue=hash(key,map->capac);
    for(i=0;i<map->capac;i++){
        int new_hvalue=(hvalue+i)%map->capac;
        if(!map->hashArray[new_hvalue]) return NULL;
        else if(map->hashArray[new_hvalue]->key == key){
           return map->hashArray[new_hvalue]->data;
        }
    }
    return NULL;
}

void H_erase(HashMap* map, long key){
    int i;
    int hvalue=hash(key,map->capac);
    for(i=0;i<map->capac;i++){
        int new_hvalue=(hvalue+i)%map->capac;
        if(!map->hashArray[new_hvalue]) return;
        else if(map->hashArray[new_hvalue]->key == key){
           map->hashArray[new_hvalue]->data=NULL;
        }
    }
}

void* H_first(HashMap* map){
    int i=0;
    for(i=0;i<map->capac;i++)
        if(map->hashArray[i] && map->hashArray[i]->data) {
            map->current=i;
            return map->hashArray[i]->data;
        }
    return NULL;
}

void* H_next(HashMap* map){
    int i=0;
    for(i=map->current+1;i<map->capac;i++){
        if(map->hashArray[i] && map->hashArray[i]->data) {
            map->current=i;
            return map->hashArray[i]->data;
        }
    }
    return NULL;
}
