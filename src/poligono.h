#ifndef POLIGONO_H
#define POLIGONO_H

/*
    poligono.h
    Módulo responsável pela implementação do polígono e operações relaciondas

    -   O polígono é um conjunto de vértices ordenados ligados por segmentos de reta;
    -   Possui identificador inteiro positivo [1, 10];
    -   Possui segmentos paralelos em seu interior, representando uma rachura;
    -   Possui coloração para a borda e a rachura.

        Convenções:
   -    Sistema de coordenadas no domínio dos números reais com (0,0) no canto superior esquerdo;
   -    x cresce para a direita; y cresce para baixo;

*/

typedef void* POLIGONO;
typedef void* VERTICE;
typedef void* FILA;
typedef void* SEGMENTO;

/// @brief cria um polígono
/// @return ponteiro para o polígono
POLIGONO cria_poligono(void);

/// @brief libera a memória do polígono
/// @param p ponteiro para handle do polígono
void libera_poligono(POLIGONO *p);

/// @brief retorna o número de vértices do polígono
/// @param p polígono
/// @return número de vértices (inteiro)
int tamanho_poligono(POLIGONO p);

/// @brief cria um vértice (ponto no plano)
/// @param x coordenada x
/// @param y coordenada y
/// @pre x e y devem ser número reais
/// @return ponteiro para o vértice
VERTICE cria_vertice(double x, double y);

/// @brief libera a memória do vértice
/// @param v ponteiro para handle do vértice
void libera_vertice(VERTICE *v);

/// @brief insere um vértice ao polígono
/// @param p pónteiro para o polígono
/// @param v ponteiro para o vértice
/// @pre p != NULL && v != NULL
void insere_vertice(POLIGONO p, VERTICE v);

/// @brief remove o último vértice inserido no polígono e libera sua memória
/// @param p polígono
/// @param fora ponteiro que recebe o vértice removido
/// @pre p != NULL
void remove_vertice(POLIGONO p, VERTICE *fora);

/// @brief cria um segmento (de borda ou de rachura)
/// @param id identificador do segmento
/// @param v1 vértice 1
/// @param v2 vértice 2
/// @param cor cor do segmento
/// @pre v1 != NULL && v2 != NULL && cor != NULL
/// @return ponteiro para o segmento
SEGMENTO cria_segmento(int id, VERTICE v1, VERTICE v2, char* cor);

/// @brief libera a memória do segmento
/// @param s ponteiro para handle do polígono
void libera_segmento(SEGMENTO *s);

#endif