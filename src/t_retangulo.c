#include "retangulo.h"
#include "unity.h"
#include <stdlib.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

// Parâmetros gerais do retângulo para teste:
    int id = 1;
    double x = 10.4;
    double y = 8.26;
    double w = 2.2;
    double h = 4.8;
    char* corb = "pink";
    char* corp = "yellow";

void teste_cria_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);
    TEST_ASSERT_NOT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, 0, h, corb, corp);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, 0, corb, corp);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, NULL, corp);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, corb, NULL);
    TEST_ASSERT_NULL(r);
    libera_retangulo(&r);
}

void teste_area_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    double area = w * h;
    double area_retornada = area_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(area, area_retornada);

    libera_retangulo(&r);
}

void teste_get_id_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    int id_teste = get_id_retangulo(r);

    TEST_ASSERT_EQUAL_INT(id, id_teste);
    libera_retangulo(&r);

    r = cria_retangulo(-18, x, y, w, h, corb, corp);
    id_teste = get_id_retangulo(r);

    TEST_ASSERT_EQUAL_INT(-18, id_teste);
    libera_retangulo(&r);
}

void teste_get_x_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    double x_teste = get_x_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(x, x_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, -8, y, w, h, corb, corp);
    x_teste = get_x_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(-8, x_teste);
    libera_retangulo(&r);
}

void teste_get_y_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    double y_teste = get_y_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(y, y_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, -6, w, h, corb, corp);
    y_teste = get_y_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(-6, y_teste);
    libera_retangulo(&r);
}

void teste_getW_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    double w_teste = getW_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(w, w_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, 4, h, corb, corp);
    w_teste = getW_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(4, w_teste);
    libera_retangulo(&r);
}

void teste_getH_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    double h_teste = getH_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(h, h_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, 6, corb, corp);
    h_teste = getH_retangulo(r);

    TEST_ASSERT_EQUAL_DOUBLE(6, h_teste);
    libera_retangulo(&r);
}

void teste_get_corb_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);
    char* corb_teste = get_corb_retangulo(r);
    TEST_ASSERT_EQUAL_STRING(corb, corb_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, "purple", corp);
    corb_teste = get_corb_retangulo(r);
    TEST_ASSERT_EQUAL_STRING("purple", corb_teste);
    libera_retangulo(&r);
}

void teste_get_corp_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);
    char* corp_teste = get_corp_retangulo(r);
    TEST_ASSERT_EQUAL_STRING(corp, corp_teste);
    libera_retangulo(&r);

    r = cria_retangulo(id, x, y, w, h, corb, "black");
    corp_teste = get_corp_retangulo(r);
    TEST_ASSERT_EQUAL_STRING("black", corp_teste);
    libera_retangulo(&r);
}

void teste_set_id_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    TEST_ASSERT_FALSE(set_id_retangulo(NULL, 2));
    TEST_ASSERT_EQUAL_INT(id, get_id_retangulo(r));

    TEST_ASSERT_TRUE(set_id_retangulo(r, 4));
    TEST_ASSERT_EQUAL_INT(4, get_id_retangulo(r));

    TEST_ASSERT_TRUE(set_id_retangulo(r, -2));
    TEST_ASSERT_EQUAL_INT(-2, get_id_retangulo(r));

    TEST_ASSERT_TRUE(set_id_retangulo(r, 0));
    TEST_ASSERT_EQUAL_INT(0, get_id_retangulo(r));

    libera_retangulo(&r);
}

void teste_set_x_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);
    
    TEST_ASSERT_FALSE(set_x_retangulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x, get_x_retangulo(r));

    TEST_ASSERT_TRUE(set_x_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, get_x_retangulo(r));

    TEST_ASSERT_TRUE(set_x_retangulo(r, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_x_retangulo(r));

    TEST_ASSERT_TRUE(set_x_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, get_x_retangulo(r));

    libera_retangulo(&r);
}

