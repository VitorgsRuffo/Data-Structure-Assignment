#include "../include/headers.h"
#include "hydrant.h"
#include "../point.h"

typedef struct hydrant{
    char* id;
    char* x;
    char* y;
    char* radius;
    Point coordinates;
    char* sw;
    char* cfill;
    char* cstrk;
}hydrant;

Hydrant createHydrant(char* id, char* x, char* y, char* sw, char* cfill, char* cstrk){

    hydrant *hyd = (hydrant*) malloc(sizeof(hydrant));

    hyd->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    hyd->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    hyd->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    hyd->radius = (char*) malloc(4 * sizeof(char));
    hyd->sw = (char*) malloc(20 * sizeof(char));
    hyd->cfill = (char*) malloc(20 * sizeof(char));
    hyd->cstrk = (char*) malloc(20 * sizeof(char));
    
    strcpy(hyd->id, id);
    strcpy(hyd->x, x);
    strcpy(hyd->y, y);
    strcpy(hyd->radius, "10");
    hyd->coordinates = createPoint(atof(x), atof(y));
    strcpy(hyd->sw, sw);
    strcpy(hyd->cfill, cfill);
    strcpy(hyd->cstrk, cstrk);

    return hyd;
}

char* getHydrantId(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->id;
}

char* getHydrantX(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->x;
}

char* getHydrantY(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->y;
}

char* getHydrantRadius(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->radius;
}

Point getHydrantCoordinates(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->coordinates;
}

char* getHydrantSw(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->sw;
}

void setHydrantSw(Hydrant Hyd, char* sw){
    if(Hyd == NULL)
        return;
    hydrant *hyd = (hydrant*) Hyd;
    strcpy(hyd->sw, sw);
}

char* getHydrantCfill(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->cfill;
}

char* getHydrantCstrk(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->cstrk;
}

double getHydrantArea(Hydrant Hyd){
    if(Hyd == NULL)
        return 0;

    hydrant *hyd = (hydrant*) Hyd;
    return 3.141592 * ( atof(hyd->radius) * atof(hyd->radius) );      
}

char* hydrantToString(Hydrant Hyd){
    if(Hyd == NULL)
        return NULL;

    hydrant *hyd = (hydrant*) Hyd;

    char* hydrantInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(hydrantInfoString, "Tipo: hidrante, id: %s, x: %s, y: %s, sw: %s, cfill: %s, cstrk: %s", hyd->id, hyd->x, hyd->y, hyd->sw, hyd->cfill, hyd->cstrk);
    return hydrantInfoString;
}

void printHydrant(Hydrant Hyd){
    if(Hyd == NULL)
        return;
    hydrant *hyd = (hydrant*) Hyd;
    printf("Hidrante:\nId: %s\nx: %s\ny: %s\nsw: %s\ncfill: %s\ncstrk: %s\n\n\n",
           hyd->id, hyd->x, hyd->y, hyd->sw, hyd->cfill, hyd->cstrk);
}


void freeHydrant(Hydrant Hyd){
    
    if(Hyd == NULL)
        return;

    hydrant *hyd = (hydrant*) Hyd;
    free(hyd->id);  
    free(hyd->x); 
    free(hyd->y);
    free(hyd->radius);
    free(hyd->coordinates);
    free(hyd->sw);
    free(hyd->cfill);  
    free(hyd->cstrk);

    free(hyd);
}