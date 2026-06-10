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
    Circulo c = cria_circulo(0, 2.2, 4.4, 2, "pink", "pink");
    Forma f = cria_forma('a', c);
    TEST_ASSERT_NULL(f);
    libera_forma(&f);

    f = cria_forma('c', c);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('c', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(c, get_handle_forma(f));
    libera_forma(&f);

    Retangulo r = cria_retangulo(1, 2.2, 4.4, 2.2, 2.2, "pink", "pink");
    f = cria_forma('r', r);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('r', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(r, get_handle_forma(f));
    libera_forma(&f);

    Linha l = cria_linha(2, 2.0, 2.0, 4.0, 4.0, "pink");
    if(!l) printf("dfa\n");
    f = cria_forma('l', l);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('l', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(l, get_handle_forma(f));
    libera_forma(&f);

    Texto t = cria_texto(3, 4.2, 4.4, "pink", "pink", 'm', "rosa");
    f = cria_forma('t', t);
    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_CHAR('t', get_tipo_forma(f));
    TEST_ASSERT_EQUAL_PTR(t, get_handle_forma(f));

    libera_forma(&f);
    TEST_ASSERT_NULL(f);

}

void teste_get_id_forma(void){
    Linha l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    Forma f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_INT(-2, get_id_forma(f));

    libera_forma(&f);
}

void teste_get_tipo_forma(void){
    Linha l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    Forma f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_CHAR('l', get_tipo_forma(f));

    libera_forma(&f);
}

void teste_get_handle_forma(void){
    Linha l = cria_linha(-2, 2.0, 2.0, 4.0, 4.0, "pink");
    Forma f = cria_forma('l', l);

    TEST_ASSERT_EQUAL_PTR(l, get_handle_forma(f));

    libera_forma(&f);
}
    
void teste_get_ancora_forma(void){
    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    Forma f = cria_forma('l', l);

    double x, y;
    get_ancora_forma(f, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(2, x);
    TEST_ASSERT_EQUAL_DOUBLE(8, y);

    libera_forma(&f);
}

void teste_set_ancora_forma(void){
    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    Forma f = cria_forma('l', l);

    TEST_ASSERT_FALSE(set_ancora_forma(NULL, 10.2, 10.4));
    TEST_ASSERT_TRUE(set_ancora_forma(f, 10.2, 10.4));

    double x, y;
    get_ancora_forma(f, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(10.2, x);
    TEST_ASSERT_EQUAL_DOUBLE(10.4, y);
    TEST_ASSERT_EQUAL_DOUBLE(10.2 - 2 + 4, get_x2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(10.4 - 8 + 6, get_y2_linha(l));
    
    libera_forma(&f);
}

void teste_set_corb_forma(void){
    Circulo c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
    Forma f = cria_forma('c', c);

    set_corb_forma(f, "yellow");

    TEST_ASSERT_EQUAL_STRING("yellow", get_corb_circulo(c));
    libera_forma(&f);

    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    f = cria_forma('l', l);

    set_corb_forma(f, "purple");

    TEST_ASSERT_EQUAL_STRING("purple", get_cor(l));

    libera_forma(&f);
}

void teste_set_corp_forma(void){
    Circulo c = cria_circulo(2, 2.2, 2.2, 2.2, "pink", "pink");
    Forma f = cria_forma('c', c);
    
    set_corp_forma(f, "yellow");

    TEST_ASSERT_EQUAL_STRING("yellow", get_corp_circulo(c));
    libera_forma(&f);

    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    f = cria_forma('l', l);

    set_corp_forma(f, "purple");

    TEST_ASSERT_EQUAL_STRING("pink", get_cor(l));

    libera_forma(&f);
}

void teste_desloca_forma(void){
    Linha l = cria_linha(-2, 2.0, 8.0, 4.0, 6.0, "pink");
    Forma f = cria_forma('l', l);

    TEST_ASSERT_FALSE(desloca_forma(NULL, 2, -4));
    TEST_ASSERT_TRUE(desloca_forma(f, 2, -4));

    TEST_ASSERT_EQUAL_DOUBLE(2 + 2, get_x1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(8 - 4, get_y1_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(4 + 2, get_x2_linha(l));
    TEST_ASSERT_EQUAL_DOUBLE(6 - 4, get_y2_linha(l));

    libera_forma(&f);
}

void teste_reporta_forma(void){
    Circulo c = cria_circulo(10, 5.0, 5.0, 2.0, "pink", "yellow");
    Forma f = cria_forma('c', c);
    
    FILE *arq = fopen("teste_reporte.txt", "w+");
    TEST_ASSERT_NOT_NULL(arq);

    reporta_forma(f, arq);
    
    // Volta ao início do arquivo para ler e validar
    rewind(arq);
    char buffer[256];
    fgets(buffer, sizeof(buffer), arq);
    TEST_ASSERT_EQUAL_STRING("Circulo\n", buffer);
    
    fgets(buffer, sizeof(buffer), arq);
    TEST_ASSERT_EQUAL_STRING("Id: 10\n", buffer);

    fclose(arq);
    remove("teste_reporte.txt"); // Limpa o arquivo de teste
    libera_forma(&f);
}

void teste_sobrepoe_retangulo(void){
    Retangulo r1 = cria_retangulo(1, 0.0, 0.0, 10.0, 10.0, "black", "white");
    Retangulo r2 = cria_retangulo(2, 5.0, 5.0, 10.0, 10.0, "black", "white");
    Forma f1 = cria_forma('r', r1);
    Forma f2 = cria_forma('r', r2);
    
    TEST_ASSERT_TRUE(sobrepoe_retangulo(f1, f2));

    set_x_retangulo(r2, 20.0); 
    TEST_ASSERT_FALSE(sobrepoe_retangulo(f1, f2));

    Linha l = cria_linha(3, -5.0, 5.0, 5.0, 5.0, "green");
    Forma fL = cria_forma('l', l);
    TEST_ASSERT_TRUE(sobrepoe_retangulo(f1, fL));

    Texto t = cria_texto(4, 5.0, 5.0, "black", "black", 'i', "Oi");
    Forma fT = cria_forma('t', t);
    TEST_ASSERT_TRUE(sobrepoe_retangulo(f1, fT));

    libera_forma(&f1);
    libera_forma(&f2);
    libera_forma(&fL);
    libera_forma(&fT);
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(teste_cria_forma);
    RUN_TEST(teste_get_id_forma);
    RUN_TEST(teste_get_tipo_forma);
    RUN_TEST(teste_get_handle_forma);
    RUN_TEST(teste_get_ancora_forma);
    RUN_TEST(teste_set_ancora_forma);
    RUN_TEST(teste_set_corb_forma);
    RUN_TEST(teste_set_corp_forma);
    RUN_TEST(teste_desloca_forma);
    RUN_TEST(teste_reporta_forma);
    RUN_TEST(teste_sobrepoe_retangulo);
    return UNITY_END();
}