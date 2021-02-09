#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"

typedef struct{    
    char id[30];
    char type[12];
    Point coordinates;
    double searchRadius;
    File txt;
    DataStructure blocks;
}UrbanEquipment;


void getUrbanEquipmentCoordinates(Info urbanEquipmentInfo, UrbanEquipment* urbanEquipment);
void setUrbanEquipmentDoubleBorder(Info urbanEquipmentInfo, List queryElementsList, UrbanEquipment urbanEquipment);

void changeBlocksCustomizationInRange(DataStructure blocks, UrbanEquipment* urbanEquipment);
void deleteBlocksInRange(DataStructure blocks, UrbanEquipment* urbanEquipment);

char* buildWrapperCircleTag(UrbanEquipment urbanEquipment);

void executeBlocksDeletion(char* command, City Ct, File txt){
    
    UrbanEquipment urbanEquipment;
    int thereIsHashtag = 0;
    
    if(command[3] == '#'){
        thereIsHashtag = 1;
        sscanf(&command[5], "%s %lf", urbanEquipment.id, &urbanEquipment.searchRadius);
    }else
        sscanf(&command[3], "%s %lf", urbanEquipment.id, &urbanEquipment.searchRadius);

    urbanEquipment.txt = txt;

    //pegando a referencia para o equipamento urbano:
    Node urbanEquipmentNode = searchForUrbanElementByIdentifier(Ct, urbanEquipment.id, urbanEquipment.type);
    if(urbanEquipmentNode == NULL) return;
    
    DataStructure urbanEquipments = getDataStructureByElementType(Ct, urbanEquipment.type);

    Info urbanEquipmentInfo = getPQuadTreeNodeInfo(urbanEquipments, urbanEquipmentNode);
    if(urbanEquipmentInfo == NULL) return;
    

    //setando a borda dupla do equipamento urbano:
    getUrbanEquipmentCoordinates(urbanEquipmentInfo, &urbanEquipment);
    List queryElementsList = getQueryElementsList(Ct);
    setUrbanEquipmentDoubleBorder(urbanEquipmentInfo, queryElementsList, urbanEquipment);
    
    //alterando/deletando as quadras dentro do raio:
    DataStructure blocks = getBlocks(Ct);
    urbanEquipment.blocks = blocks;

    if(thereIsHashtag)
        changeBlocksCustomizationInRange(blocks, &urbanEquipment);
    else
        deleteBlocksInRange(blocks, &urbanEquipment);

    //construindo a tag do raio de alteracao/delicao:
    char* wrapperCircleTag = buildWrapperCircleTag(urbanEquipment);
    insert(queryElementsList, wrapperCircleTag);
}

void getUrbanEquipmentCoordinates(Info urbanEquipmentInfo, UrbanEquipment* urbanEquipment){
    if(urbanEquipment->type[0] == 'h'){
        setPointX(urbanEquipment->coordinates, atof(getHydrantX(urbanEquipmentInfo)));
        setPointY(urbanEquipment->coordinates, atof(getHydrantY(urbanEquipmentInfo)));

    }else if(urbanEquipment->type[0] == 's'){
        setPointX(urbanEquipment->coordinates, atof(getSemaphoreX(urbanEquipmentInfo)));
        setPointY(urbanEquipment->coordinates, atof(getSemaphoreY(urbanEquipmentInfo)));

    }else if(urbanEquipment->type[0] == 'r'){
        setPointX(urbanEquipment->coordinates, atof(getBaseRadioX(urbanEquipmentInfo)));
        setPointY(urbanEquipment->coordinates, atof(getBaseRadioY(urbanEquipmentInfo)));
    }else
        return;
}

char* buildUrbanEquipmentInnerCircleTag(double x, double y, double radius, char* urbanEquipmentLetter);

