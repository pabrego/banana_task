#include <stdlib.h>
#include <stdio.h>-
#include <string.h>

typedef struct Tarea{
    char* categoria;
    char* nombre;
    char* descripcion;
    int prioridad;
    Fecha* fecha;
    int estado;
}Tarea;

typedef struct Categoria{
    TreeMap* por_fecha;
    TreeMap* por_cate;
    char* nombre;
}Categoria;

typedef struct Fecha{
    int dia;
    int mes;
    int anio;
}Fecha*

void* agregar_tarea()
void*

int main(){




}
