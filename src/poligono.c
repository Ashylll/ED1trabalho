#include "poligono.h"
#include "linha.h"
#include "fila.h"
#include "lista.h"

#include <stdlib.h>
#include <string.h>

typedef void* LISTA;

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
    if (id < 1 || id > 10) {
        free(poligono);
        return NULL;
    }

    poligono->vertices = cria_fila(100);
    poligono->lados = cria_fila(100);
    poligono->hachura = cria_fila(100);
    poligono->corb = NULL;
    poligono->corp = NULL;
    poligono->id = id;

    if (poligono->vertices == NULL || poligono->lados == NULL ||
         poligono->hachura == NULL){
            libera_poligono((POLIGONO*)&poligono);
            return NULL;
         }


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
    libera_fila(&(poligono->vertices));

    FILA lados = getLados_poligono(*p);
    while(!vazia_fila(lados)){
        remove_fila(lados, &remove);
        libera_linha(&remove);
    }
    libera_fila(&(poligono->lados));

    FILA hachura = getHachura_poligono(*p);
    while (!vazia_fila(hachura)){
        remove_fila(hachura, &remove);
        libera_linha(&remove);
    }
    libera_fila(&(poligono->hachura));

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

void setCORB(POLIGONO p, const char* corb) {
    if (!p || !corb) return;
    stPoligono *poligono = (stPoligono*)p;

    if (poligono->corb != NULL) {
        free(poligono->corb);
    }

    poligono->corb = malloc(strlen(corb) + 1);
    if (poligono->corb != NULL) {
        strcpy(poligono->corb, corb);
    }
}

void setCORP(POLIGONO p, const char* corp) {
    if (!p || !corp) return;
    stPoligono *poligono = (stPoligono*)p;

    if (poligono->corp != NULL) {
        free(poligono->corp);
    }

    poligono->corp = malloc(strlen(corp) + 1);
    if (poligono->corp != NULL) {
        strcpy(poligono->corp, corp);
    }
}

void desenha_poligono(POLIGONO p, char* corb){
    if (!p) return;
    stPoligono *poligono = (stPoligono*)p;
    setCORB(p, corb);

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

    if (!remove_fila(vertices, &v_primeiro)) {
        libera_fila(&vertices);
        return;
    }

    return;
}

void boundingBox(FILA vertices, double *ymin, double *xmin, double *ymax, double *xmax){
    if (!vertices) return;

    FILA aux = copia_fila(vertices);
    VERTICE vertice;

    remove_fila(aux, &vertice);
    double y = getY_vertice(vertice);
    double x = getX_vertice(vertice);
    
    *ymin = *ymax = y;
    *xmin = *xmax = x;
    
    while (remove_fila(aux, &vertice)){
        y = getY_vertice(vertice);
        x = getX_vertice(vertice);

        if (y < *ymin) *ymin = y;
        else if (y > *ymax) *ymax = y;
        
        if (x < *xmin) *xmin = x;
        else if (x > *xmax) *xmax = x;

    }

    libera_fila(&aux);
}

void calc_intersecao(POLIGONO p, double y_atual, LISTA coordXLista){
    FILA lados = getLados_poligono(p);
    FILA aux = copia_fila(lados);
    LINHA segmento;
    while (remove_fila(aux, &segmento)){
        double x1 = getX1_linha(segmento);
        double y1 = getY1_linha(segmento);
        double x2 = getX2_linha(segmento);
        double y2 = getY2_linha(segmento);

        if (y1 == y2) continue;

        double y_min = (y1 < y2) ? y1 : y2;
        double y_max = (y1 > y2) ? y1 : y2;

        if (y_atual >= y_min && y_atual < y_max){
            double x_intersecao = x1 + (y_atual - y1) * (x2 - x1) / (y2 - y1);

            double *p_x = malloc(sizeof(double));
            if (p_x){
                *p_x = x_intersecao;
                insere_lista(coordXLista, p_x);
            }
        }
    }
    libera_fila(&aux);
}

int compara_doubles(void *a, void *b) {
    double v1 = *(double*)a;
    double v2 = *(double*)b;

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

void hachura_poligono(POLIGONO p, int id, double d, char* corp){
    if (!p || d <= 0) return;
    stPoligono *poligono = (stPoligono*)p;
    setCORP(p, corp);

    double ymin, ymax, xmin, xmax;
    boundingBox(getVertices_poligono(p), &ymin, &xmin, &ymax, &xmax);

    double epsilon = 1e-9;
    double y_atual = ymin + d;
    while (y_atual < (ymax - epsilon)) {
        LISTA coordXLista = cria_lista();
        calc_intersecao(p, y_atual, coordXLista);

        ordena_lista(coordXLista, compara_doubles);

        for (int i = 0; i < tamanho_lista(coordXLista); i += 2) {
            double *x1_ptr = (double*) getItem_lista(coordXLista, i);
            double *x2_ptr = (double*) getItem_lista(coordXLista, i + 1);
        
            if (x1_ptr && x2_ptr) {
                double x1 = *x1_ptr;
                double x2 = *x2_ptr;
                
                LINHA hachura = cria_linha(id, x1, y_atual, x2, y_atual, poligono->corp);
                insere_fila(poligono->hachura, hachura);
            }
            id++;
        }

        for (int i = 0; i < tamanho_lista(coordXLista); i++) {
            double *p_x = (double*) getItem_lista(coordXLista, i);
            if (p_x) free(p_x);
        }
        libera_lista(&coordXLista);

        y_atual += d;
    }   
}