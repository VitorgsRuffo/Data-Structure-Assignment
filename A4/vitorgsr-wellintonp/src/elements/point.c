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

void printPoint(Point P){
    if(P == NULL)
        return;
    point* p = (point*) P;
    printf("Point - x: %.2lf y: %.2lf\n", p->x, p->y);
}