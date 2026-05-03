#include "unity.h"
#include "leitura.h"
#include "sistema.h"
#include "lista.h"
#include "forma.h"
#include "circulo.h"
#include "poligono.h"
#include "retangulo.h"
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

void teste_leitura_geo(void) {
    const char* nome_geo = "teste_leitura.geo";
    FILE* fp = fopen(nome_geo, "w");
    fprintf(fp, "c 10 50.0 50.0 20.0 blue red\n");
    fprintf(fp, "r 20 10.0 10.0 100.0 200.0 green yellow\n");
    fprintf(fp, "ts sans-serif bold 14.0\n");
    fprintf(fp, "t 30 0.0 0.0 black black i Texto de Teste\n");
    fclose(fp);

    SISTEMA s = cria_sistema("log_leitura.txt", "saida_geo.svg", NULL);
    
    bool sucesso = leitura_geo(nome_geo, s);
    TEST_ASSERT_TRUE(sucesso);

    LISTA l = get_formas(s);
    TEST_ASSERT_EQUAL_INT(3, tamanho_lista(l));

    FORMA forma = getItem_lista(l, 0);
    TEST_ASSERT_EQUAL_CHAR('t', getTipo_forma(forma));
    TEST_ASSERT_EQUAL_INT(30, getId_forma(forma));

    char family[32], weight[32];
    double size;
    get_estilo_texto(s, family, weight, &size);
    TEST_ASSERT_EQUAL_STRING("sans-serif", family);
    TEST_ASSERT_EQUAL_STRING("bold", weight);
    TEST_ASSERT_EQUAL_DOUBLE(14.0, size);

    fecha_sistema(&s);
    
    remove(nome_geo);
    remove("log_leitura.txt");
    remove("saida_geo.svg");
}

void teste_leitura_qry_inp_rmp(void) {
    SISTEMA s = cria_sistema("log_teste.txt", "geo.svg", "qry.svg");
    CIRCULO c = cria_circulo(10, 50.0, 50.0, 5.0, "blue", "red");
    insere_lista(get_formas(s), cria_forma('c', c));

    const char* qry = "teste_pol.qry";
    FILE* f = fopen(qry, "w");
    fprintf(f, "inp 1 10\n"); 
    fprintf(f, "rmp 1\n");    
    fclose(f);

    leitura_qry(qry, s);

    POLIGONO p = getPoligono(get_poligonos(s), 1);
    TEST_ASSERT_NOT_NULL(p);
    TEST_ASSERT_TRUE(vazia_fila(getVertices_poligono(p))); 

    fecha_sistema(&s);
    remove("log_Teste.txt");
    remove("geo.svg");
    remove("qry.svg");
    remove(qry);
}

void teste_leitura_qry_pol_clp(void) {
    SISTEMA s = cria_sistema("log_teste.txt", "geo.svg", "qry.svg");
    POLIGONO p = cria_poligono(1);
    insere_vertice(p, cria_vertice(0,0));
    insere_vertice(p, cria_vertice(10,10));
    insere_fila(get_poligonos(s), p);

    const char* qry = "teste_desenho.qry";
    FILE* f = fopen(qry, "w");
    fprintf(f, "pol 1 1000 1.0 black green\n"); 
    fprintf(f, "clp 1\n");                    
    fclose(f);

    leitura_qry(qry, s);

    TEST_ASSERT_FALSE(vazia_lista(get_formas(s)));
    TEST_ASSERT_TRUE(vazia_fila(getVertices_poligono(p)));

    fecha_sistema(&s);
    remove("log_Teste.txt");
    remove("geo.svg");
    remove("qry.svg");
    remove(qry);
}

void teste_leitura_qry_sel_mcs(void) {
    SISTEMA s = cria_sistema("log_teste.txt", "geo.svg", "qry.svg");
    RETANGULO r = cria_retangulo(1, 20, 20, 5, 5, "black", "white");
    insere_lista(get_formas(s), cria_forma('r', r));

    const char* qry = "teste_sel.qry";
    FILE* f = fopen(qry, "w");
    fprintf(f, "sel 10 10 40 40\n");     
    fprintf(f, "mcs 5 5 blue yellow\n"); 
    fclose(f);

    leitura_qry(qry, s);

    FORMA figura = getItem_lista(get_formas(s), 0);
    double x, y;
    getAncora_forma(figura, &x, &y);
    
    TEST_ASSERT_EQUAL_FLOAT(25.0, x); 
    TEST_ASSERT_EQUAL_FLOAT(25.0, y); 

    fecha_sistema(&s);
    remove("log_Teste.txt");
    remove("geo.svg");
    remove("qry.svg");
    remove(qry);
}

void teste_leitura_qry_dels(void) {
    SISTEMA s = cria_sistema("log_teste.txt", "geo.svg", "qry.svg");
    RETANGULO r = cria_retangulo(1, 20, 20, 5, 5, "black", "white");
    insere_lista(get_formas(s), cria_forma('r', r));

    const char* qry = "teste_del.qry";
    FILE* f = fopen(qry, "w");
    fprintf(f, "sel 0 0 100 100\n");
    fprintf(f, "dels\n");            
    fclose(f);

    leitura_qry(qry, s);

    TEST_ASSERT_TRUE(vazia_lista(get_formas(s)));
    TEST_ASSERT_FALSE(vazia_lista(get_formas_aux(s)));

    fecha_sistema(&s);
    remove("log_Teste.txt");
    remove("geo.svg");
    remove("qry.svg");
    remove(qry);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_leitura_geo);
    RUN_TEST(teste_leitura_qry_inp_rmp);
    RUN_TEST(teste_leitura_qry_pol_clp);
    RUN_TEST(teste_leitura_qry_sel_mcs);
    RUN_TEST(teste_leitura_qry_dels);

    return UNITY_END();
}