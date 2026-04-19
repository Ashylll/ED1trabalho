#include "fila.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

#define TAMANHO 100

void teste_cria_fila(void) {
    FILA f = cria_fila(TAMANHO);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_TRUE(vazia_fila(f));
    TEST_ASSERT_EQUAL_INT(0, tamanho_fila(f));
    libera_fila(&f);
}

void teste_insere_fila(void) {
    FILA f = cria_fila(TAMANHO);
    int x = 10;
    
    insere_fila(f, &x);
    
    TEST_ASSERT_FALSE(vazia_fila(f));
    TEST_ASSERT_EQUAL_INT(1, tamanho_fila(f));
    
    libera_fila(&f);
}

void teste_remove_fila(void) {
    FILA f = cria_fila(TAMANHO);
    int x = 10;
    char* c = "fasfa";
    void *removido;

    insere_fila(f, &x);
    insere_fila(f, c);

    remove_fila(f, &removido);
    TEST_ASSERT_EQUAL_INT(x, *(int*)removido);
    TEST_ASSERT_EQUAL_INT(1, tamanho_fila(f));

    remove_fila(f, NULL);
    TEST_ASSERT_TRUE(vazia_fila(f));

    libera_fila(&f);
}

void teste_vazia_fila(void){
    FILA f = cria_fila(TAMANHO);
    TEST_ASSERT_TRUE(vazia_fila(f));

    double a = 2.4;
    insere_fila(f, &a);

    TEST_ASSERT_FALSE(vazia_fila(f));

    libera_fila(&f);
}

void teste_tamanho_fila(void) {
    FILA f = cria_fila(TAMANHO);
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
    RUN_TEST(teste_vazia_fila);
    RUN_TEST(teste_tamanho_fila);
    return UNITY_END();
}