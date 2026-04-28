#ifndef LEITURA_GEO
#define LEITURA_GEO 

#include <stdbool.h>

/*
    leitura.h
    Módulo responsável pela leitura dos arquivos de entrada .geo e .svg 

*/
typedef void* FILA;

bool leitura_geo(char* path_geo, FILA formas);

bool leitura_svg(char* path_svg, FILA formas);






#endif