#include "poligono.h"
#include "fila.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_poligono(void){
    POLIGONO p = cria_poligono();
    TEST_ASSERT_NOT_NULL(p);
    libera_poligono(&p);
    TEST_ASSERT_NULL(p);
}

void teste_tamanho_poligono(void) {
    POLIGONO p = cria_poligono();

    TEST_ASSERT_EQUAL_INT(0, tamanho_poligono(p));

    VERTICE v1 = cria_vertice(4.4, 2.2);
    insere_vertice(p, v1);
    TEST_ASSERT_EQUAL_INT(1, tamanho_poligono(p));

    VERTICE v2 = cria_vertice(6.6, 8.8);
    insere_vertice(p, v2);
    TEST_ASSERT_EQUAL_INT(2, tamanho_poligono(p));

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
    POLIGONO p = cria_poligono();

    VERTICE v1 = cria_vertice(2.2, 8.8);
    VERTICE v2 = cria_vertice(4.4, 6.8);
    
    insere_vertice(p, v1);
    TEST_ASSERT_EQUAL_INT(1, tamanho_poligono(p));

    insere_vertice(p, v2);
    TEST_ASSERT_EQUAL_INT(2, tamanho_poligono(p));

    libera_poligono(&p);
}

void teste_remove_vertice(void){
    POLIGONO p = cria_poligono();

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

void teste_getY_vertice(void){

}


int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_poligono);
    RUN_TEST(teste_tamanho_poligono);
    RUN_TEST(teste_cria_vertice);
    RUN_TEST(teste_insere_vertice);
    RUN_TEST(teste_remove_vertice);
    RUN_TEST(teste_getXY_vertice);
    
    return UNITY_END();
}