void teste_set_y_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);
    
    TEST_ASSERT_FALSE(set_y_retangulo(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y, get_y_retangulo(r));

    TEST_ASSERT_TRUE(set_y_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, get_y_retangulo(r));

    TEST_ASSERT_TRUE(set_y_retangulo(r, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_y_retangulo(r));

    TEST_ASSERT_TRUE(set_y_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, get_y_retangulo(r));

    libera_retangulo(&r);
}

void teste_setW_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);
    
    TEST_ASSERT_FALSE(setW_retangulo(NULL, 2));
    TEST_ASSERT_EQUAL_DOUBLE(w, getW_retangulo(r));

    TEST_ASSERT_FALSE(setW_retangulo(r, -2));
    TEST_ASSERT_EQUAL_DOUBLE(w, getW_retangulo(r));

    TEST_ASSERT_FALSE(setW_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(w, getW_retangulo(r));

    TEST_ASSERT_TRUE(setW_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getW_retangulo(r));

    libera_retangulo(&r);
}

void teste_setH_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);
    
    TEST_ASSERT_FALSE(setH_retangulo(NULL, 2));
    TEST_ASSERT_EQUAL_DOUBLE(h, getH_retangulo(r));

    TEST_ASSERT_FALSE(setH_retangulo(r, -2));
    TEST_ASSERT_EQUAL_DOUBLE(h, getH_retangulo(r));

    TEST_ASSERT_FALSE(setH_retangulo(r, 0));
    TEST_ASSERT_EQUAL_DOUBLE(h, getH_retangulo(r));

    TEST_ASSERT_TRUE(setH_retangulo(r, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, getH_retangulo(r));

    libera_retangulo(&r);
}

void teste_set_corb_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    TEST_ASSERT_FALSE(set_corb_retangulo(NULL, "blue"));
    TEST_ASSERT_EQUAL_STRING(corb, get_corb_retangulo(r));

    TEST_ASSERT_FALSE(set_corb_retangulo(r, NULL));
    TEST_ASSERT_EQUAL_STRING(corb, get_corb_retangulo(r));

    TEST_ASSERT_TRUE(set_corb_retangulo(r, "cyan"));
    TEST_ASSERT_EQUAL_STRING("cyan", get_corb_retangulo(r));

    libera_retangulo(&r);
}

void teste_set_corp_retangulo(void){
    Retangulo r = cria_retangulo(id, x, y, w, h, corb, corp);

    TEST_ASSERT_FALSE(set_corp_retangulo(NULL, "white"));
    TEST_ASSERT_EQUAL_STRING(corp, get_corp_retangulo(r));

    TEST_ASSERT_FALSE(set_corp_retangulo(r, NULL));
    TEST_ASSERT_EQUAL_STRING(corp, get_corp_retangulo(r));

    TEST_ASSERT_TRUE(set_corp_retangulo(r, "gray"));
    TEST_ASSERT_EQUAL_STRING("gray", get_corp_retangulo(r));

    libera_retangulo(&r);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_retangulo);
    RUN_TEST(teste_area_retangulo);
    RUN_TEST(teste_get_id_retangulo);
    RUN_TEST(teste_get_x_retangulo);
    RUN_TEST(teste_get_y_retangulo);
    RUN_TEST(teste_getW_retangulo);
    RUN_TEST(teste_getH_retangulo);
    RUN_TEST(teste_get_corb_retangulo);
    RUN_TEST(teste_get_corp_retangulo);
    RUN_TEST(teste_set_id_retangulo);
    RUN_TEST(teste_set_x_retangulo);
    RUN_TEST(teste_set_y_retangulo);
    RUN_TEST(teste_setW_retangulo);
    RUN_TEST(teste_setH_retangulo);
    RUN_TEST(teste_set_corb_retangulo);
    RUN_TEST(teste_set_corp_retangulo);
    return UNITY_END();
}