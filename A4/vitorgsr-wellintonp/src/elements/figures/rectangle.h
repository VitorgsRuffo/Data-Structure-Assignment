#ifndef RECTANGLE_H
#define RECTANGLE_H

/*
* Tipo abstrato de dados que representa a figura retangulo.
*/
typedef void* Rectangle;


#include "../point.h"
#include "circle.h"


/*
* Pré-Condição: requer os dados (strings) que compoem um Retangulo.
* Pós-Condição: retorna o endereco de uma nova instancia de Retangulo que possui as informacoes passadas.
*/
Rectangle createRectangle(char* id, char* width, char* height, char* x, char* y, char* corb, char* corp, char* rw);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna o id do retangulo passado.
*/
char* getRectangleId(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna a largura do retangulo passado.
*/
char* getRectangleWidth(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo e um valor.
* Pós-Condição: atribui o valor passado para o membro "width" do retangulo.
*/
void setRectangleWidth(Rectangle Rect, char* width);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna a altura do retangulo passado.
*/
char* getRectangleHeight(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo e um valor.
* Pós-Condição: atribui o valor passado para o membro "height" do retangulo.
*/
void setRectangleHeight(Rectangle Rect, char* height);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna a coordenada x do canto superior esquerdo retangulo passado.
*/
char* getRectangleX(Rectangle Rect);

/*  
*  Pré-Condição: requer o endereco de uma instancia de retangulo e um valor x.
*  Pós-Condição: atribui o valor passado para a coordenada x do retangulo.
*/
void setRectangleX(Rectangle Rect, char* x);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna a coordenada y do canto superior esquerdo do retangulo passado.
*/
char* getRectangleY(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo e um valor y.
* Pós-Condição: atribui o valor passado para a coordenada y do retangulo.
*/
void setRectangleY(Rectangle Rect, char* y);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna uma instancia de ponto que representa a localizacao desse retangulo.
*/
Point getRectangleCoordinates(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna a cor da borda do retangulo passado.
*/
char* getRectangleCorb(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo e uma cor.
* Pós-Condição: atribui a cor passada á cor de borda do retangulo.
*/
void setRectangleCorb(Rectangle Rect, char* corb);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna a cor de preenchimento do retangulo passado.
*/
char* getRectangleCorp(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo e uma cor.
* Pós-Condição: atribui a cor passada á cor de preenchimento do retangulo.
*/
void setRectangleCorp(Rectangle Rect, char* corp);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna a espessura da borda do retangulo passado.
*/
char* getRectangleRw(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo.
* Pós-Condição: retorna uma string com todas as informacoes da instancia de Retangulo passada.
*/
char* rectangleToString(Rectangle Rect);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo e de ponto.
* Pós-Condição: retorna 1 se o ponto se encontra dentro do retangulo, retorna 0 se nao.
*/
int isPointInsideRect(Rectangle Rect, Point P);

/*  
* Pré-Condição: requer o endereco de duas instancias de retangulo.
* Pós-Condição: retorna 1 se o primeiro retangulo esta INTEIRAMENTE dentro do segundo retangulo, retorna 0 se nao.
*/
int isRectangleInsideRectangle(Rectangle Rect1, Rectangle Rect2);

/*  
* Pré-Condição: requer o endereco de uma instancia de retangulo e de circulo.
* Pós-Condição: retorna 1 se o circulo se encontra INTEIRAMENTE dentro do retangulo, se nao retorna 0.
*/
int isCircleInsideRectangle(Rectangle Rect, Circle Circ);

/*  
* Pré-Condição: requer o endereco de duas instancias de retangulo.
* Pós-Condição: retorna 1 se um retangulo se sobrepõe com o outro, retorna 0 se nao.
*/
int isThereRectanglesOverlap(Rectangle Rect1, Rectangle Rect2);


/*
* Pré-Condição: requer o endereco de uma instancia de Retangulo.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printRectangle(Rectangle Rect);

/*
* Pré-Condição: requer o endereco de uma instancia de Retangulo.
* Pós-Condição: libera a memoria usada pela instancia de Retangulo que foi passada.
*/
void freeRectangle(Rectangle Rect);


#endif