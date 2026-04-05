#ifndef TEXTO_H
#define TEXTO_H

#include <stdbool.h>

/*
    texto.h
    Módulo responsável pela criação e gerenciamento de textos

*/

typedef void* TEXTO;

/// @brief cria um texto com identificador, coordenadas, cores de borda e de preenchimento e estilo padrão (family: sans-serif | weight: normal | size: 20)
/// @param id identificador
/// @param x coordenada x
/// @param y coordenada y
/// @param corb cor da borda (string)
/// @param corp cor de preenchimento (string)
/// @param a posição da âncora no texto: i(início), m(meio), f(fim)
/// @param txto conteúdo do texto a ser criado
/// @pre corb != NULL && corp != NULL && txt != NULL && (a == 'i' || a == 'm' || a == 'f')
/// @return ponteiro para o texto; NULL se parâmetros inválidos ou falha de memória
TEXTO cria_texto(int id, double x, double y, const char* corb, const char* corp, char a, const char* txto);

/// @brief libera a memória do texto 
/// @param t ponteiro para o handle do texto
void libera_texto(TEXTO *t);

/* === Operações get === */ 

/// @brief retorna o identificador do texto
/// @param t texto
/// @pre t != NULL
/// @return identificador
int getId_texto(TEXTO t);

/// @brief retorna a coordenada x do texto
/// @param t texto
/// @pre t != NULL
/// @return coordenada x
double getX_texto(TEXTO t);

/// @brief retorna a coordenada y do texto
/// @param t texto
/// @pre t != NULL
/// @return coordenada y
double getY_texto(TEXTO t);

/// @brief retorna a cor da borda do texto
/// @param t texto
/// @pre t != NULL
/// @return ponteiro para string com a cor da borda (apenas leitura)
const char* getCORB_texto(TEXTO t);

/// @brief retorna a cor de preenchimento do texto
/// @param t texto
/// @pre t != NULL
/// @return ponteiro para string com a cor de preenchimento (apenas leitura)
const char* getCORP_texto(TEXTO t);

/// @brief retorna a posição da âncora do texto
/// @param t texto
/// @pre t != NULL
/// @return posição da âncora (char i, m, f)
char getA_texto(TEXTO t);

/// @brief retorna o conteúdo do texto
/// @param t texto
/// @pre t != NULL
/// @return ponteiro para string com txto (apenas leitura)
const char* getTXTO_texto(TEXTO t);

/* ===================== */

/* === Operações set === */

/// @brief atribui um identificador ao texto
/// @param t texto
/// @param id identificador
/// @pre t != NULL
/// @return true se a operação foi bem sucedida; false se t == NULL
bool setId_texto(TEXTO t, int id);

/// @brief atribui uma coordenada x ao texto
/// @param t texto
/// @param x coordenada x
/// @pre t != NULL
/// @return true se a operação foi bem sucedida; false se t == NULL
bool setX_texto(TEXTO t, double x);

/// @brief atribui uma coordenada y ao texto
/// @param t texto
/// @param y coordenada y
/// @pre t != NULL
/// @return true se a operação foi bem sucedida; false se t == NULL
bool setY_texto(TEXTO t, double y);

/// @brief atribui uma cor de borda ao texto
/// @param t texto
/// @param corb cor de borda
/// @pre t != NULL && corb != NULL
/// @return true se a operação foi bem sucedida; false se t == NULL || corb == NULL
bool setCORB_texto(TEXTO t, const char* corb);

/// @brief atribui uma cor de preenchimento ao texto
/// @param t texto
/// @param corp cor de preenchimento
/// @pre t != NULL && corp != NULL
/// @return true se a operação foi bem sucedida; false se t == NULL || corp == NULL
bool setCORP_texto(TEXTO t, const char* corp);

/// @brief atribui uma posição à âncora do texto
/// @param t texto
/// @param a âncora do texto
/// @pre t != NULL && (a == 'i' || a == 'm' || a == 'f')
/// @return true se a operação foi bem sucedida; false se t == NULL || a inválido
bool setA_texto(TEXTO t, char a);

/// @brief atribui um conteúdo ao texto
/// @param t texto
/// @param txto conteúdo do texto (string)
/// @pre t != NULL && txto != NULL
/// @return true se a operação foi bem sucedida; false se t == NULL || txto == NULL
bool setTXTO_texto(TEXTO t, const char* txto);

/* ===================== */


/* === Operações relacionadas ao estilo do texto === */

/// @brief muda o estilo de um texto
/// @param t texto t
/// @param fFamily família do estilo (sans-serif, serif, cursive)
/// @param fWeight expessura do estilo (n: normal, b: bold, b+: bolder, l: lighter)
/// @param fSize tamanho do estilo
/// @pre t != NULL && fFamily != NULL && fWeight != NULL && fSize > 0
/// @return true se a operação foi bem sucedida; false se t == NULL || fFamily == NULL || fWeight == NULL || fSize <= 0
bool mudar_estilo(TEXTO t, const char* fFamily, const char* fWeight, int fSize);

/// @brief obtém a font-family atual
/// @param t texto
/// @pre t != NULL
/// @return família da fonte do texto
const char* getFFamily_texto(TEXTO t);

/// @brief obtém o font-weight atual
/// @param t texto
/// @pre t != NULL
/// @return expessura da fonte do texto
const char* getFWeight_texto(TEXTO t);

/// @brief obtém o font-size atual (px)
/// @param t texto
/// @pre t != NULL
/// @return tamanho da fonte do texto
int getFSize_texto(TEXTO t);

/* ================================================= */

#endif