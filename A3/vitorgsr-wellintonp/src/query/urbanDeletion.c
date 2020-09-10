#include "../include/headers.h"
#include "../include/util.h"
#include "../include/query.h"
#include "../drawing.h"
#include "../include/urbanElements.h"

typedef struct{
    double x;
    double y;
}UrbanElementCenter;

void getUrbanElementCenter(Info urbanElementInfo, char* urbanElementType, UrbanElementCenter* urbanElementCenter);
char* buildVerticalLineTag(UrbanElementCenter* urbanElementCenter, char* identifier);
void removeUrbanElement(List urbanElementList, Node urbanElementNode, char* urbanElementType);
void writeDeletedUrbanElementInformationOnTxt(File txt, char* urbanElementToString);

void executeUrbanElementDeletion(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeUrbanElementDeletion"))
        return;

    char identifier[15];
    sscanf(&command[4], "%s", identifier);

    char urbanElementType[15];
    Node urbanElementNode = searchForUrbanElementByIdentifier(Dr, identifier, urbanElementType);
    if(isElementNull(urbanElementNode, "urbanElementNode", "executeUrbanElementDeletion | searchForUrbanElementByIdentifier"))
            return;
    
    List urbanElementList = getListByElementType(Dr, urbanElementType);
    Info urbanElementInfo = get(urbanElementList, urbanElementNode);
    if(isElementNull(urbanElementInfo, "urbanElementInfo", "executeUrbanElementDeletion | get"))
        return;
    

    char* urbanElementToString = getUrbanElementToString(urbanElementInfo, urbanElementType);
    writeDeletedUrbanElementInformationOnTxt(txt, urbanElementToString); 
    free(urbanElementToString);

    UrbanElementCenter urbanElementCenter;
    getUrbanElementCenter(urbanElementInfo, urbanElementType, &urbanElementCenter);
   
    char* verticalLineTag = buildVerticalLineTag(&urbanElementCenter, identifier);
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, verticalLineTag);
    
    removeUrbanElement(urbanElementList, urbanElementNode, urbanElementType);
}

void getUrbanElementCenter(Info urbanElementInfo, char* urbanElementType, UrbanElementCenter* urbanElementCenter){

    if(urbanElementType[0] == 'q'){
        
        urbanElementCenter->x = atof(getBlockX(urbanElementInfo)) + (atof(getBlockWidth(urbanElementInfo)) / 2.0);
        urbanElementCenter->y = atof(getBlockY(urbanElementInfo)) + (atof(getBlockHeight(urbanElementInfo)) / 2.0);

    }else if(urbanElementType[0] == 'h'){
        
        urbanElementCenter->x = atof(getHydrantX(urbanElementInfo));
        urbanElementCenter->y = atof(getHydrantY(urbanElementInfo));
  
    }else if(urbanElementType[0] == 's'){
        
        urbanElementCenter->x = atof(getSemaphoreX(urbanElementInfo));
        urbanElementCenter->y = atof(getSemaphoreY(urbanElementInfo));
    
    }else if(urbanElementType[0] == 'r'){ 

        urbanElementCenter->x = atof(getBaseRadioX(urbanElementInfo));
        urbanElementCenter->y = atof(getBaseRadioY(urbanElementInfo));
    }         
}

char* buildVerticalLineTag(UrbanElementCenter* urbanElementCenter, char* identifier){
    char* verticalLineTag = (char*) malloc(300 * sizeof(char));
    if(isElementNull(verticalLineTag, "verticalLineTag", "buildVerticalLineTag"))
        return NULL;

    
    sprintf(verticalLineTag, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"-100\" style=\"stroke:rgb(0,0,0);stroke-width:1.5\" />\t<text x=\"%lf\" y=\"-110\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %s </text>\n", urbanElementCenter->x, urbanElementCenter->y, urbanElementCenter->x, urbanElementCenter->x, identifier);
    return verticalLineTag;
}

void removeUrbanElement(List urbanElementList, Node urbanElementNode, char* urbanElementType){

    if(urbanElementType[0] == 'q')
        removeNode(urbanElementList, urbanElementNode, &freeBlock);

    else if(urbanElementType[0] == 'h')
        removeNode(urbanElementList, urbanElementNode, &freeHydrant);
  
    else if(urbanElementType[0] == 's')
        removeNode(urbanElementList, urbanElementNode, &freeSemaphore);

    else if(urbanElementType[0] == 'r') 
        removeNode(urbanElementList, urbanElementNode, &freeBaseRadio); 
}

void writeDeletedUrbanElementInformationOnTxt(File txt, char* urbanElementToString){
    fprintf(txt,"%s\n\n", urbanElementToString);
}