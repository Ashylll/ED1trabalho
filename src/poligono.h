#ifndef POLIGONO_H
#define POLIGONO_H

/*
    poligono.h
    Módulo responsável pela implementação do polígono e operações relaciondas

    -   O polígono é um conjunto de vértices ligados por segmentos de reta;
    -   Possui identificador inteiro positivo [1, 10];
    -   Possui segmentos paralelos em seu interior, representando uma rachura;
    -   Possui coloração para a borda e a rachura.

        Convenções:
   -    Sistema de coordenadas no domínio dos números reais com (0,0) no canto superior esquerdo;
   -    x cresce para a direita; y cresce para baixo;

*/

typedef void* POLIGONO;
typedef void* VERTICE;

POLIGONO cria_poligono();

void libera_poligono(POLIGONO p);

VERTICE cria_vertice(double x, double y);

bool insere_vertice(POLIGONO p, VERTICE v);

/// @brief remove o último vértice inserido no polígono e libera sua memória
/// @param p polígono
/// @param fora ponteiro que recebe o vértice removido
void remove_vertice(POLIGONO p, VERTICE *fora);



#endif