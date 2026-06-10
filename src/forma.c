#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct StForma{
    char tipo;
    void* handle;
} StForma;

Forma cria_forma(char tipo, void* handle){
    if (!handle || (tipo != 'c' && tipo != 'r' && tipo != 't' && tipo != 'l')) return NULL;

    StForma* forma = malloc(sizeof(StForma));
    if (!forma) return NULL;

    forma->tipo = tipo;
    forma->handle = handle;

    return forma;
}

void libera_forma(Forma *f){
    if (!f || !*f) return;
    StForma *forma = (StForma*)*f;

    void *h = forma->handle;
    switch (forma->tipo){
        case 'c': libera_circulo((Circulo*)&h); break;
        case 'r': libera_retangulo((Retangulo*)&h); break;
        case 't': libera_texto((Texto*)&h); break;
        case 'l': libera_linha((Linha*)&h); break;
    }
    
    free(forma);
    *f = NULL;
}

int get_id_forma(Forma f){
    StForma *forma = (StForma*)f;

    switch (forma->tipo){
        case 'c': return get_id_circulo(forma->handle);
        case 'r': return get_id_retangulo(forma->handle);
        case 't': return get_id_texto(forma->handle);
        case 'l': return get_id_linha(forma->handle); 
        default: return -100;
    }
}

char get_tipo_forma(Forma f){
    StForma* forma = (StForma*)f;

    return forma->tipo;
}

void* get_handle_forma(Forma f){
    if (!f) return NULL;
    StForma* forma = (StForma*)f;

    return forma->handle;
}

bool get_ancora_forma(Forma f, double *x, double *y){
    if (!f || !x || !y) return false;
    StForma* forma = (StForma*)f;

    switch (forma->tipo){
        case 'c': *x = get_x_circulo(forma->handle); *y = get_y_circulo(forma->handle); break;
        case 'r': *x = get_x_retangulo(forma->handle); *y = get_y_retangulo(forma->handle); break;
        case 't': *x = get_x_texto(forma->handle); *y = get_y_texto(forma->handle); break;
        case 'l': *x = get_x1_linha(forma->handle); *y = get_y1_linha(forma->handle); break;
        default: return false;
    }

    return true;
}

bool set_ancora_forma(Forma f, double x, double y){
    if (!f) return false;

    StForma* forma = (StForma*)f;

    switch (forma->tipo){
        case 'c': return set_x_circulo(forma->handle, x) && set_y_circulo(forma->handle, y);
        case 'r': return set_x_retangulo(forma->handle, x) && set_y_retangulo(forma->handle, y);
        case 't': return set_x_texto(forma->handle, x) && set_y_texto(forma->handle, y);
        case 'l': return set_ancora_linha(forma->handle, x, y);
        
        default: return false;
    }
}

void set_corb_forma(Forma f, char* corb){
    if (!f || !corb) return;

    Forma figura = get_handle_forma(f);
    switch (get_tipo_forma(f)){
        case 'c': {
            set_corb_circulo(figura, corb);
            break;
        }
        case 'r': {
            set_corb_retangulo(figura, corb);
            break;
        }
        case 't': {
            set_corb_texto(figura, corb);
            break;
        }
        case 'l': {
            set_cor_linha(figura, corb);
            break;
        }
    }
    return;
}

void set_corp_forma(Forma f, char* corp){
    if (!f || !corp) return;

    Forma figura = get_handle_forma(f);
    switch (get_tipo_forma(f)){
        case 'c': {
            set_corp_circulo(figura, corp);
            break;
        }
        case 'r': {
            set_corp_retangulo(figura, corp);
            break;
        }
        case 't': {
            set_corp_texto(figura, corp);
            break;
        }
    }
    return;
}

bool desloca_forma(Forma f, double dx, double dy){
    if (!f) return false;

    double x, y;

    if (!get_ancora_forma(f, &x, &y)) return false;

    return set_ancora_forma(f, x + dx, y + dy);
}

