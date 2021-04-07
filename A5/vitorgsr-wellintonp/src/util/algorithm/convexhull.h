#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "../../elements/point.h"
#include "../data-structure/stack.h"


/*
* Pré-condição: Requer um vetor de pontos e um valor inteiro que informa o quantidade de elementos do vetor passado.
* Pós-condição: Retorna uma pilha com contendo a envoltoria convexa dos pontos passados.
*/
Stack convexHull(Point* points, int pointsAmount);

#endif