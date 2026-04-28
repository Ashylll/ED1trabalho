#include "poligono.h"
#include "linha.h"
#include "fila.h"

#include <stdlib.h>

typedef struct stPoligono {
    FILA vertices;
    char *corb, *corp;
    FILA lados, hachura;
    int id;

} stPoligono;

typedef struct stVertice {
    double x, y;
} stVertice;


POLIGONO cria_poligono(int id){
    stPoligono *poligono = malloc(sizeof(stPoligono));
    if (!poligono) return NULL;
    if (id < 1 || id > 10) return NULL;

    poligono->vertices = cria_fila(100);
    poligono->lados = cria_fila(100);
    poligono->hachura = cria_fila(100);
    if (poligono->vertices == NULL || poligono->lados == NULL ||
         poligono->hachura == NULL) return NULL;

    poligono->corb = NULL;
    poligono->corp = NULL;
    poligono->id = id;

    return poligono;
}

void libera_poligono(POLIGONO *p){
    if (!p || !*p) return;

    stPoligono *poligono = (stPoligono*)*p;
    free(poligono->corb);
    free(poligono->corp);

    ITEM remove;
    FILA vertices = getVertices_poligono(*p);
    while (!vazia_fila(vertices)){
        remove_fila(vertices, &remove);
        free(remove);
    }

    FILA lados = getLados_poligono(*p);
    while(!vazia_fila(lados)){
        remove_fila(lados, &remove);
        free(remove);
    }

    FILA hachura = getHachura_poligono(*p);
    while (!vazia_fila(hachura)){
        remove_fila(hachura, &remove);
        free(remove);
    }

    free(poligono);
    *p = NULL;

    return;
}

int tamanho_poligono(POLIGONO p){
    if (!p) return -1;

    stPoligono *poligono = (stPoligono*)p;

    return tamanho_fila(poligono->vertices);
}

int getId_poligono(POLIGONO p){
    stPoligono *poligono = (stPoligono*)p;

    return poligono->id;
}

POLIGONO getPoligono(FILA f, int id){
    FILA copia = copia_fila(f);

    POLIGONO p;
    while(remove_fila(copia, &p)){
        if(getId_poligono(p) == id){
            libera_fila(&copia);
            return p;
        }
    }
    libera_fila(&copia);
    
    return NULL;
}

FILA getVertices_poligono(POLIGONO p){
    if (!p) return NULL;
    stPoligono *poligono = (stPoligono*)p;

    return poligono->vertices;
}

FILA getLados_poligono(POLIGONO p){
    if (!p) return NULL;
    stPoligono *poligono = (stPoligono*)p;

    return poligono->lados;
}

FILA getHachura_poligono(POLIGONO p){
    if (!p) return NULL;
    stPoligono *poligono = (stPoligono*)p;

    return poligono->hachura;
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

static int id_global = -1;

int proximo_id(){
    return --id_global;
}

void desenha_poligono(POLIGONO p){
    if (!p) return;
    stPoligono *poligono = (stPoligono*)p;

    FILA vertices = copia_fila(poligono->vertices);

    VERTICE v_primeiro, v_atual, v_prox;

    remove_fila(vertices, &v_primeiro);
    v_atual = v_primeiro;

    while (remove_fila(vertices, &v_prox)) { // Cria os segmentos ao remover da fila cópia
        double vX_atual = getX_vertice(v_atual);
        double vY_atual = getY_vertice(v_atual);

        double vX_prox = getX_vertice(v_prox);
        double vY_prox = getY_vertice(v_prox);

        SEGMENTO s = cria_linha(proximo_id(), vX_atual, vY_atual, vX_prox, vY_prox, poligono->corb);
        insere_fila(poligono->lados, s);
        
        v_atual = v_prox; 
    }

    // Cria o segmento final (conecta o primeiro vértice com o último)
    double vX_atual = getX_vertice(v_atual);
    double vY_atual = getY_vertice(v_atual);

    double vX_primeiro = getX_vertice(v_primeiro);
    double vY_primeiro = getY_vertice(v_primeiro);

    SEGMENTO s_final = cria_linha(proximo_id(), vX_atual, vY_atual, vX_primeiro, vY_primeiro, poligono->corb);
    insere_fila(poligono->lados, s_final);

    libera_fila(vertices);

    return;
}

void hachura_poligono(POLIGONO p, double d){
    if (!p || d <= 0) return;

    
}