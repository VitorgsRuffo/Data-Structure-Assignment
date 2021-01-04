#include "../include/headers.h"
#include "../include/util.h"
#include "../drawing/drawing.h"
#include "../include/figures.h"

typedef struct Point {
    double x;
    double y;
}Point;

int isPointAnInnerOne(Info elementInfo, char* elementType, Point *centerOfMass, Point *point);
char* buildPointTag(Point *point, Point *centerOfMass, char* color);
char* buildLineTag(Point *point, Point *centerOfMass, char* color);
void writeInnerPointResultOnTxt(File txt, char* command, char* elementType, char* innerPointResult);

void executeInnerPointTest(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeInnerPointTest"))
        return;

    char J[10]; Point point;
    sscanf(&command[3], "%s %lf %lf", J, &point.x, &point.y);

    char elementType[11];
    Node elementNode = searchForFigureOrTextElementByIdentifier(Dr, J, elementType);
    if(isElementNull(elementNode, "elementNode", "searchForFigureOrTextElementByIdentifier"))
        return;
    
    List elementList = getListByElementType(Dr, elementType);
    Info elementInfo = get(elementList, elementNode);
            
    if(elementType[0] == 't'){
        printf("Erro: elemento cujo id e %s nao foi encontrado nas listas de figuras..\n", J);
        return;
    }
    
    Point centerOfMass;
    int pointIsAnInnerOne = isPointAnInnerOne(elementInfo, elementType, &centerOfMass, &point);
    
    char innerPointResult[15];
    char pointFillColor[8];
    
    if(pointIsAnInnerOne){
        strcpy(innerPointResult, "INTERNO");
        strcpy(pointFillColor, "blue");
    }else{
        strcpy(innerPointResult, "NAO INTERNO");
        strcpy(pointFillColor, "magenta");
    }
    
    char* pointTag = buildPointTag(&point, &centerOfMass, pointFillColor);
    char* lineTag = buildLineTag(&point, &centerOfMass, pointFillColor);

    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, pointTag);
    insert(queryElementsList, lineTag);

    writeInnerPointResultOnTxt(txt, command, elementType, innerPointResult);
}

int checkIfPointIsInsideCircle(Info elementInfo, Point *centerOfMass, Point *point);
int checkIfPointIsInsideRect(Info elementInfo, Point *centerOfMass, Point *point);

int isPointAnInnerOne(Info elementInfo, char* elementType, Point *centerOfMass, Point *point){
    int pointIsAnInnerOne;
        
    if(elementType[0] == 'c')
        pointIsAnInnerOne = checkIfPointIsInsideCircle(elementInfo, centerOfMass, point);

    else if(elementType[0] == 'r')
        pointIsAnInnerOne = checkIfPointIsInsideRect(elementInfo, centerOfMass, point);

    else
        return -1;

    return pointIsAnInnerOne;   
}

int checkIfPointIsInsideCircle(Info elementInfo, Point *centerOfMass, Point *point){

    double jRadius = atof(getCircleRadius(elementInfo));
    double jX = atof(getCircleX(elementInfo));
    double jY = atof(getCircleY(elementInfo));

    centerOfMass->x = jX; //determinando o centro de massa da figura:
    centerOfMass->y = jY;  

    double D = sqrt(pow((point->x - jX), 2) + pow((point->y - jY), 2)); //distancia entre o centro dos circulo e o ponto:
    int isInside;

    if(D < jRadius){
        isInside = 1;
    }else if (D >= jRadius){
        isInside = 0;
    }
    return isInside;
}

int checkIfPointIsInsideRect(Info elementInfo, Point *centerOfMass, Point *point){
    
    
    double jW = atof(getRectangleWidth(elementInfo));
    double jH = atof(getRectangleHeight(elementInfo));
    double jX = atof(getRectangleX(elementInfo));
    double jY = atof(getRectangleY(elementInfo));

    centerOfMass->x = jX + (jW / 2.0);  //determinando o centro de massa da figura:
    centerOfMass->y = jY + (jH / 2.0);  

    int isInside;
    if(point->x < jX + jW && point->x > jX && point->y < jY + jH && point->y > jY){    //sera interno se as condiçoes a seguir forem atendidas:
        isInside = 1;
    }else{
        isInside = 0;
    }
    return isInside;
}

char* buildPointTag(Point *point, Point *centerOfMass, char* color){

    char* pointTag = (char*) malloc(200 * sizeof(char));
    
    
    if(isElementNull(pointTag, "pointTag", "buildPointTag"))
        return NULL;    
    
    sprintf(pointTag, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" stroke=\"black\" stroke-width=\"0\" fill=\"%s\"/>", point->x, point->y, color);

    return pointTag;
}

char* buildLineTag(Point *point, Point *centerOfMass, char* color){
    char* lineTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(lineTag, "lineTag", "buildLineTag"))
        return NULL;
        
    sprintf(lineTag, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"0.8\" />", point->x, point->y, centerOfMass->x, centerOfMass->y, color);
    return lineTag;
}


void writeInnerPointResultOnTxt(File txt, char* command, char* elementType, char* innerPointResult){
    fprintf(txt,"%s\nTipo da figura: %s | Resultado: %s\n\n", command, elementType, innerPointResult);
}