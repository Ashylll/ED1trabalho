#ifndef FORMA_H
#define FORMA_H

#include <stdbool.h>
#include <stdio.h>

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

/// @brief lê as coordenadas (x,y) da âncora da forma
/// @param f forma
/// @param x ponteiro para saída da coordenada x
/// @param y ponteiro para saída da coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool getAncora_forma(FORMA f, double* x, double* y);

/// @brief atribui coordenadas (x,y) da forma
/// @param f forma
/// @param x coordenada x
/// @param y coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool setAncora_forma(FORMA f, double x, double y);

/// @brief desloca a forma nas coordenadas (x,y)
/// @param f forma
/// @param dx deslocamento no eixo x
/// @param dy deslocamento no eixo y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool desloca_forma(FORMA f, double dx, double dy);

/// @brief escreve em um arquivo .txt os dados da forma
/// @param f forma
/// @param arquivoTxt arquivo .txt aberto em modo de escrita 
void reporta_forma(FORMA f, FILE *arquivoTxt);

/// @brief checa se há sobreposição entre uma forma e um retângulo
/// @param r retângulo
/// @param b forma (círculo, retângulo, linha, texto)
/// @return true se há sobreposição; false se não 
bool sobrepoe_retangulo(FORMA r, FORMA b);

#endif