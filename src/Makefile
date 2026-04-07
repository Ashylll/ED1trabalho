PROJ_NAME=testes_fila
ALUNO=Ashley
LIBS=
OBJETOS=fila.o t_fila.o unity.o

CC=gcc
CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -I. -I./unity -DUNITY_INCLUDE_DOUBLE
LDFLAGS=-O0

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

unity.o: unity/unity.c unity/unity.h
	$(CC) -c $(CFLAGS) unity/unity.c -o unity.o

fila.o: fila.c fila.h
	$(CC) -c $(CFLAGS) fila.c -o fila.o

t_fila.o: t_fila.c fila.h unity/unity.h
	$(CC) -c $(CFLAGS) t_fila.c -o t_fila.o

clean:
	rm -rf *.o $(PROJ_NAME)