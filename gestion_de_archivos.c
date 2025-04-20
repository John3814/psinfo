#include <stdio.h>
#include <string.h>

FILE* abriArchivoStatus(char pid[])
{
    char myDir[50];
    sprintf(myDir, "/proc/%s/status", pid);
    return fopen(myDir, "r");
}


FILE* crearArchivoReporte(int narg, char *pids[], char nombreReporte[])
{
    for (int i = 2; i < narg; i++)
    {
        strcat(nombreReporte, "-");
        strcat(nombreReporte, pids[i]);
    }
    strcat(nombreReporte, ".info");
    return fopen(nombreReporte, "w");
}
