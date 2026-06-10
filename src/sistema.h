#ifndef SISTEMA_H
#define SISTEMA_H

#include "lista.h"
#include "fila.h"
#include <stdio.h>

/*
    sistema.h

    Módulo dedicado a organizar e simplificar o banco de dados
    O sistema é responsável por armazenar todas as âncoras de dados do programa (filas, listas e arquivos) e permitir seu acesso

    Ele cria e carrega:   
        Filas de polígonos e de formas selecionadas (comando "sel")
        Listas de formas principais (entrada .geo) e de formas auxiliares (marcadores criados por comandos do .svg)

    Os arquivos .txt e .svg são passados ao sistema. Ao ser criado, escreve o cabeçalho dos .svg, e ao ser encerrado, escreve o rodapé

    Mantém o estilo atual do texto e permite sua alteração conforme a entrada de dados
    Estilo padrão inicial:
        Family: sans-serif
        Weight: normal
        Size: 12.0

*/
typedef void* Sistema;

/// @brief cria o banco de dados Sistema
/// @param path_txt caminho do arquivo .txt
/// @param path_svg_geo caminho do arquivo .svg inicial
/// @param path_svg_qry caminho do arquivo .svg final
/// @pre path_txt != NULL && path_svg_geo != NULL
/// @return sistema criado
Sistema cria_sistema(const char* path_txt, const char* path_svg_geo, const char* path_svg_qry);

/// @brief retorna a lista de formas principal do sistema
/// @param s sistema 
/// @pre s != NULL
/// @return lista de formas
Lista get_formas(Sistema s);

/// @brief retorna a fila de polígonos do sistema
/// @param s sistema
/// @pre s != NULL
/// @return fila de polígonos
Fila get_poligonos(Sistema s);

/// @brief retorna a fila das formas selecionadas por comando do .qry
/// @param s sistema
/// @pre s != NULL
/// @return fila de formas selecionas
Fila get_selecionadas(Sistema s);

/// @brief retorna a lista das formas auxiliares 
/// @param s sistema
/// @pre s != NULL
/// @return lista de formas auxiliares
Lista get_formas_aux(Sistema s);

/// @brief retorna o arquivo .txt de saída
/// @param s sistema
/// @pre s != NULL
/// @return arquivo .txt
FILE* get_arquivo_txt(Sistema s);

/// @brief retorna o arquivo .svg inicial (após a leitura do .geo)  de saída
/// @param s sistema
/// @pre s != NULL
/// @return arquivo .svg final
FILE* get_svg_geo(Sistema s);

/// @brief retorna o arquivo .svg final (após a leitura do .qry) de saída
/// @param s sistema
/// @pre s != NULL
/// @return arquivo .svg final
FILE* get_svg_qry(Sistema s);

/// @brief atribui o estilo de texto
/// @param s sistema
/// @param fFamily família do estilo (sans-serif, serif, cursive)
/// @param fWeight expessura do estilo (n: normal, b: bold, b+: bolder, l: lighter)
/// @param fSize tamanho do estilo
/// @pre t != NULL && fFamily != NULL && fWeight != NULL && fSize > 0
void set_estilo_texto(Sistema s, const char* family, const char* weight, double size);

/// @brief pega o estilo de texto atual
/// @param s sistema
/// @param family recebe a family do estilo
/// @param weight recebe o weight do estilo
/// @param size recebe o size do estilo
/// @pre s != NULL
void get_estilo_texto(Sistema s, char* family, char* weight, double* size);

/// @brief encerra o sistema
/// @param s sistema
/// @pre s != NULL
void fecha_sistema(Sistema* s);

#endif