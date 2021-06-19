#include "../../include/headers.h"
#include "healthCenter.h"

typedef struct healthCenter{
    char* id;
    char* x;
    char* y;
    Point coordinates;
    char* radius;
}healthCenter;


HealthCenter createHealthCenter(int id, char* x, char* y){

    healthCenter *healthC = (healthCenter*) malloc(sizeof(healthCenter));

    char idString[5];
    sprintf(idString, "%d", id);
    
    healthC->id = (char*) malloc(6 * sizeof(char));
    healthC->x = (char*) malloc((strlen(x) + 10) * sizeof(char));
    healthC->y = (char*) malloc((strlen(y) + 10) * sizeof(char));
    healthC->radius = (char*) malloc(20 * sizeof(char));

    strcpy(healthC->id, idString);
    strcpy(healthC->x, x);
    strcpy(healthC->y, y);
    healthC->coordinates = createPoint(atof(x), atof(y));
    strcpy(healthC->radius, "10");

    return healthC;
}

char* getHealthCenterId(HealthCenter HealthC){
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->id;
}

char* getHealthCenterX(HealthCenter HealthC){
    if(HealthC == NULL)
        return NULL;
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->x;
}

char* getHealthCenterY(HealthCenter HealthC){
    if(HealthC == NULL)
        return NULL;
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->y;
}

Point getHealthCenterCoordinates(HealthCenter HealthC){
    if(HealthC == NULL)
        return NULL;
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->coordinates;
}

char* getHealthCenterRadius(HealthCenter HealthC){
    if(HealthC == NULL)
        return NULL;
    healthCenter *healthC = (healthCenter*) HealthC;
    return healthC->radius;
}

char* healthCenterToString(HealthCenter HealthC){
    if(HealthC == NULL)
        return NULL;

    healthCenter *healthC = (healthCenter*) HealthC;

    char* string = (char*) malloc(200 * sizeof(char));
    sprintf(string, "Tipo: posto de saude, id: %s, x: %s, y: %s, radius: %s", healthC->id, healthC->x, healthC->y, healthC->radius);
    return string;
}

void freeHealthCenter(HealthCenter HealthC){
    if(HealthC == NULL)
        return;

    healthCenter *healthC = (healthCenter*) HealthC;

    free(healthC->id);
    free(healthC->x); 
    free(healthC->y);  
    free(healthC->coordinates);
    free(healthC->radius);
    free(healthC);
}