#include "lista.h"
#include <stdlib.h>

typedef struct elemento{
    void* chave;
    struct elemento *ant;
    struct elemento *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct lista{
    PONT inicio;
} stLista;

LISTA cria_lista(void){
    stLista* lista = malloc(sizeof(stLista));
    if (!lista) return NULL;

    lista->inicio = NULL;

    return lista;
}

bool libera_lista(LISTA *l){
    if (!l || !*l) return false;
    stLista* lista = (stLista*)*l;

    PONT atual = lista->inicio;
    PONT aux;
    while (atual != NULL){
        aux = atual->prox;
        free(atual);
        atual = aux;
    }

    free(lista);
    *l = NULL;

    return true;
}

bool insere_lista(LISTA l, void* chave){
    if (!l) return false;
    stLista* lista = (stLista*)l;

    PONT novo = malloc(sizeof(ELEMENTO));
    if (!novo) return false;

    novo->chave = chave;
    novo->prox = lista->inicio;
    novo->ant = NULL;

    if (lista->inicio != NULL){
        lista->inicio->ant = novo;
    }

    lista->inicio = novo;

    return true;
}

ITEM remove_lista(LISTA l, void* busca, int (*cmp)(void*, void*)){
    if (!l) return false;
    stLista* lista = (stLista*)l;
    PONT atual = lista->inicio;

    while (atual != NULL){
        if (cmp(atual->chave, busca) == 0){
            
            if(atual->ant != NULL){
                atual->ant->prox = atual->prox;
            } else {
                lista->inicio = atual->prox;
            }

            if (atual->prox != NULL){
                atual->prox->ant = atual->ant;
            }

            return (ITEM)atual; 
        }
        atual = (PONT)atual->prox;
    }

    return NULL;
}

bool vazia_lista(LISTA l){
    stLista *lista = (stLista*)l;

    return (lista->inicio == NULL);
}

int tamanho_lista(LISTA l){
    if (!l) return -1;
    stLista *lista = (stLista*)l;

    PONT atual = lista->inicio;
    int tamanho = 0;
    while(atual != NULL){
        atual = (PONT)atual->prox;
        tamanho++;
    }

    return tamanho;
}