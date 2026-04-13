#include "fila.h"
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_FILA 10

typedef struct {
    void* itens[TAMANHO_FILA];
    int inicio, fim;
    int total; 
} filaCircular;

typedef filaCircular* PONT;

FILA cria_fila (void){
    PONT fila = malloc(sizeof(filaCircular)); 

    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;

    return fila;
}

bool insere_fila(FILA f, ITEM i){
    if (!f) return;

    PONT fila = (filaCircular*)f;
    if (!fila) return false;
    if (fila->total == 10) return false;

    fila->itens[fila->fim] = i;
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;
    fila->total++;

    return true;
}

bool remove_fila(FILA f, ITEM *fora){
    if (!f) return false;
    PONT fila = (filaCircular*)f;
    if (fila->total == 0) return false;

    fora = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    fila->total--;

    return true;
}

bool vazia_fila(FILA f){
    if (!f) return true;
    PONT fila = (filaCircular*)f;

    return (fila->total == 0);
}

int tamanho_fila(FILA f){
    if (!f) return -1;
    if (vazia_fila(f)) return 0;

    PONT fila = (filaCircular*)f;

    return fila->total;
}

bool libera_fila(FILA *f){
    if (!f || !*f) return false;

    PONT fila = (filaCircular*)f;

    for(int i = 0; i < fila->total; i++){
        free(fila->itens[i]);
    }

    *f = NULL;

    return true;
}


