#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Archivos de cabecera propios del proyecto
#include "gestion_de_archivos.h"  // Funciones para manejo de archivos
#include "proceso.h"              // Definición y manipulación de estructuras de procesos

// Variables globales utilizadas en el flujo del programa
FILE *file;
proceso my_proceso;

// Declaración de funciones auxiliares para manejar errores
void manejar_error_de_sintaxis();
void manejar_error_de_apertura_de_archivo(char *pid);

// Función principal
int main(int argc, char *argv[])
{   
    // Caso 1: Solo se proporciona un PID como argumento (sin opciones)
    if (argc == 2) 
    {
        printf("Información recolectada!!!\n");

        // Intenta abrir el archivo /proc/[PID]/status
        file = abri_archivo_status(argv[1]);
        
        if (file == NULL)
        {
            // Error al abrir archivo del proceso
            manejar_error_de_apertura_de_archivo(argv[1]);
        } 
        else 
        {
            // Obtiene los datos del proceso y los imprime por consola
            my_proceso = obtener_info(file);
            imprimir_info_de_proceso(my_proceso);
            fclose(file); // Cierra el archivo abierto
        }
    } 
    // Caso 2: Se proporcionan múltiples argumentos
    else if (argc > 2)
    {
        // Subcaso 2.1: opción "-l" (listar en pantalla)
        if(strcmp(argv[1], "-l") == 0)
        {   
            printf("Información recolectada!!!\n");

            // Recorre la lista de PIDs e imprime sus datos
            for (int i = 2; i < argc; i++)
            {
                file = abri_archivo_status(argv[i]);

                if (file == NULL)
                {
                    manejar_error_de_apertura_de_archivo(argv[i]);
                    continue; // Continúa con el siguiente PID
                }

                my_proceso = obtener_info(file);
                imprimir_info_de_proceso(my_proceso);
                fclose(file);
            }
        } 
        // Subcaso 2.2: opción "-r" (generar archivo de reporte)
        else if (strcmp(argv[1], "-r") == 0) 
        {
            char nombre_reporte[100] = "psinfo-report";

            // Se crea el archivo de salida con nombre dinámico basado en PIDs
            FILE *reporte = crear_archivo_de_reporte(argc, argv, nombre_reporte);
            fprintf(reporte, "Informacion recolectada!!!\n");

            // Recorre cada PID, agrega su info al reporte
            for (int i = 2; i < argc; i++)
            {
                file = abri_archivo_status(argv[i]);

                if (file == NULL)
                {
                    manejar_error_de_apertura_de_archivo(argv[i]);
                    // También se anota el error en el archivo de reporte
                    fprintf(reporte, "\nNo se encontró información para el proceso con PID = %s\n", argv[i]);
                    continue;
                }

                my_proceso = obtener_info(file);
                agregar_info_de_proceso_en_reporte(reporte, my_proceso);
                fclose(file);
            }

            // Mensaje indicando el nombre del archivo generado
            printf("Archivo de salida generado: %s\n", nombre_reporte);
            fclose(reporte);
        } 
        // Subcaso 2.3: opción no válida
        else 
        {
            manejar_error_de_sintaxis();
        }   
    } 
    // Caso 3: No se proporcionan argumentos suficientes
    else 
    {
        manejar_error_de_sintaxis();
    }
}

/*
 * Función: manejar_error_de_sintaxis
 * ----------------------------------
 * Muestra un mensaje indicando que la sintaxis de los argumentos es incorrecta.
 */
void manejar_error_de_sintaxis()
{
    printf("Error de sintaxis!\n");
    printf("\tSintaxis correcta: psinfo [-l|-r] <listado de PIDs>\n");
    printf("\tUse la opción -l para mostrar en pantalla los datos de los procesos en la lista.\n");
    printf("\tUse la opción -r para generar un archivo de salida con los datos de los procesos en la lista.\n");
}

/*
 * Función: manejar_error_de_apertura_de_archivo
 * ---------------------------------------------
 * Informa que no se pudo acceder al archivo /proc/[PID]/status correspondiente.
 *
 * pid: PID del proceso que falló.
 */
void manejar_error_de_apertura_de_archivo(char *pid)
{
    printf("\nError en PID: %s\n", pid);
    printf("\tNo se encontró información para el proceso con PID = %s\n", pid);
    printf("\tEs posible que el proceso %s no exista o ya terminó\n", pid);
    printf("\n");
}
