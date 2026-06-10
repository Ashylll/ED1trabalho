#include "poligono.h"
#include "linha.h"
#include "fila.h"
#include "lista.h"
#include "forma.h"

#include <stdlib.h>
#include <string.h>

typedef void* Lista;

typedef struct StPoligono {
    Fila vertices;
    char *corb, *corp;
    Fila lados, hachura;
    int id;

} StPoligono;

typedef struct StVertice {
    double x, y;
} StVertice;

Poligono cria_poligono(int id){
    StPoligono *poligono = malloc(sizeof(StPoligono));
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
            libera_poligono((Poligono*)&poligono);
            return NULL;
         }


    return poligono;
}

void libera_poligono(Poligono *p){
    if (!p || !*p) return;

    StPoligono *poligono = (StPoligono*)*p;
    free(poligono->corb);
    free(poligono->corp);

    ITEM remove;
    Fila vertices = get_vertices_poligono(*p);
    while (!vazia_fila(vertices)){
        remove_fila(vertices, &remove);
        free(remove);
    }
    libera_fila(&(poligono->vertices));

    Fila lados = get_lados_poligono(*p);
    while(!vazia_fila(lados)){
        remove_fila(lados, &remove);
    }
    libera_fila(&(poligono->lados));

    Fila hachura = get_hachura_poligono(*p);
    while (!vazia_fila(hachura)){
        remove_fila(hachura, &remove);
    }
    libera_fila(&(poligono->hachura));

    free(poligono);
    *p = NULL;

    return;
}

int tamanho_poligono(Poligono p){
    if (!p) return -1;

    StPoligono *poligono = (StPoligono*)p;

    return tamanho_fila(poligono->vertices);
}

int get_id_poligono(Poligono p){
    StPoligono *poligono = (StPoligono*)p;

    return poligono->id;
}

Poligono get_poligono(Fila f, int id){
    Fila copia = copia_fila(f);

    Poligono p;
    while(remove_fila(copia, &p)){
        if(get_id_poligono(p) == id){
            libera_fila(&copia);
            return p;
        }
    }
    libera_fila(&copia);
    
    return NULL;
}

Fila get_vertices_poligono(Poligono p){
    if (!p) return NULL;
    StPoligono *poligono = (StPoligono*)p;

    return poligono->vertices;
}

Fila get_lados_poligono(Poligono p){
    if (!p) return NULL;
    StPoligono *poligono = (StPoligono*)p;

    return poligono->lados;
}

Fila get_hachura_poligono(Poligono p){
    if (!p) return NULL;
    StPoligono *poligono = (StPoligono*)p;

    return poligono->hachura;
}

Vertice cria_vertice(double x, double y ){
    StVertice *vertice = malloc(sizeof(StVertice));
    if (!vertice) return NULL;

    vertice->x = x;
    vertice->y = y;

    return vertice;
}

void libera_vertice(Vertice *v){
    if (!v) return;
    
    StVertice *vertice = (StVertice*)*v;

    free(vertice);
    *v = NULL;

    return;
}

void insere_vertice(Poligono p, Vertice v){
    if (!v || !p) return;

    StPoligono *poligono = (StPoligono*)p;

    Fila fila_v = poligono->vertices;

    insere_fila(fila_v, v);

    return;
}

void remove_vertice(Poligono p, double *x, double *y){
    if (!p) return;
    StPoligono *poligono = (StPoligono*)p;

    void* v;
    remove_fila(poligono->vertices, &v);
    
    if (x && y){
    *x = get_x_vertice(v);
    *y = get_y_vertice(v);
    }

    libera_vertice(&v);

    return;
}

double get_x_vertice(Vertice v){
    StVertice *vertice = (StVertice*)v;

    return vertice->x;
}

double get_y_vertice(Vertice v){
    StVertice *vertice = (StVertice*)v;

    return vertice->y;
}

void set_corb(Poligono p, const char* corb) {
    if (!p || !corb) return;
    StPoligono *poligono = (StPoligono*)p;

    if (poligono->corb != NULL) {
        free(poligono->corb);
    }

    poligono->corb = malloc(strlen(corb) + 1);
    if (poligono->corb != NULL) {
        strcpy(poligono->corb, corb);
    }
}

void set_corp(Poligono p, const char* corp) {
    if (!p || !corp) return;
    StPoligono *poligono = (StPoligono*)p;

    if (poligono->corp != NULL) {
        free(poligono->corp);
    }

    poligono->corp = malloc(strlen(corp) + 1);
    if (poligono->corp != NULL) {
        strcpy(poligono->corp, corp);
    }
}

