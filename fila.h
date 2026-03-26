

#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

/*
	Módulo responsável pela implementação da fila e operações relacionadas

*/

typedef void* FILA;
typedef void* ITEM;

/// @brief cria uma fila vazia
/// @return retorna ponteiro para a fila || NULL se der erro
FILA cria_fila(void);

/// @pre fila e item não devem ser nulos
/// @brief insere um item a uma fila
/// @param f fila
/// @param i item a ser inserido
void insere_fila(FILA f, ITEM i);

/// @pre fila não deve ser nula 
/// @brief remove um elemento da fila
/// @paral f fila
/// @return retorna o item removido
ITEM remove_fila(FILA f);

/// @pre fila não deve ser nula
/// @brief checa se a fila está vazia
/// @param f fila
/// @return TRUE se vazia, FALSE se não
bool vazia_fila(FILA f);

/// @brief checa o tanho da fila
/// @param f fila   
/// @return tamanho da fila
int tamanho_fila(FILA f);

/// @pre fila não deve ser nula
/// @brief libera a memória de uma fila
/// @param f fila
void libera_fila(FILA f);



#endif

