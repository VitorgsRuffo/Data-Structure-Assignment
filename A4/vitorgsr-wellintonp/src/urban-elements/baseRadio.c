#include "../include/headers.h"
#include "../include/util.h"
#include "baseRadio.h"

typedef struct baseRadio{
    char* id;
    char* x;
    char* y;
    char* radius;
    Point coordinates;
    char* sw;
    char* cfill;
    char* cstrk;
}baseRadio;

BaseRadio createBaseRadio(char* id, char* x, char* y, char* sw, char* cfill, char* cstrk){

    baseRadio *baseR = (baseRadio*) malloc(sizeof(baseRadio));

    baseR->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    baseR->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    baseR->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    baseR->radius = (char*) malloc(4 * sizeof(char));
    baseR->sw = (char*) malloc(20 * sizeof(char));
    baseR->cfill = (char*) malloc(20 * sizeof(char));
    baseR->cstrk = (char*) malloc(20 * sizeof(char));

    strcpy(baseR->id, id);
    strcpy(baseR->x, x);
    strcpy(baseR->y, y);
    strcpy(baseR->radius, "10");
    baseR->coordinates = createPoint(atof(x), atof(y));
    strcpy(baseR->sw, sw);
    strcpy(baseR->cfill, cfill);
    strcpy(baseR->cstrk, cstrk);

    return baseR;
}

char* getBaseRadioId(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioId"))
        return NULL;
    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->id;
}

char* getBaseRadioX(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioX"))
        return NULL;
    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->x;
}

char* getBaseRadioY(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioY"))
        return NULL;
    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->y;
}

char* getBaseRadioRadius(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioRadius"))
        return NULL;

    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->radius;
}

Point getBaseRadioCoordinates(BaseRadio BaseR){
    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->coordinates;
}

char* getBaseRadioSw(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioSw"))
        return NULL;
    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->sw;
}

void setBaseRadioSw(BaseRadio BaseR, char* sw){
    if(isElementNull(BaseR, "base-radio", "setBaseRadioSw"))
        return;
    baseRadio *baseR = (baseRadio*) BaseR;
    strcpy(baseR->sw, sw);
}

char* getBaseRadioCfill(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioCfill"))
        return NULL;
    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->cfill;
}

char* getBaseRadioCstrk(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioCstrk"))
        return NULL;
    baseRadio *baseR = (baseRadio*) BaseR;
    return baseR->cstrk;
}

double getBaseRadioArea(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "getBaseRadioArea"))
        return 0;

    baseRadio *baseR = (baseRadio*) BaseR;
    return 3.141592 * ( atof(baseR->radius) * atof(baseR->radius) );      
}

char* baseRadioToString(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "baseRadioToString"))
        return NULL;
    baseRadio *baseR = (baseRadio*) BaseR;

    char* baseRadioInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(baseRadioInfoString, "Tipo: Radio-base, id: %s, x: %s, y: %s, sw: %s, cfill: %s, cstrk: %s", baseR->id, baseR->x, baseR->y, baseR->sw, baseR->cfill, baseR->cstrk);
    return baseRadioInfoString;
}

void printBaseRadio(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "printBaseRadio"))
        return;

    baseRadio *baseR = (baseRadio*) BaseR;
    printf("Radio-base:\nId: %s\nx: %s\ny: %s\nsw: %s\ncfill: %s\ncstrk: %s\n\n\n",
           baseR->id, baseR->x, baseR->y, baseR->sw, baseR->cfill, baseR->cstrk);
}

void freeBaseRadio(BaseRadio BaseR){
    if(isElementNull(BaseR, "radio-base", "freeBaseRadio"))
        return;

    baseRadio *baseR = (baseRadio*) BaseR;
    free(baseR->id);  
    free(baseR->x); 
    free(baseR->y);  
    free(baseR->radius);
    free(baseR->coordinates);
    free(baseR->sw);  
    free(baseR->cfill);  
    free(baseR->cstrk);  

    free(baseR);
}