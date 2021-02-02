#ifndef POINT_H
#define POINT_H

typedef void* Point;

/*
*/

/*
    Pré condição: Requer dois valores do tipo double especificando as coordenadas do ponto.
    Pós condição: Cria uma instância de ponto com as coordenadas do parâmetro.
*/
Point createPoint(double x, double y);


/*
    Pré condição: Requer uma instancia do tipo Point.
    Pós condição: Retorna o valor de X da instancia de ponto passada por parâmetro.
*/
double getPointX(Point P);

/*
    Pré condição: Requer uma instancia do tipo Point e um valor double.
    Pós condição: Atribui o valor passado para o membro x do ponto.
*/
void setPointX(Point P, double x);

/*
    Pré condição: Requer uma instancia do tipo Point.
    Pós condição: Retorna o valor de Y da instancia de ponto passada por parâmetro.
*/
double getPointY(Point P);

/*
    Pré condição: Requer uma instancia do tipo Point e um valor double.
    Pós condição: Atribui o valor passado para o membro y do ponto.
*/
void setPointY(Point P, double y);

/*
    Pré condição: Requer uma instancia do tipo Point.
    Pós condição: Imprimir na saida padrão essa variavel.
*/
void printPoint(Point P);


#endif