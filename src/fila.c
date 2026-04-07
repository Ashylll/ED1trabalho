#include "fila.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct elemento{
    void *chave;
    struct elemento *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct stFila {
    PONT inicio;
    PONT fim;
} stFila;

FILA cria_fila (void){
    stFila *fila = malloc(sizeof(stFila));
    if (!fila){
        return NULL;
    }

    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

void insere_fila(FILA f, void *item){
    if (!f) return;

    stFila *fila = (stFila*)f;
    PONT novo = malloc(sizeof(ELEMENTO));
    if(!novo) return;
   
    novo->chave = item;
    novo->prox = NULL;

    if (fila->inicio == NULL){
        fila->inicio = novo;
    } else {
        fila->fim->prox = novo;
    }

    fila->fim = novo;
    
    return;
}

void remove_fila(FILA f, ITEM *fora){
    if (!f) return;
    f = (stFila*)f;
    stFila *fila = (stFila*)f;
    if (fila->inicio == NULL) return;

    PONT removido = fila->inicio;
    
    if(fora != NULL){
        *fora = removido->chave;
    }

    fila->inicio = removido->prox;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(removido);

    return;
}

bool vazia_fila(FILA f){
    if (!f) return true;

    stFila *fila = (stFila*)f;
    return (fila->inicio == NULL);

}

int tamanho_fila(FILA f){
    if (!f) return -1;
    if (vazia_fila(f)) return 0;

    stFila *fila = (stFila*)f;

    PONT atual = fila->inicio;

    int n = 0;

    do{
       atual = atual->prox;
       n++; 
    } while(atual != NULL);

    return n;
}

void libera_fila(FILA *f){
    if (!f || !*f) return;

    stFila *fila = (stFila*)*f;

    PONT atual = fila->inicio;
    while(atual){
        PONT apagar = atual;
        atual = atual->prox;
        free(apagar);
    } 
    free(fila);
    *f = NULL;
}


