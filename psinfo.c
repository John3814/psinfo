#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_de_archivos.h"
#include "proceso.h"

FILE *file;
proceso my_proceso;

int main(int argc, char *argv[])
{   
    if (argc == 2) 
    {
        printf("Información recolectada!!!\n");
        file = abriArchivoStatus(argv[1]);
        my_proceso = obtener_info(file);
        imprimir_info_de_proceso(my_proceso);
        fclose(file);
    } else if (argc > 2)
    {
        
        if(strcmp(argv[1], "-l")  == 0)
        {   
            printf("Información recolectada!!!\n");
            for (int i = 2; i < argc; i++)
            {
                file = abriArchivoStatus(argv[i]);
                my_proceso = obtener_info(file);
                imprimir_info_de_proceso(my_proceso);
                fclose(file);
            }
        } 
        else if (strcmp(argv[1], "-r") == 0) {
            char nombre_reporte[100] = "psinfo-report";
            FILE *reporte = crearArchivoReporte(argc, argv, nombre_reporte);
            fprintf(reporte, "Informacion recolectada!!!\n");
            for (int i = 2; i < argc; i++)
            {
                file = abriArchivoStatus(argv[i]);
                my_proceso = obtener_info(file);
                agregar_info_de_proceso_en_reporte(reporte, my_proceso);
                fclose(file);
            }
            printf("Archivo de salida generado: %s\n", nombre_reporte);
            fclose(reporte);
        } else {
            printf("La opcion %s no esta definida!!!\n", argv[1]);
        }   
    }
}