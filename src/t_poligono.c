#include "poligono.h"
#include "fila.h"
#include "lista.h"
#include "forma.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_poligono(void){
    POLIGONO p = cria_poligono(1);
    TEST_ASSERT_NOT_NULL(p);
    libera_poligono(&p);
    
    p = cria_poligono(0);
    TEST_ASSERT_NULL(p);
    libera_poligono(&p);

    p = cria_poligono(11);
    TEST_ASSERT_NULL(p);
    libera_poligono(&p);

    p = cria_poligono(4);
    TEST_ASSERT_NOT_NULL(p);

    libera_poligono(&p);
    TEST_ASSERT_NULL(p);
    TEST_ASSERT_NULL(getLados_poligono(p));
    TEST_ASSERT_NULL(getHachura_poligono(p));
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
    TEST_ASSERT_EQUAL_INT(1, getId_poligono(p));
    libera_poligono(&p);

    p = cria_poligono(9);
    TEST_ASSERT_EQUAL_INT(9, getId_poligono(p));

    libera_poligono(&p);
}

void teste_getPoligono(void){

    POLIGONO p = cria_poligono(1);
    POLIGONO p8 = cria_poligono(8);
    POLIGONO p9 = cria_poligono(9);
    
    FILA f = cria_fila(10);
    insere_fila(f, p);
    insere_fila(f, p8);
    insere_fila(f, p9);

    POLIGONO i;
    i = getPoligono(f, 6);
    TEST_ASSERT_NULL(i);
    
    i = getPoligono(f, 1);
    TEST_ASSERT_EQUAL_PTR(i, p);

    i = getPoligono(f, 8);
    TEST_ASSERT_EQUAL_PTR(i, p8);

    i = getPoligono(f, 9);
    TEST_ASSERT_EQUAL_PTR(i, p9);

    while (!vazia_fila(f)){
        void* remove;
        remove_fila(f, &remove);
        libera_poligono(&remove);
    }   
    libera_fila(&f);
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

    LISTA l = cria_lista();
    VERTICE v1 = cria_vertice(2.2, 8.8);
    VERTICE v2 = cria_vertice(4.4, 6.8);
    VERTICE v3 = cria_vertice(6.6, 8.6);
    insere_vertice(p, v1);
    insere_vertice(p, v2);
    insere_vertice(p, v3);

    int i = 7;
    desenha_poligono(p, &i, "pink", l);

    FILA lados = getLados_poligono(p);
    TEST_ASSERT_EQUAL_INT(3, tamanho_fila(lados));
    TEST_ASSERT_EQUAL_INT(10, i);

    void* remove;
    while (!vazia_lista(l)){
        remove = removeIndice_lista(l, 0); 
        libera_forma(&remove); 
    }
    libera_lista(&l);

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

    VERTICE v1 = cria_vertice(2.2, 2.3);
    VERTICE v2 = cria_vertice(4.4, 4.3);

    insere_vertice(p, v1);
    insere_vertice(p, v2);
    TEST_ASSERT_EQUAL_INT(2, tamanho_poligono(p));
    
    double x, y;
    remove_vertice(p, &x, &y);
    TEST_ASSERT_EQUAL_INT(1, tamanho_poligono(p));
    TEST_ASSERT_EQUAL_DOUBLE(2.2, x);
    TEST_ASSERT_EQUAL_DOUBLE(2.3, y);

    remove_vertice(p, &x, &y);
    TEST_ASSERT_EQUAL_INT(0, tamanho_poligono(p));
    TEST_ASSERT_EQUAL_DOUBLE(4.4, x);
    TEST_ASSERT_EQUAL_DOUBLE(4.3, y);

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
    LISTA l = cria_lista();
    VERTICE v1 = cria_vertice(2.2, 8.8);
    VERTICE v2 = cria_vertice(4.4, 6.8);
    VERTICE v3 = cria_vertice(6.6, 8.6);
    insere_vertice(p, v1);
    insere_vertice(p, v2);
    insere_vertice(p, v3);

    int i = 2;
    desenha_poligono(p, &i, "pink", l);
    FILA lados = getLados_poligono(p);
    TEST_ASSERT_EQUAL_INT(3, tamanho_fila(lados));
    TEST_ASSERT_EQUAL_INT(3, tamanho_lista(l));
    TEST_ASSERT_EQUAL_INT(5, i);

    // Testa número par de vértices
    POLIGONO p2 = cria_poligono(7);
    VERTICE v4 = cria_vertice(2.2, 8.8);
    VERTICE v5 = cria_vertice(4.4, 6.8);
    VERTICE v6 = cria_vertice(6.6, 8.6);
    VERTICE v7 = cria_vertice(8.8, 10.4);
    insere_vertice(p2, v4);
    insere_vertice(p2, v5);
    insere_vertice(p2, v6);
    insere_vertice(p2, v7);
    desenha_poligono(p2, &i, "pink", l);
    lados = getLados_poligono(p2);
    TEST_ASSERT_EQUAL_INT(4, tamanho_fila(lados));
    TEST_ASSERT_EQUAL_INT(7, tamanho_lista(l));
    TEST_ASSERT_EQUAL_INT(9, i);

    while (!vazia_lista(l)){
        ITEM remove = removeIndice_lista(l, 0); 
        libera_forma(&remove); 
    }
    libera_lista(&l);

    libera_poligono(&p);
    libera_poligono(&p2);
}

void teste_hachura_poligono(void){
    POLIGONO p = cria_poligono(7);

    LISTA l = cria_lista();
    VERTICE v1 = cria_vertice(2, 2);
    VERTICE v2 = cria_vertice(4, 4);
    VERTICE v3 = cria_vertice(6, 2);
    insere_vertice(p, v1);
    insere_vertice(p, v2);
    insere_vertice(p, v3);
    
    int i = 1;
    desenha_poligono(p, &i, "yellow", l);

    hachura_poligono(p, &i, 0.4, "pink", l);

    FILA hachura = getHachura_poligono(p);
    int tamanho = tamanho_fila(hachura);

    TEST_ASSERT_EQUAL_INT(4, tamanho);
    TEST_ASSERT_EQUAL_INT(7, tamanho_lista(l));
    TEST_ASSERT_EQUAL_INT(8, i);

    void* remove;
    while (!vazia_lista(l)){
        remove = removeIndice_lista(l, 0); 
        libera_forma(&remove); 
    }
    libera_lista(&(l));

    

    libera_poligono(&p);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_poligono);
    RUN_TEST(teste_tamanho_poligono);
    RUN_TEST(teste_getId_poligono);
    RUN_TEST(teste_getPoligono);
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