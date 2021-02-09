#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"

typedef struct{
    double x;
    double y;
}UrbanElementCenter;

void getUrbanElementCenter(Info urbanElementInfo, char* urbanElementType, UrbanElementCenter* urbanElementCenter);
char* buildVerticalLineTag(UrbanElementCenter* urbanElementCenter, char* identifier);
void removeUrbanElement(DataStructure urbanElements, Node urbanElementNode, char* urbanElementType);
void writeDeletedUrbanElementInformationOnTxt(File txt, char* urbanElementToString);

void executeUrbanElementDeletion(char* command, City Ct, File txt){
    
    char identifier[15];
    sscanf(&command[4], "%s", identifier);

    char urbanElementType[15];
    Node urbanElementNode = searchForUrbanElementByIdentifier(Ct, identifier, urbanElementType);
    if(urbanElementNode == NULL)
            return;
    
    DataStructure urbanElements = getDataStructureByElementType(Ct, urbanElementType);
    Info urbanElementInfo = getPQuadTreeNodeInfo(urbanElements, urbanElementNode);
    if(urbanElementInfo == NULL)
        return;
    

    char* urbanElementToString = getUrbanElementToString(urbanElementInfo, urbanElementType);
    writeDeletedUrbanElementInformationOnTxt(txt, urbanElementToString); 
    free(urbanElementToString);

    UrbanElementCenter urbanElementCenter;
    getUrbanElementCenter(urbanElementInfo, urbanElementType, &urbanElementCenter);
   
    char* verticalLineTag = buildVerticalLineTag(&urbanElementCenter, identifier);
    List queryElementsList = getQueryElementsList(Ct);
    insert(queryElementsList, verticalLineTag);
    
    removeUrbanElement(urbanElements, urbanElementNode, urbanElementType);
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
    if(verticalLineTag == NULL)
        return NULL;

    
    sprintf(verticalLineTag, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"-100\" style=\"stroke:rgb(0,0,0);stroke-width:1.5\" />\t<text x=\"%lf\" y=\"-110\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %s </text>\n", urbanElementCenter->x, urbanElementCenter->y, urbanElementCenter->x, urbanElementCenter->x, identifier);
    return verticalLineTag;
}

void removeUrbanElement(DataStructure urbanElements, Node urbanElementNode, char* urbanElementType){
    
    Info urbanElementInfo;

    if(urbanElementType[0] == 'q'){
        urbanElementInfo = removePQuadTreeNode(urbanElements, urbanElementNode);
        freeBlock(urbanElementInfo);
        
    }else if(urbanElementType[0] == 'h'){
        urbanElementInfo = removePQuadTreeNode(urbanElements, urbanElementNode);
        freeHydrant(urbanElementInfo);

    }else if(urbanElementType[0] == 's'){
        urbanElementInfo = removePQuadTreeNode(urbanElements, urbanElementNode);
        freeSemaphore(urbanElementInfo);

    }else if(urbanElementType[0] == 'r'){ 
        urbanElementInfo = removePQuadTreeNode(urbanElements, urbanElementNode); 
        freeBaseRadio(urbanElementInfo);
    }
}

void writeDeletedUrbanElementInformationOnTxt(File txt, char* urbanElementToString){
    fprintf(txt,"%s\n\n", urbanElementToString);
}