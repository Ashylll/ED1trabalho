#include "fila.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_fila(void) {
    FILA f = cria_fila();
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_TRUE(vazia_fila(f));
    TEST_ASSERT_EQUAL_INT(0, tamanho_fila(f));
    libera_fila(&f);
}

void teste_insere_fila(void) {
    FILA f = cria_fila();
    int x = 10;
    
    insere_fila(f, &x);
    
    TEST_ASSERT_FALSE(vazia_fila(f));
    TEST_ASSERT_EQUAL_INT(1, tamanho_fila(f));
    
    libera_fila(&f);
}

void teste_remove_fila(void) {
    FILA f = cria_fila();
    int x = 10, y = 20;
    void *removido1 = NULL;
    

    remove_fila(f, &removido1);
    TEST_ASSERT_NULL(removido1);

    insere_fila(f, &x);
    insere_fila(f, &y);

    remove_fila(f, &removido1);
    TEST_ASSERT_EQUAL_PTR(&x, removido1);
    TEST_ASSERT_EQUAL_INT(1, tamanho_fila(f));

    void *removido2 = NULL;
    remove_fila(f, &removido2);
    TEST_ASSERT_EQUAL_PTR(&y, removido2);
    TEST_ASSERT_TRUE(vazia_fila(f));

    libera_fila(&f);
}

void teste_tamanho_fila(void) {
    FILA f = cria_fila();
    int itens[] = {1, 2, 3, 4, 5};

    for(int i = 0; i < 5; i++) {
        insere_fila(f, &itens[i]);
    }

    TEST_ASSERT_EQUAL_INT(5, tamanho_fila(f));
    
    remove_fila(f, NULL);
    TEST_ASSERT_EQUAL_INT(4, tamanho_fila(f));

    libera_fila(&f);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_fila);
    RUN_TEST(teste_insere_fila);
    RUN_TEST(teste_remove_fila);
    RUN_TEST(teste_tamanho_fila);
    return UNITY_END();
}