void setUrbanEquipmentDoubleBorder(Info urbanEquipmentInfo, List queryElementsList, UrbanEquipment urbanEquipment){
    double urbanEquipmentInnerCircleRadius = 6.0;
    char urbanEquipmentLetter[4];

    if(urbanEquipment.type[0] == 'h'){
        setHydrantSw(urbanEquipmentInfo, "4.0");
        strcpy(urbanEquipmentLetter, ".H");
        
    }else if(urbanEquipment.type[0] == 's'){
        setSemaphoreSw(urbanEquipmentInfo, "4.0");
        strcpy(urbanEquipmentLetter, ".S");

    }else if(urbanEquipment.type[0] == 'r') {
        setBaseRadioSw(urbanEquipmentInfo, "4.0");
        strcpy(urbanEquipmentLetter, "RB");
    }

    double px = getPointX(urbanEquipment.coordinates);
    double py = getPointY(urbanEquipment.coordinates);

    char* urbanEquipmentInnerCircleTag = buildUrbanEquipmentInnerCircleTag(px, py, urbanEquipmentInnerCircleRadius, urbanEquipmentLetter);
    insert(queryElementsList, urbanEquipmentInnerCircleTag);
}

char* buildUrbanEquipmentInnerCircleTag(double x, double y, double radius, char* urbanEquipmentLetter){
    char* innerCircle = (char*) malloc(200 * sizeof(char));
    if(innerCircle == NULL) return NULL;

    sprintf(innerCircle, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke-width=\"0\" fill=\"forestgreen\" />\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> %s </text>\n", x, y, radius, x, y, urbanEquipmentLetter);
    return innerCircle;
}

void writeBlockDeletionResultOnTxt(Info blockInfo, UrbanEquipment* urbanEquipment);

void deleteBlockIfItsInRange(Info blockInfo, ExtraInfo extraInfo);

void deleteBlocksInRange(DataStructure blocks, UrbanEquipment* urbanEquipment){
          
    levelOrderTraversal(blocks, deleteBlockIfItsInRange, urbanEquipment);
}

void deleteBlockIfItsInRange(Info blockInfo, ExtraInfo extraInfo){
    
    UrbanEquipment* urbanEquipment = (UrbanEquipment*) extraInfo;

    if(isBlockInCircleRange(blockInfo, getPointX(urbanEquipment->coordinates), getPointY(urbanEquipment->coordinates), urbanEquipment->searchRadius)){
        
        writeBlockDeletionResultOnTxt(blockInfo, urbanEquipment);
        
        double blockX = atof(getBlockX(blockInfo));
        double blockY = atof(getBlockY(blockInfo));
        PQuadTreeNode nodeToRemove = getPQuadTreeNode(urbanEquipment->blocks, blockX, blockY);

        freeBlock(removePQuadTreeNode(urbanEquipment->blocks, nodeToRemove));
    }
}

void changeBlockCustomizationIfItsInRange(Info blockInfo, ExtraInfo extraInfo);

void changeBlocksCustomizationInRange(DataStructure blocks, UrbanEquipment* urbanEquipment){
   
    levelOrderTraversal(blocks, changeBlockCustomizationIfItsInRange, urbanEquipment);
}

void changeBlockCustomizationIfItsInRange(Info blockInfo, ExtraInfo extraInfo){
    
    UrbanEquipment* urbanEquipment = (UrbanEquipment*) extraInfo;

    if(isBlockInCircleRange(blockInfo, getPointX(urbanEquipment->coordinates), getPointY(urbanEquipment->coordinates), urbanEquipment->searchRadius)){
        setBlockRx(blockInfo, "10");
        setBlockCfill(blockInfo, "beige");
        setBlockCstrk(blockInfo, "olive");

        writeBlockDeletionResultOnTxt(blockInfo, urbanEquipment);
    }
}

void writeBlockDeletionResultOnTxt(Info blockInfo, UrbanEquipment* urbanEquipment){
    char* blockCep = getBlockCep(blockInfo);
    fprintf(urbanEquipment->txt, "%s | %s - id: %s, x:%lf, y: %lf\n\n", blockCep, urbanEquipment->type, urbanEquipment->id, getPointX(urbanEquipment->coordinates), getPointY(urbanEquipment->coordinates));
}

char* buildWrapperCircleTag(UrbanEquipment urbanEquipment){
    char* wrapperCircleTag = (char*) malloc(200 * sizeof(char));
    if(wrapperCircleTag == NULL) return NULL;

    double x = getPointX(urbanEquipment.coordinates);
    double y = getPointY(urbanEquipment.coordinates);
    double radius = urbanEquipment.searchRadius;

    sprintf(wrapperCircleTag, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"black\" stroke-width=\"1.5\" fill=\"black\" fill-opacity=\"0.0\" />\n", x, y, radius);
    return wrapperCircleTag;
}