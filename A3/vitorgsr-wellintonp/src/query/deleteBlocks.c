#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing.h"
#include "../include/query.h"

void getUrbanEquipmentInfo(Info urbanEquipmentInfo, char* urbanEquipmentType, double* x, double* y, char* *urbanEquipmentId);
void setUrbanEquipmentDoubleBorder(double x, double y, Info urbanEquipmentInfo, char* urbanEquipmentType, Drawing Dr);

void deleteBlocksInRange(List blockList, double urbanEquipmentX, double urbanEquipmentY, char* urbanEquipmentId, char* urbanEquipmentType, double radius, File txt);
void changeBlocksCustomizationInRange(List blockList, double urbanEquipmentX, double urbanEquipmentY, char* urbanEquipmentId, char* urbanEquipmentType, double radius, File txt);

char* buildWrapperCircleTag(double urbanEquipmentX, double urbanEquipmentY, double radius);

void executeBlocksDeletion(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeBlocksDeletion"))
        return;

    int thereIsHashtag = 0;
    char id[15]; double radius;
    
    if(command[3] == '#'){
        thereIsHashtag = 1;
        sscanf(&command[5], "%s %lf", id, &radius);
    }else
        sscanf(&command[3], "%s %lf", id, &radius);

    char urbanEquipmentType[12];

    Node urbanEquipmentNode = searchForUrbanElementByIdentifier(Dr, id, urbanEquipmentType);
    if(isElementNull(urbanEquipmentNode, "urbanEquipmentNode", "searchForUrbanElementByIdentifier"))
            return;
    
    List urbanEquipmentList = getListByElementType(Dr, urbanEquipmentType);
    
    Info urbanEquipmentInfo = get(urbanEquipmentList, urbanEquipmentNode);
    if(isElementNull(urbanEquipmentInfo, "urbanEquipmentInfo", "executeElementDeletion | get"))
        return;
    
    double urbanEquipmentX, urbanEquipmentY;
    char* urbanEquipmentId;
    getUrbanEquipmentInfo(urbanEquipmentInfo, urbanEquipmentType, &urbanEquipmentX, &urbanEquipmentY, &urbanEquipmentId);
    
    setUrbanEquipmentDoubleBorder(urbanEquipmentX, urbanEquipmentY, urbanEquipmentInfo, urbanEquipmentType, Dr);
    
    List blockList = getBlockList(Dr);
        
    if(thereIsHashtag){
        changeBlocksCustomizationInRange(blockList, urbanEquipmentX, urbanEquipmentY, urbanEquipmentId, urbanEquipmentType, radius, txt);
    }else{
        deleteBlocksInRange(blockList, urbanEquipmentX, urbanEquipmentY, urbanEquipmentId, urbanEquipmentType, radius, txt);
    }

    char* wrapperCircleTag = buildWrapperCircleTag(urbanEquipmentX, urbanEquipmentY, radius);
    
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, wrapperCircleTag);
}

void getUrbanEquipmentInfo(Info urbanEquipmentInfo, char* urbanEquipmentType, double* x, double* y, char* *urbanEquipmentId){
    if(urbanEquipmentType[0] == 'h'){
        *x = atof(getHydrantX(urbanEquipmentInfo));
        *y = atof(getHydrantY(urbanEquipmentInfo));
        *urbanEquipmentId = getHydrantId(urbanEquipmentInfo);
    }else if(urbanEquipmentType[0] == 's'){
        *x = atof(getSemaphoreX(urbanEquipmentInfo));
        *y = atof(getSemaphoreY(urbanEquipmentInfo));
        *urbanEquipmentId = getSemaphoreId(urbanEquipmentInfo);
    }else if(urbanEquipmentType[0] == 'r'){
        *x = atof(getBaseRadioX(urbanEquipmentInfo));
        *y = atof(getBaseRadioY(urbanEquipmentInfo));
        *urbanEquipmentId = getSemaphoreId(urbanEquipmentInfo);
    }else
        return;
}

char* buildUrbanEquipmentInnerCircleTag(double x, double y, double radius, char* urbanEquipmentLetter);

