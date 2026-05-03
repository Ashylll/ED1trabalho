#ifndef SISTEMA_H
#define SISTEMA_H

#include "lista.h"
#include "fila.h"
#include <stdio.h>

/*
    sistema.h

    Módulo dedicado a organizar e simplificar o banco de dados
    O sistema é criado no início do programa e é responsável por armazenar todas as âncoras de dados do programa 

*/
typedef void* SISTEMA;

/// @brief cria o banco de dados SISTEMA
/// @param path_txt caminho do arquivo .txt
/// @param path_svg_geo caminho do arquivo .geo
/// @param path_svg_qry caminho do arquivo .qry 
/// @return sistema criado
SISTEMA cria_sistema(const char* path_txt, const char* path_svg_geo, const char* path_svg_qry);

/// @brief retorna a lista de formas principal do sistema
/// @param s sistema 
/// @pre s != NULL
/// @return lista de formas
LISTA get_formas(SISTEMA s);

/// @brief retorna a fila de polígonos do sistema
/// @param s sistema
/// @pre s != NULL
/// @return fila de polígonos
FILA get_poligonos(SISTEMA s);

/// @brief retorna a fila das formas selecionadas por comando do .qry
/// @param s sistema
/// @pre s != NULL
/// @return fila de formas selecionas
FILA get_selecionadas(SISTEMA s);

/// @brief retorna a lista das formas auxiliares 
/// @param s sistema
/// @pre s != NULL
/// @return lista de formas auxiliares
LISTA get_svg_aux(SISTEMA s);

/// @brief retorna o arquivo .txt de saída
/// @param s sistema
/// @pre s != NULL
/// @return arquivo .txt
FILE* get_arquivo_txt(SISTEMA s);

/// @brief retorna o arquivo .svg inicial (após a leitura do .geo)  de saída
/// @param s sistema
/// @pre s != NULL
/// @return arquivo .svg final
FILE* get_svg_geo(SISTEMA s);

/// @brief retorna o arquivo .svg final (após a leitura do .qry) de saída
/// @param s sistema
/// @pre s != NULL
/// @return arquivo .svg final
FILE* get_svg_qry(SISTEMA s);

/// @brief atribui o estilo de texto
/// @param s sistema
/// @param fFamily família do estilo (sans-serif, serif, cursive)
/// @param fWeight expessura do estilo (n: normal, b: bold, b+: bolder, l: lighter)
/// @param fSize tamanho do estilo
/// @pre t != NULL && fFamily != NULL && fWeight != NULL && fSize > 0
void set_estilo_texto(SISTEMA s, const char* family, const char* weight, double size);

/// @brief pega o estilo de texto atual
/// @param s sistema
/// @param family recebe a family do estilo
/// @param weight recebe o weight do estilo
/// @param size recebe o size do estilo
void get_estilo_texto(SISTEMA s, char* family, char* weight, double* size);

/// @brief encerra o sistema
/// @param s sistema
void fecha_sistema(SISTEMA* s);

#endif