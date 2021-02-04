#include "../include/headers.h"
#include "../include/util.h"
#include "healthCenter.h"

typedef struct healthCenter{
    int id;
    char* x;
    char* y;
    Point coordinates;
    char* radius;
}healthCenter;


HealthCenter createHealthCenter(int id, char* x, char* y){

    healthCenter *healthC = (healthCenter*) malloc(sizeof(healthCenter));

    healthC->id = id;
    healthC->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    healthC->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    healthC->radius = (char*) malloc(4 * sizeof(char));

    strcpy(healthC->x, x);
    strcpy(healthC->y, y);
    healthC->coordinates = createPoint(atof(x), atof(y));
    strcpy(healthC->radius, "10");

    return healthC;
}

int getHealthCenterId(HealthCenter HealthC){
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->id;
}

char* getHealthCenterX(HealthCenter HealthC){
    if(isElementNull(HealthC, "posto de saude", "getHealthCenterX"))
        return NULL;
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->x;
}

char* getHealthCenterY(HealthCenter HealthC){
    if(isElementNull(HealthC, "posto de saude", "getHealthCenterY"))
        return NULL;
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->y;
}

Point getHealthCenterCoordinates(HealthCenter HealthC){
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->coordinates;
}

char* getHealthCenterRadius(HealthCenter HealthC){
    if(isElementNull(HealthC, "posto de saude", "getHealthCenterRadius"))
        return NULL;
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->radius;
}

void freeHealthCenter(HealthCenter HealthC){
    if(isElementNull(HealthC, "posto de saude", "freeHealthCenter"))
        return;

    healthCenter *healthC = (healthCenter*) HealthC;

    free(healthC->x); 
    free(healthC->y);  
    free(healthC->coordinates);
    free(healthC->radius);
    free(healthC);
}