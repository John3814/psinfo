#ifndef PROCESO_H
#define PROCESO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Estructura: cambios_de_contexto
 * -------------------------------
 * Almacena el número de cambios de contexto de un proceso, diferenciando entre
 * voluntarios y no voluntarios.
 */
typedef struct {
    char voluntarios[20];
    char no_voluntarios[20];
} cambios_de_contexto;

/*
 * Estructura: proceso
 * -------------------
 * Representa la información relevante de un proceso obtenida del archivo
 * /proc/[pid]/status del sistema Linux.
 */
typedef struct {
    char pid[10];               // Identificador del proceso
    char nombre[50];            // Nombre del proceso
    char estado[20];            // Estado (ej. S, R, Z)
    char memoria_total[20];     // Memoria total usada por el proceso
    char memoria_text[20];      // Segmento TEXT (código ejecutable)
    char memoria_data[20];      // Segmento DATA
    char memoria_stack[20];     // Segmento STACK
    cambios_de_contexto cambios;// Cambios de contexto (voluntarios y no voluntarios)
} proceso;

/*
 * Función: obtener_info
 * ---------------------
 * Lee un archivo abierto (/proc/[pid]/status) y extrae los datos relevantes
 * para construir una estructura proceso.
 *
 * fptr: Puntero al archivo de entrada.
 *
 * return: Estructura de tipo proceso con los datos recolectados.
 */
proceso obtener_info(FILE *fptr);

/*
 * Función: registrar_dato_en_proceso
 * ----------------------------------
 * Guarda un valor específico dentro de un campo de la estructura proceso,
 * de acuerdo al índice del dato.
 *
 * myProceso: Puntero a la estructura proceso a modificar.
 * caso: Índice que identifica qué campo se va a llenar.
 * dato: Cadena de texto con el valor extraído.
 */
void registrar_dato_en_proceso(proceso *myProceso, int caso, char dato[]);

/*
 * Función: agregar_info_de_proceso_en_reporte
 * -------------------------------------------
 * Escribe la información del proceso en un archivo de salida.
 *
 * fptr: Puntero al archivo donde se escribirá la información.
 * myProceso: Estructura proceso con los datos a escribir.
 */
void agregar_info_de_proceso_en_reporte(FILE *fptr, proceso myProceso);

/*
 * Función: imprimir_info_de_proceso
 * ---------------------------------
 * Muestra por consola los datos almacenados en la estructura proceso.
 *
 * myProceso: Estructura con los datos a imprimir.
 */
void imprimir_info_de_proceso(proceso myProceso);

#endif
