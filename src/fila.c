#include "fila.h"
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    void** itens;
    int inicio, fim;
    int total;
    int tamanho_max; 
} StFila;

Fila cria_fila (int tamanho_max){
    StFila* fila = malloc(sizeof(StFila)); 
    if (!fila) return NULL;

    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
    fila->tamanho_max = tamanho_max;

    fila->itens = malloc(tamanho_max * sizeof(void*));
    if (!fila->itens){
        free(fila);
        return NULL;
    }

    return fila;
}

bool insere_fila(Fila f, ITEM i){
    if (!f) return false;

    StFila* fila = (StFila*)f;
    if (!fila) return false;
    if (fila->total == fila->tamanho_max) return false;

    fila->itens[fila->fim] = i;
    fila->fim = (fila->fim + 1) % fila->tamanho_max;
    fila->total++;

    return true;
}

bool remove_fila(Fila f, ITEM *fora){
    if (!f) return false;
    StFila* fila = (StFila*)f;
    if (fila->total == 0) return false;

    ITEM removido = fila->itens[fila->inicio];

    if (fora) *fora = removido; 

    fila->itens[fila->inicio] = NULL;

    fila->inicio = (fila->inicio + 1) % fila->tamanho_max;
    fila->total--;

    return true;
}

bool vazia_fila(Fila f){
    if (!f) return true;
    StFila* fila = (StFila*)f;

    return (fila->total == 0);
}

int tamanho_fila(Fila f){
    if (!f) return -1;
    if (vazia_fila(f)) return 0;

    StFila* fila = (StFila*)f;

    return fila->total;
}

bool libera_fila(Fila *f){
    if (!f || !*f) return false;

    StFila* fila = (StFila*)*f;

    if (fila->itens){
        free(fila->itens);
    }

    free(fila);
    
    *f = NULL;

    return true;
}

ITEM ver_fila(Fila f, char i_f){
    if (!f || (i_f != 'i' && i_f != 'f')) return NULL;
    StFila *fila = (StFila*)f;


    if (i_f == 'i'){
        return fila->itens[fila->inicio];
    }
    int indice_ultimo = (fila->fim - 1 + fila->tamanho_max) % fila->tamanho_max;
    return fila->itens[indice_ultimo];
}

Fila copia_fila(Fila f){
    if (!f) return NULL;
    StFila *fila = (StFila*)f;

    Fila copia = cria_fila(fila->tamanho_max);
    Fila aux = cria_fila(fila->tamanho_max);

    void *item;

    while(remove_fila(f, &item)){
        insere_fila(copia, item);
        insere_fila(aux, item);
    }

    while(remove_fila(aux, &item)){
        insere_fila(f, item);
    }

    libera_fila(&aux);
    aux = NULL;

   return copia;
}


