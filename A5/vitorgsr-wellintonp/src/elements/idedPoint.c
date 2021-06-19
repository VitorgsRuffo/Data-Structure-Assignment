#include "../include/headers.h"
#include "idedPoint.h"

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

char* idedPointToString(IdedPoint IP){
   if(IP == NULL) return NULL;
    idedPoint* ip = (idedPoint*) IP; 
    
    char* string = (char*) malloc(50 * sizeof(char));
    sprintf(string, "(%s)(%.2lf, %.2lf)",ip->id, getPointX(ip->coordinates), getPointY(ip->coordinates));
    return string;
}

void freeIdedPoint(IdedPoint IP){
    if(IP == NULL) return;
    idedPoint* iP = (idedPoint*) IP;
    freePoint(iP->coordinates);
    free(iP);
}