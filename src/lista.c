#include "lista.h"
#include <stdlib.h>

typedef struct StElemento{
    void* chave;
    struct StElemento *ant;
    struct StElemento *prox;
} StElemento;

typedef struct stLista{
    StElemento* inicio;
    StElemento* fim;
    int tamanho;
} stLista;

static StElemento* get_elemento_lista(Lista l, int i){
    if (!l) return NULL;
    stLista *lista = (stLista*)l;

    StElemento* atual = lista->inicio;
    for (int j = 0; j < i && atual != NULL; j++){
        atual = atual->prox;
    }

    return atual;
}

Lista cria_lista(void){
    stLista* lista = malloc(sizeof(stLista));
    if (!lista) return NULL;

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;

    return lista;
}

bool libera_lista(Lista *l){
    if (!l || !*l) return false;
    stLista* lista = (stLista*)*l;

    StElemento* atual = lista->inicio;
    StElemento* aux;
    while (atual != NULL){
        aux = atual->prox;
        free(atual);
        atual = aux;
    }

    free(lista);
    *l = NULL;

    return true;
}

bool insere_lista(Lista l, ITEM item){
    if (!l) return false;
    stLista* lista = (stLista*)l;

    StElemento* novo = malloc(sizeof(StElemento));
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

ITEM remove_indice_lista(Lista l, int i) {
    if (!l || i < 0) return NULL;
    stLista *lista = (stLista*)l;
    
    if (i >= lista->tamanho) return NULL;

    StElemento* remove = get_elemento_lista(l, i); 
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

void remove_lista(Lista l, ITEM item){
    if (!l || !item) return;
    
    int i = 0;
    while (i < tamanho_lista(l)){
        if (get_item_lista(l, i) == item){
            remove_indice_lista(l, i);
            break;
        }
        i++;
    }
}

bool vazia_lista(Lista l){
    stLista *lista = (stLista*)l;

    return (lista->inicio == NULL);
}

int tamanho_lista(Lista l){
    if (!l) return -1;
    stLista *lista = (stLista*)l;

    return lista->tamanho;
}

ITEM get_item_lista(Lista l, int i) {
    StElemento* no = get_elemento_lista(l, i);
    return no ? no->chave : NULL;
}

void ordena_lista(Lista l, int (*cmp)(void*, void*)) {
    stLista *lista = (stLista*)l;
    if (!lista || !lista->inicio) return;

    int trocou;
    StElemento* atual;
    
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
