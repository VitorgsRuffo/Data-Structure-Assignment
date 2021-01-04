#include "../include/headers.h"
#include "../include/util.h"
#include "../include/query.h"
#include "../drawing/drawing.h"
#include "../include/urbanElements.h"

typedef struct{
    double x;
    double y;
    double radius;
    char cstrk[20];
}WrapperCircle;

void setBlocksBorderInRange(File txt, List blockList, WrapperCircle* wrapperCircle);

void executeBlocksBorderColorChanging(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeBlocksBorderColorChanging"))
        return;

    WrapperCircle wrapperCircle;
    sscanf(&command[4], "%lf %lf %lf %s", &wrapperCircle.x, &wrapperCircle.y, &wrapperCircle.radius, wrapperCircle.cstrk);

    List blockList = getBlockList(Dr);

    setBlocksBorderInRange(txt, blockList, &wrapperCircle);
}

void writeBlockCepOnTxt(File txt, Info blockInfo);

void setBlocksBorderInRange(File txt, List blockList, WrapperCircle* wrapperCircle){

    Node NODE = getFirst(blockList);
    if(isElementNull(NODE, "NODE", "setBlocksBorderInRange | getFirst")){
        return;
    }

    Info blockInfo = NULL;

    while(NODE != NULL){

        blockInfo = get(blockList, NODE);
        
        if(isBlockInCircleRange(blockInfo, wrapperCircle->x, wrapperCircle->y, wrapperCircle->radius)){

           setBlockCstrk(blockInfo, wrapperCircle->cstrk);
           writeBlockCepOnTxt(txt, blockInfo);
        }

        NODE = getNext(blockList, NODE);
    }
}

void writeBlockCepOnTxt(File txt, Info blockInfo){
    char* cep = getBlockCep(blockInfo);
    fprintf(txt, "cep: %s\n\n", cep);
}