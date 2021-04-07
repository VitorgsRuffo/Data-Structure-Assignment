#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"

void writeUrbanElementInformationOnTxt(File txt, char* urbanElementToString);

void executeUrbanElementInformationChecking(char* command, City Ct, File txt){
   
    char identifier[15];
    sscanf(&command[5], "%s", identifier);
    
    char urbanElementType[15];
    Node urbanElementNode = searchForUrbanElementByIdentifier(Ct, identifier, urbanElementType);
    if(urbanElementNode == NULL)
            return;
    
    DataStructure urbanElements = getDataStructureByElementType(Ct, urbanElementType);
    
    Info urbanElementInfo = get(urbanElements, urbanElementNode);
    if(urbanElementInfo == NULL)
        return;
    
    char* urbanElementToString = getUrbanElementToString(urbanElementInfo, urbanElementType);
    writeUrbanElementInformationOnTxt(txt, urbanElementToString);
    free(urbanElementToString);
}

void writeUrbanElementInformationOnTxt(File txt, char* urbanElementToString){
    fprintf(txt,"%s\n\n", urbanElementToString);
}