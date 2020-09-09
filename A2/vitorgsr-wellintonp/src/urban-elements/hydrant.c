#include "../include/headers.h"
#include "../include/utils.h"
#include "hydrant.h"

typedef struct hydrant{
    char* id;
    char* x;
    char* y;
    char* sw;
    char* cfill;
    char* cstrk;
}hydrant;

Hydrant createHydrant(char* id, char* x, char* y, char* sw, char* cfill, char* cstrk){

    hydrant *hyd = (hydrant*) malloc(sizeof(hydrant));

    hyd->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    hyd->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    hyd->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    hyd->sw = (char*) malloc(20 * sizeof(char));
    hyd->cfill = (char*) malloc(20 * sizeof(char));
    hyd->cstrk = (char*) malloc(20 * sizeof(char));
    
    strcpy(hyd->id, id);
    strcpy(hyd->x, x);
    strcpy(hyd->y, y);
    strcpy(hyd->sw, sw);
    strcpy(hyd->cfill, cfill);
    strcpy(hyd->cstrk, cstrk);

    return hyd;
}

char* getHydrantId(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "getHydrantId"))
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->id;
}

char* getHydrantX(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "getHydrantX"))
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->x;
}

char* getHydrantY(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "getHydrantY"))
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->y;
}

char* getHydrantSw(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "getHydrantSw"))
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->sw;
}

void setHydrantSw(Hydrant Hyd, char* sw){
    if(isElementNull(Hyd, "hidrante", "setHydrantSw"))
        return;
    hydrant *hyd = (hydrant*) Hyd;
    strcpy(hyd->sw, sw);
}

char* getHydrantCfill(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "getHydrantCfill"))
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->cfill;
}

char* getHydrantCstrk(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "getHydrantCstrk"))
        return NULL;
    hydrant *hyd = (hydrant*) Hyd;
    return hyd->cstrk;
}

double getHydrantArea(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "getHidranteArea"))
        return 0;

    //hydrant *hyd = (hydrant*) Hyd;
    return (3.141592 * (10*10));      
}

char* hydrantToString(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "hydrantToString"))
        return NULL;

    hydrant *hyd = (hydrant*) Hyd;

    char* hydrantInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(hydrantInfoString, "Tipo: hidrante, id: %s, x: %s, y: %s, sw: %s, cfill: %s, cstrk: %s", hyd->id, hyd->x, hyd->y, hyd->sw, hyd->cfill, hyd->cstrk);
    return hydrantInfoString;
}

void printHydrant(Hydrant Hyd){
    if(isElementNull(Hyd, "hidrante", "printHydrant"))
        return;
    hydrant *hyd = (hydrant*) Hyd;
    printf("Hidrante:\nId: %s\nx: %s\ny: %s\nsw: %s\ncfill: %s\ncstrk: %s\n\n\n",
           hyd->id, hyd->x, hyd->y, hyd->sw, hyd->cfill, hyd->cstrk);
}


void freeHydrant(Hydrant Hyd){
    
    if(isElementNull(Hyd, "hidrante", "freeHydrant"))
        return;

    hydrant *hyd = (hydrant*) Hyd;
    free(hyd->id);  
    free(hyd->x); 
    free(hyd->y);
    free(hyd->sw);
    free(hyd->cfill);  
    free(hyd->cstrk);

    free(hyd);
}