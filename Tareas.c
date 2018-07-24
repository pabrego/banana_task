#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tareas.h"

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
                    if(strcmp(key_1->nombre, key_2->nombre) < 0)
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

int buscar_categoria(char* nombre_categoria, Lista* lista_categoria)
{
    char* categoria;

    categoria = first_L(lista_categoria);

    while(categoria != NULL)
    {
        if(strcmp(nombre_categoria, categoria) == 0)
        {
            return 1;
        }
        categoria = next_L(lista_categoria);
    }

    return 0;
}

void agregar_tarea(HashMap* M_categorias, Lista* N_categorias, RBTree* G_fecha, RBTree** Array_prioridad)
{
    int opcion;
    char* aux;
    Tarea* nodo = crea_tarea();
    Categoria* nodo_cat = NULL;// = crear_categoria();

    while(1)
    {
        printf("Ingrese la categoria de la tarea\n");
        printf("Lista de categorias existentes:\n");
        aux = first_L(N_categorias);

        while(aux)
        {
            printf("%s\n", aux);
        }
        free(aux);
        aux = (char*)malloc(sizeof(char)*16);
        scanf(" ");
        fgets(aux, 15, stdin);
        aux[strlen(aux)-1] = '\0';

        if(buscar_categoria(aux, N_categorias) == 0)
        {
            printf("La categoria ingresada no existe.\nDesea agregarla?\n");
            printf("1. Si\n2. No\n");
seleccion:  scanf("%d", &opcion);
            switch (opcion)
            {
            case 1:
                nodo_cat = crea_n_categoria(aux);
                pushBack(N_categorias, aux);
                insert_H(M_categorias, (long)aux, nodo);
                break;
            case 2:
                printf("Porfavor, seleccione una categoria existente.\n");
            default:
                printf("Porfavor, seleccione una opcion valida.\n");
                goto seleccion;
            }
        }
    }

    nodo->categoria = aux;

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

    RB_insert(G_fecha, nodo, nodo);
    RB_insert(Array_prioridad[(nodo->prioridad)-1], nodo, nodo);
    nodo_cat = search(M_categorias, (long)nodo->categoria);
    RB_insert(nodo_cat->por_prioridad[(int)(nodo->prioridad)-1],nodo, nodo);
    RB_insert(nodo_cat->por_fecha, nodo, nodo);
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

void mostrar_categoria(HashMap* hash_categorias, Lista* list_categoria)
{
    int i, op;
    Categoria* aux = first_L(list_categoria);
    printf("\n");
    printf(" _________________________________________ \n" );
    printf("                                         \n" );
    for(i=0;i<(int)get_size_L(list_categoria);i++)
    {
        printf(" %d.- %s \n", i+1, aux->n_categoria);
        aux = next_L(list_categoria);
    }
    printf(" _________________________________________\n" );
    scanf("%d", &op);
    aux = first_L(list_categoria);
    for(op; op > 1; op--)
    {
        aux = next_L(list_categoria);
    }
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
        case 1: mostrar_arbol(aux->por_fecha);break;
        case 2: mostrar_prioridad(aux->por_priori);break;
        case 0: break;
    }

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
