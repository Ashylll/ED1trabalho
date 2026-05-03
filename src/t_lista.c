#include "lista.h"
#include "unity.h"

#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

int cmp_int(void* a, void* b) {
    return (*(int*)a - *(int*)b);
}

void teste_cria_lista(void){
    LISTA l = cria_lista();
    TEST_ASSERT_NOT_NULL(l);

    libera_lista(&l);
    TEST_ASSERT_NULL(l);
}

void teste_insere_lista(void){
    LISTA l = cria_lista();
    int a = 10, b = 20, c = 30;

    TEST_ASSERT_TRUE(insere_lista(l, &a));
    TEST_ASSERT_EQUAL_INT(1, tamanho_lista(l));
    
    insere_lista(l, &b);
    insere_lista(l, &c);
    
    TEST_ASSERT_EQUAL_INT(3, tamanho_lista(l));
    TEST_ASSERT_EQUAL_PTR(&b, getItem_lista(l, 1)); 

    libera_lista(&l);
}

void teste_removeIndice_lista(void){
    LISTA l = cria_lista();
    int valores[] = {1, 2, 3}; 
    
    for(int i = 0; i < 3; i++){
        insere_lista(l, &valores[i]);
    }
    
    void* removido = removeIndice_lista(l, 1);
    TEST_ASSERT_EQUAL_PTR(&valores[1], removido);
    TEST_ASSERT_EQUAL_INT(2, tamanho_lista(l));
    
    removido = removeIndice_lista(l, 0);
    TEST_ASSERT_EQUAL_PTR(&valores[2], removido);
    TEST_ASSERT_EQUAL_INT(1, tamanho_lista(l));
    
    libera_lista(&l);
}

void teste_remove_lista(void){
    LISTA l = cria_lista();
    int a = 151, b = 200;
    
    insere_lista(l, &a);
    insere_lista(l, &b);
    
    remove_lista(l, &a); 
    TEST_ASSERT_EQUAL_INT(1, tamanho_lista(l));
    TEST_ASSERT_EQUAL_PTR(&b, getItem_lista(l, 0));
    
    libera_lista(&l);
}

void teste_vazia_lista(void){
    LISTA l = cria_lista();
    TEST_ASSERT_TRUE(vazia_lista(l));
    
    int x = 5;
    insere_lista(l, &x);
    TEST_ASSERT_FALSE(vazia_lista(l));
    
    removeIndice_lista(l, 0);
    TEST_ASSERT_TRUE(vazia_lista(l));
    
    libera_lista(&l);
}

void teste_tamanho_lista(void){
    LISTA l = cria_lista();
    TEST_ASSERT_EQUAL_INT(0, tamanho_lista(l));

    int v[] = {34, 28, 12};
    for(int i = 0; i < 3; i++){
        insere_lista(l, &v[i]);
    }

    TEST_ASSERT_EQUAL_INT(3, tamanho_lista(l));
    removeIndice_lista(l, 1);

    TEST_ASSERT_EQUAL_INT(2, tamanho_lista(l));

    libera_lista(&l);
}

void teste_getItem_lista(void){
    LISTA l = cria_lista();
    int x = 50, y = 60;
    
    insere_lista(l, &x);
    insere_lista(l, &y);
    
    TEST_ASSERT_EQUAL_PTR(&y, getItem_lista(l, 0));
    TEST_ASSERT_EQUAL_PTR(&x, getItem_lista(l, 1));
    TEST_ASSERT_NULL(getItem_lista(l, 5)); 
    
    libera_lista(&l);
}

void teste_ordena_lista(void){
    LISTA l = cria_lista();
    int v[] = {30, 10, 20};
    
    for(int i = 0; i < 3; i++){
        insere_lista(l, &v[i]);
    }
    ordena_lista(l, cmp_int);
    
    TEST_ASSERT_EQUAL_INT(10, *(int*)getItem_lista(l, 0));
    TEST_ASSERT_EQUAL_INT(20, *(int*)getItem_lista(l, 1));
    TEST_ASSERT_EQUAL_INT(30, *(int*)getItem_lista(l, 2));
    
    libera_lista(&l);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_lista);
    RUN_TEST(teste_insere_lista);
    RUN_TEST(teste_removeIndice_lista);
    RUN_TEST(teste_remove_lista);
    RUN_TEST(teste_vazia_lista);
    RUN_TEST(teste_tamanho_lista);
    RUN_TEST(teste_getItem_lista);
    RUN_TEST(teste_ordena_lista);
    return UNITY_END();
}