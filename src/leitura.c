#include "leitura.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "fila.h"
#include "poligono.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static char fFamily[32] = "sans-serif";
static char fWeight[16] = "normal";
static double fSize = 20.0;
    
static const char* converter_weight(const char *weight){
    if (!weight) return "normal";
    if (strcmp(weight, "b+") == 0) return "bolder";
    if (strcmp(weight, "b")  == 0) return "bold";
    if (strcmp(weight, "n")  == 0) return "normal";
    if (strcmp(weight, "l")  == 0) return "lighter";
    
    return weight;
}

/* Comandos .geo */

FORMAS => LISTA

static bool comando_c(const char *linha, LISTA formas){
    int i; 
    double x, y, r;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &i, &x, &y, &r, corb, corp) != 6) return false;

    CIRCULO c = cria_circulo(i, x, y, r, corb, corp);
    if (!c) return false;

    FORMA f = cria_forma('c', c);
    insere_fila(formas, f);

    return true;    
}

static bool comando_r(const char *linha, FILA formas){
    int i;
    double x, y, w, h;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &i, &x, &y, &w, &h, corb, corp) != 7) return false;
    
    RETANGULO r = cria_retangulo(i, x, y, w, h, corb, corp);
    if (!r) return false;

    FORMA f = cria_forma('r', r);
    insere_fila(formas, f);

    return true;
}

static bool comando_l(const char *linha, FILA formas){
    int i;
    double x1, y1, x2, y2;
    char cor[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s", &i, &x1, &y1, &x2, &y2, cor) != 6) return false;

    LINHA l;
    if (x1 < x2){ // Determina âncora
        l = cria_linha(i, x1, y1, x2, y2, cor);
    } else if (x1 > x2){
        l = cria_linha(i, x2, y2, x1, y1, cor);
    } else if (y1 < y2){
        l = cria_linha(i, x1, y1, x2, y2, cor);
    } else{
        l = cria_linha(i, x2, y2, x1, y1, cor);
    }
    if (!l) return false;

    FORMA f = cria_forma('l', l);
    insere_fila(formas, f);

    return true;

}

static bool comando_t(const char *linha, const char *fFamily, const char *fWeight, int fSize, FILA formas){
    int i;
    double x, y;
    char corb[32], corp[32], ancora, txto[512];

    if(sscanf(linha, "%*s %d %lf %lf %31s %31s %c %[^\n]", &i, &x, &y, corb, corp, &ancora, txto) < 7) return false;
    
    TEXTO t = cria_texto(i, x, y, corb, corp, ancora, txto);
    if (!t) return false;

    
    muda_estilo(t, fFamily, fWeight, fSize);
    FORMA f = cria_forma('t', t);
    insere_fila(formas, f);
    
    return true;
}

static bool comando_ts(const char *linha){
    char novo_family[32], novo_weight[8];
    double novo_size;

    if (sscanf(linha, "%*s %31s %7s %lf", novo_family, novo_weight, &novo_size) != 3) return false;

    const char *wt  = converter_weight(novo_weight);

    strcpy(fFamily, novo_family);
    strcpy(fWeight, wt);
    fSize = novo_size;

    return true;
}

bool ler_geo(const char *path_geo, FILA formas){
    FILE *fp = fopen(path_geo, "r");
    if(!fp) return false;

    char linha[1024], comando[8];

    while (fgets(linha, sizeof linha, fp)){
        if(sscanf(linha, "%7s", comando) != 1) continue;
        if(comando[0] == '#') continue;

        if (strcmp(comando, "c") == 0){
            if(!comando_c(linha, formas)){
                fprintf(stderr, "Erro ao processar o comando 'c'\n");
            }
        }

        else if (strcmp(comando, "r") == 0){
            if(!comando_r(linha, formas)){
                fprintf(stderr, "Erro ao processar o comando 'r'\n");
            }
        }

        else if (strcmp(comando, "l") == 0){
            if(!comando_l(linha, formas)){
                fprintf(stderr, "Erro ao processar o comando 'l'\n");
            }

        }

        else if(strcmp(comando, "t") == 0){
           if(!comando_t(linha, fFamily, fWeight, fSize, formas)){
                fprintf(stderr, "Erro ao processar o comando 't'\n");
           }
        }

        else if (strcmp(comando, "ts") == 0){
            if(!comando_ts(linha)){
                fprintf(stderr, "Erro ao processar o comando 'ts'\n");
            }
        }
    }

    fclose(fp);

    return true;
}

/* Comandos .svg */

static bool comando_inp(const char* linha, FILA poligonos, FILA formas){
    int poligono_id, forma_id;
    if(sscanf(linha, "%*s %d %d", poligono_id, forma_id) != 2) return false;

    FILA p_copia = copia_fila(poligonos);
    POLIGONO p = getPoligono(poligonos, poligono_id);
    
}