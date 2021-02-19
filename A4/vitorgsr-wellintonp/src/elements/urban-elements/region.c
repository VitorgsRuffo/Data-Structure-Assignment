#include "../../include/headers.h"
#include "region.h"

typedef struct region {
    int id;
    double x;
    double y;
    double width;
    double height;
    double demographicDensity;
}region;


Region createRegion(int id, double x, double y, double w, double h, double demographicDensity){

    region* reg = (region*) malloc(sizeof(region));

    reg->id = id;
    reg->x = x;
    reg->y = y;
    reg->width = w;
    reg->height = h;
    reg->demographicDensity = demographicDensity;

    return reg;
}

double getRegionId(Region Reg){
    if(Reg == NULL)
        return -1.0;
    region *reg = (region*) Reg;
    return reg->id;
}

double getRegionX(Region Reg){
    if(Reg == NULL)
        return -1.0;
    region *reg = (region*) Reg;
    return reg->x;
}

double getRegionY(Region Reg){
    if(Reg == NULL)
        return -1.0;
    region *reg = (region*) Reg;
    return reg->y;
}

double getRegionWidth(Region Reg){
    if(Reg == NULL)
        return -1.0;
    region *reg = (region*) Reg;
    return reg->width;
}

double getRegionHeight(Region Reg){
    if(Reg == NULL)
        return -1.0;
    region *reg = (region*) Reg;
    return reg->height;
}

double getRegionDemographicDensity(Region Reg){
    if(Reg == NULL)
        return -1.0;
    region *reg = (region*) Reg;
    return reg->demographicDensity;
}

void freeRegion(Region Reg){
    if(Reg == NULL)
        return;
    region *reg = (region*) Reg;
    free(reg);
}