void reporta_forma(Forma f, FILE *arquivoTxt){
    if (!f || !arquivoTxt) return;

    char tipo = get_tipo_forma(f);

    switch (tipo){
        case 'c': {
            Circulo c = get_handle_forma(f);
            fprintf(arquivoTxt, "Circulo\nId: %d\nÂncora (coordenadas): (%.2lf, %.2lf)\nRaio: %.2lf\nCor de borda: %s\nCor de preenchimento: %s\n\n"
            , get_id_circulo(c), get_x_circulo(c), get_y_circulo(c), getR_circulo(c), get_corb_circulo(c), get_corp_circulo(c));

            break;
        }

        case 'r': {
            Retangulo r = get_handle_forma(f);
            fprintf(arquivoTxt, "Retângulo\nId: %d\nÂncora (coordenadas): (%.2lf, %.2lf)\nLargura: %.2lf\nAltura: %.2lf\nCor de borda: %s\nCor de preenchimento: %s\n\n"
            , get_id_retangulo(r), get_x_retangulo(r), get_y_retangulo(r), getW_retangulo(r), getH_retangulo(r), get_corb_retangulo(r), get_corp_retangulo(r));

            break;
        }

        case 't': {
            Texto t = get_handle_forma(f);
            char a = get_posicao_ancora_texto(t);
            char* ancora = "desconhecido";
            switch (a){
                case 'i': {
                    ancora = "início";
                    break;
                }
                case 'm': {
                    ancora = "meio";
                    break;
                }
                case 'f': {
                    ancora = "fim";
                }
            }

            fprintf(arquivoTxt, "Texto\nId: %d\nÂncora (coordenadas): (%.2lf, %.2lf)\nCor de borda: %s\nCor de preenchimento: %s\nPosição da âncora: %s\nConteúdo: %s\n\n"
            , get_id_texto(t), get_x_texto(t), get_y_texto(t), get_corb_texto(t), get_corp_texto(t), ancora, get_palavra_texto(t));

            break;
        }

        case 'l': {
            Linha l = get_handle_forma(f);
            fprintf(arquivoTxt, "Linha\nId: %d\nCoordenadas:\n  - Âncora (x1, y1): (%.2lf, %.2lf)\n - (x2, y2): (%.2lf, %.2lf)\nCor: %s\n\n"
            , get_id_linha(l), get_x1_linha(l), get_y1_linha(l), get_x2_linha(l), get_y2_linha(l), get_cor(l));
        }
    }
}

double dist_ponto_segmento(double px, double py, double x1, double y1, double x2, double y2){
    // Define a equação geral da reta (Ax + By + C = 0) a partir dos pontos (x1,y1) e (x2,y2)
    // vetor direcional da reta -> (A,B) = (x2 - x1, y2 - y1)
    // vetor normal (projeção ortogonal) -> (A,B) = (y1 - y2, x2 - x1)
    
    double A = y1 - y2;
    double B = x2 - x1;
    double C = x1*y2 - x2*y1;

    double denom = sqrt(A*A + B*B);
    if (denom < 1e-18)  return hypot(px - x1, py - y1); // Segmento degenerado tratado como ponto
    
    // Distância do ponto à reta -> |Apx + Bpy + C| / sqrt(A² + B²)
    double dist_reta = fabs(A*px + B*py + C) / denom; 

    // Projeção escalar normalizada -> t = w . v / ||v||
    double vx = x2 - x1, vy = y2 - y1;
    double t = ((px - x1)*vx + (py - y1)*vy) / (vx*vx + vy*vy);

    // Se t ∈ [0,1], a menor distância é perpendicular à reta
    if (t >= 0.0 && t <= 1.0) return dist_reta; 

    // Projeção fora -> checa distância até as extremidades
    double d1 = hypot(px - x1, py - y1);
    double d2 = hypot(px - x2, py - y2);

    return fmin(d1, d2);
}

static inline bool ponto_no_retangulo(double x, double y, double xR, double yR, double w, double h){
    const double eps = 1e-9;
    return (xR - eps <= x && x <= xR + w + eps) && (yR - eps <= y && y <= yR + h + eps);
}

static bool seg_intersect(double x1, double y1,double x2, double y2, double x3, double y3, double x4, double y4){
    // Segmento 1 -> P(t) = P1 + t(P2 - P1)
    // Segmento 2 -> P(u) = P3 + u(P4 - P3)
    // Instersecção -> P(t) = P(u), sistema com determinante D (regra de Crammer)
    double D = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    
    const double eps = 1e-9;
    if (fabs(D) < eps) {
        double A = y1 - y2;
        double B = x2 - x1;
        double C = x1*y2 - x2*y1;

        if (fabs(A*x3 + B*y3 + C) > eps) return false; // Verifica se são paralelas

        // Verifica se intervalos se tocam (colinearidade)
        bool overlapX = fmax(fmin(x1, x2), fmin(x3, x4)) <= fmin(fmax(x1, x2), fmax(x3, x4)) + eps;
        bool overlapY = fmax(fmin(y1, y2), fmin(y3, y4)) <= fmin(fmax(y1, y2), fmax(y3, y4)) + eps;

        return overlapX && overlapY;
    }

    // t = Dt/D; u = Du/D
    double t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4)) / D;
    double u = ((x1 - x3)*(y1 - y2) - (y1 - y3)*(x1 - x2)) / D;
    // se t ∈ [0,1], o ponto pertence ao segmento 1; se u ∈ [0,1], o ponto pertence ao segmento 2 

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

