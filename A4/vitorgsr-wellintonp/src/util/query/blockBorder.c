#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"


void setBlocksBorderInRange(File txt, DataStructure blocks, Circle wrapper);

void executeBlocksBorderColorChanging(char* command, City Ct, File txt){
    
    char x[10], y[10], radius[10], cstrk[20];
    sscanf(&command[4], "%s %s %s %s", x, y, radius, cstrk);
    
    Circle wrapper = createCircle("..", radius, x, y, cstrk, "..", "..");

    DataStructure blocks = getBlocks(Ct);
    if(blocks == NULL) return;

    setBlocksBorderInRange(txt, blocks, wrapper);

    freeCircle(wrapper);
}

typedef struct {
    Circle wrapper;
    Rectangle block;
    File txt;
}Variables;


void setBlockBorderIfItsInRange(Info blockInfo, ExtraInfo extraInfo);

void setBlocksBorderInRange(File txt, DataStructure blocks, Circle wrapper){

    Variables variables;

    variables.wrapper = wrapper;
    variables.txt = txt;
    variables.block = createRectangle("..", "..", "..", "..", "..", "..", "..", "..");

    preOrderTraversal(blocks, setBlockBorderIfItsInRange, &variables);
    
    freeRectangle(variables.block);
}

void writeBlockCepOnTxt(File txt, Info blockInfo);

void setBlockBorderIfItsInRange(Info blockInfo, ExtraInfo extraInfo){
    
    Variables *variables = (Variables*) extraInfo; 
    
    setRectangleX(variables->block, getBlockX(blockInfo));
    setRectangleY(variables->block, getBlockY(blockInfo));
    setRectangleWidth(variables->block, getBlockWidth(blockInfo));
    setRectangleHeight(variables->block, getBlockHeight(blockInfo));

    if(isRectangleInsideCircle(variables->wrapper, variables->block)){
        
        setBlockCstrk(blockInfo, getCircleCorb(variables->wrapper));
        writeBlockCepOnTxt(variables->txt, blockInfo);
    }
}

void writeBlockCepOnTxt(File txt, Info blockInfo){
    char* cep = getBlockCep(blockInfo);
    fprintf(txt, "cep: %s\n\n", cep);
}