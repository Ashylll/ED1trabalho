#include "sistema.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_e_fecha_sistema(void) {
    const char *log = "t_log.txt";
    const char *geo = "t_geo.svg";
    const char *qry = "t_qry.svg";

    SISTEMA s = cria_sistema(log, geo, qry);
    TEST_ASSERT_NOT_NULL(s);

    TEST_ASSERT_NOT_NULL(get_formas(s));
    TEST_ASSERT_NOT_NULL(get_poligonos(s));
    TEST_ASSERT_NOT_NULL(get_selecionadas(s));
    TEST_ASSERT_NOT_NULL(get_formas_aux(s));

    TEST_ASSERT_NOT_NULL(get_arquivo_txt(s));
    TEST_ASSERT_NOT_NULL(get_svg_geo(s));
    TEST_ASSERT_NOT_NULL(get_svg_qry(s));

    fecha_sistema(&s);
    TEST_ASSERT_NULL(s);

    remove(log);
    remove(geo);
    remove(qry);
}

void teste_sistema_qry_opcional(void) {
    SISTEMA s = cria_sistema("log.txt", "geo.svg", NULL);
    TEST_ASSERT_NOT_NULL(s);

    TEST_ASSERT_NULL(get_svg_qry(s));
    TEST_ASSERT_NOT_NULL(get_svg_geo(s));

    fecha_sistema(&s);
    TEST_ASSERT_NULL(s);

    remove("log.txt");
    remove("geo.svg");
}

void teste_estilo_texto_sistema(void) {
    SISTEMA s = cria_sistema("l.txt", "g.svg", NULL);
    
    char family[32], weight[32];
    double size;

    get_estilo_texto(s, family, weight, &size);
    TEST_ASSERT_EQUAL_STRING("sans-serif", family);
    TEST_ASSERT_EQUAL_STRING("normal", weight);
    TEST_ASSERT_EQUAL_DOUBLE(12.0, size);

    set_estilo_texto(s, "Arial", "bold", 15.5);
    get_estilo_texto(s, family, weight, &size);
    
    TEST_ASSERT_EQUAL_STRING("Arial", family);
    TEST_ASSERT_EQUAL_STRING("bold", weight);
    TEST_ASSERT_EQUAL_DOUBLE(15.5, size);

    fecha_sistema(&s);
    remove("l.txt");
    remove("g.svg");
}

void teste_arquivos_estao_abertos_para_escrita(void) {
    SISTEMA s = cria_sistema("l.txt", "g.svg", NULL);
    
    FILE *f_txt = get_arquivo_txt(s);
    int resultado = fprintf(f_txt, "Teste de escrita\n");
    TEST_ASSERT_TRUE(resultado > 0);

    fecha_sistema(&s);
    remove("l.txt");
    remove("g.svg");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_e_fecha_sistema);
    RUN_TEST(teste_sistema_qry_opcional);
    RUN_TEST(teste_estilo_texto_sistema);
    RUN_TEST(teste_arquivos_estao_abertos_para_escrita);
    return UNITY_END();
}