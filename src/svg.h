#ifndef SVG_H
#define SVG_H

#include "sistema.h"

/*
    svg.h
    Módulo responsável pela escrita em arquivos .svg
    Desenha as figuras iniciais e finais do programa

*/

/// @brief escreve o cabeçalho do .svg
/// @param fp arquivo .svg aberto em modo escrita
void svg_begin(FILE *fp);

/// @brief escreve o rodapé do .svg
/// @param fp arquivo .svg aberto em modo escrita
void svg_end(FILE *fp);

/// @brief escreve em um arquivo .svg as figuras do banco de dados
/// @param fp arquivo .svg aberto em modo escrita
/// @param s sistema
/// @return true se a operação foi bem-sucedida; false se não
bool escreve_svg(FILE *fp, SISTEMA s);

#endif