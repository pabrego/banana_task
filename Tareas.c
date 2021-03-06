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


int lower_than(Tarea* key_1, Tarea* key_2)                    /*La funcion ordena por fecha. Si la fecha es igual, */
{                                                             /*ordena por orden alfabetico.*/
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

Categoria* crea_n_categoria(char* nombre)                           /*Se crea un nodo de categoria con su respectivo nombre*/
{        
    int i;
    RBTree** Array = (RBTree**)malloc(sizeof(RBTree*)*5);
    Categoria* nodo = (Categoria*) malloc(sizeof(Categoria));
    for(i=0; i<5; i++)
    {
        Array[i] = create_RBTree((int(*)(void*, void*))(lower_than));      
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

Categoria* buscar_categoria(Lista* Categorias, char* nombre)    /*Se busca una categoria en la lista de categorias.*/
{                                                               /*Si la encuentra, retorna el nodo, sino retorna NULL*/
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
        printf("Lista de categorias existentes:\n");                /*Se imprime la lista de categorias.*/
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
                nodo_cat = crea_n_categoria(n_categoria);                   /*Si la categoria ingresada no existe, se le pregunta */ 
                break;                                                      /*al usuario si desea crearla.*/
            case 2:
                printf("Porfavor, seleccione una categoria existente\n");
            }
        }
    }
    nodo->categoria = n_categoria;
    printf("Ingrese el nombre de la tarea:\n");                /*Se leen los datos de la tarea.*/
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

    RB_insert(todoPorFecha, nodo, nodo);                                    /*Una vez ingresados los datos, se ingresa la tarea */
    RB_insert(todoPorPrioridad[(nodo->prioridad)-1], nodo, nodo);           /*a las estructruras respectivas.*/
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
    int opcion, existe = 0;
    Tarea* nodo;

    Categoria* nodo_cat = NULL;

    printf("¿Desea imprimir todos los nombres de las tareas existentes?\n");        /*Se le pregunta al usuario si desea ver */
    printf("1. Si   2. No\n");                                                      /*los nombres de las tareas existentes.*/
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
    printf("Ingrese el nombre de la tarea a eliminar:\n");                      /*Luego se le pedira que ingrese el nombre de */
    fgets(cadena, 30, stdin);                                                   /*la tarea a eliminar.*/
    cadena[strlen(cadena)-1] = '\0';

    nodo = RB_first(todoPorFecha);
    while (nodo)
    {
        if(strcmp(nodo->nombre, cadena) == 0)
        {
            nodo_cat = buscar_categoria(Categorias, nodo->categoria);           /*Si la tarea existe, es eliminada de todos los mapas.*/
            RB_delete(todoPorFecha, nodo);
            RB_delete(todoPorPrioridad[(nodo->prioridad)-1], nodo);
            RB_delete(nodo_cat->por_fecha, nodo);
            RB_delete(nodo_cat->por_prioridad[(nodo->prioridad)-1], nodo);
            free(nodo);
            nodo = NULL;
            existe = 1;
            printf("Tarea %s exitosamente elimindada\n", cadena);
        }
        else
        {
            nodo = RB_next(todoPorFecha);
        }
    }
    if(!existe)
    {
        printf("La tarea ingresada no se encuentra en el sistema.\n");      /*Si no existe, se imprime en pantalla un mensaje de error.*/
    }
    printf("Presione ENTER para continuar");
    getchar();
    system("cls");
}

void mostrar_arbol(RBTree* arbol)
{
    Tarea* imprimir = RB_first(arbol);
    int i, day, month, year, priority, activa;
    char* name, *category;

    if(arbol == NULL)       //si el arbol no contiene nada....
    {
        printf("No se han encontrado tareas en el sistema.");
    }
    else
    {
        for(i=0;imprimir;i++){
            day = imprimir->fecha->dia;     //actualizo valores de variables
            month = imprimir->fecha->mes;   //con la nueva tarea 'imprimir'
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
            imprimir = RB_next(arbol);   //paso a la siguiente tarea del arbol
        }
    }
}

void mostrar_prioridad(RBTree** por_prioridad)
{
    int i;
    for(i=4;i>=0;i--)   //recorro el arreglo de arboles por prioridad
    {
        mostrar_arbol(por_prioridad[i]);//imprimo el arbol
    }
}

