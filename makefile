# 1. Detecção do Sistema Operacional
ifeq ($(OS),Windows_NT)
    # Configurações para Windows
    RM = del /q
    CP = copy
    TARGET = buscaTesouro.exe
    # No Windows, o executável precisa do .exe
    FIXPATH = $(subst /,\,$1)
else
    # Configurações para Linux/Mac
    RM = rm -f
    CP = cp
    TARGET = buscaTesouro
    FIXPATH = $1
endif

# 2. Variáveis de Compilação
CC = gcc
CFLAGS = -Wall -g
SRC = main.c

# 3. Regras
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	chmod +x $(TARGET)

# A regra clean agora usa a variável RM correta para cada sistema
clean:
	$(RM) $(TARGET)

run: all
	./$(TARGET)
