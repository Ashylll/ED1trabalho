#ifndef LEITURA_GEO
#define LEITURA_GEO 

#include <stdbool.h>

/*
    leitura.h
    Módulo responsável pela leitura dos arquivos de entrada .geo e .qry
    .geo: contém informações das formas que são criadas no início do programa  
    .qry: contém instruções a serem realizadas sobre as formas, podendo criar, deletar ou modificá-las
    Ao ler o .qry, o programa já escreve na saída .txt os logs das operações
    Recebe de entrada o SISTEMA, responsável por armazenar e permitir acesso às filas, listas e arquivos correntes

*/

typedef void* SISTEMA;

/// @brief realiza a leitura do arquivo .geo, cria as figuras iniciais e as insere na lista corrente de formas
/// @param path_geo caminho do arquivo de entrada .geo
/// @param s sistema
/// @return true se a operação foi bem-sucedida; false se não
bool leitura_geo(const char* path_geo, SISTEMA s);

/// @brief realiza a leitura do arquivo .qry, registra as mudanças realizadas pelos comandos e escreve no arquivo log .txt
/// @param path_qry caminho do arquivo de entrada .qry
/// @param s sistema
/// @return true se a operação foi bem-sucedida; false se não
bool leitura_qry(const char* path_qry, SISTEMA s);

#endif