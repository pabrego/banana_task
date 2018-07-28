#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "rbtree.h"
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
    RBTree** por_prioridad;
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
    char* n_categoria;
    Tarea* nodo = crea_tarea();
    Categoria* nodo_cat;
    nodo_cat = L_first(Categorias);
    if(nodo_cat != NULL)
    {
        printf("Lista de categorias existentes:\n");
        while(nodo_cat)
        {
            printf("%s\n", nodo_cat->n_categoria);
            nodo_cat = L_next(Categorias);

        }
    }
    else
    {
        printf("No hay categorias existentes.\n");
    }
    free(nodo_cat);
    n_categoria = (char*)malloc(sizeof(char)*16);

    printf("Ingrese la categoria de la tarea:\n");

    while (nodo_cat == NULL)
    {
        scanf(" ");
        fgets(n_categoria, 15, stdin);
        n_categoria[strlen(n_categoria)-1] = '\0';
        nodo_cat = buscar_categoria(Categorias, n_categoria);
        if(nodo_cat == NULL)
        {
            printf("La categoria ingresada no existe.\n Desea agregarla?\n1. Si 2.No\n");
            scanf("%d", &opcion);
            getchar();
            switch (opcion)
            {
            case 1:
                nodo_cat = crea_n_categoria(n_categoria);
                break;
            case 2:
                printf("Porfavor, seleccione una categoria existente\n");
            }
        }
    }
    nodo->categoria = n_categoria;
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

    printf("Inserte la fecha de la tarea:\n");
    printf("Ingrese el dia:  ");
    scanf("%d", &nodo->fecha->dia);
    printf("\n");
    printf("Ingrese el mes:  ");
    scanf("%d", &nodo->fecha->mes);
    printf("\n");
    printf("Ingrese el a%co:  ", 164);
    scanf("%d", &nodo->fecha->anio);
    printf("\n");

    RB_insert(todoPorFecha, nodo, nodo);
    RB_insert(todoPorPrioridad[(nodo->prioridad)-1], nodo, nodo);
    RB_insert(nodo_cat->por_fecha, nodo, nodo);
    RB_insert(nodo_cat->por_prioridad[(nodo->prioridad)-1], nodo, nodo);

    if(opcion == 1)
    {
        L_pushBack(Categorias, nodo_cat);
    }

    system("cls");
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
    getchar();
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
            nodo_cat = buscar_categoria(Categorias, nodo->categoria);
            RB_delete(todoPorFecha, nodo);
            RB_delete(todoPorPrioridad[(nodo->prioridad)-1], nodo);
            RB_delete(nodo_cat->por_fecha, nodo);
            RB_delete(nodo_cat->por_prioridad[(nodo->prioridad)-1], nodo);
            free(nodo);
            nodo = NULL;
            printf("Tarea %s exitosamente elimindada\n", cadena);
            getchar();
        }
        else
        {
            nodo = RB_next(todoPorFecha);
        }
    }
    system("cls");
}

void mostrar_arbol(RBTree* arbol)
{
    Tarea* imprimir = RB_first(arbol);
    int i, day, month, year, priority, activa;
    char* name, *category;
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
        if(!activa)
        {
            printf(" Sin realizar\n");
        }
        else
        {
            printf(" Realizada\n");
        }
        imprimir = RB_next(arbol);
    }
}

void mostrar_prioridad(RBTree** por_prioridad)
{
    int i;
    for(i=4;i>=0;i--)
    {
        mostrar_arbol(por_prioridad[i]);
    }
}

void mostrar_categoria(Lista* list_categoria)
{
    system("cls");
    int i, opcion;
    Categoria* aux = L_first(list_categoria);
    printf(" _________________________________________ \n" );
    printf("\n" );
    for(i=0;i<L_get_size(list_categoria);i++)
    {
        printf(" %d.- %s \n", i+1, aux->n_categoria);
        aux = L_next(list_categoria);
    }
    printf(" _________________________________________ \n" );

    printf("Eliga una de las categorias.\n");
    scanf("%d", &opcion);
    getchar();
    aux = L_first(list_categoria);
    for(i=0;i<L_get_size(list_categoria);i++)
    {
        if (opcion == i+1)
            break;
        aux = L_next(list_categoria);
    }

    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|   1.-  Categorias por fecha.            |\n" );
    printf("|   2.-  Categorias por prioridad.        |\n" );
    printf("|_________________________________________|\n" );

    scanf("%d", &opcion);
    getchar();
    system("cls");
    printf("\n");
    switch (opcion)
    {
        case 1: mostrar_arbol(aux->por_fecha);break;
        case 2: mostrar_prioridad(aux->por_prioridad);break;
        case 0: break;
        default: printf("Opcion invalida\n");
    }
}

