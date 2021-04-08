#include "../include/headers.h"
#include "idedPoint.h"
#include "point.h"

typedef struct {
    char id[50];
    Point coordinates;
}idedPoint;

IdedPoint createIdedPoint(char* id, double x, double y){
    idedPoint* iP = (idedPoint*) malloc(sizeof(idedPoint));
    if(iP == NULL) return NULL;

    strcpy(iP->id, id);

    iP->coordinates = createPoint(x, y);
    if(iP->coordinates == NULL){
        free(iP);
        return NULL;
    }

    return iP;
}

char* getIdedPointId(IdedPoint IP){
    if(IP == NULL) return NULL;
    idedPoint* iP = (idedPoint*) IP;

    return iP->id;   
}

Point getIdedPointCoordinates(IdedPoint IP){
    if(IP == NULL) return NULL;
    idedPoint* iP = (idedPoint*) IP;

    return iP->coordinates;   
}

void freeIdedPoint(IdedPoint IP){
    if(IP == NULL) return NULL;
    idedPoint* iP = (idedPoint*) IP;
    free(iP);
}