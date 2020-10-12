#include "../include/headers.h"
#include "../include/util.h"
#include "region.h"

typedef struct region {
    char* x;
    char* y;
    char* width;
    char* height;
    char* demographicDensity;
}region;


Region createRegion(char* x, char* y, char* w, char* h, char* demographicDensity){

    region* reg = (region*) malloc(sizeof(region));

    reg->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    reg->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    reg->width = (char*) malloc((strlen(w) + 1) * sizeof(char));
    reg->height = (char*) malloc((strlen(h) + 1) * sizeof(char));
    reg->demographicDensity = (char*) malloc((strlen(demographicDensity) + 1) * sizeof(char));
    
    strcpy(reg->x, x);
    strcpy(reg->y, y);
    strcpy(reg->width, w);
    strcpy(reg->height, h);
    strcpy(reg->demographicDensity, demographicDensity);

    return reg;
}

char* getRegionX(Region Reg){
    if(isElementNull(Reg, "Regiao", "GetRegionX"))
        return NULL;
    region *reg = (region*) Reg;
    return reg->x;
}

char* getRegionY(Region Reg){
    if(isElementNull(Reg, "Regiao", "GetRegionY"))
        return NULL;
    region *reg = (region*) Reg;
    return reg->y;
}

char* getRegionWidth(Region Reg){
    if(isElementNull(Reg, "Regiao", "getRegionWidth"))
        return NULL;
    region *reg = (region*) Reg;
    return reg->width;
}

char* getRegionHeight(Region Reg){
    if(isElementNull(Reg, "Regiao", "getRegionHeight"))
        return NULL;
    region *reg = (region*) Reg;
    return reg->height;
}

char* getRegionDemographicDensity(Region Reg){
    if(isElementNull(Reg, "Regiao", "getRegionDemographicDensity"))
        return NULL;
    region *reg = (region*) Reg;
    return reg->demographicDensity;
}


void freeRegion(Region Reg){
    if(isElementNull(Reg, "regiao", "freeRegion"))
        return;

    region *reg = (region*) Reg;

    free(reg->x); 
    free(reg->y); 
    free(reg->width); 
    free(reg->height); 
    free(reg->demographicDensity); 
    free(reg);
}