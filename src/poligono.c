#include "poligono.h"
#include "fila.h"

#include <stdlib.h>

typedef struct stPoligono {
    FILA vertices;
    char *corb, *corp;
    FILA lados, rachura;

} stPoligono;

typedef struct stVertice {
    double x, y;
} stVertice;

typedef struct stSegmento {
    int id;
    VERTICE v1, v2;
    char *cor;
} stSegmento;

POLIGONO cria_poligono(void){
    stPoligono *poligono = malloc(sizeof(stPoligono));
    if (!poligono) return NULL;

    poligono->vertices = cria_fila(100);
    poligono->lados = cria_fila(100);
    poligono->rachura = cria_fila(100);
    if (poligono->vertices == NULL || poligono->lados == NULL ||
         poligono->rachura == NULL) return NULL;

    poligono->corb = NULL;
    poligono->corp = NULL;

    return poligono;
}

void libera_poligono(POLIGONO *p){
    if (!p || !*p) return;

    stPoligono *poligono = (stPoligono*)*p;
    free(poligono->corb);
    free(poligono->corp);

    void* v;
    int tamanho = tamanho_poligono(p);
    for(int i = 0; i < tamanho; i++){
        remove_vertice(p);
    }
    libera_fila(&(poligono->vertices));
    libera_fila(&(poligono->lados));
    libera_fila(&(poligono->rachura));
    free(poligono);
    *p = NULL;

    return;
}

int tamanho_poligono(POLIGONO p){
    if (!p) return -1;

    stPoligono *poligono = (stPoligono*)p;

    return tamanho_fila(poligono->vertices);
}

VERTICE cria_vertice(double x, double y ){
    stVertice *vertice = malloc(sizeof(stVertice));
    if (!vertice) return NULL;

    vertice->x = x;
    vertice->y = y;

    return vertice;
}

void libera_vertice(VERTICE *v){
    if (!v) return;
    
    stVertice *vertice = (stVertice*)*v;

    free(vertice);
    *v = NULL;

    return;
}

void insere_vertice(POLIGONO p, VERTICE v){
    if (!v || !p) return;

    stPoligono *poligono = (stPoligono*)p;

    FILA fila_v = poligono->vertices;

    insere_fila(fila_v, v);

    return;
}

void remove_vertice(POLIGONO p){
    if (!p) return;
    stPoligono *poligono = (stPoligono*)p;

    void* v;
    remove_fila(poligono->vertices, &v);
    libera_vertice(&v);

    return;
}

double getX_vertice(VERTICE v){
    stVertice *vertice = (stVertice*)v;

    return vertice->x;
}

double getY_vertice(VERTICE v){
    stVertice *vertice = (stVertice*)v;

    return vertice->y;
}

SEGMENTO cria_segmento(int id, VERTICE v1, VERTICE v2, char* cor){
    stSegmento *segmento = malloc(sizeof(stSegmento));
    if (!segmento || !v1 || !v2 || !cor) return NULL;

    segmento->id = id;
    segmento->v1 = v1;
    segmento->v2 = v2;
    segmento->cor = cor;

    return segmento;
}

void libera_segmento(SEGMENTO *s){
    if (!s || !*s) return;
    stSegmento *segmento = (stSegmento*)*s;
    free(segmento);

    *s = NULL;
}
