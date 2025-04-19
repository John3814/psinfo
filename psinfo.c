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
};

char *names[] = {"Name", "State", "Pid", "VmSize", "VmData", "VmStk", "VmExe", "voluntary_ctxt_switches", "nonvoluntary_ctxt_switches"};
int lengthName = sizeof(names) / sizeof(names[0]);

FILE *file;
struct proceso obtenerInfo(FILE *fptr);
void registrarDatoEnProceso(struct proceso *myProceso, int caso, char dato[]);
void imprimirInfo(struct proceso myProceso);

int main(int argc, char *argv[])
{
    if (argc == 2) 
    {
        char dir[50];
        char pid[6];
        sprintf(pid, "%s", argv[1]);
        sprintf(dir, "/proc/%s/status", pid);
        file = fopen(dir, "r");
        struct proceso myProceso = obtenerInfo(file);
        imprimirInfo(myProceso);
        fclose(file);
    } else if (argc > 2)
    {
        if(strcmp(argv[1], "-l")  == 0)
        {   
            printf("\nInformación recolectada!!!\n\n");
            for (int i = 2; i < argc; i++)
            {
                char dir[50];
                char pid[6];
                sprintf(pid, "%s", argv[i]);
                sprintf(dir, "/proc/%s/status", pid);
                file = fopen(dir, "r");
                struct proceso myProceso = obtenerInfo(file);
                imprimirInfo(myProceso);
                fclose(file);
                printf("\n\n");
            }
        } 
        else if (strcmp(argv[1], "-r") == 0) {
            printf("La opcion %s no esta implementada!!", argv[1]);

        } else {
            printf("La opcion %s no esta definida!!", argv[1]);
        }
        
    }
    
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
                //printf("%s:%s\n", key, value);
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




