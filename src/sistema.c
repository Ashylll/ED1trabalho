#include "sistema.h"
#include "poligono.h"
#include "forma.h"

#include <stdlib.h>
#include <string.h>

typedef struct sistema {
    LISTA formas;
    FILA poligonos;
    FILA selecionadas;
    LISTA formas_aux;

    FILE* txt;
    FILE* svg_geo;
    FILE* svg_qry;
    
    char fFamily[32];
    char fWeight[32];
    double fSize;
} sistema;

SISTEMA cria_sistema(const char* path_txt, const char* path_svg_geo, const char* path_svg_qry){
    sistema* s = malloc(sizeof(sistema));
    
    s->formas = cria_lista();
    s->poligonos = cria_fila(10);
    s->selecionadas = cria_fila(200);
    s->formas_aux = cria_lista();
    
    s->txt = fopen(path_txt, "w");
    s->svg_geo = fopen(path_svg_geo, "w");
    svg_begin(s->svg_geo);

    if(s->svg_qry){
        s->svg_qry = fopen(path_svg_qry, "w");
        svg_begin(s->svg_qry);
    }

    strcpy(s->fFamily, "sans-serif");
    strcpy(s->fWeight, "normal");
    s->fSize = 12.0;

    return (SISTEMA)s;
}

LISTA get_formas(SISTEMA s){

    return ((sistema*)s)->formas;
}

FILA get_poligonos(SISTEMA s){

    return ((sistema*)s)->poligonos;
}

FILA get_selecionadas(SISTEMA s){

    return ((sistema*)s)->selecionadas;
}

LISTA get_formas_aux(SISTEMA s){

    return ((sistema*)s)->formas_aux;
}

FILE* get_arquivo_txt(SISTEMA s){

    return ((sistema*)s)->txt;
}

FILE* get_svg_geo(SISTEMA s){

    return ((sistema*)s)->svg_geo;
}

FILE* get_svg_qry(SISTEMA s){

    return ((sistema*)s)->svg_qry;
}

void get_estilo_texto(SISTEMA s, char* family, char* weight, double* size) {
    sistema* sys = (sistema*)s;

    if (family) strcpy(family, sys->fFamily);
    if (weight) strcpy(weight, sys->fWeight);
    if (size) *size = sys->fSize;

    return;
}

void set_estilo_texto(SISTEMA s, const char* family, const char* weight, double size){
    sistema* sys = (sistema*)s;

    strcpy(sys->fFamily, family);
    strcpy(sys->fWeight, weight);
    sys->fSize = size;

    return;
}

void fecha_sistema(SISTEMA* s) {
    sistema* sys = (sistema*)*s;
   
    ITEM remove;
    while (!vazia_fila(sys->poligonos)){
        remove_fila(sys->poligonos, &remove);
        libera_poligono(&remove);
    }   
    libera_fila(&(sys->poligonos));
    
    while (!vazia_fila(sys->selecionadas)){
        remove_fila(sys->selecionadas, &remove);
    }
    libera_fila(&(sys->selecionadas));

    while (!vazia_lista(sys->formas)){
        remove = removeIndice_lista(sys->formas, 0); 
        libera_forma(&remove); 
    }
    libera_lista(&(sys->formas));

    
    while (!vazia_lista(sys->formas_aux)){
        remove = removeIndice_lista(sys->formas_aux, 0); 
        libera_forma(&remove); 
    }
    libera_lista(&(sys->formas_aux));

    if (sys->svg_geo) {
        fprintf(sys->svg_geo, "</svg>");
        fclose(sys->svg_geo);
    }
    if (sys->svg_qry) {
        fprintf(sys->svg_qry, "</svg>");
        fclose(sys->svg_qry);
    }
    
    if (sys->txt) fclose(sys->txt);

    free(sys);
    *s = NULL;
}