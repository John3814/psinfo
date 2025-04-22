# Configuración
CC = gcc
CFLAGS = -Wall -Iinclude

# Archivos fuente y objetos
SRCS = gestion_de_archivos.c proceso.c psinfo.c
OBJS = $(SRCS:.c=.o )

# Nombre del ejecutable
TARGET = psinfo

# Directorio de instalacion
INSTALL_DIR = /usr/local/bin


# Reglas

# Regla por defecto
all: $(TARGET)

# Cómo construir el ejecutable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# Cómo compilar cada archivo .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Instalar psinfo en el path
install: $(TARGET)
	sudo cp $(TARGET) $(INSTALL_DIR)
	@echo "Instalado en $(INSTALL_DIR)/$(TARGET)"

uninstall:
	sudo rm -f $(INSTALL_DIR)/$(TARGET)
	@echo "Eliminado de $(INSTALL_DIR)/$(TARGET)"

# Limpieza de archivos compilados 
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all install uninstall  clean