#ifndef FORMA_H
#define FORMA_H

#include <stdbool.h>

/*
    forma.h
    Módulo responsável por conciliar e unificar operações sobre as formas do projeto (wrapper)
    
    Convenção de tipos:
      'c' = círculo
      'r' = retângulo
      't' = texto
      'l' = linha

*/

typedef void* FORMA;

/// @brief cria uma forma
/// @param tipo tipo da forma (círculo, retângulo, texto, linha)
/// @param handle handle para a forma (ponteiro para a forma)
/// @return ponteiro para a forma
FORMA cria_forma(char tipo, void* handle);

/// @brief libera a forma
/// @param f ponteiro para handle FORMA
void libera_forma(FORMA *f);

/* === Operações get === */

/// @brief retorna o identificador da forma
/// @param f forma
/// @pre f != NULL
/// @return identificador
int getId_forma(FORMA f);

/// @brief retorna o tipo da forma
/// @param f forma
/// @pre f != NULL
/// @return caractere para o tipo ('c', 'r', 't', 'l')
char getTipo_forma(FORMA f);

/// @brief retorna o handle da forma
/// @param f forma
/// @return handle
void* getHandle_forma(FORMA f);

/* ===================== */


/* === Operações set === */

/// @brief lê as coordenadas (x,y) da forma
/// @param f forma
/// @param x ponteira para saída da coordenada x
/// @param y ponteira para saída da coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool getXY_forma(FORMA f, double* x, double* y);

/// @brief atribui coordenadas (x,y) da forma
/// @param f forma
/// @param x coordenada x
/// @param y coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool setXY_forma(FORMA f, double x, double y);

/// @brief desloca a forma nas coordenadas (x,y)
/// @param f forma
/// @param dx deslocamento no eixo x
/// @param dy deslocamento no eixo y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool desloca_forma(FORMA f, double dx, double dy);


#endif