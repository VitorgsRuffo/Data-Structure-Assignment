#include "../include/headers.h"
#include "../include/utils.h"
#include "block.h"

typedef struct block{
    char* cep;  
    char* x;
    char* y;
    char* w;
    char* h;
    char* sw;
    char* cfill;
    char* cstrk;
    char* rx;
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
    strcpy(blk->sw, sw);
    strcpy(blk->cfill, cfill);
    strcpy(blk->cstrk, cstrk);
    strcpy(blk->rx, "0.0");

    return blk;
}

char* getBlockCep(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockCep"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->cep;
}

char* getBlockX(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockX"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->x;
}

char* getBlockY(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockY"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->y;
}

char* getBlockWidth(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockWidth"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->w;
}

char* getBlockHeight(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockHeight"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->h;
}

char* getBlockSw(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockSw"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->sw;
}

char* getBlockCfill(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockCfill"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->cfill;
}

void setBlockCfill(Block Blk, char* cfill){
    if(isElementNull(Blk, "quadra", "setBlockCfill"))
        return;

    block *blk = (block*) Blk;
    strcpy(blk->cfill, cfill);
}

char* getBlockCstrk(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockCstrk"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->cstrk;
}

void setBlockCstrk(Block Blk, char* cstrk){
    if(isElementNull(Blk, "quadra", "setBlockCstrk"))
        return;

    block *blk = (block*) Blk;
    strcpy(blk->cstrk, cstrk);
}

char* getBlockRx(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockRx"))
        return NULL;
    block *blk = (block*) Blk;
    return blk->rx;
}

void setBlockRx(Block Blk, char* rx){
    if(isElementNull(Blk, "quadra", "setBlockRx"))
        return;

    block *blk = (block*) Blk;
    strcpy(blk->rx, rx);
}

double getBlockArea(Block Blk){
    if(isElementNull(Blk, "quadra", "getBlockArea"))
        return 0;
    block *blk = (block*) Blk;

    double length = (atof(blk->x) + atof(blk->w)) - atof(blk->x);
    double width = (atof(blk->y) + atof(blk->h)) - atof(blk->y);
    return length * width;
}

char* blockToString(Block Blk){
    if(isElementNull(Blk, "quadra", "blockToString"))
        return NULL;
    block *blk = (block*) Blk;

    char* blockInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(blockInfoString, "Tipo: quadra, Cep: %s, x: %s, y: %s, w: %s, h: %s, sw: %s, cfill: %s, cstrk: %s, rx: %s", blk->cep, blk->x, blk->y, blk->w, blk->h, blk->sw, blk->cfill, blk->cstrk, blk->rx);
    return blockInfoString;
}

void printBlock(Block Blk){
    if(isElementNull(Blk, "quadra", "printBlock"))
        return;
    block *blk = (block*) Blk;
    printf("Quadra:\ncep: %s\nx: %s\ny: %s\nw: %s\nh: %s\nsw: %s\ncfill: %s\ncstrk: %s\n\n\n",
           blk->cep, blk->x, blk->y, blk->w, blk->h, blk->sw, blk->cfill, blk->cstrk);
}

void freeBlock(Block Blk){
    if(isElementNull(Blk, "quadra", "freeBlock"))
        return;

    block *blk = (block*) Blk;
    free(blk->cep);  
    free(blk->x);  
    free(blk->y); 
    free(blk->w);  
    free(blk->h);  
    free(blk->sw);  
    free(blk->cfill);  
    free(blk->cstrk);  
    free(blk->rx);

    free(blk);
}