#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"

typedef struct WrapperRectangle {
    double x;
    double y;
    double width;
    double height;
}WrapperRectangle;


int isThereOverlaping(Info element1Info, Info element2Info, char* element1Type, char* element2Type);
void calculateWrapperRectangleInformation(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info, char* element1Type, char* element2Type);
char* buildWrapperRectangleTag(WrapperRectangle *wrapperRectangle, char* extraAttribute);
void writeOverlapResultOnTxt(File txt, char* command, char* J, char* element1Type, char* K, char* element2Type, char* overlapResult);


void executeOverlapTest(char* command, City Ct, File txt){

    char J[10]; char K[10];
    sscanf(&command[3], "%s %s", J, K);

    char element1Type[11]; char element2Type[11];

    Node element1Node = searchForFigureOrTextElementByIdentifier(Ct, J, element1Type);
    if(element1Node == NULL)
        return;

    Node element2Node = searchForFigureOrTextElementByIdentifier(Ct, K, element2Type);
    if(element2Node == NULL)
        return;

    DataStructure elements1 = getDataStructureByElementType(Ct, element1Type);
    Info element1Info = getPQuadTreeNodeInfo(elements1, element1Node);

    DataStructure elements2 = getDataStructureByElementType(Ct, element2Type);
    Info element2Info = getPQuadTreeNodeInfo(elements2, element2Node);

    int thereIsOverlaping = isThereOverlaping(element1Info, element2Info, element1Type, element2Type);
    char overlapResult[5];
    char extraWrapperRectangleAttribute[30];
    
    if(thereIsOverlaping){
        strcpy(overlapResult, "SIM");
        strcpy(extraWrapperRectangleAttribute, "");
    }else{
        strcpy(overlapResult, "NAO");
        strcpy(extraWrapperRectangleAttribute, "stroke-dasharray=\"5,5\"");
    }

    WrapperRectangle wrapperRectangle;

    calculateWrapperRectangleInformation(&wrapperRectangle, element1Info, element2Info, element1Type, element2Type);   
    char* wrapperRectangleTag = buildWrapperRectangleTag(&wrapperRectangle, extraWrapperRectangleAttribute);

    List queryElementsList = getQueryElements(Ct);
    insert(queryElementsList, wrapperRectangleTag);

    writeOverlapResultOnTxt(txt, command, J, element1Type, K, element2Type, overlapResult);
}

int isThereOverlaping(Info element1Info, Info element2Info, char* element1Type, char* element2Type){ 
    int thereIsOverlaping;
        
    if(element1Type[0] == 'c' && element2Type[0] == 'c')
        thereIsOverlaping = isThereCirclesOverlap(element1Info, element2Info);

    else if(element1Type[0] == 'r' && element2Type[0] == 'r' )
        thereIsOverlaping = isThereRectanglesOverlap(element1Info, element2Info);

    else if(element1Type[0] == 'c' && element2Type[0] == 'r')
        thereIsOverlaping = isThereOverlapBetweenCircleAndRectangle(element1Info, element2Info);

    else if(element1Type[0] == 'r' && element2Type[0] == 'c'){
        swapInformations(&element1Info, &element2Info);
        thereIsOverlaping = isThereOverlapBetweenCircleAndRectangle(element1Info, element2Info);
        swapInformations(&element1Info, &element2Info);
    }

    else
        return -1;

    return thereIsOverlaping;
}

void calculateCircCircWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info);
void calculateRectRectWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info);
void calculateRectCircWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info);
void calculateCircRectWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info);

void calculateWrapperRectangleInformation(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info, char* element1Type, char* element2Type){
    if(element1Type[0] == 'c' && element2Type[0] == 'c')
        calculateCircCircWrapperRectangle(wrapperRectangle, element1Info, element2Info);
    
    else if(element1Type[0] == 'r' && element2Type[0] == 'r' )
        calculateRectRectWrapperRectangle(wrapperRectangle, element1Info, element2Info);

    else if(element1Type[0] == 'r' && element2Type[0] == 'c')
        calculateRectCircWrapperRectangle(wrapperRectangle, element1Info, element2Info);

    else if(element1Type[0] == 'c' && element2Type[0] == 'r')
        calculateCircRectWrapperRectangle(wrapperRectangle, element1Info, element2Info);

    else
        return;
}

void calculateCircCircWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info){
    
    float jRadius = atof(getCircleRadius(element1Info)); //**refatorar**//
    float jX = atof(getCircleX(element1Info));
    float jY = atof(getCircleY(element1Info));

    float kRadius = atof(getCircleRadius(element1Info));
    float kX = atof(getCircleX(element2Info));
    float kY = atof(getCircleY(element2Info));
        
    //X:
    if(jX - jRadius < kX - kRadius){
        wrapperRectangle->x = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois circulos.
    }else{
        wrapperRectangle->x = (kX - kRadius) - 10;
    }

    //Y:
    if(jY - jRadius < kY - kRadius){
        wrapperRectangle->y = (jY - jRadius) - 10;
    }else{
        wrapperRectangle->y = (kY - kRadius) - 10;
    }

    //Width:
    if(jX + jRadius > kX + kRadius){
        wrapperRectangle->width = (jX + jRadius + 10) - wrapperRectangle->x;
    }else{
        wrapperRectangle->width = (kX + kRadius + 10) - wrapperRectangle->x;
    }

    //Height:
    if(jY + jRadius > kY + kRadius){
        wrapperRectangle->height = (jY + jRadius + 10) - wrapperRectangle->y;
    }else{
        wrapperRectangle->height = (kY + kRadius + 10) - wrapperRectangle->y;
    }
}

void calculateRectRectWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info){
    
    double jX = atof(getRectangleX(element1Info));
    double jY = atof(getRectangleY(element1Info));
    double jW = atof(getRectangleWidth(element1Info));
    double jH = atof(getRectangleHeight(element1Info));

    double kX = atof(getRectangleX(element2Info));
    double kY = atof(getRectangleY(element2Info));
    double kW = atof(getRectangleWidth(element2Info));
    double kH = atof(getRectangleHeight(element2Info));                                                      

    if(jX < kX){//X:
        wrapperRectangle->x = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
    }else{
        wrapperRectangle->x = kX - 10;
    }

    if(jY < kY){ //Y:
        wrapperRectangle->y = jY - 10;
    }else{
        wrapperRectangle->y = kY - 10;
    }

    if(jX + jW > kX + kW){ //W:
        wrapperRectangle->width = (jX + jW + 10) - wrapperRectangle->x;
    }else{
        wrapperRectangle->width = (kX + kW + 10) - wrapperRectangle->x;
    }

    if(jY + jH > kY + kH){ //H:
        wrapperRectangle->height = (jY + jH + 10) - wrapperRectangle->y;
    }else{
        wrapperRectangle->height = (kY + kH + 10) - wrapperRectangle->y;
    }
}

void calculateRectCircWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info){
    
    double jX = atof(getRectangleX(element1Info));
    double jY = atof(getRectangleY(element1Info));
    double jW = atof(getRectangleWidth(element1Info));
    double jH = atof(getRectangleHeight(element1Info));     

    double kRadius = atof(getCircleRadius(element2Info));
    double kX = atof(getCircleX(element2Info));
    double kY = atof(getCircleY(element2Info));

    if(jX < kX - kRadius){  //X:
        wrapperRectangle->x = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
    }else{
        wrapperRectangle->x = (kX - kRadius) - 10;
    }

    if(jY < kY - kRadius){ //Y:
        wrapperRectangle->y = jY - 10;
    }else{
        wrapperRectangle->y = (kY - kRadius) - 10;
    }

    if(jX + jW > kX + kRadius){ //W:
        wrapperRectangle->width = (jX + jW + 10) - wrapperRectangle->x;
    }else{
        wrapperRectangle->width = (kX + kRadius + 10) - wrapperRectangle->x;
    }

    if(jY + jH > kY + kRadius){ //H:
        wrapperRectangle->height = (jY + jH + 10) - wrapperRectangle->y;
    }else{
        wrapperRectangle->height = (kY + kRadius + 10) - wrapperRectangle->y;
    }
}

void calculateCircRectWrapperRectangle(WrapperRectangle *wrapperRectangle, Info element1Info, Info element2Info){
    
    double jRadius = atof(getCircleRadius(element1Info));
    double jX = atof(getCircleX(element1Info));
    double jY = atof(getCircleY(element1Info));

    double kX = atof(getRectangleX(element2Info));
    double kY = atof(getRectangleY(element2Info));
    double kW = atof(getRectangleWidth(element2Info));
    double kH = atof(getRectangleHeight(element2Info));     

    
    if(jX - jRadius < kX){ //X:
        wrapperRectangle->x = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
    }else{
        wrapperRectangle->x = kX - 10;
    }

    if(jY - jRadius < kY){ //Y:
        wrapperRectangle->y = (jY - jRadius) - 10;
    }else{
        wrapperRectangle->y = kY - 10;
    }

    if(jX + jRadius > kX + kW){//W:
        wrapperRectangle->width = (jX + jRadius + 10) - wrapperRectangle->x;
    }else{
        wrapperRectangle->width = (kX + kW + 10) - wrapperRectangle->x;
    }

    if(jY + jRadius > kY + kH){//H:
        wrapperRectangle->height = (jY + jRadius + 10) - wrapperRectangle->y;
    }else{
        wrapperRectangle->height = (kY + kH + 10) - wrapperRectangle->y;
    }
}

char* buildWrapperRectangleTag(WrapperRectangle *wrapperRectangle, char* extraWrapperRectangleAttribute){
    char* wrapperRectangleTag = (char*) malloc(200 * sizeof(char));
    if(wrapperRectangleTag == NULL)
        return NULL;

    sprintf(wrapperRectangleTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"rgb(0,0,0)\" stroke-width=\"1.5\" fill=\"#044B94\" fill-opacity=\"0.0\" %s />\n", wrapperRectangle->width, wrapperRectangle->height, wrapperRectangle->x, wrapperRectangle->y, extraWrapperRectangleAttribute);
    return wrapperRectangleTag;
}

void writeOverlapResultOnTxt(File txt, char* command, char* J, char* element1Type, char* K, char* element2Type, char* overlapResult){
    fprintf(txt,"%s\nTipo da figura J: %s, Tipo da figura K: %s | Resultado: %s\n\n", command, element1Type, element2Type, overlapResult);
}