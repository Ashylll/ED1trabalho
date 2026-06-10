#include "texto.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

// Parâmetros gerais do texto para teste:
    int id = 1;
    double x = 10.4;
    double y = 8.26;
    char* corb = "pink";
    char* corp = "yellow";
    char a = 'm';
    char* txto = "Oii";

void teste_cria_texto(void){

    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    TEST_ASSERT_NOT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, NULL, corp, a, txto);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, NULL, a, txto);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'e', txto);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, a, NULL);
    TEST_ASSERT_NULL(t);
    libera_texto(&t);
}


void teste_get_id_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    int id_teste = get_id_texto(t);

    TEST_ASSERT_EQUAL_INT(id, id_teste);
    libera_texto(&t);

    t = cria_texto(-18, x, y, corb, corp, a, txto);
    id_teste = get_id_texto(t);

    TEST_ASSERT_EQUAL_INT(-18, id_teste);
    libera_texto(&t);
}

void teste_get_x_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    double x_teste = get_x_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(x, x_teste);
    libera_texto(&t);

    t = cria_texto(id, -8, y, corb, corp, a, txto);
    x_teste = get_x_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(-8, x_teste);
    libera_texto(&t);
}

void teste_get_y_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    double y_teste = get_y_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(y, y_teste);
    libera_texto(&t);

    t = cria_texto(id, x, -6, corb, corp, a, txto);
    y_teste = get_y_texto(t);

    TEST_ASSERT_EQUAL_DOUBLE(-6, y_teste);
    libera_texto(&t);
}


void teste_get_corb_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    char* corb_teste = get_corb_texto(t);
    TEST_ASSERT_EQUAL_STRING(corb, corb_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, "purple", corp, a, txto);
    corb_teste = get_corb_texto(t);
    TEST_ASSERT_EQUAL_STRING("purple", corb_teste);
    libera_texto(&t);
}

void teste_get_corp_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    char* corp_teste = get_corp_texto(t);
    TEST_ASSERT_EQUAL_STRING(corp, corp_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, "black", a, txto);
    corp_teste = get_corp_texto(t);
    TEST_ASSERT_EQUAL_STRING("black", corp_teste);
    libera_texto(&t);
}

void teste_getA_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    char a_teste = get_posicao_ancora_texto(t);
    TEST_ASSERT_EQUAL_CHAR(a, a_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'i', txto);
    a_teste = get_posicao_ancora_texto(t);
    TEST_ASSERT_EQUAL_CHAR('i', a_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'm', txto);
    a_teste = get_posicao_ancora_texto(t);
    TEST_ASSERT_EQUAL_CHAR('m', a_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, 'f', txto);
    a_teste = get_posicao_ancora_texto(t);
    TEST_ASSERT_EQUAL_CHAR('f', a_teste);
    libera_texto(&t);
}

void teste_getTXTO_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    char* txto_teste = get_palavra_texto(t);
    TEST_ASSERT_EQUAL_STRING(txto, txto_teste);
    libera_texto(&t);

    t = cria_texto(id, x, y, corb, corp, a, "yupiii");
    txto_teste = get_palavra_texto(t);
    TEST_ASSERT_EQUAL_STRING("yupiii", txto_teste);
    libera_texto(&t);
}

void teste_set_id_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(set_id_texto(NULL, 2));
    TEST_ASSERT_EQUAL_INT(id, get_id_texto(t));

    TEST_ASSERT_TRUE(set_id_texto(t, 4));
    TEST_ASSERT_EQUAL_INT(4, get_id_texto(t));

    TEST_ASSERT_TRUE(set_id_texto(t, -2));
    TEST_ASSERT_EQUAL_INT(-2, get_id_texto(t));

    TEST_ASSERT_TRUE(set_id_texto(t, 0));
    TEST_ASSERT_EQUAL_INT(0, get_id_texto(t));

    libera_texto(&t);
}

