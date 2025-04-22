#ifndef PROCESO_H
#define PROCESO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char voluntarios[20];
    char no_voluntarios[20];
} cambios_de_contexto;

typedef struct {
    char pid[10];
    char nombre[50];
    char estado[20];
    char memoria_total[20];
    char memoria_text[20];
    char memoria_data[20];
    char memoria_stack[20];
    cambios_de_contexto cambios;
} proceso;

proceso obtener_info(FILE *fptr);
void registrar_dato_en_proceso(proceso *myProceso, int caso, char dato[]);
void agregar_info_de_proceso_en_reporte(FILE *fptr, proceso myProceso);
void imprimir_info_de_proceso(proceso myProceso);

#endif