void mostrar_todo(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    int opcion;
    seleccionorden: system("cls");
    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|        TODAS:                           |\n" );
    printf("|   1.-  Ordenadas por fecha.             |\n" );
    printf("|   2.-  Ordenadas por prioridad.         |\n" );
    printf("|   3.-  Ordenadas por categoria.         |\n" );
    printf("|                                         |\n" );
    printf("|   0.-  Volver al menu principal.        |\n" );
    printf("|_________________________________________|\n" );
    scanf("%d", &opcion);
    getchar();

    system("cls");
    printf("\n");
    switch (opcion)
    {
        case 1: mostrar_arbol(por_fecha); getchar(); goto seleccionorden;
        case 2: mostrar_prioridad(por_prioridad); getchar(); goto seleccionorden;
        case 3: mostrar_categoria(lista_categorias); getchar(); goto seleccionorden;
        case 0: break;
        default: printf("Opcion invalida\n");
    }
    system("cls");
}

Tarea* leer_tarea(char line[])
{
    Tarea* t = crea_tarea();
    const char s[2] = ",";
    char *token;

    token = strtok(line, s);
    token[strlen(token)]='\0';
    t->fecha->dia = atoi(token);

    token = strtok(NULL, s);
    token[strlen(token)]='\0';
    t->fecha->mes = atoi(token);

    token = strtok(NULL, s);
    token[strlen(token)]='\0';
    t->fecha->anio = atoi(token);

    token = strtok(NULL, s);
    token[strlen(token)]='\0';
    t->prioridad = atoi(token);

    token = strtok(NULL, s);
    token[strlen(token)]='\0';
    strcpy(t->nombre, token);

    token = strtok(NULL, s);
    token[strlen(token)]='\0';
    strcpy(t->descripcion, token);

    token = strtok(NULL, s);
    token[strlen(token)]='\0';
    strcpy(t->categoria, token);

    token = strtok(NULL,s);
    if(token != NULL)
    {
        t->estado = atoi(token);
    }
    return t;
}

void guardar_todo(RBTree* por_fecha)
{
    FILE* fp = fopen("tareas_guardadas.csv", "w");
    Tarea* imprimir = RB_first(por_fecha);
    int day, month, year, priority, activa;
    char* name, *category, *desc;

    while(imprimir)
    {
        day = imprimir->fecha->dia;
        month = imprimir->fecha->mes;
        year = imprimir->fecha->anio;
        name = imprimir->nombre;
        priority = imprimir->prioridad;
        category = imprimir->categoria;
        activa = imprimir->estado;
        desc = imprimir->descripcion;
        fprintf(fp, "%d,%d,%d,%d,%s,%s,%s,%d\n", day, month, year, priority, name, desc, category, activa);
        imprimir = RB_next(por_fecha);
    }
    fclose(fp);
}

void cargar_archivo(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    FILE* fp = fopen("tareas_guardadas.csv","r");
    if(fp == NULL){
        printf("error de lectura\n");
        exit(0);
    }
    Tarea* aux;
    Categoria* category;
    char linea[250];
    int existe;
    while(fgets(linea, 250, fp))
    {
        existe = 1;
        linea[strlen(linea)-1] = '\0';
        aux = leer_tarea(linea);
        category = buscar_categoria(lista_categorias, aux->categoria);
        if(category == NULL)
        {
            existe = 0;
            category = crea_n_categoria(aux->categoria);
        }
        RB_insert(por_fecha, aux, aux);
        RB_insert(por_prioridad[aux->prioridad - 1], aux, aux);
        RB_insert(category->por_fecha, aux, aux);
        RB_insert(category->por_prioridad[aux->prioridad - 1], aux, aux);
        if(!existe)
        {
            L_pushBack(lista_categorias, category);
        }
    }
}


void editar_tarea(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    int opcion, i;
    system("cls");
    
    //Aqui debe ir un menu que de la posibilidad de hacer el realizar_tarea() o lo que esta aca abajo.
    
    printf("\n");
    mostrar_arbol(por_fecha);
    printf("\n");
    printf("Eliga la tarea a editar: ");
    scanf("%d", &opcion);
    getchar();
    Tarea* aux = RB_first(por_fecha);
    i = 1;
    while (aux)
    {
        if (opcion == i)
            break;
        i++;
        aux = RB_next(por_fecha);
    }
    
    printf("\n");
    printf("|%d.- %d/%d/%d  %s  %s ", opcion, aux->fecha->dia, aux->fecha->mes, aux->fecha->anio, aux->nombre, aux->categoria);

    if(aux->prioridad == 1)
        printf("Muy Baja  ");
    else if(aux->prioridad == 2)
        printf("Baja  ");
    else if(aux->prioridad == 3)
        printf("Media  ");
    else if(aux->prioridad == 4)
        printf("Alta  ");
    else if(aux->prioridad == 5)
        printf("Muy Alta  ");

    if(!aux->estado)
        printf(" Sin realizar\n");
    else
        printf(" Realizada\n");
    
    printf("Modifique los datos...\n");
    //Hacer copia del nodo Tarea* y luego modificar este, una vez hecho se elimina el nodo original de los arboles
    //Una vez eliminado de los arboles, ingreso el nodo copia en todos los arboles, EZ.
    system("cls");
}
