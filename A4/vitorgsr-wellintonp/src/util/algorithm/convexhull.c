#include "../../include/headers.h"
#include "convexhull.h"
#include "sort.h"
#include "../tools.h"

Point p0; 

int comparePoints(Info P1, Info P2);

Stack convexHull(Point* points, int pointsAmount) { 

    //encontrando o ponto mais a cima do plano (considerando que o eixo y cresce para baixo).
    //obs: caso mais de um ponto tem o menor y o desempate é feito checando quem tem o menor x.
    int ymin = getPointY(*points), min = 0; 
    
    for (int i = 1; i < pointsAmount; i++) { 
        int y = getPointY(*(points + i)); 

        if ((y < ymin) ||
            (ymin == y && getPointX(*(points + i)) < getPointX(*(points + min)))) 

            ymin = getPointY(*(points + i)), min = i; 
    } 

    //colocando o ponto mais a cima do plano na primeira posicao do vetor.
    swapInformations(points, points + min); 

    //teremos uma referencia especial(p0) para esse ponto mais a cima do plano. 
    p0 = *points;

    //ordenaremos os pontos (a partir do segundo) efetuando uma comparacao que depende do ponto p0.
    quicksort((points + 1), 0, pointsAmount-1, comparePoints);

    
    int m = 1; 
    for (int i=1; i<pointsAmount; i++) { 
    
        while (i < pointsAmount-1 && findOrientationOfOrderedPoints(p0, *(points + i), *(points + i + 1)) == 0) 
            i++; 

        *(points + m) = *(points + i);
        m++; 
    } 

    
    if (m < 3) 
        return NULL; 

    
    Stack head = createStack();
    stackPush(&head, *(points)); 
    stackPush(&head, *(points + 1));
    stackPush(&head, *(points + 2));

    
    for (int i = 3; i < m; i++) { 
        while (findOrientationOfOrderedPoints(nextToTop(&head), stackTop(&head), *(points + i)) != 2) 
            stackPop(&head); 
        
        stackPush(&head, *(points + i));
    } 

    return head;
} 

// Funcao que compara dois pontos em relacao ao ponto p0.
//P1 vai vai vir antes (ou, vai ser menor) que P2, se P2 tiver um angulo polar maior do que o de P1 (obs: considerando o sentido anti-horario)
int comparePoints(Info P1, Info P2) { 

    Point p1 = (Point) P1; 
    Point p2 = (Point) P2;

    int orientation = findOrientationOfOrderedPoints(p0, p1, p2); 

    if(orientation == 0){
        
        double squareOfDistanceBetweenp0Np2 = pow(distanceBetweenPoints(p0, p2), 2);
        double squareOfDistanceBetweenp0Np1 = pow(distanceBetweenPoints(p0, p1), 2);

        if(squareOfDistanceBetweenp0Np2 >= squareOfDistanceBetweenp0Np1)
            return -1;
        else
            return 1;

    }

    else if(orientation == 2)
        return -1;
    else
        return 1;
}