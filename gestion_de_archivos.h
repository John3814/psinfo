#ifndef GESTION_DE_ARCHIVOS_H
#define GESTION_DE_ARCHIVOS_H

#include <stdio.h>
#include <string.h>

/*
 * Función: abri_archivo_status
 * ----------------------------
 * Abre el archivo /proc/<pid>/status correspondiente al PID recibido.
 *
 * pid: Cadena de caracteres que representa el PID de un proceso.
 *
 * return: Puntero al archivo abierto en modo lectura ("r").
 *         Si no se puede abrir, retorna NULL.
 */
FILE* abri_archivo_status(char pid[]);

/*
 * Función: crear_archivo_de_reporte
 * ---------------------------------
 * Crea un archivo de reporte cuyo nombre se genera automáticamente
 * concatenando los PIDs provistos.
 *
 * narg: Número de argumentos (usualmente argc del main).
 * pids: Lista de argumentos que contiene los PIDs (usualmente argv).
 * nombreReporte: Cadena donde se construirá el nombre del archivo.
 *
 * return: Puntero al archivo creado en modo escritura ("w").
 */
FILE* crear_archivo_de_reporte(int narg, char *pids[], char nombreReporte[]);

#endif
