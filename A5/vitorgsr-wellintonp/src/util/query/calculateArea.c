#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"

typedef struct {
    double x;
    double y;
    double width;
    double height;
}WrapperRectangle;

typedef struct {
    File txt;
    WrapperRectangle rectangle;
    double totalArea;
    List queryElementsList;
    char* urbanEquipmentType;
    double (*getUrbanEquipmentArea)(void*);
}Variables;


void calculateBlocksTotalAreaInRange(DataStructure blocks, Variables* variables);
void calculateUrbanEquipmentsTotalAreaInRange(DataStructure urbanEquipments, Variables* variables, char* urbanEquipmentType, double (*getUrbanEquipmentArea)(void*));

void writeTotalAreaOnTxt(File txt, double totalArea);
char* buildUrbanWrapperRectangleTag(WrapperRectangle wrapperRectangle, double totalArea);

void executeUrbanElementsTotalAreaCalculationInRange(char* command, City Ct, File txt){

    Variables variables;
    sscanf(&command[4], "%lf %lf %lf %lf", &variables.rectangle.x, &variables.rectangle.y, &variables.rectangle.width, &variables.rectangle.height);

    variables.totalArea = 0.0;
    variables.txt = txt;
    variables.queryElementsList = getQueryElements(Ct);

    DataStructure blocks = getBlocks(Ct);
    calculateBlocksTotalAreaInRange(blocks, &variables);

    DataStructure semaphores = getSemaphores(Ct);
    calculateUrbanEquipmentsTotalAreaInRange(semaphores, &variables, "semaforo", getSemaphoreArea);    
    
    DataStructure hydrants = getHydrants(Ct);
    calculateUrbanEquipmentsTotalAreaInRange(hydrants, &variables, "hidrante", getHydrantArea);    

    DataStructure baseRadios = getBaseRadios(Ct);
    calculateUrbanEquipmentsTotalAreaInRange(baseRadios, &variables, "radio-base", getBaseRadioArea);    
    
    char* urbanWrapperRectangleTag = buildUrbanWrapperRectangleTag(variables.rectangle, variables.totalArea);
    insert(variables.queryElementsList, urbanWrapperRectangleTag);

    writeTotalAreaOnTxt(txt, variables.totalArea);
}

int isBlockInRectangleRange(Info blockInfo, WrapperRectangle wrapperRectangle);
void drawBlockAreaOnSvg(Info blockInfo, double blockArea, List queryElementsList);
void writeBlockAreaOnTxt(File txt, char* cep, double blockArea);


void calculateBlockAreaIfItsInRange(Info blockInfo, ExtraInfo extraInfo);

void calculateBlocksTotalAreaInRange(DataStructure blocks, Variables* variables){

    levelOrderTraversal(blocks, calculateBlockAreaIfItsInRange, variables);
}

void calculateBlockAreaIfItsInRange(Info blockInfo, ExtraInfo extraInfo){
 
    Variables* variables = (Variables*) extraInfo;

    if(isBlockInRectangleRange(blockInfo, variables->rectangle)){
        double blockArea = getBlockArea(blockInfo);
        variables->totalArea += blockArea;

        drawBlockAreaOnSvg(blockInfo, blockArea, variables->queryElementsList);

        char* cep = getBlockCep(blockInfo);
        writeBlockAreaOnTxt(variables->txt, cep, blockArea);
    }

}
    
int isBlockInRectangleRange(Info blockInfo, WrapperRectangle wrapperRectangle){
    double x = atof(getBlockX(blockInfo));
    double y = atof(getBlockY(blockInfo));
    double w = atof(getBlockWidth(blockInfo));
    double h = atof(getBlockHeight(blockInfo));

    if((x > wrapperRectangle.x) && (x + w < wrapperRectangle.x + wrapperRectangle.width) &&
       (y > wrapperRectangle.y) && (y + h < wrapperRectangle.y + wrapperRectangle.height))
       
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
    if(blockAreaTag) return NULL;

    sprintf(blockAreaTag, "\t<text x=\"%lf\" y=\"%lf\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %.2lf </text>\n", blockCenterX, (blockCenterY + 10.0), blockArea);
    return blockAreaTag;
}

