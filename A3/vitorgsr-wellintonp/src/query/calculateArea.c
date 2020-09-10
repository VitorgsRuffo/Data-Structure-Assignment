#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing.h"
#include "../include/query.h"

typedef struct {
    double x;
    double y;
    double width;
    double height;
}WrapperRectangle;


void calculateBlocksTotalAreaInRange(double* totalArea, List blockList, WrapperRectangle* wrapperRectangle, List queryElementsList, File txt);
void calculateUrbanEquipmentsTotalAreaInRange(double* totalArea, List urbanEquipmentList, char* urbanEquipmentType, WrapperRectangle* wrapperRectangle, double (*getUrbanEquipmentArea)(void*));

void writeTotalAreaOnTxt(File txt, double totalArea);
char* buildUrbanWrapperRectangleTag(WrapperRectangle wrapperRectangle, double totalArea);

void executeUrbanElementsTotalAreaCalculationInRange(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeUrbanElementsTotalAreaCalculationInRange"))
        return;

    WrapperRectangle wrapperRectangle;
    sscanf(&command[4], "%lf %lf %lf %lf", &wrapperRectangle.x, &wrapperRectangle.y, &wrapperRectangle.width, &wrapperRectangle.height);

    double totalArea = 0.0;

    List blockList = getBlockList(Dr);
    List queryElementsList = getQueryElementsList(Dr);
    calculateBlocksTotalAreaInRange(&totalArea, blockList, &wrapperRectangle, queryElementsList, txt);

    List semaphoreList = getSemaphoreList(Dr);
    calculateUrbanEquipmentsTotalAreaInRange(&totalArea, semaphoreList, "semaforo", &wrapperRectangle, &getSemaphoreArea);    
    
    List hydrantList = getHydrantList(Dr);
    calculateUrbanEquipmentsTotalAreaInRange(&totalArea, hydrantList, "hidrante", &wrapperRectangle, &getHydrantArea);    

    List baseRadioList = getBaseRadioList(Dr);
    calculateUrbanEquipmentsTotalAreaInRange(&totalArea, baseRadioList, "radio-base", &wrapperRectangle, &getBaseRadioArea);    
    
    
    char* urbanWrapperRectangleTag = buildUrbanWrapperRectangleTag(wrapperRectangle, totalArea);
    insert(queryElementsList, urbanWrapperRectangleTag);

    writeTotalAreaOnTxt(txt, totalArea);
}

int isBlockInRectangleRange(Info blockInfo, WrapperRectangle* wrapperRectangle);
void drawBlockAreaOnSvg(Info blockInfo, double blockArea, List queryElementsList);
void writeBlockAreaOnTxt(File txt, char* cep, double blockArea);

void calculateBlocksTotalAreaInRange(double* totalArea, List blockList, WrapperRectangle* wrapperRectangle, List queryElementsList, File txt){
    Node NODE = getFirst(blockList);
    if(isElementNull(NODE, "NODE", "calculateBlocksTotalAreaInRange | getFirst"))
        return;
    
    Info blockInfo = NULL;
    double blockArea = 0.0;
    char* cep = NULL;

    while(NODE != NULL){

        blockInfo = get(blockList, NODE);
       
        if(isBlockInRectangleRange(blockInfo, wrapperRectangle)){
            blockArea = getBlockArea(blockInfo);
            *totalArea += blockArea;

            drawBlockAreaOnSvg(blockInfo, blockArea, queryElementsList);

            cep = getBlockCep(blockInfo);
            writeBlockAreaOnTxt(txt, cep, blockArea);
        }

        NODE = getNext(blockList, NODE);
    }
}
    
int isBlockInRectangleRange(Info blockInfo, WrapperRectangle* wrapperRectangle){
    double x = atof(getBlockX(blockInfo));
    double y = atof(getBlockY(blockInfo));
    double w = atof(getBlockWidth(blockInfo));
    double h = atof(getBlockHeight(blockInfo));

    if((x > wrapperRectangle->x) && (x + w < wrapperRectangle->x + wrapperRectangle->width) &&
       (y > wrapperRectangle->y) && (y + h < wrapperRectangle->y + wrapperRectangle->height))
       
        return 1;
        
    else
        return 0;
}
        
char* buildBlockAreaTag(double blockCenterX, double blockCenterY, double blockArea);

void drawBlockAreaOnSvg(Info blockInfo, double blockArea, List queryElementsList){
    double blockCenterX = atof(getBlockX(blockInfo)) + (atof(getBlockWidth(blockInfo)) / 2.0);
    double blockCenterY = atof(getBlockY(blockInfo)) + (atof(getBlockHeight(blockInfo)) / 2.0);

    char* blockAreaTag = buildBlockAreaTag(blockCenterX, blockCenterY, blockArea);
    insert(queryElementsList, blockAreaTag);
}

