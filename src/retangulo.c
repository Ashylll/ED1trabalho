#include "retangulo.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct St_retangulo {
    int id;
    double x, y, w, h;
    char *corb, *corp;
} St_retangulo;

Retangulo cria_retangulo(int id, double x, double y, double w, double h, const char* corb, const char* corp){
    if (!corb || !corp || w <= 0 || h <= 0) return NULL;
 
    St_retangulo *retangulo = malloc(sizeof(*retangulo));
    if (!retangulo) return NULL;

    retangulo->id = id;
    retangulo->x = x;
    retangulo->y = y;
    retangulo->w = w;
    retangulo->h = h;

    retangulo->corb = malloc(strlen(corb)+1);
    if (!retangulo->corb){
        free(retangulo);
        return NULL;
    }
    strcpy(retangulo->corb, corb);

    retangulo->corp = malloc(strlen(corp)+1);
    if (!retangulo->corp){
        free(retangulo->corb);
        free(retangulo);
        return NULL;
    }
    strcpy(retangulo->corp, corp);

    return retangulo;
}

double area_retangulo(Retangulo r){
    if(!r) return -1;
    St_retangulo *retangulo = (St_retangulo*)r;

     double area = retangulo->w * retangulo->h;

     return area;
} 

void libera_retangulo(Retangulo *r){
    if(!r || !*r) return;
    St_retangulo *retangulo = (St_retangulo*)*r;

    free(retangulo->corb);
    free(retangulo->corp);
    free(retangulo);

    *r = NULL;
}

int get_id_retangulo(Retangulo r){
    St_retangulo *retangulo = (St_retangulo*)r;

    return retangulo->id;
}

double get_x_retangulo(Retangulo r){
    St_retangulo *retangulo = (St_retangulo*)r;

    return retangulo->x;
}

double get_y_retangulo(Retangulo r){
    St_retangulo *retangulo = (St_retangulo*)r;

    return retangulo->y;
}

double getW_retangulo(Retangulo r){
    St_retangulo *retangulo = (St_retangulo*)r;

    return retangulo->w;
}

double getH_retangulo(Retangulo r){
    St_retangulo *retangulo = (St_retangulo*)r;

    return retangulo->h;
}

char* get_corb_retangulo(Retangulo r){
    if (!r)  return NULL;
    St_retangulo *retangulo = (St_retangulo*)r;

    return retangulo->corb;
}

char* get_corp_retangulo(Retangulo r){
    if (!r)  return NULL;
    St_retangulo *retangulo = (St_retangulo*)r;

    return retangulo->corp;
}

bool set_id_retangulo(Retangulo r, int id){
    if (!r) return false;

    St_retangulo *retangulo = (St_retangulo*)r; 
    retangulo->id = id;

    return true;
}

bool set_x_retangulo(Retangulo r, double x){
    if (!r) return false;

   St_retangulo *retangulo = (St_retangulo*)r; 
    retangulo->x = x;

    return true;
}

bool set_y_retangulo(Retangulo r, double y){
    if (!r) return false;

    St_retangulo *retangulo = (St_retangulo*)r; 
    retangulo->y = y;

    return true;
}

bool setW_retangulo(Retangulo r, double w){
    if (!r || w <= 0) return false;

    St_retangulo *retangulo = (St_retangulo*)r; 
    retangulo->w = w;

    return true;
}

bool setH_retangulo(Retangulo r, double h){
    if (!r || h <= 0) return false;

    St_retangulo *retangulo = (St_retangulo*)r; 
    retangulo->h = h;

    return true;
}


bool set_corb_retangulo(Retangulo r, const char* corb){
    if (!r || !corb) return false;

    St_retangulo *retangulo = (St_retangulo*)r;
    
    if (retangulo->corb && strcmp(retangulo->corb, corb) == 0) return true;

    char *novo = malloc(strlen(corb)+1);
    if (!novo) return false;

    strcpy(novo, corb);
    free(retangulo->corb);
    retangulo->corb = novo;

    return true;
}

bool set_corp_retangulo(Retangulo r, const char* corp){
    if (!r || !corp) return false;

    St_retangulo *retangulo = (St_retangulo*)r;
    
    if (retangulo->corp && strcmp(retangulo->corp, corp) == 0) return true;             

    char *novo = malloc(strlen(corp)+1);
    if (!novo) return false;

    strcpy(novo, corp);
    free(retangulo->corp);
    retangulo->corp = novo;

    return true;
}