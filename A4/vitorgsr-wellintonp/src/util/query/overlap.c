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

int checkCircleCircleOverlap(Info circ1, Info circ2);
int checkRectRectOverlap(Info rect1, Info rect2);
int checkCircRectOverlap(Info circ, Info rect);

int isThereOverlaping(Info element1Info, Info element2Info, char* element1Type, char* element2Type){ 
    int thereIsOverlaping;
        
    if(element1Type[0] == 'c' && element2Type[0] == 'c')
        thereIsOverlaping = checkCircleCircleOverlap(element1Info, element2Info);

    else if(element1Type[0] == 'r' && element2Type[0] == 'r' )
        thereIsOverlaping = checkRectRectOverlap(element1Info, element2Info);
        
    else if(element1Type[0] == 'r' && element2Type[0] == 'c')
        thereIsOverlaping = checkRectCircOverlap(element1Info, element2Info);

    else if(element1Type[0] == 'c' && element2Type[0] == 'r')
        thereIsOverlaping = checkCircRectOverlap(element1Info, element2Info);
     
    else
        return -1;

    return thereIsOverlaping;
}

int checkCircleCircleOverlap(Info circ1, Info circ2){

    double jRadius = atof(getCircleRadius(circ1));  //**refatorar**//
    double jX = atof(getCircleX(circ1));
    double jY = atof(getCircleY(circ1));

    double kRadius = atof(getCircleRadius(circ2));
    double kX = atof(getCircleX(circ2));
    double kY = atof(getCircleY(circ2));

    //Eles vão se sobrepor quando a distancia entre os centros dos circulos for menor que a soma dos seus raios.
    double D = sqrt(pow((kX - jX), 2) + pow((kY - jY), 2)); //distancia entre os centros dos circulos:

    if(D < jRadius + kRadius){ //Se sobrepõem:
        return 1;
    }else{ //Não se sobrepõem:
        return 0;
    } 
}

int checkRectRectOverlap(Info rect1, Info rect2){
    double jX = atof(getRectangleX(rect1));
    double jY = atof(getRectangleY(rect1));
    double jWidth = atof(getRectangleWidth(rect1));
    double jHeight = atof(getRectangleHeight(rect1));
    double kX = atof(getRectangleX(rect2));
    double kY = atof(getRectangleY(rect2));
    double kWidth = atof(getRectangleWidth(rect2));
    double kHeight = atof(getRectangleHeight(rect2));
        
    //Eles vão se sobrepor quando pelo menos umas das condiçoes abaixo forem satisfeitas: 
    if( ((kY + kHeight > jY) && (kY < jY + jHeight)) ||
        ((kY < jY + jHeight) && (kY + kHeight > jY)) ||
        ((kX + kWidth > jX) && (kX < jX + jWidth)) ||
        ((kX < jX + jWidth) && (kX + kWidth > jX)) ){

        return 1;
    }else{
        return 0;
    }
}


int checkCircRectOverlap(Info circ, Info rect){

    double jRadius = atof(getCircleRadius(circ));
    double jX = atof(getCircleX(circ));
    double jY = atof(getCircleY(circ));

    double kX = atof(getRectangleX(rect));
    double kY = atof(getRectangleY(rect));
    double kWidth = atof(getRectangleWidth(rect));
    double kHeight = atof(getRectangleHeight(rect));

    double rectPointX = getNextestRectPointToCircCenter(kX, kX + kWidth, jX);
    double rectPointY = getNextestRectPointToCircCenter(kY, kY + kHeight, jY);                                                      

    //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:
    double D = sqrt(pow((rectPointX - jX), 2) + pow((rectPointY - jY), 2));

    if(D < jRadius){
        return 1;
    }else{
        return 0;
    }   
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