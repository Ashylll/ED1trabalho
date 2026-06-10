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
#include <string.h>


const char* traduz_tipo(char tipo) {
    switch(tipo) {
        case 'r': return "retângulo";
        case 'c': return "circulo";
        case 'l': return "linha";
        case 't': return "triângulo";
        default:  return "desconhecido";
    }
}

/* Comandos .geo */

static bool comando_c(const char *linha, Sistema s){
    int i; 
    double x, y, r;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &i, &x, &y, &r, corb, corp) != 6) return false;

    Circulo c = cria_circulo(i, x, y, r, corb, corp);
    if (!c) return false;

    Forma f = cria_forma('c', c);
    insere_lista(get_formas(s), f);

    return true;    
}

static bool comando_r(const char *linha, Sistema s){
    int i;
    double x, y, w, h;
    char corb[32], corp[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &i, &x, &y, &w, &h, corb, corp) != 7) return false;
    
    Retangulo r = cria_retangulo(i, x, y, w, h, corb, corp);
    if (!r) return false;

    Forma f = cria_forma('r', r);
    insere_lista(get_formas(s), f);

    return true;
}

static bool comando_l(const char *linha, Sistema s){
    int i;
    double x1, y1, x2, y2;
    char cor[32];

    if(sscanf(linha, "%*s %d %lf %lf %lf %lf %31s", &i, &x1, &y1, &x2, &y2, cor) != 6) return false;

    Linha l;
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

    Forma f = cria_forma('l', l);
    insere_lista(get_formas(s), f);

    return true;

}

static bool comando_t(const char *linha, Sistema s){
    int i;
    double x, y;
    char corb[32], corp[32], ancora, txto[512];

    char family[32], weight[32];
    double size;

    if(sscanf(linha, "%*s %d %lf %lf %31s %31s %c %[^\n]", &i, &x, &y, corb, corp, &ancora, txto) < 7) return false;
    
    Texto t = cria_texto(i, x, y, corb, corp, ancora, txto);
    if (!t) return false;

    get_estilo_texto(s, family, weight, &size);
    
    muda_estilo(t, family, weight, size);
    Forma f = cria_forma('t', t);
    insere_lista(get_formas(s), f);
    
    return true;
}

static const char* converte_weight(const char *weight){
    if (!weight) return "normal";
    if (strcmp(weight, "b+") == 0) return "bolder";
    if (strcmp(weight, "b")  == 0) return "bold";
    if (strcmp(weight, "n")  == 0) return "normal";
    if (strcmp(weight, "l")  == 0) return "lighter";
    
    return weight;
}

static bool comando_ts(const char *linha, Sistema s){
    char novo_family[32], novo_weight[8];
    double novo_size;

    if (sscanf(linha, "%*s %31s %7s %lf", novo_family, novo_weight, &novo_size) != 3) return false;

    const char *wt  = converte_weight(novo_weight);

    set_estilo_texto(s, novo_family, wt, novo_size);

    return true;
}

