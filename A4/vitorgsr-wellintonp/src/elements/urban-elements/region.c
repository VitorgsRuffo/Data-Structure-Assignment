#include "../include/headers.h"
#include "region.h"
#include "point.h"

typedef struct region {
    int id;
    char* x;
    char* y;
    char* width;
    char* height;
    char* demographicDensity;
}region;


Region createRegion(int id, char* x, char* y, char* w, char* h, char* demographicDensity){

    region* reg = (region*) malloc(sizeof(region));

    reg->id = id;
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

int getRegionId(Region Reg){
    if(Reg == NULL)
        return;
    region *reg = (region*) Reg;
    return reg->id;
}

char* getRegionX(Region Reg){
    if(Reg == NULL)
        return NULL;
    region *reg = (region*) Reg;
    return reg->x;
}

char* getRegionY(Region Reg){
    if(Reg == NULL)
        return NULL;
    region *reg = (region*) Reg;
    return reg->y;
}

char* getRegionWidth(Region Reg){
    if(Reg == NULL)
        return NULL;
    region *reg = (region*) Reg;
    return reg->width;
}

char* getRegionHeight(Region Reg){
    if(Reg == NULL)
        return NULL;
    region *reg = (region*) Reg;
    return reg->height;
}

double getRegionDemographicDensity(Region Reg){
    if(Reg == NULL)
        return -1.0;

    region *reg = (region*) Reg;
    return atof(reg->demographicDensity);
}

void printRegion(Region Reg){
    if(Reg == NULL)
        return;

    region *reg = (region*) Reg;

    printf("Regiao:\nid:%d\n w: %s\nh: %s\nx: %s\ny: %s\ndensidade demografica: %s\n\n", reg->id, reg->width, 
    reg->height, reg->x, reg->y, reg->demographicDensity);
}

void freeRegion(Region Reg){
    if(Reg == NULL)
        return;

    region *reg = (region*) Reg;

    free(reg->x); 
    free(reg->y); 
    free(reg->width); 
    free(reg->height); 
    free(reg->demographicDensity); 
    free(reg);
}