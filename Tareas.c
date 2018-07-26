#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tareas.h"

typedef struct Tarea{
    char* categoria;
    char* nombre;
    char* descripcion;
    int prioridad;
    struct Fecha* fecha;
    int estado;
}Tarea;
 
typedef struct Categoria{
    RBTree* por_fecha;
    RBTree** por_priori;
    char* n_categoria;
}Categoria;
 
typedef struct Fecha{
    int dia;
    int mes;
    int anio;
}Fecha;

int lower_than(Tarea* key_1, Tarea* key_2)
{
        if(key_1->fecha->anio < key_2->fecha->anio)
        {
            return 1;
        }
        else if(key_1->fecha->anio > key_2->fecha->anio)
        {
            return 0;
        }
        else
        {
            if(key_1->fecha->mes < key_2->fecha->mes)
            {
                return 1;
            }
            else if (key_1->fecha->mes > key_2->fecha->mes)
            {
                return 0;
            }
            else
            {
                if(key_1->fecha->dia < key_2->fecha->dia)
                {
                    return 1;
                }
                else if (key_1->fecha->dia > key_2->fecha->dia)
                {
                    return 0;
                }
                else
                {
                    if(strcasecmp(key_1->nombre, key_2->nombre) < 0) //NO ES SENSIBLE A MAYUSCULAS
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
}

Categoria* crea_n_categoria(char* nombre)
{
    int i;
    RBTree** Array = (RBTree**)malloc(sizeof(RBTree*)*5);
    Categoria* nodo = (Categoria*) malloc(sizeof(Categoria));
    for(i=0; i<5; i++)
    {
        Array[i] = create_RBTree((int(*)(void*, void*))(lower_than));       //R E V I S A R
    }
    nodo->n_categoria = nombre;
    nodo->por_prioridad = Array;
    nodo->por_fecha = create_RBTree((int(*)(void*, void*))(lower_than));
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

Categoria* buscar_categoria(Lista* Categorias, char* nombre)
{
    Categoria* nodo;
    nodo = L_first(Categorias);
    while (nodo)
    {
        if(strcasecmp(nombre, nodo->n_categoria) == 0)
        {
            return nodo;
        }
        nodo = L_next(Categorias);
    }
    return NULL;
}

void agregar_tarea(Lista* Categorias, RBTree* todoPorFecha, RBTree** todoPorPrioridad)
{
    system("cls");
    int opcion;
    char* nombre;
    Tarea* nodo = crea_tarea();
    Categoria* nodo_cat;

    printf("Ingrese la categoria de la tarea\n");
    printf("Lista de categorias existentes:\n");
    nodo_cat = L_first(Categorias);

    while(nodo_cat)
    {
        printf("%s\n", nodo_cat->n_categoria);
        nodo_cat = L_next(Categorias);
    }
    free(nodo_cat);
    nombre = (char*)malloc(sizeof(char)*16);
    while (1)
    {
        fgets(nombre, 15, stdin);
        nombre[strlen(nombre)-1] = '\0';
        nodo_cat = buscar_categoria(nombre, Categorias);
        if(nodo_cat == NULL)
        {
            printf("La categoria ingresada no existe.\n ¿Desea agregarla?\n1. Si \n2. No\n");
            scanf("%d", &opcion);
            switch (opcion)
            {
                case 1:
                    nodo_cat = crea_n_categoria(nombre);
                    break;
                case 2:
                    printf("Porfavor, seleccione una categoria existente\n");
                    break;
                default:
                    printf("ingrese opcion valida\n");
                    break;
            }
        }
        else
        {
            break;
        }
    }

    printf("Ingrese el nombre de la tarea:\n");
    fgets(nodo->nombre, 30, stdin);
    nodo->nombre[strlen(nodo->nombre)-1] = '\0';

    printf("Ingrese la descripcion de la tarea:\n");
    fgets(nodo->descripcion, 140, stdin);
    nodo->descripcion[strlen(nodo->descripcion) -1] = '\0';


    printf("Del 1 al 5, ingrese la prioridad de la tarea:\n");
    while((nodo->prioridad<1) || (nodo->prioridad>5))
    {
        scanf("%d", &nodo->prioridad);
        if((nodo->prioridad>5) || (nodo->prioridad<1))
        {
            printf("Porfavor, ingrese una prioridad valida:\n");
        }
    }

    RB_insert(todoPorFecha, nodo, nodo);
    RB_insert(todoPorPrioridad[(nodo->prioridad)-1], nodo, nodo);
    RB_insert(nodo_cat->por_fecha, nodo, nodo);
    RB_insert(nodo_cat->por_prioridad[(nodo->prioridad)-1], nodo, nodo);
    L_pushBack(Categorias, nodo_cat);
}

void quitar_tarea(Lista* Categorias, RBTree* todoPorFecha, RBTree** todoPorPrioridad)
{
    system("cls");
    char cadena[31];
    int opcion;
    Tarea* nodo;
    Categoria* nodo_cat = NULL;

    printf("¿Desea imprimir todos los nombres de las tareas existentes?\n");
    printf("1. Si   2. No\n");
pregunta: scanf("%d", &opcion);
    if(opcion == 1)
    {
        nodo = RB_first(todoPorFecha);
        while (nodo)
        {
            printf("%s\n", nodo->nombre);
            nodo = RB_next(todoPorFecha);
        }
    }
    else if (opcion != 2)
    {
        printf("Porfavor, seleccione una opcion valida.\n");
        goto pregunta;
    }
    printf("Ingrese el nombre de la tarea a eliminar:\n");
    fgets(cadena, 30, stdin);
    cadena[strlen(cadena)-1] = '\0';

    nodo = RB_first(todoPorFecha);
        while (nodo)
        {
            if(strcmp(nodo->nombre, cadena) == 0)
            {
                RB_delete(todoPorFecha, nodo);
                RB_delete(todoPorPrioridad[(nodo->prioridad)-1], nodo);
                nodo_cat = buscar_categoria(Categorias, cadena);
                RB_delete(nodo_cat->por_fecha, nodo);
                RB_delete(nodo_cat->por_prioridad[(nodo->prioridad)-1], nodo);
                printf("Tarea %s exitosamente elimindada\n", cadena);
            }
        }

        if(nodo == NULL)
        {
            printf("La tarea ingresada no existe.\n");
        }
}


void mostrar_todo(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
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
    scanf("%d", &opcion);

    switch (opcion)
    {
        case 1: mostrar_arbol(por_fecha);break;
        case 2: mostrar_prioridad(por_prioridad);break;
        case 3: mostrar_categoria(lista_categorias);break;
        case 0: break;
        default: printf("Opcion invalida\n");
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

void mostrar_categoria(Lista* list_categoria)
{
    int i, opcion, op;
    Categoria* aux = L_first(list_categoria);
    printf("\n");
    printf(" _________________________________________ \n" );
    printf("                                         \n" );
    for(i=0;i<L_get_size(list_categoria);i++)
    {
        printf(" %d.- %s \n", i+1, aux->n_categoria);
        aux = L_next(list_categoria);
    }
    printf(" _________________________________________\n" );
    scanf("%d", &opcion);



    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|   1.-  Ordenadas por fecha.             |\n" );
    printf("|   2.-  Ordenadas por prioridad.         |\n" );
    printf("|                                         |\n" );
    printf("|   0.-  Volver al menú principal.        |\n" );
    printf("|_________________________________________|\n" );

    switch (opcion)
    {
        case 1: mostrar_arbol(aux->por_fecha);
            break;
        case 2: mostrar_prioridad(aux->por_prioridad);break;
        case 0: break;
        default: printf("Opcion invalida\n");
    }
}

void mostrar_arbol(RBTree* arbol)
{
    Tarea* imprimir = RB_first(arbol);
    int i, day, month, year, priority, activa, op;
    char* name;
    char* category;
    for(i=0;imprimir;i++){
        day = imprimir->fecha->dia;
        month = imprimir->fecha->mes;
        year = imprimir->fecha->anio;
        name = imprimir->nombre;
        priority = imprimir->prioridad;
        category = imprimir->categoria;
        activa = imprimir->estado;
        if(priority == 1)
        {
            printf("|%d.- %d/%d/%d  Muy Baja   %s  %s ",i+1 ,day, month, year, name, category);
        }
        else if(priority == 2)
        {
            printf("|%d.- %d/%d/%d  Baja  %s  %s ", i+1 ,day, month, year, name, category);
        }
        else if(priority == 3)
        {
            printf("|%d.- %d/%d/%d  Media   %s  %s ", i+1,day, month, year, name, category);
        }
        else if(priority == 4)
        {
            printf("|%d.- %d/%d/%d  Alta   %s  %s ", i+1, day, month, year, name, category);
        }
        else if(priority == 5)
        {
            printf("|%d.- %d/%d/%d  Muy Alta   %s  %s ", i+1 ,day, month, year, name, category);
        }
        if(activa)
        {
            printf("   Activa  \n");
        }
        else
        {
            printf(" Realizada \n");
        }
        imprimir = RB_next(arbol);
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
