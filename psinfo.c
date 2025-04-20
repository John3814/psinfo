#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cambiosDeContexto
{
    char voluntarios[20];
    char noVoluntarios[20];
};

struct proceso
{
    char pid[10];
    char nombre[50];
    char estado[20];
    char memoriaTotal[20];
    char memoriaText[20];
    char memoriaData[20];
    char memoriaStack[20];
    struct cambiosDeContexto cambios;
} myProceso;

char *names[] = {"Name", "State", "Pid", "VmSize", "VmData", "VmStk", "VmExe", "voluntary_ctxt_switches", "nonvoluntary_ctxt_switches"};
int lengthName = sizeof(names) / sizeof(names[0]);

FILE *file, *reporte;
void abriArchivoStatus(char pid[]);
void crearArchivoReporte(int arg, char *pids[], char nombreReporte[]);
struct proceso obtenerInfo(FILE *fptr);
void registrarDatoEnProceso(struct proceso *myProceso, int caso, char dato[]);
void imprimirInfo(struct proceso myProceso);
void agregarInfoEnReporte(FILE *fptr, struct proceso myProceso);

int main(int argc, char *argv[])
{   
    if (argc == 2) 
    {
        abriArchivoStatus(argv[1]);
        myProceso = obtenerInfo(file);
        imprimirInfo(myProceso);
        fclose(file);
    } else if (argc > 2)
    {
        
        if(strcmp(argv[1], "-l")  == 0)
        {   
            printf("\nInformación recolectada!!!\n\n");
            for (int i = 2; i < argc; i++)
            {
                abriArchivoStatus(argv[i]);
                myProceso = obtenerInfo(file);
                imprimirInfo(myProceso);
                fclose(file);
            }
        } 
        else if (strcmp(argv[1], "-r") == 0) {
            char nombreReporte[100] = "psinfo-report";
            crearArchivoReporte(argc, argv, nombreReporte);
            for (int i = 2; i < argc; i++)
            {
                abriArchivoStatus(argv[i]);
                myProceso = obtenerInfo(file);
                agregarInfoEnReporte(reporte, myProceso);
                fclose(file);
            }
            printf("Archivo de salida generado: %s\n", nombreReporte);
            fclose(reporte);
            
        } else {
            printf("La opcion %s no esta definida!!!\n", argv[1]);
        }   
    }
    
}

void abriArchivoStatus(char pid[])
{
    char myDir[50];
    sprintf(myDir, "/proc/%s/status", pid);
    file = fopen(myDir, "r");
}


void crearArchivoReporte(int arg, char *pids[], char nombreReporte[])
{
    for (int i = 2; i < arg; i++)
    {
        strcat(nombreReporte, "-");
        strcat(nombreReporte, pids[i]);
    }
    strcat(nombreReporte, ".info");
    reporte = fopen(nombreReporte, "w");
    fprintf(reporte, "Informacion recolectada!!!\n");
}


struct proceso obtenerInfo(FILE *fptr)
{
    char myString[100];
    int i = 0;
    struct proceso myProceso;
    while (fgets(myString, 100, fptr) && (i<lengthName))
    {
        char *myPtr = strtok(myString, ":\t");
        char key[50], value[500];
        int contador = 1;
        while (myPtr != NULL)
        {
            sprintf(value, "%s", myPtr);
            if (contador == 1)
            {
                sprintf(key, "%s", myPtr);
            } else {
                sprintf(value, "%s", myPtr);
            }
            myPtr = strtok(NULL, "\n");
            contador++;
        }
        if (strcmp(key, names[i]) == 0)
        {
                registrarDatoEnProceso(&myProceso, i, value);
                i++;
        }
    }
    return myProceso;
}


void registrarDatoEnProceso(struct proceso *myProceso, int caso, char dato[])
{
    switch (caso)
    {
        case 0:
            strcpy(myProceso->nombre, dato);
            break;
        case 1:
            strcpy(myProceso->estado, dato);
            break;
        case 2:
            strcpy(myProceso->pid, dato);
            break;
        case 3:
            strcpy(myProceso->memoriaTotal, dato);
            break;
        case 4:
            strcpy(myProceso->memoriaData, dato);
            break;
        case 5:
            strcpy(myProceso->memoriaStack, dato);
            break;
        case 6:
            strcpy(myProceso->memoriaText, dato);
            break;
        case 7:
            strcpy(myProceso->cambios.voluntarios, dato);
            break;
        case 8:
            strcpy(myProceso->cambios.noVoluntarios, dato);
        default:
            break;
    }
}

void imprimirInfo(struct proceso myProceso)
{
    printf("\n");
    printf("Pid:%s\n", myProceso.pid);
    printf("Nombre del proceso:%s\n", myProceso.nombre);
    printf("Tamaño total de la imagen de memoria:%s\n", myProceso.memoriaTotal);
    printf("Tamaño de la memoria TEXT:%s\n", myProceso.memoriaText);
    printf("Tamaño de la memoria DATA:%s\n", myProceso.memoriaData);
    printf("Tamaños de la memoria STACK%s\n", myProceso.memoriaStack);
    printf("Número de cambios de contexto:\n");
    printf("\tvoluntarios:%s\n", myProceso.cambios.voluntarios);
    printf("\tno voluntarios:%s\n", myProceso.cambios.noVoluntarios);
}

void agregarInfoEnReporte(FILE *fptr, struct proceso myProceso)
{
    fprintf(fptr, "\n");
    fprintf(fptr, "Pid:%s\n", myProceso.pid);
    fprintf(fptr, "Nombre del proceso:%s\n", myProceso.nombre);
    fprintf(fptr, "Tamaño total de la imagen de memoria:%s\n", myProceso.memoriaTotal);
    fprintf(fptr, "Tamaño de la memoria TEXT:%s\n", myProceso.memoriaText);
    fprintf(fptr, "Tamaño de la memoria DATA:%s\n", myProceso.memoriaData);
    fprintf(fptr, "Tamaños de la memoria STACK%s\n", myProceso.memoriaStack);
    fprintf(fptr, "Número de cambios de contexto:\n");
    fprintf(fptr, "\tvoluntarios:%s\n", myProceso.cambios.voluntarios);
    fprintf(fptr, "\tno voluntarios:%s\n", myProceso.cambios.noVoluntarios);
}