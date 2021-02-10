#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"

typedef struct{    
    char urbanEquipmentType[12];
    Circle deletionRange;
    DataStructure blocks;
    Rectangle block;
    File txt;
}Variables;


void setDeletionRangeCoordinates(Variables* variables, Info urbanEquipmentInfo);
void setUrbanEquipmentDoubleBorder(Variables* variables, Info urbanEquipmentInfo, List queryElementsList);

void changeBlocksCustomizationInRange(DataStructure blocks, Variables* variables);
void deleteBlocksInRange(DataStructure blocks, Variables* variables);

char* buildWrapperCircleTag(Circle deletionRange);

void executeBlocksDeletion(char* command, City Ct, File txt){
    
    Variables variables;
    int thereIsHashtag = 0;
    
    char id[30], radius[10];

    if(command[3] == '#'){
        thereIsHashtag = 1;
        sscanf(&command[5], "%s %s", id, radius);
    }else
        sscanf(&command[3], "%s %s", id, radius);

    variables.txt = txt;
    variables.deletionRange = createCircle(id, radius, "..", "..", "..", "..", "..");

    //pegando a referencia para o equipamento urbano:
    Node urbanEquipmentNode = searchForUrbanElementByIdentifier(Ct, id, variables.urbanEquipmentType);
    if(urbanEquipmentNode == NULL) return;
    
    DataStructure urbanEquipments = getDataStructureByElementType(Ct, variables.urbanEquipmentType);
    
    Info urbanEquipmentInfo = getPQuadTreeNodeInfo(urbanEquipments, urbanEquipmentNode);
    if(urbanEquipmentInfo == NULL) return;
    

    //setando a borda dupla do equipamento urbano:
    setDeletionRangeCoordinates(&variables, urbanEquipmentInfo);
    List queryElementsList = getQueryElements(Ct);
    setUrbanEquipmentDoubleBorder(&variables, urbanEquipmentInfo, queryElementsList);
    
    //alterando/deletando as quadras dentro do raio:
    DataStructure blocks = getBlocks(Ct);
    variables.blocks = blocks;
    variables.block = createRectangle("..", "..", "..", "..", "..", "..", "..", "..");

    if(thereIsHashtag)
        changeBlocksCustomizationInRange(blocks, &variables);
    else
        deleteBlocksInRange(blocks, &variables);

    //construindo a tag do raio de alteracao/delicao:
    char* wrapperCircleTag = buildWrapperCircleTag(variables.deletionRange);
    insert(queryElementsList, wrapperCircleTag);
    
    freeCircle(variables.deletionRange);
    freeRectangle(variables.block);
}

void setDeletionRangeCoordinates(Variables* variables, Info urbanEquipmentInfo){
    if(variables->urbanEquipmentType[0] == 'h'){
        setCircleX(variables->deletionRange, getHydrantX(urbanEquipmentInfo));
        setCircleY(variables->deletionRange, getHydrantY(urbanEquipmentInfo));

    }else if(variables->urbanEquipmentType[0] == 's'){
        setCircleX(variables->deletionRange, getSemaphoreX(urbanEquipmentInfo));
        setCircleY(variables->deletionRange, getSemaphoreY(urbanEquipmentInfo));

    }else if(variables->urbanEquipmentType[0] == 'r'){
        setCircleX(variables->deletionRange, getBaseRadioX(urbanEquipmentInfo));
        setCircleY(variables->deletionRange, getBaseRadioY(urbanEquipmentInfo));
    }else
        return;
}

char* buildUrbanEquipmentInnerCircleTag(double x, double y, double radius, char* urbanEquipmentLetter);

void setUrbanEquipmentDoubleBorder(Variables* variables, Info urbanEquipmentInfo, List queryElementsList){
    double urbanEquipmentInnerCircleRadius = 6.0;
    char urbanEquipmentLetter[4];

    if(variables->urbanEquipmentType[0] == 'h'){
        setHydrantSw(urbanEquipmentInfo, "4.0");
        strcpy(urbanEquipmentLetter, ".H");
        
    }else if(variables->urbanEquipmentType[0] == 's'){
        setSemaphoreSw(urbanEquipmentInfo, "4.0");
        strcpy(urbanEquipmentLetter, ".S");

    }else if(variables->urbanEquipmentType[0] == 'r') {
        setBaseRadioSw(urbanEquipmentInfo, "4.0");
        strcpy(urbanEquipmentLetter, "RB");
    }

    double px = atof(getCircleX(variables->deletionRange));
    double py = atof(getCircleY(variables->deletionRange));

    char* urbanEquipmentInnerCircleTag = buildUrbanEquipmentInnerCircleTag(px, py, urbanEquipmentInnerCircleRadius, urbanEquipmentLetter);
    insert(queryElementsList, urbanEquipmentInnerCircleTag);
}

