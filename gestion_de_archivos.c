#include "gestion_de_archivos.h"

/*
 * Implementación de abri_archivo_status
 *
 * Construye la ruta al archivo de estado de un proceso dentro del sistema
 * de archivos virtual /proc, y lo abre en modo lectura.
 *
 * Ejemplo: para pid = "1234", se abre "/proc/1234/status".
 */
FILE* abri_archivo_status(char pid[])
{
    char myDir[50];
    sprintf(myDir, "/proc/%s/status", pid);  // Construye la ruta al archivo
    return fopen(myDir, "r");                // Intenta abrir el archivo
}

/*
 * Implementación de crear_archivo_de_reporte
 *
 * Construye un nombre para el archivo de salida concatenando los PIDs
 * recibidos, seguido de la extensión ".info". Luego, lo crea en modo
 * escritura.
 *
 * Ejemplo: si los PIDs son 123 y 456, se generará "psinfo-report-123-456.info"
 */
FILE* crear_archivo_de_reporte(int narg, char *pids[], char nombreReporte[])
{
    for (int i = 2; i < narg; i++)
    {
        strcat(nombreReporte, "-");         // Agrega separador
        strcat(nombreReporte, pids[i]);     // Agrega PID al nombre
    }
    strcat(nombreReporte, ".info");         // Agrega extensión del archivo
    return fopen(nombreReporte, "w");       // Crea archivo en modo escritura
}
