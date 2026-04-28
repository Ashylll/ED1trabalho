#include "poligono.h"
#include "fila.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_poligono(void){
    POLIGONO p = cria_poligono(1);
    TEST_ASSERT_NOT_NULL(p);

    p = cria_poligono(0);
    TEST_ASSERT_NULL(p);

    p = cria_poligono(11);
    TEST_ASSERT_NULL(p);

    p = cria_poligono(4);
    TEST_ASSERT_NOT_NULL(p);

    libera_poligono(&p);
    TEST_ASSERT_NULL(p);
}

void teste_tamanho_poligono(void) {
    POLIGONO p = cria_poligono(1);

    TEST_ASSERT_EQUAL_INT(0, tamanho_poligono(p));

    VERTICE v1 = cria_vertice(4.4, 2.2);
    insere_vertice(p, v1);
    TEST_ASSERT_EQUAL_INT(1, tamanho_poligono(p));

    VERTICE v2 = cria_vertice(6.6, 8.8);
    insere_vertice(p, v2);
    TEST_ASSERT_EQUAL_INT(2, tamanho_poligono(p));

    libera_poligono(&p);
}

void teste_getId_poligono(void){
    POLIGONO p = cria_poligono(1);
    TEST_ASSERT_EQUAL_INT(1, getId_poligono);

    p = cria_poligono(9);
    TEST_ASSERT_EQUAL_INT(9, getId_poligono);

    libera_poligono(&p);
}

void teste_getVertices_poligono(void){
    POLIGONO p = cria_poligono(9);

    TEST_ASSERT_NOT_NULL(getVertices_poligono(p));

    VERTICE v1 = cria_vertice(2.2, 8.8);
    VERTICE v2 = cria_vertice(4.4, 6.8);
    insere_vertice(p, v1);
    insere_vertice(p, v2);

    FILA vertices = getVertices_poligono(p);
    TEST_ASSERT_EQUAL_INT(2, tamanho_fila(vertices));

    libera_poligono(&p);
}

void teste_getLados_poligono(void){
    POLIGONO p = cria_poligono(9);
    TEST_ASSERT_NOT_NULL(getLados_poligono(p));

    VERTICE v1 = cria_vertice(2.2, 8.8);
    VERTICE v2 = cria_vertice(4.4, 6.8);
    VERTICE v3 = cria_vertice(6.6, 8.6);
    insere_vertice(p, v1);
    insere_vertice(p, v2);
    insere_vertice(p, v3);
    desenha_poligono(p);

    FILA lados = getLados_poligono(p);
    TEST_ASSERT_EQUAL_INT(3, tamanho_fila(lados));

    libera_poligono(&p);
}

void teste_getHachura_poligono(void){
    POLIGONO p = cria_poligono(9);
    TEST_ASSERT_NOT_NULL(getHachura_poligono(p));

    libera_poligono(&p);
}

void teste_cria_vertice(void){
    VERTICE v = cria_vertice(2.4, 8.2);
    TEST_ASSERT_NOT_NULL(v);

    TEST_ASSERT_EQUAL_DOUBLE(2.4, getX_vertice(v));
    TEST_ASSERT_EQUAL_DOUBLE(8.2, getY_vertice(v));

    libera_vertice(&v);
    TEST_ASSERT_NULL(v);
}

void teste_insere_vertice(void){
    POLIGONO p = cria_poligono(1);

    VERTICE v1 = cria_vertice(2.2, 8.8);
    VERTICE v2 = cria_vertice(4.4, 6.8);
    
    insere_vertice(p, v1);
    TEST_ASSERT_EQUAL_INT(1, tamanho_poligono(p));

    insere_vertice(p, v2);
    TEST_ASSERT_EQUAL_INT(2, tamanho_poligono(p));

    libera_poligono(&p);
}

void teste_remove_vertice(void){
    POLIGONO p = cria_poligono(1);

    VERTICE v1 = cria_vertice(2.2, 2.2);
    VERTICE v2 = cria_vertice(4.4, 4.4);

    insere_vertice(p, v1);
    insere_vertice(p, v2);
    TEST_ASSERT_EQUAL_INT(2, tamanho_poligono(p));
    
    remove_vertice(p);
    TEST_ASSERT_EQUAL_INT(1, tamanho_poligono(p));

    remove_vertice(p);
    TEST_ASSERT_EQUAL_INT(0, tamanho_poligono(p));

    libera_poligono(&p);
}

void teste_getXY_vertice(void){
    VERTICE v = cria_vertice(2.2, 2.4);

    TEST_ASSERT_EQUAL_DOUBLE(2.2, getX_vertice(v));

    TEST_ASSERT_EQUAL_DOUBLE(2.4, getY_vertice(v));

    libera_vertice(&v);
}

void teste_desenha_poligono(void){
    POLIGONO p = cria_poligono(7);

    // Testa número ímpar de vértices
    VERTICE v1 = cria_vertice(2.2, 8.8);
    VERTICE v2 = cria_vertice(4.4, 6.8);
    VERTICE v3 = cria_vertice(6.6, 8.6);
    insere_vertice(p, v1);
    insere_vertice(p, v2);
    insere_vertice(p, v3);
    desenha_poligono(p);
    FILA lados = getLados_poligono(p);
    TEST_ASSERT_EQUAL_INT(3, tamanho_fila(lados));
    libera_poligono(&p);

    // Testa número par de vértices
    p = cria_poligono(7);
    v1 = cria_vertice(2.2, 8.8);
    v2 = cria_vertice(4.4, 6.8);
    v3 = cria_vertice(6.6, 8.6);
    VERTICE v4 = cria_vertice(8.8, 10.4);
    insere_vertice(p, v1);
    insere_vertice(p, v2);
    insere_vertice(p, v3);
    insere_vertice(p, v4);
    desenha_poligono(p);
    lados = getLados_poligono(p);
    TEST_ASSERT_EQUAL_INT(4, tamanho_fila(lados));

    libera_poligono(&p);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_poligono);
    RUN_TEST(teste_tamanho_poligono);
    RUN_TEST(teste_getVertices_poligono);
    RUN_TEST(teste_getLados_poligono);
    RUN_TEST(teste_getHachura_poligono);
    RUN_TEST(teste_cria_vertice);
    RUN_TEST(teste_insere_vertice);
    RUN_TEST(teste_remove_vertice);
    RUN_TEST(teste_getXY_vertice);
    RUN_TEST(teste_desenha_poligono);
    RUN_TEST(teste_hachura_poligono);
   
    
    return UNITY_END();
}