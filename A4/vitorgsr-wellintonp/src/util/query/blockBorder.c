#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../input/openInput.h"
#include "../../include/dataStructure.h"
#include "../tools.h"

typedef struct{
    double x;
    double y;
    double radius;
    char cstrk[20];
}WrapperCircle;


void setBlocksBorderInRange(File txt, List blockList, WrapperCircle* wrapperCircle);

void executeBlocksBorderColorChanging(char* command, City Ct, File txt){
    if(Ct == NULL || txt == NULL)
        return;

    WrapperCircle wrapperCircle;
    sscanf(&command[4], "%lf %lf %lf %s", &wrapperCircle.x, &wrapperCircle.y, &wrapperCircle.radius, wrapperCircle.cstrk);

    DataStructure blocks = getBlocks(Ct);

    setBlocksBorderInRange(txt, blocks, &wrapperCircle);
}

typedef struct {
    WrapperCircle* wrapperCircle;
    File txt;
} extraInfos;


void setBlockBorderIfItsInRange(Info blockInfo, ExtraInfo extraInfo);

void setBlocksBorderInRange(File txt, DataStructure blocks, WrapperCircle* wrapperCircle){

    if(txt == NULL || blocks == NULL || wrapperCircle == NULL)
        return;

    extraInfos extraInfo;

    extraInfo.wrapperCircle = wrapperCircle;
    extraInfo.txt = txt;

    preOrderTraversal(blocks, setBlockBorderIfItsInRange, &extraInfo);
}

void writeBlockCepOnTxt(File txt, Info blockInfo);

void setBlockBorderIfItsInRange(Info blockInfo, ExtraInfo extraInfo){
    
    extraInfos *exInfo = (extraInfos*) extraInfo; 

    if(isBlockInCircleRange(blockInfo, exInfo->wrapperCircle->x, exInfo->wrapperCircle->y, exInfo->wrapperCircle->radius)){
        
        setBlockCstrk(blockInfo, exInfo->wrapperCircle->cstrk);
        writeBlockCepOnTxt(exInfo->txt, blockInfo);
    }
}

void writeBlockCepOnTxt(File txt, Info blockInfo){
    char* cep = getBlockCep(blockInfo);
    fprintf(txt, "cep: %s\n\n", cep);
}