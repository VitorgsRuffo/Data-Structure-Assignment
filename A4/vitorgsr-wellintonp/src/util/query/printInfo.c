#include "../include/headers.h"
#include "../include/urbanElements.h"
#include "../input/openInput.h"

void writeUrbanElementInformationOnTxt(File txt, char* urbanElementToString);

void executeUrbanElementInformationChecking(char* command, City Ct, File txt){
    if(command == NULL || Ct == NULL || txt == NULL)
        return;
    
    char identifier[15];
    sscanf(&command[5], "%s", identifier);
    
    char urbanElementType[15];
    Node urbanElementNode = searchForUrbanElementByIdentifier(Ct, identifier, urbanElementType);
    if(isElementNull(urbanElementNode, "urbanElementNode", "printUrbanElementInformationOnTxt | searchForUrbanElementByIdentifier"))
            return;
    
    List urbanElementList = getListByElementType(Ct, urbanElementType);
    
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