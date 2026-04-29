#include "forma.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

#include "unity.h"
#include <stdlib.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

void teste_cria_forma(void){
    CIRCULO c = cria_circulo(0, 2.2, 4.4, 2, "pink", "pink");
    FORMA f = cria_forma('a', c);
    TEST_ASSERT_NULL(f);
    libera_forma(&f);

    f = cria_forma('c', c);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('c', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(c, getHandle_forma(f));
    libera_forma(&f);

    RETANGULO r = cria_retangulo(1, 2.2, 4.4, 2.2, 2.2, "pink", "pink");
    f = cria_forma('r', r);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('r', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(r, getHandle_forma(f));
    libera_forma(&f);

    LINHA l = cria_linha(2, 2.0, 2.0, 4.0, 4.0, "pink");
    if(!l) printf("dfa\n");
    f = cria_forma('l', l);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('l', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(l, getHandle_forma(f));
    libera_forma(&f);

    TEXTO t = cria_texto(3, 4.2, 4.4, "pink", "pink", 'm', "rosa");
    f = cria_forma('t', t);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('t', getTipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(t, getHandle_forma(f));

    libera_forma(&f);
    TEST_ASSERT_NULL(f);

}

void teste_getId_forma(void){
    LINHA l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_INT(-2, getId_forma(f));

    libera_forma(&f);
}

void teste_getTipo_forma(void){
    LINHA l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_CHAR('l', getTipo_forma(f));

    libera_forma(&f);
}

void teste_getHandle_forma(void){
    LINHA l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_PTR(l, getHandle_forma(f));

    libera_forma(&f);
}
    
void teste_getXY_forma(void){
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f = cria_forma('l', l);

    double x, y;
    getXY_forma(f, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(2, x);
    TEST_ASSERT_EQUAL_DOUBLE(8, y);

    libera_forma(&f);
}

void teste_setXY_forma(void){
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_FALSE(setXY_forma(NULL, 10.2, 10.4));
    TEST_ASSERT_TRUE(setXY_forma(f, 10.2, 10.4));

    double x, y;
    getXY_forma(f, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(10.2, x);
    TEST_ASSERT_EQUAL_DOUBLE(10.4, y);
    TEST_ASSERT_EQUAL_DOUBLE(10.2 - 2 + 4, getX2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(10.4 - 8 + 6, getY2_linha(l));
    
    libera_forma(&f);
}

void teste_desloca_forma(void){
    LINHA l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    FORMA f = cria_forma('l', l);

    TEST_ASSERT_FALSE(desloca_forma(NULL, 2, -4));
    TEST_ASSERT_TRUE(desloca_forma(f, 2, -4));

    TEST_ASSERT_EQUAL_DOUBLE(2 + 2, getX1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(8 - 4, getY1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(4 + 2, getX2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(6 - 4, getY2_linha(l));

    libera_forma(&f);
}
    
int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_forma);
    RUN_TEST(teste_getId_forma);
    RUN_TEST(teste_getTipo_forma);
    RUN_TEST(teste_getHandle_forma);
    RUN_TEST(teste_getXY_forma);
    RUN_TEST(teste_setXY_forma);
    RUN_TEST(teste_desloca_forma);
    return UNITY_END();
}