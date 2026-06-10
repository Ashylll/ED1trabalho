#include "sistema.h"
#include "poligono.h"
#include "forma.h"
#include "svg.h"

#include <stdlib.h>
#include <string.h>

typedef struct StSistema {
    Lista formas;
    Fila poligonos;
    Fila selecionadas;
    Lista formas_aux;

    FILE* txt;
    FILE* svg_geo;
    FILE* svg_qry;
    
    char fFamily[32];
    char fWeight[32];
    double fSize;
} StSistema;

Sistema cria_sistema(const char* path_txt, const char* path_svg_geo, const char* path_svg_qry){
    StSistema* s = malloc(sizeof(StSistema));
    
    s->formas = cria_lista();
    s->poligonos = cria_fila(10);
    s->selecionadas = cria_fila(200);
    s->formas_aux = cria_lista();
    
    if (path_txt) s->txt = fopen(path_txt, "w");
    else s->txt = NULL;
    
    s->svg_geo = fopen(path_svg_geo, "w");
    svg_begin(s->svg_geo);

    if(path_svg_qry){
        s->svg_qry = fopen(path_svg_qry, "w");
        svg_begin(s->svg_qry);
    } else {
        s->svg_qry = NULL;
    }

    strcpy(s->fFamily, "sans-serif");
    strcpy(s->fWeight, "normal");
    s->fSize = 12.0;

    return (Sistema)s;
}

Lista get_formas(Sistema s){

    return ((StSistema*)s)->formas;
}

Fila get_poligonos(Sistema s){

    return ((StSistema*)s)->poligonos;
}

Fila get_selecionadas(Sistema s){

    return ((StSistema*)s)->selecionadas;
}

Lista get_formas_aux(Sistema s){

    return ((StSistema*)s)->formas_aux;
}

FILE* get_arquivo_txt(Sistema s){

    return ((StSistema*)s)->txt;
}

FILE* get_svg_geo(Sistema s){

    return ((StSistema*)s)->svg_geo;
}

FILE* get_svg_qry(Sistema s){

    return ((StSistema*)s)->svg_qry;
}

void get_estilo_texto(Sistema s, char* family, char* weight, double* size) {
    StSistema* sys = (StSistema*)s;

    if (family) strcpy(family, sys->fFamily);
    if (weight) strcpy(weight, sys->fWeight);
    if (size) *size = sys->fSize;

    return;
}

void set_estilo_texto(Sistema s, const char* family, const char* weight, double size){
    StSistema* sys = (StSistema*)s;

    strcpy(sys->fFamily, family);
    strcpy(sys->fWeight, weight);
    sys->fSize = size;

    return;
}

void fecha_sistema(Sistema* s) {
    StSistema* sys = (StSistema*)*s;
   
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
        remove = remove_indice_lista(sys->formas, 0); 
        libera_forma(&remove); 
    }
    libera_lista(&(sys->formas));

    
    while (!vazia_lista(sys->formas_aux)){
        remove = remove_indice_lista(sys->formas_aux, 0); 
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