#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

/*
	fila.h
	Módulo responsável pela implementação da fila e operações relacionadas

	A fila é uma forma abstrata de se manusear elementos de mesmo tipo, seguindo a lógica convencional de uma fila.
	First In, First Out (FIFO): os elementos são inseridos no fim da fila e retirados em seu início.

*/

typedef void* Fila;
typedef void* ITEM;

/// @brief cria uma fila vazia
/// @param tamanho_fila tamanho máximo da fila
/// @pre tamanho_fila deve ser inteiro positivo
/// @return retorna ponteiro para a fila || NULL se der erro
Fila cria_fila(int tamanho_fila);

/// @brief insere um item ao fim da fila
/// @param f fila
/// @param i item a ser inserido
/// @pre f != NULL && i != NULL. Fila não deve estar cheia
/// @return FALSE se a operação falhou, TRUE se foi bem sucedida
bool insere_fila(Fila f, ITEM i);

/// @brief remove o elemento no início fila
/// @param f fila
/// @param fora ponteiro que recebe o item removido
/// @pre f != NULL. Fila não deve estar vazia
/// @return FALSE se a operação falhou, TRUE se foi bem sucedida
bool remove_fila(Fila f, ITEM *fora);

/// @brief checa se a fila está vazia
/// @param f fila
/// @pre f != NULL
/// @return TRUE se vazia, FALSE se não
bool vazia_fila(Fila f);

/// @brief checa o tanho da fila
/// @param f fila   
/// @pre f != NULL
/// @return tamanho da fila
int tamanho_fila(Fila f);

/// @brief libera a memória apenas da fila. Não libera os elementos contidos
/// @param f ponteiro para a fila
/// @pre f != NULL
/// @return FALSE se a operação falhou, TRUE se foi bem sucedida
bool libera_fila(Fila *f);

/// @brief retorna o elemento no início ou no fim da fila
/// @param f fila
/// @param i_f 'i' para retornar o início; 'f' para o fim
/// @return 
ITEM ver_fila(Fila f, char i_f);

/// @brief faz uma cópia da fila
/// @param f fila original
/// @pre f != NULL
/// @return cópia da fila
Fila copia_fila(Fila f);

#endif

