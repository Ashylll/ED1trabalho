#include "leitura.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "fila.h"
#include "lista.h"
#include "poligono.h"
#include "sistema.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* Comandos .geo */

static bool comando_c(const char *linha, SISTEMA s){
    int i; 
    double x, y, r;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &i, &x, &y, &r, corb, corp) != 6) return false;

    CIRCULO c = cria_circulo(i, x, y, r, corb, corp);
    if (!c) return false;

    FORMA f = cria_forma('c', c);
    insere_lista(get_formas(s), f);

    return true;    
}

static bool comando_r(const char *linha, SISTEMA s){
    int i;
    double x, y, w, h;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &i, &x, &y, &w, &h, corb, corp) != 7) return false;
    
    RETANGULO r = cria_retangulo(i, x, y, w, h, corb, corp);
    if (!r) return false;

    FORMA f = cria_forma('r', r);
    insere_lista(get_formas(s), f);

    return true;
}

static bool comando_l(const char *linha, SISTEMA s){
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
    insere_lista(get_formas(s), f);

    return true;

}

static bool comando_t(const char *linha, SISTEMA s){
    int i;
    double x, y;
    char corb[32], corp[32], ancora, txto[512];

    char family[32], weight[32];
    double size;

    if(sscanf(linha, "%*s %d %lf %lf %31s %31s %c %[^\n]", &i, &x, &y, corb, corp, &ancora, txto) < 7) return false;
    
    TEXTO t = cria_texto(i, x, y, corb, corp, ancora, txto);
    if (!t) return false;

    get_estilo_texto(s, family, weight, &size);
    
    muda_estilo(t, family, weight, size);
    FORMA f = cria_forma('t', t);
    insere_lista(get_formas(s), f);
    
    return true;
}

static bool comando_ts(const char *linha, SISTEMA s){
    char novo_family[32], novo_weight[8];
    double novo_size;

    if (sscanf(linha, "%*s %31s %7s %lf", novo_family, novo_weight, &novo_size) != 3) return false;

    const char *wt  = converter_weight(novo_weight);

    set_estilo_texto(s, novo_family, wt, novo_size);

    return true;
}

