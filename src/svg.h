#ifndef SVG_H
#define SVG_H

#include "sistema.h"

/*
    svg.h
    Módulo responsável pela escrita em arquivos .svg

    Escreve as figuras iniciais (.geo) e finais (após .qry, caso haja) do programa nos arquivos do sistema

*/

/// @brief escreve o cabeçalho do .svg
/// @param fp arquivo .svg aberto em modo escrita
/// @pre fp != NULL
void svg_begin(FILE *fp);

/// @brief escreve o rodapé do .svg
/// @param fp arquivo .svg aberto em modo 
/// @pre fp != NULL
void svg_end(FILE *fp);

/// @brief escreve em um arquivo .svg apenas as figuras do banco de dados (guardadas em sistema)
/// @param fp arquivo .svg aberto em modo escrita
/// @param s sistema
/// @pre fp != NULL && s != NULL
/// @return true se a operação foi bem-sucedida; false se não
bool escreve_svg(FILE *fp, SISTEMA s);

#endif