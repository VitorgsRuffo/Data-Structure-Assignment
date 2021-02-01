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
    point* p = (point*) P;
    return (*p).x;
}

double getPointY(Point P){
    point* p = (point*) P;
    return p->y;
}

void printPoint(Point P){
    point* p = (point*) P;
    printf("Point - x: %.2lf y: %.2lf\n", p->x, p->y);
}