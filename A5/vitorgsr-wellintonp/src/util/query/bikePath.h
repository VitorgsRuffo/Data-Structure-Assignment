#ifndef BIKE_PATH_H
#define BIKE_PATH_H

/*
* Pré-Condição: requer uma referencia para a string do comando ccv, uma referencia para uma instancia do TAD cidade. 
* Pós-Condição: cria uma arvore geradora minima do grafo que representa as ruas da cidade, e armazena no TAD cidade. Esta arvore representa as ciclovias da cidade.
*               A arvore tambem é desenhada em um svg.
*/
void createCityBikePath(char* command, City Ct, Parameters Param);

#endif