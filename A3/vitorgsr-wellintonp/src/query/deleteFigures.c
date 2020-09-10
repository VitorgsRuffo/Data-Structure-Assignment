#include "../include/headers.h"
#include "../include/util.h"
#include "../drawing.h"
#include "../include/figures.h"

void* getElementFreeFunction(char* elementType);
void* getElementToStringFunction(char* elementType);
void writeElementDeletionResultOnTxt(File txt, char* command, char* (*elementToString)(void*), Info elementInfo);

void executeElementDeletion(char* command, Drawing Dr, File txt, char* deletionType){
    if(isElementNull(Dr, "drawing", "executeElementDeletion"))
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
        
        Node elementNode = searchForFigureOrTextElementByIdentifier(Dr, I, elementType);
        if(isElementNull(elementNode, "elementNode", "searchForFigureOrTextElementByIdentifier"))
            continue;
        
        List elementList = getListByElementType(Dr, elementType);

        Info elementInfo = get(elementList, elementNode);
        if(isElementNull(elementNode, "elementInfo", "searchForFigureOrTextElementByIdentifier"))
            continue;
        

        char* (*elementToStringFunction)(void*);
        elementToStringFunction = getElementToStringFunction(elementType);
        writeElementDeletionResultOnTxt(txt, command, elementToStringFunction, elementInfo);
        
        void (*freeElementFunction)(void*);
        freeElementFunction = getElementFreeFunction(elementType);
        removeNode(elementList, elementNode, freeElementFunction);        
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