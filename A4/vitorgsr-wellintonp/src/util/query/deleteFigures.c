#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../input/openInput.h"
#include "../../include/dataStructure.h"

void* getElementFreeFunction(char* elementType);
void* getElementToStringFunction(char* elementType);
void writeElementDeletionResultOnTxt(File txt, char* command, char* (*elementToString)(void*), Info elementInfo);

void executeElementDeletion(char* command, City Ct, File txt, char* deletionType){
    
    if(command == NULL || Ct == NULL || txt == NULL || deletionType == NULL)
        return;

    int J = 0; int K = 0; 
    
    if(!strcmp(deletionType, "delf")){
        sscanf(&command[5], "%d", &J);
        K = J;
    }else if(!strcmp(deletionType, "delf*")){
        sscanf(&command[6], "%d %d", &J, &K);
    }else
        return;
    
    char elementType[11]; char I[10];

    for(int i = J; i<=K; i++){
        sprintf(I,"%d", i);  
        
        Node elementNode = searchForFigureOrTextElementByIdentifier(Ct, I, elementType);
        if(elementNode == NULL)
            continue;
        
        DataStructure elements = getDataStructureByElementType(Ct, elementType);

        Info elementInfo = getPQuadTreeNodeInfo(elements, elementNode);
        if(elementInfo == NULL)
            continue;
        

        char* (*elementToStringFunction)(void*);
        elementToStringFunction = getElementToStringFunction(elementType);
        writeElementDeletionResultOnTxt(txt, command, elementToStringFunction, elementInfo);
        
        
        void (*freeElementFunction)(void*);
        freeElementFunction = getElementFreeFunction(elementType);

        Info info = removePQuadTreeNode(elements, elementNode);
        (*freeElementFunction)(info);
    }
}
    
void* getElementFreeFunction(char* elementType){
    if(elementType[0] == 'c')
        return &freeCircle;
    
    else if(elementType[0] == 'r')
        return &freeRectangle;
    
    else if(elementType[0] == 't')
        return &freeText;
    
    else
        return NULL;
}

void* getElementToStringFunction(char* elementType){
    if(elementType[0] == 'c')
        return &circleToString;
    
    else if(elementType[0] == 'r')
        return &rectangleToString;
    
    else if(elementType[0] == 't')
        return &textToString;
    
    else
        return NULL;
}

void writeElementDeletionResultOnTxt(File txt, char* command, char* (*elementToStringFunction)(void*), Info elementInfo){
    char* elementFormatedInfo = (*elementToStringFunction)(elementInfo);
    fprintf(txt,"%s\n%s\n\n", command, elementFormatedInfo);
    free(elementFormatedInfo);
}