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
typedef void* SEGMENTO;
typedef void* FILA;
typedef void* LISTA;

/// @brief cria um polígono
/// @param id identificador
/// @pre id deve pertencer ao intervalo de inteiros [1, 10]
/// @return ponteiro para o polígono; NULL se falha na criação ou id inválido
POLIGONO cria_poligono(int id);

/// @brief libera a memória do polígono
/// @pre p != NULL
/// @param p ponteiro para handle do polígono
void libera_poligono(POLIGONO *p);

/// @brief retorna o número de vértices do polígono
/// @param p polígono
/// @pre p != NULL
/// @return número de vértices (inteiro)
int tamanho_poligono(POLIGONO p);

/// @brief retorna o id do polígono
/// @param p polígono
/// @pre p != NULL
/// @return identificador
int getId_poligono(POLIGONO p);

/// @brief busca polígono por id em uma fila
/// @param f fila
/// @param id identificador 
/// @pre f != NULL && id pertencer ao intervalo de inteiros [1, 10]
/// @return polígono, se encontrou; NULL se não encontrou
POLIGONO getPoligono(FILA f, int id);

/// @brief retorna a fila de vértices do polígono
/// @param p polígono
/// @pre p != NULL
/// @return fila de vértices
FILA getVertices_poligono(POLIGONO p);

/// @brief retorna a fila de lados do polígono
/// @param p polígono
/// @pre p != NULL
/// @return fila de lados 
FILA getLados_poligono(POLIGONO p);

/// @brief retorna a fila de hachura do polígono
/// @param p polígono
/// @pre p != NULL
/// @return fila de hachura
FILA getHachura_poligono(POLIGONO p);


/// @brief cria um vértice (ponto no plano)
/// @param x coordenada x
/// @param y coordenada y
/// @pre x e y devem ser número reais
/// @return ponteiro para o vértice
VERTICE cria_vertice(double x, double y);

/// @brief libera a memória do vértice
/// @pre v != NULL
/// @param v ponteiro para handle do vértice
void libera_vertice(VERTICE *v);

/// @brief insere um vértice ao polígono
/// @param p pónteiro para o polígono
/// @param v ponteiro para o vértice
/// @pre p != NULL && v != NULL
void insere_vertice(POLIGONO p, VERTICE v);

/// @brief remove o vértice mais antigo inserido no polígono e libera sua memória
/// @param p polígono
/// @param x ponteiro para receber a coordenda x do vértice removido
/// @param y ponteiro para receber a coordenada y do vértice removido 
/// @pre p != NULL
void remove_vertice(POLIGONO p, double *x, double *y);

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

/// @brief cria os segmentos dos lados do polígono sequencialmente a partir de um id
/// @param p polígono
/// @param id identificador do primeiro segmento
/// @param corb cor dos segmentos dos lados
/// @param formas bando de dados de formas para receber os novos segmentos
/// @details o valor real de id é incrementado de um em um a cada criação de segmento, terminando com o valor do último id + 1
/// @pre p != NULL && corb != NULL
void desenha_poligono(POLIGONO p, int *id, char *corb, LISTA formas);

/// @brief cria os segmentos da hachura do polígono sequencialmente a partir de um id
/// @param p polígono
/// @param id identificador do primeiro segmento 
/// @param d distância entre os segmentos da hachura
/// @param corp cor dos segmentos da hachura
/// @param formas bando de dados de formas para receber os novos segmentos
/// @details o valor real de id é incrementado de um em um a cada criação de segmento, terminando com o valor do último id + 1
/// @pre p != NULL && d > 0 && corp != NULL
void hachura_poligono(POLIGONO p, int *id, double d, char* corp, LISTA formas); 

#endif