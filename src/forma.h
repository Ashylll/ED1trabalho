#ifndef FORMA_H
#define FORMA_H

#include <stdbool.h>
#include <stdio.h>

/*
    forma.h
    Forma é um contâiner (wrapper) que carrega um ponteiro para uma figura e o seu tipo.

*/

typedef void* Forma;

/// @brief cria uma forma
/// @param tipo tipo da forma (círculo, retângulo, texto, linha)
/// @param handle handle para a forma (ponteiro para a forma)
/// @return ponteiro para a forma
Forma cria_forma(char tipo, void* handle);

/// @brief libera a forma
/// @param f ponteiro para handle Forma
void libera_forma(Forma *f);

/* === Operações get === */

/// @brief retorna o identificador da forma
/// @param f forma
/// @pre f != NULL
/// @return identificador
int get_id_forma(Forma f);

/// @brief retorna o tipo da forma
/// @param f forma
/// @pre f != NULL
/// @return caractere para o tipo ('c', 'r', 't', 'l')
char get_tipo_forma(Forma f);

/// @brief retorna o handle da forma
/// @param f forma
/// @return handle
void* get_handle_forma(Forma f);

/* ===================== */


/* === Operações set === */

/// @brief lê as coordenadas (x,y) da âncora da forma
/// @param f forma
/// @param x ponteiro para saída da coordenada x
/// @param y ponteiro para saída da coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool get_ancora_forma(Forma f, double* x, double* y);

/// @brief atribui coordenadas (x,y) da forma
/// @param f forma
/// @param x coordenada x
/// @param y coordenada y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool set_ancora_forma(Forma f, double x, double y);

/// @brief atribui uma cor de borda à forma (atribui cor se for tipo linha)
/// @param f forma
/// @param corb cor de borda
/// @pre f != NULL && corp != NULL
void set_corb_forma(Forma f, char* corb);

/// @brief atribui uma cor de preenchimento à forma (não muda se for tipo linha)
/// @param f forma
/// @param corp cor de preenchimento
/// @pre f != NULL && corp != NULL
void set_corp_forma(Forma f, char* corp);

/// @brief desloca a forma nas coordenadas (x,y)
/// @param f forma
/// @param dx deslocamento no eixo x
/// @param dy deslocamento no eixo y
/// @return true se a operação foi bem sucedida; false se f == NULL
bool desloca_forma(Forma f, double dx, double dy);

/// @brief escreve em um arquivo .txt os dados da forma
/// @param f forma
/// @param arquivoTxt arquivo .txt aberto em modo de escrita 
void reporta_forma(Forma f, FILE *arquivoTxt);

/// @brief checa se há sobreposição entre uma forma e um retângulo
/// @param r retângulo
/// @param b forma (círculo, retângulo, linha, texto)
/// @return true se há sobreposição; false se não 
bool sobrepoe_retangulo(Forma r, Forma b);

#endif