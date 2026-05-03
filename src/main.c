#include "sistema.h"
#include "leitura.h"
#include "svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper para copiar o nome-base sem diretório e sem extensão
void nome_base(const char *path, char *dest) {
    const char *p = strrchr(path, '/');
    if (!p) p = path;
    else p++;
    
    strcpy(dest, p);
    char *ponto = strrchr(dest, '.'); 
    if (ponto) *ponto = '\0';
}

int main(int argc, char *argv[]) {
    char *dir_entrada = "./"; 
    char *nome_arq_geo = NULL;
    char *nome_arq_qry = NULL;
    char *dir_saida = NULL;

    // Processa argumentos da linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) dir_entrada = argv[++i];
        else if (strcmp(argv[i], "-f") == 0) nome_arq_geo = argv[++i];
        else if (strcmp(argv[i], "-q") == 0) nome_arq_qry = argv[++i];
        else if (strcmp(argv[i], "-o") == 0) dir_saida = argv[++i];
    }

    // Validação de parâmetros obrigatórios (-f e -o)
    if (!nome_arq_geo || !dir_saida) {
        printf("Parametros obrigatorios -f e -o nao informados\n");
        return 1;
    }

    // Construção do caminho de ENTRADA
    char path_geo[1024];
    sprintf(path_geo, "%s/%s", dir_entrada, nome_arq_geo);

    // Preparação dos nomes de SAÍDA
    char base_geo[256], base_qry[256];
    nome_base(nome_arq_geo, base_geo);

    char out_svg_geo[1024];
    sprintf(out_svg_geo, "%s/%s.svg", dir_saida, base_geo);

    // Variáveis para arquivos combinados (geo + qry)
    char out_svg_comb[1024] = "", out_txt_comb[1024] = "";
    if (nome_arq_qry) {
        nome_base(nome_arq_qry, base_qry);
        sprintf(out_svg_comb, "%s/%s-%s.svg", dir_saida, base_geo, base_qry);
        sprintf(out_txt_comb, "%s/%s-%s.txt", dir_saida, base_geo, base_qry);
    }

    // Inicialização do Sistema
    SISTEMA s = cria_sistema(nome_arq_qry ? out_txt_comb : NULL, out_svg_geo, nome_arq_qry ? out_svg_comb : NULL);


    printf("Processando .geo: %s\n", path_geo);
    leitura_geo(path_geo, s);
    escreve_svg(get_svg_geo(s), s); // Gera SVG inicial

    if (nome_arq_qry) {
        char path_qry[1024];
        sprintf(path_qry, "%s/%s", dir_entrada, nome_arq_qry);
        
        printf("Processando .qry: %s\n", path_qry);
        leitura_qry(path_qry, s);
        escreve_svg(get_svg_qry(s), s); // Gera SVG final combinado
    }

    // Finalização e Liberação de memória
    fecha_sistema(&s);
    printf("Feito. Arquivos salvos em: %s\n", dir_saida);

    return 0;
}