bool ler_geo(const char *path_geo, SISTEMA s){
    FILE *fp = fopen(path_geo, "r");
    if(!fp) return false;

    char linha[1024], comando[8];

    while (fgets(linha, sizeof linha, fp)){
        if(sscanf(linha, "%7s", comando) != 1) continue;
        if(comando[0] == '#') continue;

        if (strcmp(comando, "c") == 0){
            if(!comando_c(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'c'\n");
            }
        }

        else if (strcmp(comando, "r") == 0){
            if(!comando_r(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'r'\n");
            }
        }

        else if (strcmp(comando, "l") == 0){
            if(!comando_l(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'l'\n");
            }

        }

        else if(strcmp(comando, "t") == 0){
           if(!comando_t(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 't'\n");
           }
        }

        else if (strcmp(comando, "ts") == 0){
            if(!comando_ts(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'ts'\n");
            }
        }
    }

    fclose(fp);

    return true;
}

/* Comandos .qry */

static bool comando_inp(const char* linha, SISTEMA s){
    LISTA formas = get_formas(s);
    FILA poligonos = get_poligonos(s);
    FILE* arquivoTxt = get_arquivo_txt(s);

    int poligono_id, forma_id;
    if(sscanf(linha, "%*s %d %d", &poligono_id, &forma_id) != 2) return false;

    POLIGONO p = getPoligono(poligonos, poligono_id);
    if(!p){
        p = cria_poligono(poligono_id);
        insere_fila(poligonos, p);
    }

    double x, y;
    FORMA figura = getItem_lista(formas, forma_id);
    getAncora_forma(figura, &x, &y);
    VERTICE v = cria_vertice(x, y);
    insere_vertice(p, v);

    fprintf(arquivoTxt, "[*] inp %d %d\n", poligono_id, forma_id);
    fprintf(arquivoTxt, "Coordenada inserida: (%.2f, %.2f)\n", x, y);
    reporta_forma(figura, arquivoTxt);
    
    return true;
}

static bool comando_rmp(const char* linha, SISTEMA s){
    FILA poligonos = get_poligonos(s);
    FILE* arquivoTxt = get_arquivo_txt(s);

    int poligono_id;
    if(sscanf(linha, "%*s %d", &poligono_id) != 1) return false;

    POLIGONO p = getPoligono(poligonos, poligono_id);
    double x, y;
    remove_vertice(p, &x, &y);

    fprintf(arquivoTxt, "[*] rmp %d\n", poligono_id);
    fprintf(arquivoTxt, "Vértice removido: (%.2f, %.2f)\n\n", x, y);

    return true;
}

static bool comando_pol(const char* linha, SISTEMA s){
    FILA poligonos = get_poligonos(s);
    LISTA formas = get_formas(s);

    int poligono_id, id_sequencial;
    double d;
    char corb[32], corp[32];
    if(sscanf(linha, "%*s %d %d %lf %s %s", &poligono_id, &id_sequencial, &d, corb, corp) != 5) return false;

    POLIGONO p = getPoligono(poligonos, poligono_id);
    if (!p) return false;

    desenha_poligono(p, &id_sequencial, corb, formas);
    hachura_poligono(p, &id_sequencial, d, corp, formas);

    return true;
}

static bool comando_clp(const char *linha, SISTEMA s){
    FILA poligonos = get_poligonos(s);

    int poligono_id;
    if(sscanf(linha, "%*s %d", &poligono_id) != 1) return false;

    POLIGONO p = getPoligono(poligonos, poligono_id);
    FILA vertices = getVertices_poligono(p);

    ITEM remove;
    while(remove_fila(vertices, &remove)){
        free(remove);
    }

    return true;
}

static bool comando_sel(const char *linha, SISTEMA s){
    double x, y, w, h;
    if(sscanf(linha, "%*s %lf %lf %lf %lf", &x, &y, &w, &h) != 4) return false;

    LISTA formas = get_formas(s);
    FILA selecionadas = get_selecionadas(s);
    FILE *arquivoTxt = get_arquivo_txt(s);
    LISTA formas_aux = get_formas_aux(s);

    RETANGULO ret = cria_retangulo(-1, x, y, w, h, "red", "none");
    FORMA retangulo_sel = cria_forma('r', retangulo_sel);
    insere_lista(formas_aux, retangulo_sel);

    fprintf(arquivoTxt, "[*] sel %lf %lf %lf %lf \nFormas selecionadas:\n\n", x, y, w, h);
    for (int i = 0; i < tamanho_lista(formas); i++){
        FORMA b = getItem_lista(formas, i);
        if (sobrepoe_retangulo(retangulo_sel, b)){
            insere_fila(selecionadas, b);

            double xc, yc;
            getAncora_forma(b, &xc, &yc);
            CIRCULO circ = cria_circulo(-2, xc, yc, 1.0, "red", "none");
            FORMA circulo_sel = cria_forma('c', circ);
            insere_lista(formas_aux, circulo_sel);

            fprintf(arquivoTxt, "Id: %d\nTipo: %c\n\n", getId_forma(b), getTipo_forma(b));
        }
    }

    return true;
}

static bool comando_dels(const char *linha, SISTEMA s) {
    LISTA formas = get_formas(s);
    FILA selecionadas = get_selecionadas(s);
    FILE *arquivoTxt = get_arquivo_txt(s);
    LISTA formas_aux = get_formas_aux(s);

    fprintf(arquivoTxt, "[*] dels\nFormas removidas:\n\n");

    if (vazia_fila(selecionadas)) {
    fprintf(arquivoTxt, "Nenhuma forma selecionada\n\n");

    return true;
    } 

    while (!vazia_fila(selecionadas)) {
        FORMA f;
        remove_fila(selecionadas, &f);
        
        reporta_forma(f, arquivoTxt);

        double ax, ay;
        getAncora_forma(f, &ax, &ay);
        TEXTO x = cria_texto(-3, ax, ay, "red", "red", 'm', "x");
        muda_estilo(x, "sans-serif", "bold", 12.0);
        FORMA marca_x = cria_forma('t', x);
        insere_lista(formas_aux, marca_x);

        remove_lista(formas, f);
        libera_forma(&f); 
    }

    return true;
}

static bool comando_mcs(const char *linha, SISTEMA s){
    FILA selecionadas = get_selecionadas(s);

    double dx, dy;
    char corb[32], corp[32];
    if(sscanf(linha, "%*s %lf %lf %s %s", &dx, &dy, corb, corp) != 4) return false;

    FILA selecionadas_copia = copia_fila(selecionadas);
    while (!vazia_fila(selecionadas_copia)){
        FORMA f;
        remove_fila(selecionadas_copia, &f);

        desloca_forma(f, dx, dy);
        setCORB_forma(f, corb);
        setCORP_forma(f, corp);
    }

    libera_fila(&selecionadas_copia);

    return true;
}                                 

bool leitura_qry(const char* path_qry, SISTEMA s){
    FILE *fp = fopen(path_qry, "r");
    if (!fp) return false;

    char linha[1024], comando [8];

    while (fgets(linha, sizeof linha, fp)){
        if (sscanf(linha, "%7s", comando) != 1) continue;
        if (comando[0] == '#') continue;

        if (strcmp(comando, "inp") == 0){
            if (!comando_inp(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'inp'\n");
                return false;
            }
        }

        if (strcmp(comando, "rmp") == 0){
            if (!comando_rmp(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'rmp'\n");
                return false;
            }
        }

        if (strcmp(comando, "pol") == 0){
            if (!comando_pol(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'pol'\n");
                return false;
            }
        }

        if (strcmp(comando, "clp") == 0){
            if (!comando_clp(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'clp'\n");
                return false;
            }
        }

        if (strcmp(comando, "sel") == 0){
            if (!comando_sel(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'sel'\n");
                return false;
            }
        }

        if (strcmp(comando, "dels") == 0){
            if (!comando_dels(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'dels'\n");
                return false;
            }
        }

        if (strcmp(comando, "mcs") == 0){
            if (!comando_mcs(linha, s)){
                fprintf(stderr, "Erro ao processar o comando 'mcs'\n");
                return false;
            }
        }
    }

    fclose(fp);

    return true;
}