void teste_set_x_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    
    TEST_ASSERT_FALSE(set_x_texto(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(x, get_x_texto(t));

    TEST_ASSERT_TRUE(set_x_texto(t, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, get_x_texto(t));

    TEST_ASSERT_TRUE(set_x_texto(t, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_x_texto(t));

    TEST_ASSERT_TRUE(set_x_texto(t, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, get_x_texto(t));

    libera_texto(&t);
}

void teste_set_y_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    
    TEST_ASSERT_FALSE(set_y_texto(NULL, -10));
    TEST_ASSERT_EQUAL_DOUBLE(y, get_y_texto(t));

    TEST_ASSERT_TRUE(set_y_texto(t, 4.2));
    TEST_ASSERT_EQUAL_DOUBLE(4.2, get_y_texto(t));

    TEST_ASSERT_TRUE(set_y_texto(t, -2.8));
    TEST_ASSERT_EQUAL_DOUBLE(-2.8, get_y_texto(t));

    TEST_ASSERT_TRUE(set_y_texto(t, 0));
    TEST_ASSERT_EQUAL_DOUBLE(0, get_y_texto(t));

    libera_texto(&t);
}


void teste_set_corb_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(set_corb_texto(NULL, "blue"));
    TEST_ASSERT_EQUAL_STRING(corb, get_corb_texto(t));

    TEST_ASSERT_FALSE(set_corb_texto(t, NULL));
    TEST_ASSERT_EQUAL_STRING(corb, get_corb_texto(t));

    TEST_ASSERT_TRUE(set_corb_texto(t, "cyan"));
    TEST_ASSERT_EQUAL_STRING("cyan", get_corb_texto(t));

    libera_texto(&t);
}

void teste_set_corp_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(set_corp_texto(NULL, "white"));
    TEST_ASSERT_EQUAL_STRING(corp, get_corp_texto(t));

    TEST_ASSERT_FALSE(set_corp_texto(t, NULL));
    TEST_ASSERT_EQUAL_STRING(corp, get_corp_texto(t));

    TEST_ASSERT_TRUE(set_corp_texto(t, "gray"));
    TEST_ASSERT_EQUAL_STRING("gray", get_corp_texto(t));

    libera_texto(&t);
}

void teste_setA_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(set_posicao_ancora_texto(NULL, 'i'));
    TEST_ASSERT_EQUAL_CHAR(a, get_posicao_ancora_texto(t));

    TEST_ASSERT_FALSE(set_posicao_ancora_texto(t, 'h'));
    TEST_ASSERT_EQUAL_CHAR(a, get_posicao_ancora_texto(t));

    TEST_ASSERT_TRUE(set_posicao_ancora_texto(t, 'i'));
    TEST_ASSERT_EQUAL_CHAR('i', get_posicao_ancora_texto(t));

    TEST_ASSERT_TRUE(set_posicao_ancora_texto(t, 'm'));
    TEST_ASSERT_EQUAL_CHAR('m', get_posicao_ancora_texto(t));

    TEST_ASSERT_TRUE(set_posicao_ancora_texto(t, 'f'));
    TEST_ASSERT_EQUAL_CHAR('f', get_posicao_ancora_texto(t));

    libera_texto(&t);
}

void teste_setTXTO_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(set_palavra_texto(NULL, "Tchau"));
    TEST_ASSERT_EQUAL_STRING(txto, get_palavra_texto(t));

    TEST_ASSERT_FALSE(set_palavra_texto(t, NULL));
    TEST_ASSERT_EQUAL_STRING(txto, get_palavra_texto(t));

    TEST_ASSERT_TRUE(set_palavra_texto(t, "Ahhh"));
    TEST_ASSERT_EQUAL_STRING("Ahhh", get_palavra_texto(t));

    libera_texto(&t);
}

void teste_getFFamily_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    char* family = get_family_texto(t);
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, family);

    libera_texto(&t);
}

void teste_getFWeight_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    char* weight = get_weight_texto(t);
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, weight);

    libera_texto(&t);
}

void teste_getFSize_texto(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);
    double size = get_size_texto(t);
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, size);

    libera_texto(&t);
}
void teste_muda_estilo(void){
    Texto t = cria_texto(id, x, y, corb, corp, a, txto);

    TEST_ASSERT_FALSE(muda_estilo(NULL, "serif", "bold", 2));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, get_family_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, get_weight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, get_size_texto(t));

    TEST_ASSERT_FALSE(muda_estilo(t, NULL, "normal", 8));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, get_family_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, get_weight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, get_size_texto(t));

    TEST_ASSERT_FALSE(muda_estilo(t, "cursive", NULL, 12));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, get_family_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, get_weight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, get_size_texto(t));

    TEST_ASSERT_FALSE(muda_estilo(t, "cursive", "bold", -4));
    TEST_ASSERT_EQUAL_STRING(FFAMILY_PADRAO, get_family_texto(t));
    TEST_ASSERT_EQUAL_STRING(FWEIGHT_PADRAO, get_weight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(FSIZE_PADRAO, get_size_texto(t));

    TEST_ASSERT_TRUE(muda_estilo(t, "serif", "bold", 10));
    TEST_ASSERT_EQUAL_STRING("serif", get_family_texto(t));
    TEST_ASSERT_EQUAL_STRING("bold", get_weight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(10, get_size_texto(t));

    TEST_ASSERT_TRUE(muda_estilo(t, "cursive", "bolder", 218.9481674));
    TEST_ASSERT_EQUAL_STRING("cursive", get_family_texto(t));
    TEST_ASSERT_EQUAL_STRING("bolder", get_weight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(218.9481674, get_size_texto(t));

    TEST_ASSERT_TRUE(muda_estilo(t, "sans-serif", "lighter", 20));
    TEST_ASSERT_EQUAL_STRING("sans-serif", get_family_texto(t));
    TEST_ASSERT_EQUAL_STRING("lighter", get_weight_texto(t));
    TEST_ASSERT_EQUAL_DOUBLE(20, get_size_texto(t));

    libera_texto(&t);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(teste_cria_texto);
    RUN_TEST(teste_get_id_texto);
    RUN_TEST(teste_get_x_texto);
    RUN_TEST(teste_get_y_texto);
    RUN_TEST(teste_get_corb_texto);
    RUN_TEST(teste_get_corp_texto);
    RUN_TEST(teste_getA_texto);
    RUN_TEST(teste_getTXTO_texto);
    RUN_TEST(teste_set_id_texto);
    RUN_TEST(teste_set_x_texto);
    RUN_TEST(teste_set_y_texto);
    RUN_TEST(teste_set_corb_texto);
    RUN_TEST(teste_set_corp_texto);
    RUN_TEST(teste_setA_texto);
    RUN_TEST(teste_setTXTO_texto);
    RUN_TEST(teste_muda_estilo);
    RUN_TEST(teste_getFFamily_texto);
    RUN_TEST(teste_getFWeight_texto);
    RUN_TEST(teste_getFSize_texto);
    return UNITY_END();
}