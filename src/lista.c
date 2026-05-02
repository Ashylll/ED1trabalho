#include "lista.h"
#include <stdlib.h>

typedef struct elemento{
    void* chave;
    struct elemento *ant;
    struct elemento *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct stLista{
    PONT inicio;
    PONT fim;
    int tamanho;
} stLista;

static PONT getElemento_lista(LISTA l, int i){
    if (!l) return NULL;
    stLista *lista = (stLista*)l;

    PONT atual = lista->inicio;
    for (int j = 0; j < i && atual != NULL; j++){
        atual = atual->prox;
    }

    return atual;
}

LISTA cria_lista(void){
    stLista* lista = malloc(sizeof(stLista));
    if (!lista) return NULL;

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;

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

bool insere_lista(LISTA l, ITEM item){
    if (!l) return false;
    stLista* lista = (stLista*)l;

    PONT novo = malloc(sizeof(ELEMENTO));
    if (!novo) return false;

    novo->chave = item;
    novo->prox = lista->inicio;
    novo->ant = NULL;

    if (lista->inicio != NULL){
        lista->inicio->ant = novo;
    }

    lista->inicio = novo;
    lista->tamanho++;
    return true;
}

ITEM removeIndice_lista(LISTA l, int i) {
    if (!l || i < 0) return NULL;
    stLista *lista = (stLista*)l;
    
    if (i >= lista->tamanho) return NULL;

    PONT remove = getElemento_lista(l, i); 
    if (!remove) return NULL;

    if (remove->ant != NULL) {
        remove->ant->prox = remove->prox;
    } else {
        lista->inicio = remove->prox;
    }

    if (remove->prox != NULL) {
        remove->prox->ant = remove->ant;
    } else {
        lista->fim = remove->ant;
    }

    ITEM chave = remove->chave;
    free(remove);
    lista->tamanho--;

    return chave;
}

void remove_lista(LISTA l, ITEM item){
    if (!l || !item) return;
    
    int i = 0;
    while (i < tamanho_lista(l)){
        if (getItem_lista(l, i) == item){
            removeIndice_lista(l, i);
            break;
        }
        i++;
    }
}

bool vazia_lista(LISTA l){
    stLista *lista = (stLista*)l;

    return (lista->inicio == NULL);
}

int tamanho_lista(LISTA l){
    if (!l) return -1;
    stLista *lista = (stLista*)l;

    return lista->tamanho;
}

ITEM getItem_lista(LISTA l, int i) {
    PONT no = getElemento_lista(l, i);
    return no ? no->chave : NULL;
}

void ordena_lista(LISTA l, int (*cmp)(void*, void*)) {
    stLista *lista = (stLista*)l;
    if (!lista || !lista->inicio) return;

    int trocou;
    PONT atual;
    
    do {
        trocou = 0;
        atual = lista->inicio;

        while (atual->prox != NULL) {
            if (cmp(atual->chave, atual->prox->chave) > 0) {
                void* aux = atual->chave;
                atual->chave = atual->prox->chave;
                atual->prox->chave = aux;
                trocou = 1;
            }
            atual = atual->prox; 
        }
    } while (trocou);
}
