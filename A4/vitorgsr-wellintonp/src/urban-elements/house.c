#include "../include/headers.h"
#include "../include/util.h"
#include "../drawing/drawing.h"
#include "../urban-elements/block.h"
#include "house.h"

#define houseWidth 15
#define houseHeight 15

typedef struct {
    char cep[30]; 
    char face;
    int number;
}Address;

typedef struct {
    double x, y;
    double w, h;    
}HouseBlock;

typedef struct {
    double x;
    double y;
}CenterOfMass;

typedef struct {
    Address address;
    HouseBlock block;
    double x, y, w, h;
    CenterOfMass centerOfMass;
    int casesNumber;
}house;


House createHouse(char* cep, char face, int number, int casesNumber){
    
    house *h = (house*) malloc(sizeof(house));
    
    strcpy(h->address.cep, cep);
    h->address.face = face;
    h->address.number = number;
    h->w = houseWidth;
    h->h = houseHeight;
    h->casesNumber = casesNumber;

    return h;
}

void readBlockAttributes(Info blockInfo, HouseBlock *block);

void setHouseBlock(House H, Drawing Dr){
    if(isElementNull(H, "Casa", "setHouseBlock"))
        return;

    house *h = (house*) H;

    Node blockNode;
    blockNode = searchForBlockByCep(Dr, h->address.cep);
    if(isElementNull(blockNode, "blockNode", "searchForBlockByCep | setHouseBlock"))
        return;
    
    List blockList = getBlockList(Dr);
    Info blockInfo = get(blockList, blockNode);
    readBlockAttributes(blockInfo, &h->block);    
}

void readBlockAttributes(Info blockInfo, HouseBlock *block){
    
    block->x = atof(getBlockX(blockInfo));
    block->y = atof(getBlockY(blockInfo));
    block->w = atof(getBlockWidth(blockInfo));
    block->h = atof(getBlockHeight(blockInfo));

    return;
}

void setHouseLocationOnNorthFace(house *h);
void setHouseLocationOnSouthFace(house *h);
void setHouseLocationOnEastFace(house *h);
void setHouseLocationOnWestFace(house *h);

void setHouseLocation(House H){
    if(isElementNull(H, "Casa", "setHouseLocation"))
        return;

    house *h = (house*) H;

    switch (h->address.face){
        case 'N':
        case 'n':
            setHouseLocationOnNorthFace(h);
            break;
            
        case 'S':
        case 's':
            setHouseLocationOnSouthFace(h);
            break;

        case 'L':
        case 'l':
            setHouseLocationOnEastFace(h);
            break;
        
        case 'O':
        case 'o':
            setHouseLocationOnWestFace(h);
            break;

        default:
            printf("A face da quadra (%s) e invalida.\n", h->address.cep);
    }

    h->centerOfMass.x = h->x + (h->w / 2.0);
    h->centerOfMass.y = h->y + (h->h / 2.0);

    return;
}

// Face Norte
void setHouseLocationOnNorthFace(house *h){
    h->x = (h->block.x + h->address.number) - (h->w / 2.0);
    h->y = (h->block.y + h->block.h) - h->h;
}
// Face Sul
void setHouseLocationOnSouthFace(house *h){
    h->x = (h->block.x + h->address.number) - (h->w / 2.0);
    h->y = h->block.y;
}
// Face Leste
void setHouseLocationOnEastFace(house *h){
    h->x = h->block.x;
    h->y = (h->block.y + h->address.number) - (h->h / 2.0);  
}
// Face Oeste
void setHouseLocationOnWestFace(house *h){
    h->x = (h->block.x + h->block.w) - h->w;
    h->y = (h->block.y + h->address.number) - (h->h / 2.0);
}

double getHouseX(House H){
    if(isElementNull(H, "Casa", "getHouseX"))
        return 0;
    house *h = (house*) H;
    return h->x;
}
double getHouseY(House H){
    if(isElementNull(H, "Casa", "getHouseY"))
        return 0;
    house *h = (house*) H;
    return h->y;
}
double getHouseW(House H){
    if(isElementNull(H, "Casa", "getHouseWidth"))
        return 0;
    house *h = (house*) H;
    return h->w;
}
double getHouseH(House H){
    if(isElementNull(H, "Casa", "getHouseHeight"))
        return 0;
    house *h = (house*) H;
    return h->h;
}

double getHouseCenterOfMassX(House H){
    if(isElementNull(H, "Casa", "getHouseCenterOfMassX"))
        return 0;
    house *h = (house*) H;
    return h->centerOfMass.x;
}

double getHouseCenterOfMassY(House H){
    if(isElementNull(H, "Casa", "getHouseCenterOfMassY"))
        return 0;
    house *h = (house*) H;
    return h->centerOfMass.y;
}

int getHouseCasesNumber(House H){
    if(isElementNull(H, "Casa", "getHouseCasesNumber"))
        return 0;
    house *h = (house*) H;
    return h->casesNumber;
}

void printHouse(House H){
    if(isElementNull(H, "Casa", "printHouse"))
        return;
    house *h = (house*) H;
    printf("Casa:\nw: %lf\nh: %lf\nx: %lf\ny: %lf\ncasos: %d\n\n",
            h->w, h->h, h->x, h->y, h->casesNumber);
}

void freeHouse(House H){
    if(isElementNull(H, "Casa", "freeHouse"))
        return;

    house *h = (house*) H;
    free(h);
}