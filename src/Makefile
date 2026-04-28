PROJ_NAME= ted
ALUNO= Ashley
LIBS= -lm
OBJETOS= main.o circulo.o retangulo.o linha.o texto.o poligono.o forma.o fila.o lista.o leitura.o

CC=gcc
CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -I. -I./unity -DUNITY_INCLUDE_DOUBLE
LDFLAGS= -O0

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

circulo.o: circulo.c circulo.h
retangulo.o: retangulo.c retangulo.h
linha.o: linha.c linha.h
texto.o: texto.c texto.h
poligono.o: poligono.c poligono.h fila.h
forma.o: forma.c circulo.h retangulo.h linha.h texto.h

fila.o: fila.c fila.h
lista.o: lista.c lista.h

leitura.o: leitura.c leitura.h circulo.h retangulo.h linha.h  texto.h forma.h poligono.h fila.h lista.h

.PHONY: clean run memcheck testes run_testes

clean:
	rm -rf *.o $(PROJ_NAME) $(TESTES)

run: $(PROJ_NAME)
	./$(PROJ_NAME)

memcheck: $(PROJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROJ_NAME)


# Makefile somente para arquivos de teste
teste_circulo: circulo.o unity.o t_circulo.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_retangulo: retangulo.o unity.o t_retangulo.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_linha: linha.o unity.o t_linha.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_texto: texto.o unity.o t_texto.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_forma: forma.o circulo.o retangulo.o linha.o texto.o unity.o t_forma.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_lista: lista.o unity.o t_lista.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

teste_fila: fila.o unity.o t_fila.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS) 

teste_poligono: poligono.o linha.o fila.o unity.o t_poligono.o
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

TESTES = teste_circulo teste_retangulo teste_linha teste_texto teste_forma teste_fila teste_poligono

testes: $(TESTES)

realiza_testes: testes
	@echo "Realizando testes..."
	@./teste_circulo
	@./teste_retangulo
	@./teste_linha
	@./teste_texto
	@./teste_fila
	@./teste_poligono
	@echo "Testes completos"