void desenha_poligono(Poligono p, int *id, char* corb, Lista formas){
    if (!p) return;
    StPoligono *poligono = (StPoligono*)p;
    set_corb(p, corb);

    Fila vertices = copia_fila(poligono->vertices);

    Vertice v_primeiro, v_atual, v_prox;

    remove_fila(vertices, &v_primeiro);
    v_atual = v_primeiro;

    while (remove_fila(vertices, &v_prox)) { // Cria os segmentos ao remover da fila cópia
        double vX_atual = get_x_vertice(v_atual);
        double vY_atual = get_y_vertice(v_atual);

        double vX_prox = get_x_vertice(v_prox);
        double vY_prox = get_y_vertice(v_prox);

        Segmento s = cria_linha(*id, vX_atual, vY_atual, vX_prox, vY_prox, poligono->corb);
        insere_fila(poligono->lados, s);

        Forma f = cria_forma('l', s);
        insere_lista(formas, f);
        v_atual = v_prox; 

        (*id)++;
    }

    // Cria o segmento final (conecta o primeiro vértice com o último)
    double vX_atual = get_x_vertice(v_atual);
    double vY_atual = get_y_vertice(v_atual);

    double vX_primeiro = get_x_vertice(v_primeiro);
    double vY_primeiro = get_y_vertice(v_primeiro);

    Segmento s_final = cria_linha(*id, vX_atual, vY_atual, vX_primeiro, vY_primeiro, poligono->corb);
    insere_fila(poligono->lados, s_final);

    Forma f_final = cria_forma('l', s_final);
    insere_lista(formas, f_final);

    (*id)++;

    
    libera_fila(&vertices);
     
    return;
}

void boundingBox(Fila vertices, double *ymin, double *xmin, double *ymax, double *xmax){
    if (!vertices) return;

    Fila aux = copia_fila(vertices);
    Vertice vertice;

    remove_fila(aux, &vertice);
    double y = get_y_vertice(vertice);
    double x = get_x_vertice(vertice);
    
    *ymin = *ymax = y;
    *xmin = *xmax = x;
    
    while (remove_fila(aux, &vertice)){
        y = get_y_vertice(vertice);
        x = get_x_vertice(vertice);

        if (y < *ymin) *ymin = y;
        else if (y > *ymax) *ymax = y;
        
        if (x < *xmin) *xmin = x;
        else if (x > *xmax) *xmax = x;

    }

    libera_fila(&aux);
}

void calc_intersecao(Poligono p, double y_atual, Lista coordXLista){
    Fila lados = get_lados_poligono(p);
    Fila aux = copia_fila(lados);
    Linha segmento;
    while (remove_fila(aux, &segmento)){
        double x1 = get_x1_linha(segmento);
        double y1 = get_y1_linha(segmento);
        double x2 = get_x2_linha(segmento);
        double y2 = get_y2_linha(segmento);

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

void hachura_poligono(Poligono p, int *id, double d, char* corp, Lista formas){
    if (!p || d <= 0) return;
    StPoligono *poligono = (StPoligono*)p;
    set_corp(p, corp);

    double ymin, ymax, xmin, xmax;
    boundingBox(get_vertices_poligono(p), &ymin, &xmin, &ymax, &xmax);

    double epsilon = 1e-9;
    double y_atual = ymin + d;
    while (y_atual < (ymax - epsilon)) {
        Lista coordXLista = cria_lista();
        calc_intersecao(p, y_atual, coordXLista);

        ordena_lista(coordXLista, compara_doubles);

        for (int i = 0; i < tamanho_lista(coordXLista); i += 2) {
            double *x1_ptr = (double*) get_item_lista(coordXLista, i);
            double *x2_ptr = (double*) get_item_lista(coordXLista, i + 1);
        
            if (x1_ptr && x2_ptr) {
                double x1 = *x1_ptr;
                double x2 = *x2_ptr;
                
                Linha hachura = cria_linha(*id, x1, y_atual, x2, y_atual, poligono->corp);
                insere_fila(poligono->hachura, hachura);

                Forma f = cria_forma('l', hachura);
                insere_lista(formas, f);

                (*id)++;
            }
        }

        for (int i = 0; i < tamanho_lista(coordXLista); i++) {
            double *p_x = (double*) get_item_lista(coordXLista, i);
            if (p_x) free(p_x);
        }
        libera_lista(&coordXLista);

        y_atual += d;
    }   
}