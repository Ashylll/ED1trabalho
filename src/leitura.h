#ifndef LEITURA_GEO
#define LEITURA_GEO 

#include <stdbool.h>

/*
    leitura.h
    Módulo responsável pela leitura dos arquivos de entrada .geo e .svg 

*/

typedef void* LISTA;

bool leitura_geo(char* path_geo, LISTA formas);

bool leitura_svg(char* path_svg, LISTA formas);






#endif