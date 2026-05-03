#include "svg.h"
#include "sistema.h"
#include "forma.h"
#include "circulo.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void teste_escreve_svg(void) {
    const char* nome_arq = "svg_teste.svg";
    SISTEMA s = cria_sistema("log.txt", nome_arq, NULL);
    TEST_ASSERT_NOT_NULL(s);

    CIRCULO c = cria_circulo(1, 100.0, 100.0, 20.0, "pink", "pink");
    FORMA f = cria_forma('c', c);
    LISTA l = get_formas(s);
    insere_lista(l, f);

    FILE *fp = get_svg_geo(s);
    bool resultado = escreve_svg(fp, s);
    TEST_ASSERT_TRUE(resultado);
    fecha_sistema(&s); 

    FILE *checa = fopen(nome_arq, "r");
    TEST_ASSERT_NOT_NULL(checa);

    char linha[256];
    bool tem_cabecalho = false;
    bool tem_circulo = false;
    bool tem_rodape = false;
    while (fgets(linha, sizeof(linha), checa)) {
        if (strstr(linha, "<?xml")) tem_cabecalho = true;
        if (strstr(linha, "<circle")) tem_circulo = true;
        if (strstr(linha, "</svg>")) tem_rodape = true;

    }

    TEST_ASSERT_TRUE(tem_cabecalho);
    TEST_ASSERT_TRUE(tem_circulo);
    TEST_ASSERT_TRUE(tem_rodape);

    remove(nome_arq);
    remove("log.txt");
    fclose(checa);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_escreve_svg);
    return UNITY_END();
}