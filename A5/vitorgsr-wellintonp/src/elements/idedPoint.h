#ifndef IDED_POINT_H
#define IDED_POINT_H

#include "point.h"

typedef void* IdedPoint;

/*
*   Pre-condicao: requer um id, um valor x e um valor y.
*   Pos-condicao: criar e retorna um objeto do tipo IdedPoint com as informacoes passadas.
*/
IdedPoint createIdedPoint(char* id, double x, double y);

/*
*   Pre-condicao: Requer uma instancia do tipo IdedPoint.
*   Pos-condicao: retorna o id da instancia.
*/
char* getIdedPointId(IdedPoint IP);

/*
*   Pre-condicao: Requer uma instancia do tipo IdedPoint.
*   Pos-condicao: retorna as coordenadas da instancia.
*/
Point getIdedPointCoordinates(IdedPoint IP);

/*
    Pré condição: Requer uma instancia do tipo IdedPoint.
    Pós condição: desaloca a memoria usada pelo tad.
*/
void freeIdedPoint(IdedPoint IP);

#endif