char* buildBlockAreaTag(double blockCenterX, double blockCenterY, double blockArea){
    char* blockAreaTag = (char*) malloc(300 * sizeof(char));
    if(isElementNull(blockAreaTag, "blockAreaTag", "buildblockAreaTag"))
        return NULL;

    
    sprintf(blockAreaTag, "\t<text x=\"%lf\" y=\"%lf\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %.2lf </text>\n", blockCenterX, (blockCenterY + 10.0), blockArea);
    return blockAreaTag;
}

void writeBlockAreaOnTxt(File txt, char* cep, double blockArea ){
    fprintf(txt, "cep: %s - area: %lf\n\n", cep, blockArea); 
}

int isUrbanEquipmentInRectangleRange(Info urbanEquipmentInfo, char* urbanEquipmentType, WrapperRectangle* wrapperRectangle);

void calculateUrbanEquipmentsTotalAreaInRange(double* totalArea, List urbanEquipmentList, char* urbanEquipmentType, WrapperRectangle* wrapperRectangle, double (*getUrbanEquipmentArea)(void*)){
    Node NODE = getFirst(urbanEquipmentList);
    if(isElementNull(NODE, "NODE", "calculateUrbanEquipmentsTotalAreaInRange | getFirst"))
        return;
    
    Info urbanEquipmentInfo = NULL;
    double urbanEquipmentArea = 0.0;

    while(NODE != NULL){

        urbanEquipmentInfo = get(urbanEquipmentList, NODE);
       
        if(isUrbanEquipmentInRectangleRange(urbanEquipmentInfo, urbanEquipmentType, wrapperRectangle)){
            urbanEquipmentArea = (*getUrbanEquipmentArea)(urbanEquipmentInfo);
            *totalArea += urbanEquipmentArea;
        }

        NODE = getNext(urbanEquipmentList, NODE);
    }
}

void getUrbanEquipmentInfoByType(Info urbanEquipmentInfo, char* urbanEquipmentType, double* x, double* y, double* radius);

int isUrbanEquipmentInRectangleRange(Info urbanEquipmentInfo, char* urbanEquipmentType, WrapperRectangle* wrapperRectangle){

    double x, y, radius;
    getUrbanEquipmentInfoByType(urbanEquipmentInfo, urbanEquipmentType, &x, &y, &radius);

    if((x - radius > wrapperRectangle->x) && (x + radius < wrapperRectangle->x + wrapperRectangle->width) &&
       (y - radius > wrapperRectangle->y) && (y + radius < wrapperRectangle->y + wrapperRectangle->height))
        
        return 1;
    else
        return 0;
}

void getUrbanEquipmentInfoByType(Info urbanEquipmentInfo, char* urbanEquipmentType, double* x, double* y, double* radius){
        
    if(urbanEquipmentType[0] == 'h'){
        *x = atof(getHydrantX(urbanEquipmentInfo));
        *y = atof(getHydrantY(urbanEquipmentInfo));
        *radius = 10.0;

    }else if(urbanEquipmentType[0] == 's'){
        *x = atof(getSemaphoreX(urbanEquipmentInfo));
        *y = atof(getSemaphoreY(urbanEquipmentInfo));
        *radius = 10.0;

    }else if(urbanEquipmentType[0] == 'r'){
        *x = atof(getBaseRadioX(urbanEquipmentInfo));
        *y = atof(getBaseRadioY(urbanEquipmentInfo));
        *radius = 10.0;
    }
}

char* buildUrbanWrapperRectangleTag(WrapperRectangle wrapperRectangle, double totalArea){
    char* wrapperUrbanRectangleTag = (char*) malloc(500 * sizeof(char));
    if(isElementNull(wrapperUrbanRectangleTag, "wrapperUrbanRectangleTag", "buildWrapperUrbanRectangleTag"))
        return NULL;

    sprintf(wrapperUrbanRectangleTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"black\" stroke-width=\"1.5\" fill-opacity=\"0.0\" />\n\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"-100\" style=\"stroke:rgb(0,0,0);stroke-width:1.5\" />\t<text x=\"%lf\" y=\"-110\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %.2lf </text>\n", wrapperRectangle.width, wrapperRectangle.height, wrapperRectangle.x, wrapperRectangle.y, wrapperRectangle.x, wrapperRectangle.y, wrapperRectangle.x, wrapperRectangle.x, totalArea);

    return wrapperUrbanRectangleTag;
}

void writeTotalAreaOnTxt(File txt, double totalArea){
    fprintf(txt, "Area total: %lf\n\n", totalArea);
}