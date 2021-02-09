#include "../../include/headers.h"
#include "./circle.h"

typedef struct circle{
    char* id;
    char* radius;
    char* x;
    char* y;
    Point coordinates;
    char* corb;
    char* corp;
    char* cw;
}circle;

Circle createCircle(char* id, char* radius, char* x, char* y, char* corb, char* corp, char* cw){

    circle *circ = (circle*) malloc(sizeof(circle));

    circ->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    circ->radius = (char*) malloc((strlen(radius) + 1) * sizeof(char));
    circ->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    circ->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    circ->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    circ->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    circ->cw = (char*) malloc((strlen(cw) + 1) * sizeof(char));

    strcpy(circ->id, id);
    strcpy(circ->radius, radius);
    strcpy(circ->x, x);
    strcpy(circ->y, y);
    circ->coordinates = createPoint(atof(x), atof(y));
    strcpy(circ->corb, corb);
    strcpy(circ->corp, corp);
    strcpy(circ->cw, cw);

    return circ;
}

char* getCircleId(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->id;
}

char* getCircleRadius(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->radius;
}

char* getCircleX(Circle Circ){
    if(Circ == NULL)
        return NULL; 
    circle *circ = (circle*) Circ;
    return circ->x;
}

char* getCircleY(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->y;
}

Point getCircleCoordinates(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->coordinates;
}

char* getCircleCorb(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->corb;
}

void setCircleCorb(Circle Circ, char* corb){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    strcpy(circ->corb, corb);
}

char* getCircleCorp(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->corp;
}

void setCircleCorp(Circle Circ, char* corp){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    strcpy(circ->corp, corp);
}

char* getCircleCw(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->cw;
}

char* circleToString(Circle Circ){
    if(Circ == NULL)
        return NULL;

    circle *circ = (circle*) Circ;

    char* circleInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(circleInfoString, "Tipo: circulo, id: %s, radius: %s, x: %s, y: %s, corb: %s, corp: %s, cw: %s", circ->id, circ->radius, circ->x, circ->y, circ->corb, circ->corp, circ->cw);
    return circleInfoString;
}

int isPointInsideCirc(Circle Circ, Point P){
    circle *circ = (circle*) Circ;

    double pointX = getPointX(P);
    double pointY = getPointY(P);
    double circX = atof((*circ).x);
    double circY = atof((*circ).y);
    double circR = atof((*circ).radius);

    double pointCircCenterDistance = sqrt( pow((pointX-circX), 2) + pow((pointY-circY), 2) );

    if(pointCircCenterDistance < circR)
        return 1;
    else
        return 0;
}

void printCircle(Circle Circ){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    printf("Circulo:\nId: %s\nradius: %s\nx: %s\ny: %s\ncorb: %s\ncorp: %s\ncw: %s\n\n\n", 
           circ->id, circ->radius, circ->x, circ->y, circ->corb, circ->corp, circ->cw);
}

void freeCircle(Circle Circ){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    free(circ->id);  
    free(circ->radius);    
    free(circ->x); 
    free(circ->y); 
    free(circ->coordinates);
    free(circ->corb); 
    free(circ->corp); 
    free(circ->cw);   
    free(circ);
}