void mostrar_categoria(Lista* list_categoria)
{
    system("cls");
    int i, opcion;
    Categoria* aux = L_first(list_categoria);
    printf(" _________________________________________ \n" );
    printf("\n" );
    for(i=0;i<L_get_size(list_categoria);i++)   //recorro lista de categorias
    {
        printf(" %d.- %s \n", i+1, aux->n_categoria);//imprimo el nombre de la categoria
        aux = L_next(list_categoria);
    }
    printf(" _________________________________________ \n" );

    printf("Eliga una de las categorias.\n");
    scanf("%d", &opcion);       //se pregunta por el numero de la categoria
    getchar();
    aux = L_first(list_categoria);
    for(i=0;i<L_get_size(list_categoria);i++)
    {                        //recorro la lista hasta la categoria seleccionada
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

    scanf("%d", &opcion);       //leo opcion elegida
    getchar();
    system("cls");
    printf("\n");
    switch (opcion)
    {
        case 1: mostrar_arbol(aux->por_fecha);break;// si es 1, paso el arbol ordenado por fechas
        case 2: mostrar_prioridad(aux->por_prioridad);break;//si es 2, paso el arbol ordenado por prioridad
        case 0: break;
        default: printf("Opcion invalida\n");
    }
}

void mostrar_todo(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    system("cls");
    int opcion;
    Tarea* val;
    val = RB_first(por_fecha);
    if(val == NULL)
    {
        printf("No hay tareas en el sistema.\n Presione ENTER para continuar");
    }
    else
    {
    seleccionorden:
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
        switch (opcion) //se pregunta opcion y se llama a la funcion respectiva
        {               //segun el orden en el cual se quieran imprimir las tareas
            case 1: mostrar_arbol(por_fecha);
            {
                printf("Presione ENTER para continuar");
                getchar();
                system("cls");
                goto seleccionorden;
            }
            case 2: mostrar_prioridad(por_prioridad);
            {
                printf("Presione ENTER para continuar");
                getchar();
                system("cls");
                goto seleccionorden;
            }
            case 3: mostrar_categoria(lista_categorias);
            {
                printf("Presione ENTER para continuar");
                getchar();
                system("cls");
                goto seleccionorden;
            }
            case 0: break;
            default:
                {
                    printf("Opcion invalida\n");
                    opcion = 0;
                    goto seleccionorden;
                }
        }
    }
    system("cls");
}

Tarea* leer_tarea(char line[])//recibo una linea del archivo con la informacion de la tarea
{                             //devuelvo informacion en formato 'Tarea'
    Tarea* t = crea_tarea();
    const char s[2] = ",";//datos separados por ','
    char *token;

    token = strtok(line, s);       //leo el dia de la tarea
    token[strlen(token)]='\0';
    t->fecha->dia = atoi(token);

    token = strtok(NULL, s);        //leo el mes de la tarea
    token[strlen(token)]='\0';
    t->fecha->mes = atoi(token);

    token = strtok(NULL, s);        //leo al año de la tarea
    token[strlen(token)]='\0';
    t->fecha->anio = atoi(token);

    token = strtok(NULL, s);        //leo la prioridad de la tarea
    token[strlen(token)]='\0';
    t->prioridad = atoi(token);

    token = strtok(NULL, s);        //leo el nombre de la tarea
    token[strlen(token)]='\0';
    strcpy(t->nombre, token);

    token = strtok(NULL, s);        //leo la descripcion de la tarea
    token[strlen(token)]='\0';
    strcpy(t->descripcion, token);

    token = strtok(NULL, s);        //leo la categoria de la tarea
    token[strlen(token)]='\0';
    strcpy(t->categoria, token);

    token = strtok(NULL,s);         //verifico el estado de la tarea
    if(token != NULL)
    {
        t->estado = atoi(token);
    }
    return t;

void guardar_todo(RBTree* por_fecha)
{
    FILE* fp = fopen("tareas_guardadas.csv", "w");// creo/abro cargar_archivo
    Tarea* imprimir = RB_first(por_fecha);
    int day, month, year, priority, activa;
    char* name, *category, *desc;

    while(imprimir)
    {
        day = imprimir->fecha->dia;     //actualizo dato de la tarea a guardar
        month = imprimir->fecha->mes;
        year = imprimir->fecha->anio;
        name = imprimir->nombre;
        priority = imprimir->prioridad;
        category = imprimir->categoria;
        activa = imprimir->estado;
        desc = imprimir->descripcion;
        fprintf(fp, "%d,%d,%d,%d,%s,%s,%s,%d\n", day, month, year, priority, name, desc, category, activa);
        //guardo en una linea todos los datos de la tarea
        imprimir = RB_next(por_fecha);
    }
    fclose(fp);//cierro archivo
}

void cargar_archivo(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    //inicializo 3 categorias predeterminadas
    L_pushBack(lista_categorias, crea_n_categoria("Universidad"));
    L_pushBack(lista_categorias, crea_n_categoria("Casa"));
    L_pushBack(lista_categorias, crea_n_categoria("Trabajo"));
    FILE* fp = fopen("tareas_guardadas.csv","r");//abro archivo con las tareas
    if(fp == NULL){
        return;     //si no existe retorno
    }
    Tarea* aux;
    Categoria* category;
    char linea[250];
    int existe;
    while(fgets(linea, 250, fp))//leo cada linea del archivo
    {
        existe = 1;
        linea[strlen(linea)-1] = '\0';
        aux = leer_tarea(linea);    //creo la tarea con la info de la linea
        category = buscar_categoria(lista_categorias, aux->categoria);//busco categoria
        if(category == NULL)
        {
            existe = 0; //si no existe, creo la categoria
            category = crea_n_categoria(aux->categoria);
        }
     //inserto la tarea en sus respectivos arboles
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

void realizar_tarea(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    system("cls");
    int opcion, i;
    Tarea* aux;
    printf("\n");
    mostrar_arbol(por_fecha);
    printf("\n");
    printf("Eliga la tarea a realizar: ");
    scanf("%d", &opcion);
    getchar();

    aux = RB_first(por_fecha);
    i = 1;
    while (aux)
    {
        if (opcion == i)
            break;
        i++;
        aux = RB_next(por_fecha);
    }
    aux->estado = 1;
    printf("\n");
    printf("| %d/%d/%d  %s  Realizada\n", aux->fecha->dia, aux->fecha->mes, aux->fecha->anio, aux->nombre);
    getchar();
    system("cls");
}

void insertar_copia(Tarea* auxCopia, Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    Categoria* nodo_cat = buscar_categoria(lista_categorias, auxCopia->categoria);
    RB_insert(por_fecha, auxCopia, auxCopia);
    RB_insert(por_prioridad[(auxCopia->prioridad)-1], auxCopia, auxCopia);
    RB_insert(nodo_cat->por_fecha, auxCopia, auxCopia);
    RB_insert(nodo_cat->por_prioridad[(auxCopia->prioridad)-1], auxCopia, auxCopia);
}

void quitar_original(Tarea* aux, Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    Categoria* nodo_cat = buscar_categoria(lista_categorias, aux->categoria);
    RB_delete(por_fecha, aux);
    RB_delete(por_prioridad[(aux->prioridad)-1], aux);
    RB_delete(nodo_cat->por_fecha, aux);
    RB_delete(nodo_cat->por_prioridad[(aux->prioridad)-1], aux);
    free(aux);
}

void modificar_tarea(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    system("cls");
    int opcion, i;
    printf("\n");
    mostrar_arbol(por_fecha);
    printf("\n");
    printf("Seleccione el n%cmero la tarea a editar: ", 163);
    scanf("%d", &opcion);
    getchar();

    Tarea* aux = RB_first(por_fecha);
    i = 1;
    while(aux)
    {
        if (opcion == i)
            break;
        i++;
        aux = RB_next(por_fecha);
    }

    if(aux)
    {
        Tarea* auxCopia = crea_tarea();
        auxCopia->nombre = aux->nombre;
        auxCopia->categoria = aux->categoria;
        auxCopia->descripcion = aux->descripcion;
        auxCopia->fecha->dia = aux->fecha->dia;
        auxCopia->fecha->mes = aux->fecha->mes;
        auxCopia->fecha->anio = aux->fecha->anio;
        auxCopia->estado = aux->estado;
        auxCopia->prioridad = aux->prioridad;

    noterminar: system("cls");
        printf("\n");
        printf("|%d.- %d/%d/%d  %s  |%s|  %s  ", i, auxCopia->fecha->dia, auxCopia->fecha->mes, auxCopia->fecha->anio, auxCopia->nombre, auxCopia->descripcion, auxCopia->categoria);

        if(auxCopia->prioridad == 1)
            printf("Muy Baja  ");
        else if(auxCopia->prioridad == 2)
            printf("Baja  ");
        else if(auxCopia->prioridad == 3)
            printf("Media  ");
        else if(auxCopia->prioridad == 4)
            printf("Alta  ");
        else if(auxCopia->prioridad == 5)
            printf("Muy Alta  ");

        if(!auxCopia->estado)
            printf(" Sin realizar\n");
        else
            printf(" Realizada\n");

        printf("\n");
        printf("Modifique los datos...\n");
        printf("\n");
        printf(" _________________________________________ \n" );
        printf("|                                         |\n" );
        printf("|   1.-  Fecha.                           |\n" );
        printf("|   2.-  Nombre.                          |\n" );
        printf("|   3.-  Descripcion.                     |\n" );
        printf("|   4.-  Prioridad.                       |\n" );
        printf("|                                         |\n" );
        printf("|   0.-  Guardar cambios y volver.        |\n" );
        printf("|_________________________________________|\n" );
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
            case 1: printf("Ingrese el dia:  ");
                    scanf("%d", &auxCopia->fecha->dia);
                    printf("\n");
                    printf("Ingrese el mes:  ");
                    scanf("%d", &auxCopia->fecha->mes);
                    printf("\n");
                    printf("Ingrese el a%co:  ", 164);
                    scanf("%d", &auxCopia->fecha->anio);
                    goto noterminar;
            case 2: printf("Ingrese el nombre: ");
                    fgets(auxCopia->nombre, 30, stdin);
                    auxCopia->nombre[strlen(auxCopia->nombre)-1] = '\0';
                    goto noterminar;
            case 3: printf("Ingrese la descripcion: ");
                    fgets(auxCopia->descripcion, 140, stdin);
                    auxCopia->descripcion[strlen(auxCopia->descripcion)-1] = '\0';
                    goto noterminar;
            case 4: printf("Ingrese la prioridad: ");
    priori:         scanf("%d", &auxCopia->prioridad);
                    if((auxCopia->prioridad>5) || (auxCopia->prioridad<1))
                    {
                        printf("Porfavor, ingrese una prioridad valida: ");
                        goto priori;
                    }
                    goto noterminar;
            case 0: quitar_original(aux, lista_categorias, por_fecha, por_prioridad);
                    insertar_copia(auxCopia, lista_categorias, por_fecha, por_prioridad);
                    printf("Se guardaron los datos exitosamente.");
                    break;
            default: printf("Opcion invalida\n");
            {
                getchar();
            }
        }
    }
    else
    {
        printf("La opcion ingresada no es valida.\n");
        printf("Presione ENTER para continuar");
        getchar();
    }
    system("cls");
}

void editar_tarea(Lista* lista_categorias, RBTree* por_fecha, RBTree** por_prioridad)
{
    int opcion;
editar: system("cls");
    printf("\n");
    printf(" _________________________________________ \n" );
    printf("|                                         |\n" );
    printf("|   1.-  Modificar tarea.                 |\n" );
    printf("|   2.-  Realizar tarea.                  |\n" );
    printf("|                                         |\n" );
    printf("|   0.-  Volver al menu principal.        |\n" );
    printf("|_________________________________________|\n" );

    scanf("%d", &opcion);
    getchar();

    printf("\n");
    switch (opcion)
    {
        case 1: modificar_tarea(lista_categorias, por_fecha, por_prioridad); goto editar;
        case 2: realizar_tarea(lista_categorias, por_fecha, por_prioridad); goto editar;
        case 0: break;
        default: printf("Opcion invalida\n");
    }
    system("cls");
}
