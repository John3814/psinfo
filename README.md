# psinfo – Comando personalizado en C para Ubuntu  

---
## Descripción General

**psinfo** es un nuevo comando creado para sistemas Ubuntu, escrito en el lenguaje C. Este comando permite al usuario obtener información detallada sobre uno o varios procesos del sistema. Puede mostrar la información en pantalla o guardarla en un archivo de reporte.

### Información que muestra:
- **Nombre del proceso (`Name`)**
- **Estado del proceso (`State`)**
- **Tamaño total de la imagen de memoria**
- **Tamaño de la sección TEXT (`VmExe`)**
- **Tamaño de la sección DATA (`VmData`)**
- **Tamaño de la sección STACK (`VmStk`)**
- **Cambios de contexto realizados:**
  - Voluntarios (`voluntary_ctxt_switches`)
  - No voluntarios (`nonvoluntary_ctxt_switches`)


En este caso la información se toma del archivo status que se encuentra en el directorio de cada proceso presente en la carpeta `/proc` de Ubuntu es decir en la dirección `/proc/<pid>/status`.

---

## Sintaxis del Comando

```bash
$ psinfo [-l|-r] <listado de PIDs>
```

O si no está instalado en el PATH:

```bash
$ ./psinfo [-l|-r] <listado de PIDs>
```

### Opciones:
- `-l`: Muestra la información en pantalla.
- `-r`: Genera un archivo de reporte con la información y muestra la ruta del archivo generado.


### Manejo de errores:
- Si el comando se usa incorrectamente o con una opción inválida, muestra un mensaje de error con la sintaxis correcta.
- Si uno de los PIDs no existe, se informa del error y se continúa con los demás.
- En el modo `-r`, también se registra el error en el archivo generado.


---

## Makefile

### Comandos disponibles:
- `make`: Compila y genera el ejecutable local (`./psinfo`).
- `make install`: Instala el ejecutable en `/usr/local/bin/psinfo`.
- `make clean`: Elimina los archivos `.o` y el ejecutable.
- `make uninstall`: Elimina el ejecutable del sistema (`/usr/local/bin/psinfo`).
