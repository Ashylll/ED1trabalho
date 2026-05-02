#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

/*
    lista.h
    Módulo responsável pela mplementação a lista e operações relacionadas

    A lista 
*/

typedef void* LISTA;
typedef void* ITEM;

/// @brief cria uma lista duplamente encadeada
/// @return ponteiro para a lista
LISTA cria_lista(void);

/// @brief libera a memória da lista
/// @param l lista  
/// @pre l != NULL
/// @return true se a operação foi bem-sucedida; false caso o contrário
bool libera_lista(LISTA *l);

/// @brief insere um elemento no início da lista
/// @param l lista
/// @pre l != NULL && i != NULL
/// @param i item a ser inserido
/// @return true se a operação foi bem-sucedida; false caso o contrário
bool insere_lista(LISTA l, ITEM item);

/// @brief remove um elemento da lista por índice e retorna o item guardado
/// @param l lista
/// @param i índice do elemento a ser removido
/// @pre l != NULL
/// @return item removido; NULL se não foi encontrado
ITEM remove_lista(LISTA l,  int i);

/// @brief checa se a lista está vazia
/// @param l lista
/// @pre l != NULL
/// @return true se estiver vazia; false se não
bool vazia_lista(LISTA l);

/// @brief checa o número de elementos contidos na lista    
/// @param l lista
/// @pre l != NULL
/// @return número de elementos na lista
int tamanho_lista(LISTA l);

/// @brief busca o item de indice i na lista
/// @param l lista
/// @param i índice
/// @pre l != NULL && i >= 0 && i <= maior índice da lista (tamanho)
/// @return item
ITEM getItem_lista(LISTA l, int i);

/// @brief ordena a lista de acordo com uma função de comparação genérica
/// @param l lista
/// @param cmp função genérica de comparação
void ordena_lista(LISTA l, int (*cmp)(void*, void*));

#endif