#ifndef GESTION_DE_ARCHIVOS_H
#define GESTION_DE_ARCHIVOS_H

#include <stdio.h>
#include <string.h>

FILE* abriArchivoStatus(char pid[]);
FILE* crearArchivoReporte(int narg, char *pids[], char nombreReporte[]);

#endif