bool leitura_geo(const char *path_geo, Sistema s){
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

static bool comando_inp(const char* linha, Sistema s){
    Lista formas = get_formas(s);
    Fila poligonos = get_poligonos(s);
    FILE* arquivoTxt = get_arquivo_txt(s);

    int poligono_id, forma_id;
    if(sscanf(linha, "%*s %d %d", &poligono_id, &forma_id) != 2) return false;

    Poligono p = get_poligono(poligonos, poligono_id);
    if(!p){
        p = cria_poligono(poligono_id);
        insere_fila(poligonos, p);
    }

    double x, y;
    Forma figura = NULL;
    for (int i = 0; i < tamanho_lista(formas); i++) {
        Forma aux = get_item_lista(formas, i);
        if (get_id_forma(aux) == forma_id) {
            figura = aux;
            break;
        }
    }

    get_ancora_forma(figura, &x, &y);
    Vertice v = cria_vertice(x, y);
    insere_vertice(p, v);

    fprintf(arquivoTxt, "[*] inp %d %d\n", poligono_id, forma_id);
    fprintf(arquivoTxt, "Coordenada inserida: (%.2f, %.2f)\n", x, y);
    reporta_forma(figura, arquivoTxt);
    
    return true;
}

static bool comando_rmp(const char* linha, Sistema s){
    Fila poligonos = get_poligonos(s);
    FILE* arquivoTxt = get_arquivo_txt(s);

    int poligono_id;
    if(sscanf(linha, "%*s %d", &poligono_id) != 1) return false;

    Poligono p = get_poligono(poligonos, poligono_id);
    double x, y;
    remove_vertice(p, &x, &y);

    fprintf(arquivoTxt, "[*] rmp %d\n", poligono_id);
    fprintf(arquivoTxt, "Vértice removido: (%.2f, %.2f)\n\n", x, y);

    return true;
}

static bool comando_pol(const char* linha, Sistema s){
    Fila poligonos = get_poligonos(s);
    Lista formas = get_formas(s);

    int poligono_id, id_sequencial;
    double d;
    char corb[32], corp[32];
    if(sscanf(linha, "%*s %d %d %lf %s %s", &poligono_id, &id_sequencial, &d, corb, corp) != 5) return false;

    Poligono p = get_poligono(poligonos, poligono_id);
    if (!p) return false;

    desenha_poligono(p, &id_sequencial, corb, formas);
    hachura_poligono(p, &id_sequencial, d, corp, formas);

    return true;
}

static bool comando_clp(const char *linha, Sistema s){
    Fila poligonos = get_poligonos(s);

    int poligono_id;
    if(sscanf(linha, "%*s %d", &poligono_id) != 1) return false;

    Poligono p = get_poligono(poligonos, poligono_id);
    if (!p) return false;

    Fila vertices = get_vertices_poligono(p);

    double x, y;
    while(tamanho_poligono(p) > 0){
        remove_vertice(p, &x, &y);
    }

    return true;
}

static bool comando_sel(const char *linha, Sistema s){
    double x, y, w, h;
    if(sscanf(linha, "%*s %lf %lf %lf %lf", &x, &y, &w, &h) != 4) return false;

    Lista formas = get_formas(s);
    Fila selecionadas = get_selecionadas(s);
    FILE *arquivoTxt = get_arquivo_txt(s);
    Lista formas_aux = get_formas_aux(s);

    while(!vazia_fila(selecionadas)) {
        Forma remove;
        remove_fila(selecionadas, &remove);
    }

    Retangulo ret = cria_retangulo(-1, x, y, w, h, "red", "none");
    Forma retangulo_sel = cria_forma('r', ret);
    insere_lista(formas_aux, retangulo_sel);

    fprintf(arquivoTxt, "[*] sel %lf %lf %lf %lf \nFormas selecionadas:\n\n", x, y, w, h);
    for (int i = 0; i < tamanho_lista(formas); i++){
        Forma b = get_item_lista(formas, i);
        if (sobrepoe_retangulo(retangulo_sel, b)){
            insere_fila(selecionadas, b);

            double xc, yc;
            get_ancora_forma(b, &xc, &yc);
            Circulo circ = cria_circulo(-2, xc, yc, 3.4, "red", "none");
            Forma circulo_sel = cria_forma('c', circ);
            insere_lista(formas_aux, circulo_sel);

            fprintf(arquivoTxt, "Id: %d\nTipo: %s\n\n", get_id_forma(b), traduz_tipo(get_tipo_forma(b)));
        }
    }

    return true;
}

static bool comando_dels(const char *linha, Sistema s) {
    Lista formas = get_formas(s);
    Fila selecionadas = get_selecionadas(s);
    FILE *arquivoTxt = get_arquivo_txt(s);
    Lista formas_aux = get_formas_aux(s);

    fprintf(arquivoTxt, "[*] dels\nFormas removidas:\n\n");

    if (vazia_fila(selecionadas)) {
    fprintf(arquivoTxt, "Nenhuma forma selecionada\n\n");

    return true;
    } 

    while (!vazia_fila(selecionadas)) {
        Forma f;
        remove_fila(selecionadas, &f);
        
        reporta_forma(f, arquivoTxt);

        double ax, ay;
        get_ancora_forma(f, &ax, &ay);
        Texto x = cria_texto(-3, ax, ay - 0.4, "red", "red", 'm', "x");
        muda_estilo(x, "cursive", "normal", 7.6);
        Forma marca_x = cria_forma('t', x);
        insere_lista(formas_aux, marca_x);

        remove_lista(formas, f);
        libera_forma(&f); 
    }

    return true;
}

static bool comando_mcs(const char *linha, Sistema s){
    Fila selecionadas = get_selecionadas(s);

    double dx, dy;
    char corb[32], corp[32];
    if(sscanf(linha, "%*s %lf %lf %s %s", &dx, &dy, corb, corp) != 4) return false;

    Fila selecionadas_copia = copia_fila(selecionadas);
    while (!vazia_fila(selecionadas_copia)){
        Forma f;
        remove_fila(selecionadas_copia, &f);

        desloca_forma(f, dx, dy);
        set_corb_forma(f, corb);
        set_corp_forma(f, corp);
    }

    libera_fila(&selecionadas_copia);

    return true;
}                                 

bool leitura_qry(const char* path_qry, Sistema s){
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