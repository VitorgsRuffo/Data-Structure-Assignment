#include "../../include/headers.h"
#include "block.h"
#include "house.h"

typedef struct {
    int northFace;
    int southFace;
    int eastFace;
    int westFace;
}CovidCases;

typedef struct block{
    char* cep;  
    char* x;
    char* y;
    char* w;
    char* h;
    Point coordinates;
    char* sw;
    char* cfill;
    char* cstrk;
    char* rx;
    double demographicDensity;
    char* shadowColor;
    List housesInBlock;
    CovidCases covidCases;
}block;

Block createBlock(char* cep, char* x, char* y, char* w, char* h, char* sw, char* cfill, char* cstrk){

    block *blk = (block*) malloc(sizeof(block));

    blk->cep = (char*) malloc((strlen(cep) + 1) * sizeof(char));
    blk->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    blk->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    blk->w = (char*) malloc((strlen(w) + 1) * sizeof(char));
    blk->h = (char*) malloc((strlen(h) + 1) * sizeof(char));
    blk->sw = (char*) malloc(20 * sizeof(char));
    blk->cfill = (char*) malloc(20 * sizeof(char));
    blk->cstrk = (char*) malloc(20 * sizeof(char));
    blk->rx = (char*) malloc(5 * sizeof(char));

    strcpy(blk->cep, cep);
    strcpy(blk->x, x);
    strcpy(blk->y, y);
    strcpy(blk->w, w);
    strcpy(blk->h, h);
    blk->coordinates = createPoint(atof(x), atof(y));
    strcpy(blk->sw, sw);
    strcpy(blk->cfill, cfill);
    strcpy(blk->cstrk, cstrk);
    strcpy(blk->rx, "0.0");
    blk->demographicDensity = 0.0;
    blk->shadowColor = NULL;
    blk->housesInBlock = createList();
    blk->covidCases.northFace = 0;
    blk->covidCases.southFace = 0;
    blk->covidCases.eastFace = 0;
    blk->covidCases.westFace = 0;

    return blk;
}

char* getBlockCep(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->cep;
}

char* getBlockX(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->x;
}

char* getBlockY(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->y;
}

char* getBlockWidth(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->w;
}

char* getBlockHeight(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->h;
}

Point getBlockCoordinates(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->coordinates;
}

char* getBlockSw(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->sw;
}

char* getBlockCfill(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->cfill;
}

void setBlockCfill(Block Blk, char* cfill){
    if(Blk == NULL)
        return;

    block *blk = (block*) Blk;
    strcpy(blk->cfill, cfill);
}

char* getBlockCstrk(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->cstrk;
}

void setBlockCstrk(Block Blk, char* cstrk){
    if(Blk == NULL)
        return;

    block *blk = (block*) Blk;
    strcpy(blk->cstrk, cstrk);
}

char* getBlockRx(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;
    return blk->rx;
}

void setBlockRx(Block Blk, char* rx){
    if(Blk == NULL)
        return;

    block *blk = (block*) Blk;
    strcpy(blk->rx, rx);
}

double getBlockDemographicDensity(Block Blk){
    if(Blk == NULL) return -1;

    block *blk = (block*) Blk;
    return blk->demographicDensity;
}

void setBlockDemographicDensity(Block Blk, double demographicDensity){
    if(Blk == NULL || demographicDensity < 0)
        return;

    block *blk = (block*) Blk;
    blk->demographicDensity = demographicDensity;
}

char* getBlockShadowColor(Block Blk){
    if(Blk == NULL) return NULL; 

    block *blk = (block*) Blk;
    return blk->shadowColor;
}

