#ifndef CIRCLE_H
#define CIRCLE_H
/*
*   Tipo abstrato de dado que representa a figura circulo.
*/
typedef void* Circle;

#include "../point.h"
#include "rectangle.h"

/*  
* Pré-Condição: requer os dados (strings) que compoem um Circulo.
* Pós-Condição: retorna o endereco de uma nova instancia de circulo que possui as informacoes passadas.
*/
Circle createCircle(char* id, char* radius, char* x, char* y, char* corb, char* corp, char* cw);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna o id do circulo passado.
*/
char* getCircleId(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna o raio do circulo passado.
*/
char* getCircleRadius(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorOna a coordenada x do centro do circulo passado.
*/
char* getCircleX(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna a coordenada y do centro do circulo passado.
*/
char* getCircleY(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna uma instancia de ponto que representa a localizacao desse circulo.
*/
Point getCircleCoordinates(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna a cor da borda do circulo passado.
*/
char* getCircleCorb(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo e uma cor.
* Pós-Condição: atribui a cor passada á cor de borda do circulo.
*/
void setCircleCorb(Circle Circ, char* corb);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna a cor de preenchimento do circulo passado.
*/
char* getCircleCorp(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo e uma cor.
* Pós-Condição: atribui a cor passada á cor de preenchimento do circulo.
*/
void setCircleCorp(Circle Circ, char* corp);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna a espessura da borda do circulo passado.
*/
char* getCircleCw(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: retorna uma string com todas as informacoes da instancia de circulo passada.
*/
char* circleToString(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo e de ponto.
* Pós-Condição: retorna 1 se o ponto se encontra dentro do circulo, retorna 0 se nao.
*/
int isPointInsideCirc(Circle Circ, Point P);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo e de retangulo.
* Pós-Condição: retorna 1 se o retangulo se encontra INTEIRAMENTE dentro do circulo, se nao retorna 0.
*/
int isRectangleInsideCircle(Circle Circ, Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de duas instancias de circulos.
* Pós-Condição: retorna 1 caso um dos circulos se sobrepõe o outro, caso contrário retorna 0.
*/
int isThereCirclesOverlap(Circle Circ1, Circle Circ2);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo e de retangulo.
* Pós-Condição: retorna 1 se as figuras se sobrepoẽm, caso contrário retorna 0.
*/
int isThereOverlapBetweenCircleAndRectangle(Circle Circ, Rectangle Rect);

/*
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printCircle(Circle Circ);

/*  
* Pré-Condição: requer o endereco de uma instancia de circulo.
* Pós-Condição: libera a memoria usada pela instancia de circulo que foi passada.
*/
void freeCircle(Circle Circ);

#endif