char* buildUrbanEquipmentInnerCircleTag(double x, double y, double radius, char* urbanEquipmentLetter){
    char* innerCircle = (char*) malloc(200 * sizeof(char));
    if(innerCircle == NULL) return NULL;

    sprintf(innerCircle, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke-width=\"0\" fill=\"forestgreen\" />\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> %s </text>\n", x, y, radius, x, y, urbanEquipmentLetter);
    return innerCircle;
}

void writeBlockDeletionResultOnTxt(Info blockInfo, Variables* variables);

void deleteBlockIfItsInRange(Info blockInfo, ExtraInfo extraInfo);

void deleteBlocksInRange(DataStructure blocks, Variables* variables){
          
    levelOrderTraversal(blocks, deleteBlockIfItsInRange, variables);
}

void deleteBlockIfItsInRange(Info blockInfo, ExtraInfo extraInfo){
    
    Variables* variables = (Variables*) extraInfo;

    setRectangleX(variables->block, getBlockX(blockInfo));
    setRectangleY(variables->block, getBlockY(blockInfo));
    setRectangleWidth(variables->block, getBlockWidth(blockInfo));
    setRectangleHeight(variables->block, getBlockHeight(blockInfo));
    
    if(isRectangleInsideCircle(variables->deletionRange, variables->block)){
        
        writeBlockDeletionResultOnTxt(blockInfo, variables);
        
        double blockX = atof(getBlockX(blockInfo));
        double blockY = atof(getBlockY(blockInfo));
        
        PQuadTreeNode nodeToRemove = getPQuadTreeNode(variables->blocks, blockX, blockY);
        freeBlock(removePQuadTreeNode(variables->blocks, nodeToRemove));
    }
}

void changeBlockCustomizationIfItsInRange(Info blockInfo, ExtraInfo extraInfo);

void changeBlocksCustomizationInRange(DataStructure blocks, Variables* variables){
   
    levelOrderTraversal(blocks, changeBlockCustomizationIfItsInRange, variables);
}

void changeBlockCustomizationIfItsInRange(Info blockInfo, ExtraInfo extraInfo){
    
    Variables* variables = (Variables*) extraInfo;

    setRectangleX(variables->block, getBlockX(blockInfo));
    setRectangleY(variables->block, getBlockY(blockInfo));
    setRectangleWidth(variables->block, getBlockWidth(blockInfo));
    setRectangleHeight(variables->block, getBlockHeight(blockInfo));

    if(isRectangleInsideCircle(variables->deletionRange, variables->block)){
        setBlockRx(blockInfo, "10");
        setBlockCfill(blockInfo, "beige");
        setBlockCstrk(blockInfo, "olive");

        writeBlockDeletionResultOnTxt(blockInfo, variables);
    }
}

void writeBlockDeletionResultOnTxt(Info blockInfo, Variables* variables){
    char* blockCep = getBlockCep(blockInfo);
    fprintf(variables->txt, "%s | %s - id: %s, x:%s, y: %s\n\n", blockCep, variables->urbanEquipmentType, getCircleId(variables->deletionRange), getCircleX(variables->deletionRange), getCircleY(variables->deletionRange));
}

char* buildWrapperCircleTag(Circle deletionRange){
    char* wrapperCircleTag = (char*) malloc(200 * sizeof(char));
    if(wrapperCircleTag == NULL) return NULL;

    char* x = getCircleX(deletionRange);
    char* y = getCircleY(deletionRange);
    char* radius = getCircleRadius(deletionRange);

    sprintf(wrapperCircleTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"black\" stroke-width=\"1.5\" fill=\"black\" fill-opacity=\"0.0\" />\n", x, y, radius);
    return wrapperCircleTag;
}