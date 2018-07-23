#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tareas.h"

int lower_than(Fecha* key_1, Fecha* key_2)
{
    if(key_1->anio < key_2->anio)
    {
        return 1;
    }
    else if(key_1->anio > key_2->anio)
    {
        return 0;
    }
    else
    {
        if(key_1->mes < key_2->mes)
        {
            return 1;
        }
        else if (key_1->mes > key_2->mes)
        {
            return 0;
        }
        else
        {
            if(key_1->dia < key_2->dia)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

Categoria* crea_n_categoria(){
    Categoria* nodo = (Categoria*) malloc(sizeof(Categoria));
    nodo->n_categoria = (char*) malloc(sizeof(char)*16);
  /*nodo->por_cate = create_treeMap();
    nodo->por_fecha = create_treeMap();*/
    return nodo;
}

Fecha* crea_fecha(){
    Fecha* nodo = (Fecha*) malloc(sizeof(Fecha));
    nodo->anio = 0;
    nodo->mes = 0;
    nodo->dia = 0;
    return nodo;
}

Tarea* crea_tarea(){
    Tarea* nodo = (Tarea*) malloc(sizeof(Tarea));
    nodo->nombre = (char*) malloc(sizeof(char)*31);
    nodo->descripcion = (char*) malloc(sizeof(char)*141);
    nodo->categoria = (char*) malloc(sizeof(char)*16);
    nodo->prioridad = 0;
    nodo->estado = 0;
    nodo->fecha = crea_fecha();
    return nodo;
}

void mostrar_todo(HashMap* hash_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    int opcion;

    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|        TODAS:                           |\n" );
    printf("|   1.-  Ordenadas por fecha.             |\n" );
    printf("|   2.-  Ordenadas por prioridad.         |\n" );
    printf("|                                         |\n" );
    printf("|   3.-  Revisar categorias.              |\n" );
    printf("|                                         |\n" );
    printf("|   0.-  Volver al menú principal.        |\n" );
    printf("|_________________________________________|\n" );

    switch (opcion)
    {
        case 1: mostrar_arbol(por_fecha);break;
        case 2: mostrar_prioridad(por_prioridad);break;
        case 3: mostrar_categoria(hash_categorias);break;
        case 0: break;
    }

}

void mostrar_prioridad(RBTree** por_prioridad)
{
    int i;
    for(i=0;i<5;i++)
    {
        mostrar_arbol(por_prioridad[i]);
    }
}

void mostrar_categoria(HashMap* hash_categorias)
{

}

void mostrar_arbol(RBTree* arbol)
{
    Tarea* imprimir = first(arbol);
    int* day = imprimir->fecha->dia;
    int* month = imprimir->fecha->mes;
    int* year = imprimir->fecha->anio;
    char* name = imprimir->nombre;
    int* priority = imprimir->prioridad;
    char* category = imprimir->categoria;
    int* activa = imprimir->estado;
    while(imprimir){
        if(*priority == 1)
        {
            printf("|%d/%d/%d  Baja   %s  %s ",day, month, year, name, category);
        }
        else if(*priority == 2)
        {
            printf("|%d/%d/%d  Media  %s  %s ",day, month, year, name, category);
        }
        else if(*priority == 3)
        {
            printf("|%d/%d/%d  Alta   %s  %s ",day, month, year, name, category);
        }
        if(activa)
        {
            printf("   Activa  \n");
        }
        else
        {
            printf(" Realizada \n");
        }
        imprimir = next(arbol);
    }
}

void guardar_todo(RBTree* por_fecha)
{
    FILE* fp = fopen("tareas_guardadas.csv", "w");
    Tarea* imprimir = first(por_fecha);
    int* day = imprimir->fecha->dia;
    int* month = imprimir->fecha->mes;
    int* year = imprimir->fecha->anio;
    char* name = imprimir->nombre;
    int* priority = imprimir->prioridad;
    char* category = imprimir->categoria;
    int* activa = imprimir->estado;
    char* desc = imprimir->descripcion;
    while(imprimir)
    {
        fprintf(fp, "%d,%d,%d,%d,%s,%s,%d\n", day, month, year, priority, name, desc, category, activa);
        imprimir = next(por_fecha);
    }
    fclose(fp);
}

void cargar_archivo(HashMap* hash_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    FILE* fp = fopen("tareas_guardadas.csv","r");
    if(fp == NULL){
        printf("error de lectura\n");exit(0);
    }
    Tarea* aux;
    Categoria* category;
    char* linea[250];
    int i;
    while(fgets(linea, 250, fp))
    {
        linea[strlen(linea)-1] = '\0';
        aux = leer_tarea(linea);
        RB_insert(por_fecha, aux->fecha, aux);
        RB_insert(por_prioridad[aux->prioridad - 1], aux->fecha, aux);
        category = hp_search(hash_categorias, atoi(aux->categoria));
        RB_insert(category->por_fecha, aux->flecha, aux);
        RB_insert(category->por_prioridad[aux->prioridad - 1], aux->fecha, aux);
    }

}

Tarea* leer_tarea(char line[])
{
    t = crea_tarea();
    const char s[2] = ",";
    char *token;

    token = strtok(line, s);
    token[strlen(token)-1]='\0';
    t->dia = atoi(token);

    token = strtok(NULL, s);
    token[strlen(token)-1]='\0';
    t->mes = atoi(token);

    token = strtok(NULL, s);
    token[strlen(token)-1]='\0';
    t->anio = atoi(token);

    token = strtok(NULL, s);
    token[strlen(token)-1]='\0';
    strcpy(p->nombre, token);

    token = strtok(NULL, s);
    token[strlen(token)-1]='\0';
    strcpy(p->descripcion, token);

    token = strtok(NULL, s);
    token[strlen(token)-1]='\0';
    strcpy(p->categoria, token);

    token = strtok(NULL,caracter);
    if(token != NULL)
    {
        p->estado = atoi(token);
    }
    return t;
}
