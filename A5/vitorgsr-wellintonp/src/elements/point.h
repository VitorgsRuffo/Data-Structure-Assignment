#ifndef POINT_H
#define POINT_H

/*
* Tipo que representa um ponto no plano.
*/
typedef void* Point;


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
    Pré condição: Requer duas instancias do tipo Point.
    Pós condição: Calcula e retorna a distancia entre esses dois pontos.
*/
double distanceBetweenPoints(Point P1, Point P2);

/*
    Pré condição: Requer um trio ordenado de instancias do tipo Point.
    Pós condição: Calcula e retorna a orientacao desses pontos.
                  Retorna 0 se os pontos forem colineares.
                  Retorna 1 se os pontos estao em sentido horario.
                  Retorna 2 se os pontos estao em sentido anti-horario.
*/
int findOrientationOfOrderedPoints(Point P1, Point P2, Point P3);

/*  
* Pré-Condição: requer o endereco de uma instancia de ponto.
* Pós-Condição: retorna uma string com as informacoes da instancia de ponto passada.
*/
char* pointToString(Point P);

/*
    Pré condição: Requer uma instancia do tipo Point.
    Pós condição: Imprimir na saida padrão essa variavel.
*/
void printPoint(Point P);

/*
    Pré condição: Requer uma instancia do tipo Point.
    Pós condição: desaloca a memoria usada pelo tad.
*/
void freePoint(Point P);

#endif