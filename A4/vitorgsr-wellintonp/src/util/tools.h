#ifndef TOOLS_H
#define TOOLS_H

#include "./input/parameters.h"
#include "../include/dataStructure.h"
#include "../elements/point.h"

/* 
* Definicao do tamanho maximo de uma linha de comando de um arquivo de entrada (linha do geo/qry) 
*/
#define commandMaxLength 200

/*
* Pré-condição: requer o endereço de duas informacoes.
* Pós-condição: as informacoes têm seu conteudo trocado.
*/
void swapInformations(Info* info1, Info* info2);

/*
* Pré-condição: nenhuma.
* Pós-condição: aloca memoria dinamicamente para um vetor de ponteiros para char e retorna o endereco do vetor.
*/
char** createCommandParts(int numberOfParts);

/*
* Pré-Condição: requer um caminho (svg ou geo) contendo uma possivel extensao.
* Pós-Condição: retorna somente o nome do arquivo, retirando possivel caminho e a sua extensão.
*/
char* getFileNameWithoutPathAndExtension(char* fullFileName);

/*
* Pré-Condição: requer um TAD parametros, e a extensao de um arquivo de saida (svg ou txt).
* Pós-Condição: constroi o caminho de saida para uma arquivo de output do query, seja ele um svg ou txt. Esse caminho e retornado.
*/
char* buildQryOutputPath(Parameters Param, char* extension);

/*
* Pré-Condição: requer um TAD que seja um elemento urbano e o tipo desse elemento.
* Pós-Condição: retorna a string que informa todas as informacoes do elemento urbano passado.
*/
char* getUrbanElementToString(Info urbanElementInfo, char* urbanElementType);

/*
* Pré-Condição: requer um vetor de pontos e o tamanho do vetor.
* Pós-Condição: retorna uma pilha contendo a envoltoria convexa dos pontos do vetor.
*/
Stack convexHull(Point* points, int n);

#endif 