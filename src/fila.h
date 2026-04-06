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

/// @brief insere um item a uma fila
/// @param f fila
/// @param i item a ser inserido
/// @pre f != NULL && i != NULL
void insere_fila(FILA f, ITEM i);

/// @brief remove um elemento da fila
/// @param f fila
/// @param fora ponteiro que recebe o item removido
/// @pre f != NULL. Fila não deve estar vazia
void remove_fila(FILA f, ITEM *fora);

/// @pre fila não deve ser nula
/// @brief checa se a fila está vazia
/// @param f fila
/// @pre f != NULL
/// @return TRUE se vazia, FALSE se não
bool vazia_fila(FILA f);

/// @brief checa o tanho da fila
/// @param f fila   
/// @pre f != NULL
/// @return tamanho da fila
int tamanho_fila(FILA f);

/// @pre fila não deve ser nula
/// @brief libera a memória da fila
/// @param f ponteiro para a fila
/// @pre f != NULL
void libera_fila(FILA *f);


#endif

