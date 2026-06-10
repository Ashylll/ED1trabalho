#include "svg.h"
#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

void svg_begin(FILE *fp){
    if (!fp) return;

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp,
        "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" "
        "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
    );
}

void svg_end(FILE *fp){
    if (!fp) return;
    
    fprintf(fp, "</svg>\n");
}

static void svg_escreve_forma(FILE *fp, Forma f){
    if (!fp || !f) return;

    char tipo = get_tipo_forma(f);
    void *hand = get_handle_forma(f);

    switch (tipo){
        case 'c': { 
            double x = get_x_circulo(hand);
            double y = get_y_circulo(hand);
            double r = getR_circulo(hand);
            const char *corb = get_corb_circulo(hand);
            const char *corp = get_corp_circulo(hand);

            double opacidade = 0.6;

            fprintf(fp,
            "<circle style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" r=\"%.2f\" cy=\"%.2f\" cx=\"%.2f\" />\n", corp, opacidade, corb, r, y, x);

            break;
        }

        case 'r': { 
            double x = get_x_retangulo(hand);
            double y = get_y_retangulo(hand);
            double w = getW_retangulo(hand);
            double h = getH_retangulo(hand);
            const char *corb = get_corb_retangulo(hand);
            const char *corp = get_corp_retangulo(hand);

            double opacidade = 0.6;

            if (get_id_retangulo(hand) == -1){
                fprintf(fp,
            "<rect style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-dasharray:5;stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n"
            , corp, opacidade, corb, x, y, w, h);
            } else {
                fprintf(fp,
            "<rect style=\"fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:1.0\" x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" />\n"
            , corp, opacidade, corb, x, y, w, h);
            }

            break;
        }

        case 'l': {
            double x1 = get_x1_linha(hand);
            double y1 = get_y1_linha(hand);
            double x2 = get_x2_linha(hand);
            double y2 = get_y2_linha(hand);
            const char *cor = get_cor(hand);

            double opacidade = 0.8;

            fprintf(fp,
            "<line style=\"stroke:%s;stroke-width:2.0;stroke-opacity:%.1f\" x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" />\n", cor, opacidade, x1, y1, x2, y2);

            break;
        }

        case 't': {
            double x = get_x_texto(hand);
            double y = get_y_texto(hand);
            const char *corb = get_corb_texto(hand);  
            const char *corp = get_corp_texto(hand);   
            const char *txto = get_palavra_texto(hand);   
            const char *family = get_family_texto(hand);
            const char *weight = get_weight_texto(hand);
            const char a = get_posicao_ancora_texto(hand);
            const char *ancora;
            switch (a){
                case 'i': ancora = "start"; break;
                case 'm': ancora = "middle"; break;
                case 'f': ancora = "end"; break;
            }
            int size = get_size_texto(hand);

            double opacidade = 1.0;

            fprintf(fp,
                "<text style=\"text-anchor:%s;alignment-baseline:central;fill:%s;fill-opacity:%.1f;stroke:%s;stroke-width:0.7;"
                "font-family:%s;font-weight:%s;font-size:%dpx;line-height:0%%\" "
                "x=\"%.2f\" y=\"%.2f\">%s</text>\n", ancora, corp, opacidade, corb, family, weight, size, x, y, txto);
                
                break;
        }

        default:
            fprintf(stderr, "[svg_escreve_forma] tipo desconhecido: %c\n", tipo);
            break;
    }
}

bool escreve_svg(FILE *fp, Sistema s){
    if (!fp || !s) return false;

    Lista formas = get_formas(s);

    int i = 0;
    while (i < tamanho_lista(formas)){
        Forma figura = get_item_lista(formas, i);
        svg_escreve_forma(fp, figura);
        i++;
    }

    i = 0;
    Lista formas_aux = get_formas_aux(s);
    while (i < tamanho_lista(formas_aux)){
        Forma figura = get_item_lista(formas_aux, i);
        svg_escreve_forma(fp, figura);
        i++;
    }

    return true;
}