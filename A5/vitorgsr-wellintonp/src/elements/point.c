#include "../include/headers.h"
#include "point.h"

typedef struct {
    double x;
    double y;
}point;

Point createPoint(double x, double y){

    point* p = (point*) malloc(sizeof(point));
    if(p == NULL)
        return NULL;

    (*p).x = x;
    (*p).y = y;

    return p;
}

double getPointX(Point P){
    if(P == NULL)
        return 0;
    point* p = (point*) P;
    return (*p).x;
}

void setPointX(Point P, double x){
    if(P == NULL)
        return;
    point* p = (point*) P;
    p->x = x;
}


double getPointY(Point P){
    if(P == NULL)
        return 0;
    point* p = (point*) P;
    return p->y;
}

void setPointY(Point P, double y){
    if(P == NULL)
        return;
    point* p = (point*) P;
    p->y = y;
}


double distanceBetweenPoints(Point P1, Point P2) { 
    if(P1 == NULL || P2 == NULL) return -1;

    point* p1 = (point*) P1;
    point* p2 = (point*) P2;

    return sqrt(pow((p1->x - p2->x), 2) + pow((p1->y - p2->y), 2)); 
} 
  

int findOrientationOfOrderedPoints(Point P1, Point P2, Point P3){ 
    
    if(P1 == NULL || P2 == NULL || P3 == NULL) return -1;

    point* p1 = (point*) P1;
    point* p2 = (point*) P2;
    point* p3 = (point*) P3;

    int orientation = (int) ((p2->y - p1->y) * (p3->x - p2->x) - (p2->x - p1->x) * (p3->y - p2->y)); 

    if (orientation == 0) 
        return 0; // os pontos sao colineares.

    else if(orientation > 0)
        return 1; // os pontos estao em sentido horario.

    else
        return 2; // os pontos estao em sentido anti-horario.
} 

char* pointToString(Point P){
   if(P == NULL) return NULL;
    point* p = (point*) P; 
    char* string = (char*) malloc(30 * sizeof(char));
    sprintf(string, "(%.2lf, %.2lf)", p->x, p->y);
    return string;
}

void printPoint(Point P){
    if(P == NULL)
        return;
    point* p = (point*) P;
    printf("Point - x: %.2lf y: %.2lf\n", p->x, p->y);
}

void freePoint(Point P){
    if(P == NULL) return;
    point* p = (point*) P;
    free(p);
}