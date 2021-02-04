#include "../include/headers.h"
#include "../include/elements.h"
#include "../input/openInput.h"

void setElementCorbAndCorp(Info elementInfo, char* elementType, char* corb, char* corp, char** originalCorb, char** originalCorp);
void writeElementPaintResultOnTxt(File txt, char* command, char* I, char* elementType, char* originalCorb, char* originalCorp);

void executeElementPainting(char* command, Drawing Dr, File txt, char* paintingType){
    if(isElementNull(Dr, "drawing", "executeElementPainting"))
        return;

    int J = 0; int K = 0; char corb[15]; char corp[15]; 
    
    if(!strcmp(paintingType, "pnt")){
        sscanf(&command[4], "%d %s %s", &J, corb, corp);
        K = J;
    }else if(!strcmp(paintingType, "pnt*")){
        sscanf(&command[4], "%d %d %s %s", &J, &K, corb, corp);
    }else
        return;
    

    char* originalCorb = (char*) malloc(50 * sizeof(char));
    char* originalCorp = (char*) malloc(50 * sizeof(char));

    char elementType[11]; char I[10];

    for(int i = J; i<=K; i++){
        sprintf(I,"%d", i);
        Node elementNode = searchForFigureOrTextElementByIdentifier(Dr, I, elementType);
        if(isElementNull(elementNode, "elementNode", "searchForFigureOrTextElementByIdentifier"))
            return;

        List elementList = getListByElementType(Dr, elementType);
        if(isElementNull(elementList, "elementList", "searchForFigureOrTextElementByIdentifier"))
            return;

        Info elementInfo = get(elementList, elementNode);
        if(isElementNull(elementInfo, "elementInfo", "searchForFigureOrTextElementByIdentifier"))
            return;
        
        setElementCorbAndCorp(elementInfo, elementType, corb, corp, &originalCorb, &originalCorp);
        writeElementPaintResultOnTxt(txt, command, I, elementType, originalCorb, originalCorp);
    }

    free(originalCorb);
    free(originalCorp);
}

void setElementCorbAndCorp(Info elementInfo, char* elementType, char* corb, char* corp, char** originalCorb, char** originalCorp){

    if(elementType[0] == 'c'){
        strcpy(*originalCorb, getCircleCorb(elementInfo));
        strcpy(*originalCorp, getCircleCorp(elementInfo));
        
        setCircleCorb(elementInfo, corb);
        setCircleCorp(elementInfo, corp);
    }
    else if(elementType[0] == 'r'){
        strcpy(*originalCorb, getRectangleCorb(elementInfo));
        strcpy(*originalCorp, getRectangleCorp(elementInfo));

        setRectangleCorb(elementInfo, corb);
        setRectangleCorp(elementInfo, corp);
    }
    else if(elementType[0] == 't'){
        
        strcpy(*originalCorb, getTextCorb(elementInfo));
        strcpy(*originalCorp, getTextCorp(elementInfo));

        setTextCorb(elementInfo, corb);
        setTextCorp(elementInfo, corp);
    }else
        return;
}

void writeElementPaintResultOnTxt(File txt, char* command, char* I, char* elementType, char* originalCorb, char* originalCorp){
    fprintf(txt,"%s\nId: %s, Tipo da figura: %s | corb original: %s, corp original: %s\n\n", command, I, elementType, originalCorb, originalCorp);
}