static bool sob_rc(Forma a, Forma b){
    StForma *circulo = (StForma*)a;
    StForma *retangulo = (StForma*)b;

    double xC = get_x_circulo(circulo->handle);
    double yC = get_y_circulo(circulo->handle);
    double rC = getR_circulo(circulo->handle);

    double xR = get_x_retangulo(retangulo->handle);
    double yR = get_y_retangulo(retangulo->handle);
    double wR = getW_retangulo(retangulo->handle);
    double hR = getH_retangulo(retangulo->handle);

    double nx = fmax(xR, fmin(xC, xR + wR));
    double ny = fmax(yR, fmin(yC, yR + hR));

    double dx = nx - xC;
    double dy = ny - yC;

    return hypot(dx, dy) <= rC;
}

static bool sob_rr(Forma a, Forma b){
    StForma *retanguloA = (StForma*)a, *retanguloB = (StForma*)b;

    double xA = get_x_retangulo(retanguloA->handle);
    double yA = get_y_retangulo(retanguloA->handle);
    double wA = getW_retangulo(retanguloA->handle);
    double hA = getH_retangulo(retanguloA->handle);

    double xB = get_x_retangulo(retanguloB->handle);
    double yB = get_y_retangulo(retanguloB->handle);
    double wB = getW_retangulo(retanguloB->handle);
    double hB = getH_retangulo(retanguloB->handle);

    const double eps = 1e-9;
    bool separado =
    (xA + wA < xB - eps) || (xB + wB < xA - eps) ||
    (yA + hA < yB - eps) || (yB + hB < yA - eps);

    return !separado; 
}

static bool sob_rl(Forma a, Forma b){
    StForma *retangulo = (StForma*)a, *linha = (StForma*)b;

    double xR = get_x_retangulo(retangulo->handle);
    double yR = get_y_retangulo(retangulo->handle);
    double wR = getW_retangulo(retangulo->handle);
    double hR = getH_retangulo(retangulo->handle);

    double x1 = get_x1_linha(linha->handle);
    double y1 = get_y1_linha(linha->handle);
    double x2 = get_x2_linha(linha->handle);
    double y2 = get_y2_linha(linha->handle);

    if (ponto_no_retangulo(x1, y1, xR, yR, wR, hR) || ponto_no_retangulo(x2, y2, xR, yR, wR, hR)) return true;

    double ax = xR,      ay = yR;
    double bx = xR + wR, by = yR;
    double cx = xR + wR, cy = yR + hR;
    double dx = xR,      dy = yR + hR;

    if (seg_intersect(x1, y1, x2, y2, ax, ay, bx, by)) return true;
    if (seg_intersect(x1, y1, x2, y2, bx, by, cx, cy)) return true;
    if (seg_intersect(x1, y1, x2, y2, cx, cy, dx, dy)) return true; 
    if (seg_intersect(x1, y1, x2, y2, dx, dy, ax, ay)) return true; 

    return false;
}

static bool sob_rt(Forma a, Forma b){
    StForma *retangulo = (StForma*)a;  
    StForma *texto = (StForma*)b;

    double xR = get_x_retangulo(retangulo->handle);
    double yR = get_y_retangulo(retangulo->handle);
    double wR = getW_retangulo(retangulo->handle);
    double hR = getH_retangulo(retangulo->handle);

    double xT = get_x_texto(texto->handle);
    double yT = get_y_texto(texto->handle);
    const char *txt = get_palavra_texto(texto->handle);
    char ancora = get_posicao_ancora_texto(texto->handle);

    double comprimento = 10.0 * (txt ? strlen(txt) : 0);
    double x1, y1 = yT, x2, y2 = yT;

    if (ancora == 'i'){        
        x1 = xT;
        x2 = xT + comprimento;
    }
    else if (ancora == 'f'){     
        x1 = xT - comprimento;
        x2 = xT;
    }
    else {                      
        x1 = xT - comprimento / 2.0;
        x2 = xT + comprimento / 2.0;
    }

    if (ponto_no_retangulo(x1, y1, xR, yR, wR, hR) || ponto_no_retangulo(x2, y2, xR, yR, wR, hR)) return true;

    double ax = xR,      ay = yR;
    double bx = xR + wR, by = yR;
    double cx = xR + wR, cy = yR + hR;
    double dx = xR,      dy = yR + hR;

    if (seg_intersect(x1, y1, x2, y2, ax, ay, bx, by)) return true;
    if (seg_intersect(x1, y1, x2, y2, bx, by, cx, cy)) return true;
    if (seg_intersect(x1, y1, x2, y2, cx, cy, dx, dy)) return true; 
    if (seg_intersect(x1, y1, x2, y2, dx, dy, ax, ay)) return true; 

    return false;
}

bool sobrepoe_retangulo(Forma r, Forma b){
    StForma *retangulo = (StForma*)r;
    StForma *B = (StForma*)b;

    
    switch (B->tipo){
        case 'c': return sob_rc(retangulo, b);
        case 'r': return sob_rr(retangulo, b);
        case 'l': return sob_rl(retangulo, b);
        case 't': return sob_rt(retangulo, b);
        default: break;
    }

    return false;
}