void writeBlockAreaOnTxt(File txt, char* cep, double blockArea ){
    fprintf(txt, "cep: %s - area: %lf\n\n", cep, blockArea); 
}


void calculateUrbanEquipmentAreaIfItsInRange(Info urbanEquipmentInfo, ExtraInfo extraInfo);

void calculateUrbanEquipmentsTotalAreaInRange(DataStructure urbanEquipments, Variables* variables, char* urbanEquipmentType, double (*getUrbanEquipmentArea)(void*)){
    
    variables->urbanEquipmentType = urbanEquipmentType;
    variables->getUrbanEquipmentArea = getUrbanEquipmentArea;
    
    levelOrderTraversal(urbanEquipments, calculateUrbanEquipmentAreaIfItsInRange, variables);
}

int isUrbanEquipmentInRectangleRange(Info urbanEquipmentInfo, char* urbanEquipmentType, WrapperRectangle wrapperRectangle);

void calculateUrbanEquipmentAreaIfItsInRange(Info urbanEquipmentInfo, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;

    if(isUrbanEquipmentInRectangleRange(urbanEquipmentInfo, variables->urbanEquipmentType, variables->rectangle)){
        double urbanEquipmentArea = (*(variables->getUrbanEquipmentArea))(urbanEquipmentInfo);
        variables->totalArea += urbanEquipmentArea;
    }
}

void getUrbanEquipmentInfoByType(Info urbanEquipmentInfo, char* urbanEquipmentType, double* x, double* y, double* radius);

int isUrbanEquipmentInRectangleRange(Info urbanEquipmentInfo, char* urbanEquipmentType, WrapperRectangle wrapperRectangle){

    double x, y, radius;
    getUrbanEquipmentInfoByType(urbanEquipmentInfo, urbanEquipmentType, &x, &y, &radius);

    if((x - radius > wrapperRectangle.x) && (x + radius < wrapperRectangle.x + wrapperRectangle.width) &&
       (y - radius > wrapperRectangle.y) && (y + radius < wrapperRectangle.y + wrapperRectangle.height))
        
        return 1;
    else
        return 0;
}

void getUrbanEquipmentInfoByType(Info urbanEquipmentInfo, char* urbanEquipmentType, double* x, double* y, double* radius){
    
    *radius = 10.0;

    if(urbanEquipmentType[0] == 'h'){
        *x = atof(getHydrantX(urbanEquipmentInfo));
        *y = atof(getHydrantY(urbanEquipmentInfo)); 

    }else if(urbanEquipmentType[0] == 's'){
        *x = atof(getSemaphoreX(urbanEquipmentInfo));
        *y = atof(getSemaphoreY(urbanEquipmentInfo));

    }else if(urbanEquipmentType[0] == 'r'){
        *x = atof(getBaseRadioX(urbanEquipmentInfo));
        *y = atof(getBaseRadioY(urbanEquipmentInfo));
    }
}

char* buildUrbanWrapperRectangleTag(WrapperRectangle wrapperRectangle, double totalArea){
    char* wrapperUrbanRectangleTag = (char*) malloc(500 * sizeof(char));
    if(wrapperUrbanRectangleTag == NULL) return NULL;

    sprintf(wrapperUrbanRectangleTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"black\" stroke-width=\"1.5\" fill-opacity=\"0.0\" />\n\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"-100\" style=\"stroke:rgb(0,0,0);stroke-width:1.5\" />\t<text x=\"%lf\" y=\"-110\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %.2lf </text>\n", wrapperRectangle.width, wrapperRectangle.height, wrapperRectangle.x, wrapperRectangle.y, wrapperRectangle.x, wrapperRectangle.y, wrapperRectangle.x, wrapperRectangle.x, totalArea);
    return wrapperUrbanRectangleTag;
}

void writeTotalAreaOnTxt(File txt, double totalArea){
    fprintf(txt, "Area total: %lf\n\n", totalArea);
}