void setBlockShadowColor(Block Blk){

    if(Blk == NULL) return;

    block *blk = (block*) Blk;

    /*  shadow     density
        == NULL    >=10  * aloca memoria e atribui sombra
        != NULL    >=10  * somente sobreescreve cor da sombra ja existente
        == NULL    <10   * nao acontece nada
        != NULL    <10   * retira sombra
    */
    //Obs: quadras com densidade inferior a 10 hab/k² nao possuem sombra.

    if(blk->shadowColor == NULL && blk->demographicDensity >= 10) {     
        blk->shadowColor = (char*) malloc(10 * sizeof(char));

    }else if(blk->shadowColor != NULL && blk->demographicDensity < 10){ //remover a sombra da quadra.
        free(blk->shadowColor);
        blk->shadowColor = NULL;
        return;
    }


    if(blk->demographicDensity >= 10 && blk->demographicDensity < 500)
        strcpy(blk->shadowColor, "#FFFF00");

    else if(blk->demographicDensity >= 500 && blk->demographicDensity < 1500)
        strcpy(blk->shadowColor, "#FF9955");

    else if(blk->demographicDensity >= 1500 && blk->demographicDensity < 3000)
        strcpy(blk->shadowColor, "#FF0000");

    else if(blk->demographicDensity >= 3000 && blk->demographicDensity < 4500)
        strcpy(blk->shadowColor, "#FF00CC");
        
    else if(blk->demographicDensity >= 4500 && blk->demographicDensity < 6000)
        strcpy(blk->shadowColor, "#6600FF");
        
    else if(blk->demographicDensity >= 6000) 
        strcpy(blk->shadowColor, "#A02C5A");
}

double getBlockArea(Block Blk){
    if(Blk == NULL)
        return 0;
    block *blk = (block*) Blk;

    double length = (atof(blk->x) + atof(blk->w)) - atof(blk->x);
    double width = (atof(blk->y) + atof(blk->h)) - atof(blk->y);
    return length * width;
}

List getListOfHousesInBlock(Block Blk){
    if(Blk == NULL) return NULL;

    block *blk = (block*) Blk;
    return blk->housesInBlock;
}

int getBlockCovidCases(Block Blk, char face){
    if(Blk == NULL) return -1;
    block *blk = (block*) Blk;

    switch(face){
        case 'n':
            return blk->covidCases.northFace;
            break;
        case 's':
            return blk->covidCases.southFace;
            break;
        case 'e':
            return blk->covidCases.eastFace;
            break;
        case 'w':
            return blk->covidCases.westFace;
    }

    return -1;
}

void incrementBlockCovidCases(Block Blk, char face, int newCases){
    if(Blk == NULL || newCases <= 0) return;
    block *blk = (block*) Blk;

    switch(face){
        case 'n':
            blk->covidCases.northFace += newCases;
            break;
        case 's':
            blk->covidCases.southFace += newCases;
            break;
        case 'e':
            blk->covidCases.eastFace += newCases;
            break;
        case 'w':
            blk->covidCases.westFace += newCases;
    }
}


char* blockToString(Block Blk){
    if(Blk == NULL)
        return NULL;
    block *blk = (block*) Blk;

    char* blockInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(blockInfoString, "Tipo: quadra, Cep: %s, x: %s, y: %s, w: %s, h: %s, sw: %s, cfill: %s, cstrk: %s, rx: %s", blk->cep, blk->x, blk->y, blk->w, blk->h, blk->sw, blk->cfill, blk->cstrk, blk->rx);
    return blockInfoString;
}

void printBlock(Block Blk){
    if(Blk == NULL)
        return;
    block *blk = (block*) Blk;
    printf("Quadra:\ncep: %s\nx: %s\ny: %s\nw: %s\nh: %s\nsw: %s\ncfill: %s\ncstrk: %s\n\n\n",
           blk->cep, blk->x, blk->y, blk->w, blk->h, blk->sw, blk->cfill, blk->cstrk);
}

void freeBlock(Block Blk){
    if(Blk == NULL)
        return;

    block *blk = (block*) Blk;
    free(blk->cep);  
    free(blk->x);  
    free(blk->y); 
    free(blk->w);  
    free(blk->h);
    free(blk->coordinates);
    free(blk->sw);  
    free(blk->cfill);  
    free(blk->cstrk);  
    free(blk->rx);
    if(blk->shadowColor != NULL) free(blk->shadowColor);
    freeList(blk->housesInBlock, NULL);
    free(blk);
}