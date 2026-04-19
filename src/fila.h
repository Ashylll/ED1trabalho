#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

/*
	fila.h
	Módulo responsável pela implementação da fila e operações relacionadas

	A fila é uma forma abstrata de se manusear elementos, seguindo a lógica convencional de uma fila.
	First In, First Out (FIFO): os elementos são inseridos no fim da fila e retirados em seu início.

	Tamanho máximo de elementos: 10
*/

typedef void* FILA;
typedef void* ITEM;

/// @brief cria uma fila vazia
/// @param tamanho_fila tamanho máximo da fila
/// @pre tamanho_fila deve ser inteiro positivo
/// @return retorna ponteiro para a fila || NULL se der erro
FILA cria_fila(int tamanho_fila);

/// @brief insere um item à fila
/// @param f fila
/// @param i item a ser inserido
/// @pre f != NULL && i != NULL && TAMANHO_FILA <= 10
/// @return FALSE se a operação falhou, TRUE se foi bem sucedida
bool insere_fila(FILA f, ITEM i);

/// @brief remove um elemento da fila
/// @param f fila
/// @param fora ponteiro que recebe o item removido
/// @pre f != NULL. Fila não deve estar vazia
/// @return FALSE se a operação falhou, TRUE se foi bem sucedida
bool remove_fila(FILA f, ITEM *fora);

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

/// @brief libera a memória apenas da fila. Não libera os elementos contidos
/// @param f ponteiro para a fila
/// @pre f != NULL
/// @return FALSE se a operação falhou, TRUE se foi bem sucedida
bool libera_fila(FILA *f);

/// @brief retorna o elemento no início ou no fim da fila
/// @param f fila
/// @param i_f 'i' para retornar o início; 'f' para o fim
/// @return 
ITEM ver_fila(FILA f, char i_f);

/// @brief faz uma cópia da fila
/// @param f fila original
/// @pre f != NULL
/// @return cópia da fila
FILA copia_fila(FILA f);

#endif

