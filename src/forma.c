#include "forma.h"
#include <stdlib.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef struct stForma{
    char tipo;
    void* handle;
} stForma;

FORMA cria_forma(char tipo, void* handle){
    if (!handle || (tipo != 'c' && tipo != 'r' && tipo != 't' && tipo != 'l')) return NULL;

    stForma* forma = malloc(sizeof(stForma));
    if (!forma) return NULL;

    forma->tipo = tipo;
    forma->handle = handle;

    return forma;
}

void libera_forma(FORMA *f){
    if (!f || !*f) return;
    stForma *forma = (stForma*)*f;

    switch (forma->tipo){
        case 'c': libera_circulo((CIRCULO*)&forma->handle); break;
        case 'r': libera_retangulo((RETANGULO*)&forma->handle); break;
        case 't': libera_texto((TEXTO*)&forma->handle); break;
        case 'l': libera_linha((LINHA*)&forma->handle); break;
    }
    
    free(forma);
    *f = NULL;
}

int getId_forma(FORMA f){
    stForma *forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': return getId_circulo(forma->handle);
        case 'r': return getId_retangulo(forma->handle);
        case 't': return getId_texto(forma->handle);
        case 'l': return getId_linha(forma->handle); 
        default: return -100;
    }
}

char getTipo_forma(FORMA f){
    stForma* forma = (stForma*)f;

    return forma->tipo;
}

void* getHandle_forma(FORMA f){
    if (!f) return NULL;
    stForma* forma = (stForma*)f;

    return forma->handle;
}

bool getXY_forma(FORMA f, double *x, double *y){
    if (!f || !x || !y) return false;
    stForma* forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': *x = getX_circulo(forma->handle); *y = getY_circulo(forma->handle); break;
        case 'r': *x = getX_retangulo(forma->handle); *y = getY_retangulo(forma->handle); break;
        case 't': *x = getX_texto(forma->handle); *y = getY_texto(forma->handle); break;
        case 'l': *x = getX1_linha(forma->handle); *y = getY1_linha(forma->handle); break;
        default: return false;
    }

    return true;
}

bool setXY_forma(FORMA f, double x, double y){
    if (!f) return false;

    stForma* forma = (stForma*)f;

    switch (forma->tipo){
        case 'c': return setX_circulo(forma->handle, x) && setY_circulo(forma->handle, y);
        case 'r': return setX_retangulo(forma->handle, x) && setY_retangulo(forma->handle, y);
        case 't': return setX_texto(forma->handle, x) && setY_texto(forma->handle, y);
        case 'l': return setAncora_linha(forma->handle, x, y);
        
        default: return false;
    }
}

bool desloca_forma(FORMA f, double dx, double dy){
    if (!f) return false;

    double x, y;

    if (!getXY_forma(f, &x, &y)) return false;

    return setXY_forma(f, x + dx, y + dy);
}