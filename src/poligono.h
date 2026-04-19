#ifndef POLIGONO_H
#define POLIGONO_H

/*
    poligono.h
    Módulo responsável pela implementação do polígono e operações relaciondas

    -   O polígono é um conjunto de vértices ordenados ligados por segmentos de reta;
    -   Possui identificador inteiro positivo [1, 10];
    -   Possui segmentos paralelos em seu interior, representando uma hachura;
    -   Possui coloração para a borda e a hachura.

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

/// @brief retorna o id do polígono
/// @param p polígono
/// @return id
int getId_poligono(POLIGONO p);

/// @brief busca polígono por id em uma fila
/// @param f fila
/// @param id identificador 
/// @return polígono, se encontrou; NULL se não encontrou
POLIGONO getPoligono(FILA f, int id);

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
/// @pre p != NULL
void remove_vertice(POLIGONO p);

/// @brief retorna a coordenada x do vértice
/// @param v vértice
/// @pre v != NULL
/// @return coordenada x
double getX_vertice (VERTICE v);

/// @brief retorna a coordenada y do vértice
/// @param v vértice
/// @pre v != NULL
/// @return coordenada y
double getY_vertice (VERTICE v);

/// @brief cria os segmentos dos lados do polígono
/// @param p polígono
/// @pre p != NULL
void desenha_poligono(POLIGONO p);

/// @brief cria os segmentos da hachura do polígono
/// @param p polígono
/// @param d distância entre os segmentos da hachura
/// @pre p != NULL
void hachura_poligono(POLIGONO p, double d); 

#endif