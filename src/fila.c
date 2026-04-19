#include "fila.h"
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    void** itens;
    int inicio, fim;
    int total;
    int tamanho_max; 
} filaCircular;

typedef filaCircular* PONT;

FILA cria_fila (int tamanho_max){
    PONT fila = malloc(sizeof(filaCircular)); 
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

bool insere_fila(FILA f, ITEM i){
    if (!f) return false;

    PONT fila = (PONT)f;
    if (!fila) return false;
    if (fila->total == 10) return false;

    fila->itens[fila->fim] = i;
    fila->fim = (fila->fim + 1) % fila->tamanho_max;
    fila->total++;

    return true;
}

bool remove_fila(FILA f, ITEM *fora){
    if (!f) return false;
    PONT fila = (PONT)f;
    if (fila->total == 0) return false;

    ITEM removido = fila->itens[fila->inicio];

    if (fora) *fora = removido; 

    fila->itens[fila->inicio] = NULL;

    fila->inicio = (fila->inicio + 1) % fila->tamanho_max;
    fila->total--;

    return true;
}

bool vazia_fila(FILA f){
    if (!f) return true;
    PONT fila = (PONT)f;

    return (fila->total == 0);
}

int tamanho_fila(FILA f){
    if (!f) return -1;
    if (vazia_fila(f)) return 0;

    PONT fila = (PONT)f;

    return fila->total;
}

bool libera_fila(FILA *f){
    if (!f || !*f) return false;

    PONT fila = (PONT)*f;

    if (fila->itens){
        free(fila->itens);
    }

    free(fila);
    
    *f = NULL;

    return true;
}

FILA copia_fila(FILA f){
    if (!f) return NULL;
    filaCircular *fila = (filaCircular*)f;

    FILA copia = cria_fila(fila->tamanho_max);
    FILA aux = cria_fila(fila->tamanho_max);

    void *item;

    while(remove_fila(f, &item)){
        insere_fila(copia, item);
        insere_fila(aux, item);
    }

    while(remove_fila(f, &item)){
        insere_fila(f, item);
    }

    libera_fila(&aux);
    aux = NULL;

   return copia;
}