void setUrbanEquipmentDoubleBorder(double x, double y, Info urbanEquipmentInfo, char* urbanEquipmentType, Drawing Dr){
    double urbanEquipmentInnerCircleRadius;
    char urbanEquipmentLetter[4];

    if(urbanEquipmentType[0] == 'h'){
        setHydrantSw(urbanEquipmentInfo, "4.0");
        urbanEquipmentInnerCircleRadius = 6.0;
        strcpy(urbanEquipmentLetter, ".H");
    }else if(urbanEquipmentType[0] == 's'){
        setSemaphoreSw(urbanEquipmentInfo, "4.0");
        urbanEquipmentInnerCircleRadius = 6.0;
        strcpy(urbanEquipmentLetter, ".S");
    }else if(urbanEquipmentType[0] == 'r') {
        setBaseRadioSw(urbanEquipmentInfo, "4.0");
        urbanEquipmentInnerCircleRadius = 6.0;
        strcpy(urbanEquipmentLetter, "RB");
    }

    char* urbanEquipmentInnerCircleTag = buildUrbanEquipmentInnerCircleTag(x, y, urbanEquipmentInnerCircleRadius, urbanEquipmentLetter);
    
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, urbanEquipmentInnerCircleTag);
}

char* buildUrbanEquipmentInnerCircleTag(double x, double y, double radius, char* urbanEquipmentLetter){
    char* innerCircle = (char*) malloc(200 * sizeof(char));
    if(isElementNull(innerCircle, "innerCircle", "buildUrbanEquipmentInnerCircle"))
        return NULL;

    sprintf(innerCircle, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke-width=\"0\" fill=\"forestgreen\" />\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> %s </text>\n", x, y, radius, x, y, urbanEquipmentLetter);
    return innerCircle;
}

void writeBlockDeletionResultOnTxt(File txt, Info blockInfo,  char* urbanEquipmentType, char* urbanEquipmentId, double urbanEquipmentX, double urbanEquipmentY);

void deleteBlocksInRange(List blockList, double urbanEquipmentX, double urbanEquipmentY, char* urbanEquipmentId, char* urbanEquipmentType, double radius, File txt){

    Node auxNODE = NULL;
    Node NODE = getFirst(blockList);
    if(isElementNull(NODE, "NODE", "deleteBlocksInRange | getFirst")){
        return;
    }

    Info blockInfo = NULL;

    while(NODE != NULL){
        blockInfo = get(blockList, NODE);
        
        isElementNull(blockInfo, "blockInfo", "deleteBlocksInRange | get");

        if(isBlockInCircleRange(blockInfo, urbanEquipmentX, urbanEquipmentY, radius)){
            auxNODE = NODE;
            NODE = getNext(blockList, NODE);
            
            writeBlockDeletionResultOnTxt(txt, blockInfo, urbanEquipmentType, urbanEquipmentId, urbanEquipmentX, urbanEquipmentY);
            
            removeNode(blockList, auxNODE, &freeBlock);
        }else{
            NODE = getNext(blockList, NODE);
        }    
    }
}

void changeBlocksCustomizationInRange(List blockList, double urbanEquipmentX, double urbanEquipmentY, char* urbanEquipmentId, char* urbanEquipmentType, double radius, File txt){
    Node NODE = getFirst(blockList);
    if(isElementNull(NODE, "NODE", "changeBlocksCustomizationInRange | getFirst")){
        return;
    }

    Info blockInfo = NULL;
    while(NODE != NULL){
        blockInfo = get(blockList, NODE);
        isElementNull(blockInfo, "blockInfo", "changeBlocksCustomizationInRange | get");

        if(isBlockInCircleRange(blockInfo, urbanEquipmentX, urbanEquipmentY, radius)){
            setBlockRx(blockInfo, "10");
            setBlockCfill(blockInfo, "beige");
            setBlockCstrk(blockInfo, "olive");

            writeBlockDeletionResultOnTxt(txt, blockInfo, urbanEquipmentType, urbanEquipmentId, urbanEquipmentX, urbanEquipmentY);
        }
            
        NODE = getNext(blockList, NODE);      
    }
}

void writeBlockDeletionResultOnTxt(File txt, Info blockInfo,  char* urbanEquipmentType, char* urbanEquipmentId, double urbanEquipmentX, double urbanEquipmentY){
    char* blockCep = getBlockCep(blockInfo);
    fprintf(txt,"%s | %s - id: %s, x:%lf, y: %lf\n\n", blockCep, urbanEquipmentType, urbanEquipmentId, urbanEquipmentX, urbanEquipmentY);
}

char* buildWrapperCircleTag(double urbanEquipmentX, double urbanEquipmentY, double radius){
    char* wrapperCircleTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(wrapperCircleTag, "wrapperCircleTag", "buildWrapperCircleTag"))
        return NULL;

    sprintf(wrapperCircleTag, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"black\" stroke-width=\"1.5\" fill=\"black\" fill-opacity=\"0.0\" />\n", urbanEquipmentX, urbanEquipmentY, radius);
    return wrapperCircleTag;
}