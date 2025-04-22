#include "proceso.h"

char *datos[] = {"Name", "State", "Pid", "VmSize", "VmData", "VmStk", "VmExe", "voluntary_ctxt_switches", "nonvoluntary_ctxt_switches"};
int length_datos = sizeof(datos) / sizeof(datos[0]);

proceso obtener_info(FILE *fptr)
{
    char my_string[100];
    int i = 0;
    proceso my_proceso;
    while (fgets(my_string, 100, fptr) && (i<length_datos))
    {
        char *myPtr = strtok(my_string, ":\t");
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
        if (strcmp(key, datos[i]) == 0)
        {
                registrar_dato_en_proceso(&my_proceso, i, value);
                i++;
        }
    }
    return my_proceso;
}


void registrar_dato_en_proceso(proceso *my_proceso, int caso, char dato[])
{
    switch (caso)
    {
        case 0:
            strcpy(my_proceso->nombre, dato);
            break;
        case 1:
            strcpy(my_proceso->estado, dato);
            break;
        case 2:
            strcpy(my_proceso->pid, dato);
            break;
        case 3:
            strcpy(my_proceso->memoria_total, dato);
            break;
        case 4:
            strcpy(my_proceso->memoria_data, dato);
            break;
        case 5:
            strcpy(my_proceso->memoria_stack, dato);
            break;
        case 6:
            strcpy(my_proceso->memoria_text, dato);
            break;
        case 7:
            strcpy(my_proceso->cambios.voluntarios, dato);
            break;
        case 8:
            strcpy(my_proceso->cambios.no_voluntarios, dato);
        default:
            break;
    }
}

void agregar_info_de_proceso_en_reporte(FILE *fptr, proceso my_proceso)
{
    fprintf(fptr, "\n");
    fprintf(fptr, "Pid:%s\n", my_proceso.pid);
    fprintf(fptr, "Nombre del proceso:%s\n", my_proceso.nombre);
    fprintf(fptr, "Estado:%s\n", my_proceso.estado);
    fprintf(fptr, "Tamaño total de la imagen de memoria:%s\n", my_proceso.memoria_total);
    fprintf(fptr, "Tamaño de la memoria TEXT:%s\n", my_proceso.memoria_text);
    fprintf(fptr, "Tamaño de la memoria DATA:%s\n", my_proceso.memoria_data);
    fprintf(fptr, "Tamaños de la memoria STACK%s\n", my_proceso.memoria_stack);
    fprintf(fptr, "Número de cambios de contexto:\n");
    fprintf(fptr, "\tvoluntarios:%s\n", my_proceso.cambios.voluntarios);
    fprintf(fptr, "\tno voluntarios:%s\n", my_proceso.cambios.no_voluntarios);
}

void imprimir_info_de_proceso(proceso my_proceso)
{
    printf("\n");
    printf("Pid:%s\n", my_proceso.pid);
    printf("Nombre del proceso:%s\n", my_proceso.nombre);
    printf("Estado:%s\n", my_proceso.estado);
    printf("Tamaño total de la imagen de memoria:%s\n", my_proceso.memoria_total);
    printf("Tamaño de la memoria TEXT:%s\n", my_proceso.memoria_text);
    printf("Tamaño de la memoria DATA:%s\n", my_proceso.memoria_data);
    printf("Tamaños de la memoria STACK%s\n", my_proceso.memoria_stack);
    printf("Número de cambios de contexto:\n");
    printf("\tvoluntarios:%s\n", my_proceso.cambios.voluntarios);
    printf("\tno voluntarios:%s\n", my_proceso.cambios.no_voluntarios);
}