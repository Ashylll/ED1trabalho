#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

/*
    lista.h
    Módulo responsável pela implementação da lista e operações relacionadas

    A lista é uma forma abstrata de se estruturar dados
    Utiliza encadeamento duplo e permite inserção no início, remoção por índice e ordenação

*/

typedef void* Lista;
typedef void* ITEM;

/// @brief cria uma lista duplamente encadeada
/// @return ponteiro para a lista
Lista cria_lista(void);

/// @brief libera a memória da lista
/// @param l lista  
/// @pre l != NULL
/// @return true se a operação foi bem-sucedida; false caso o contrário
bool libera_lista(Lista *l);

/// @brief insere um elemento no início da lista
/// @param l lista
/// @param i item a ser inserido
/// @pre l != NULL && i != NULL
/// @return true se a operação foi bem-sucedida; false caso o contrário
bool insere_lista(Lista l, ITEM item);

/// @brief remove um elemento da lista por índice e retorna o item guardado
/// @param l lista
/// @param i índice do elemento a ser removido
/// @pre l != NULL
/// @return item removido; NULL se não foi encontrado
ITEM remove_indice_lista(Lista l,  int i);

/// @brief remove um elemento da lista a partir do item a ser retirado
/// @param l lista
/// @param item ponteiro para o item que deve ser retirado
/// @pre l != NULL && item != NULL
void remove_lista(Lista l, ITEM item);

/// @brief checa se a lista está vazia
/// @param l lista
/// @pre l != NULL
/// @return true se estiver vazia; false se não
bool vazia_lista(Lista l);

/// @brief checa o número de elementos contidos na lista    
/// @param l lista
/// @pre l != NULL
/// @return número de elementos na lista
int tamanho_lista(Lista l);

/// @brief busca o item de indice i na lista
/// @param l lista
/// @param i índice
/// @pre l != NULL && i >= 0 && i <= maior índice da lista (tamanho)
/// @return item; NULL se índice fora de limite
ITEM get_item_lista(Lista l, int i);

/// @brief ordena a lista de acordo com uma função de comparação genérica
/// @param l lista
/// @param cmp função genérica de comparação
/// @pre l != NULL && cmp != NULL
void ordena_lista(Lista l, int (*cmp)(void*, void*));

#endif