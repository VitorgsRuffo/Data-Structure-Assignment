#include "../include/headers.h"
#include "../include/utils.h"
#include "../include/query.h"
#include "../drawing.h"
#include "../include/urbanElements.h"

void writeUrbanElementInformationOnTxt(File txt, char* urbanElementToString);

void executeUrbanElementInformationChecking(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "Drawing", "printUrbanElementInformationOnTxt"))
        return;
    
    char identifier[15];
    sscanf(&command[5], "%s", identifier);
    
    char urbanElementType[15];
    Node urbanElementNode = searchForUrbanElementByIdentifier(Dr, identifier, urbanElementType);
    if(isElementNull(urbanElementNode, "urbanElementNode", "printUrbanElementInformationOnTxt | searchForUrbanElementByIdentifier"))
            return;
    
    List urbanElementList = getListByElementType(Dr, urbanElementType);
    
    Info urbanElementInfo = get(urbanElementList, urbanElementNode);
    if(isElementNull(urbanElementInfo, "urbanElementInfo", "printUrbanElementInformationOnTxt | get"))
        return;
    
    char* urbanElementToString = getUrbanElementToString(urbanElementInfo, urbanElementType);
    writeUrbanElementInformationOnTxt(txt, urbanElementToString);
    free(urbanElementToString);
}

void writeUrbanElementInformationOnTxt(File txt, char* urbanElementToString){
    fprintf(txt,"%s\n\n", urbanElementToString);
}