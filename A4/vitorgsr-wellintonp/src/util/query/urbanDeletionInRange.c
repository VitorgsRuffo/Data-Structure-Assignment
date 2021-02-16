#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../input/openInput.h"


typedef struct {
    DataStructure elements;
    Rectangle block;
    Circle range;
    File txt;
}Variables;

void deleteBlocksInRange(Variables variables);
char* buildUrbanElementsDeletionRangeTag(char* x, char* y, char* radius);

void executeUrbanElementsDeletionInRange(char* command, City Ct, File txt){

    char x[10], y[10], r[10];
    sscanf(&command[6], "%s %s %s", x, y, r);

    Variables variables;
    variables.block = 
        createRectangle("..", "......", "......", "......", "......", "......", "..", "..");
    variables.range = 
        createCircle("..", r, x, y, "..", "..", "..");
    variables.txt = txt;

    variables.elements = getBlocks(Ct);
    deleteBlocksInRange(variables);

    //deleteUrbanEquipmentsInRange(txt);

    //deleteHousesInRange(txt);

    //deleteEstablishmentsInRange(txt);

    char* rangeTag = buildUrbanElementsDeletionRangeTag(x, y, r);
    insert(getQueryElements(Ct), rangeTag);
    
    free(variables.range);
}

void function(Info blockInfo, ExtraInfo extraInfo);

void deleteBlocksInRange(Variables variables){

    levelOrderTraversal(variables.elements, function, &variables);
}

void function(Info blockInfo, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;

    setRectangleX(variables->block, getBlockX(blockInfo));
    setRectangleY(variables->block, getBlockY(blockInfo));
    setRectangleWidth(variables->block, getBlockWidth(blockInfo));
    setRectangleHeight(variables->block, getBlockHeight(blockInfo));

    if(isRectangleInsideCircle(variables->block, variables->range)){
        fprintf(variables->txt, "\"%s\" foi removido.\n", blockToString(blockInfo));

        double blockX = atof(getBlockX(blockInfo));
        double blockY = atof(getBlockY(blockInfo));
        
        PQuadTreeNode nodeToRemove = getPQuadTreeNode(variables->elements, blockX, blockY);
        freeBlock(removePQuadTreeNode(variables->elements, nodeToRemove));
        //remover o node da tabela hash (caso exista uma tabela hash de quadras.)
    }

}


char* buildUrbanElementsDeletionRangeTag(char* x, char* y, char* radius){
    char* rangeTag = (char*) malloc(300 * sizeof(char));
    if(rangeTag == NULL) return NULL;

    sprintf(rangeTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"#6C6753\" stroke-width=\"3\" fill=\"#CCFF00\" fill-opacity=\"0.5\" />\n", x, y, radius);
    return rangeTag;
}