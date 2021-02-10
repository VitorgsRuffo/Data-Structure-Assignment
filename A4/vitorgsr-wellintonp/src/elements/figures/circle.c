#include "../../include/headers.h"
#include "./circle.h"

typedef struct circle{
    char* id;
    char* radius;
    char* x;
    char* y;
    Point coordinates;
    char* corb;
    char* corp;
    char* cw;
}circle;

Circle createCircle(char* id, char* radius, char* x, char* y, char* corb, char* corp, char* cw){

    circle *circ = (circle*) malloc(sizeof(circle));

    circ->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    circ->radius = (char*) malloc((strlen(radius) + 1) * sizeof(char));
    circ->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    circ->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    circ->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    circ->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    circ->cw = (char*) malloc((strlen(cw) + 1) * sizeof(char));

    strcpy(circ->id, id);
    strcpy(circ->radius, radius);
    strcpy(circ->x, x);
    strcpy(circ->y, y);
    circ->coordinates = createPoint(atof(x), atof(y));
    strcpy(circ->corb, corb);
    strcpy(circ->corp, corp);
    strcpy(circ->cw, cw);

    return circ;
}

char* getCircleId(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->id;
}

char* getCircleRadius(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->radius;
}

char* getCircleX(Circle Circ){
    if(Circ == NULL)
        return NULL; 
    circle *circ = (circle*) Circ;
    return circ->x;
}

char* getCircleY(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->y;
}

Point getCircleCoordinates(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->coordinates;
}

char* getCircleCorb(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->corb;
}

void setCircleCorb(Circle Circ, char* corb){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    strcpy(circ->corb, corb);
}

char* getCircleCorp(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->corp;
}

void setCircleCorp(Circle Circ, char* corp){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    strcpy(circ->corp, corp);
}

char* getCircleCw(Circle Circ){
    if(Circ == NULL)
        return NULL;
    circle *circ = (circle*) Circ;
    return circ->cw;
}

char* circleToString(Circle Circ){
    if(Circ == NULL)
        return NULL;

    circle *circ = (circle*) Circ;

    char* circleInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(circleInfoString, "Tipo: circulo, id: %s, radius: %s, x: %s, y: %s, corb: %s, corp: %s, cw: %s", circ->id, circ->radius, circ->x, circ->y, circ->corb, circ->corp, circ->cw);
    return circleInfoString;
}

int isPointInsideCirc(Circle Circ, Point P){
    circle *circ = (circle*) Circ;

    double pointX = getPointX(P);
    double pointY = getPointY(P);
    double circX = atof((*circ).x);
    double circY = atof((*circ).y);
    double circR = atof((*circ).radius);

    double pointCircCenterDistance = sqrt( pow((pointX-circX), 2) + pow((pointY-circY), 2) );

    if(pointCircCenterDistance < circR)
        return 1;
    else
        return 0;
}


int isRectangleInsideCircle(Circle Circ, Rectangle Rect){
    if(Circ == NULL || Rect == NULL) return -1;
    
    double rx = atof(getRectangleX(Rect));
    double ry = atof(getRectangleY(Rect));
    double rw = atof(getRectangleWidth(Rect));
    double rh = atof(getRectangleHeight(Rect));
  
    Point vertex1 = createPoint(rx, ry);
    Point vertex2 = createPoint(rx+rw, ry);
    Point vertex3 = createPoint(rx, ry+rh);
    Point vertex4 = createPoint(rx+rw, ry+rh);

    int rectangleIsInsideCircle = 0;

    if( isPointInsideCirc(Circ, vertex1) &&
        isPointInsideCirc(Circ, vertex2) &&
        isPointInsideCirc(Circ, vertex3) &&
        isPointInsideCirc(Circ, vertex4)  )

        rectangleIsInsideCircle = 1;
    
    free(vertex1);
    free(vertex2);
    free(vertex3);
    free(vertex4);

    return rectangleIsInsideCircle;
}


int isThereCirclesOverlap(Circle Circ1, Circle Circ2){
    if(Circ1 == NULL || Circ2 == NULL) return -1;

    circle *circ1 = (circle*) Circ1;
    circle *circ2 = (circle*) Circ2;

    double c1R = atof(getCircleRadius(circ1->radius));  
    double c1X = atof(getCircleX(circ1->x));
    double c1Y = atof(getCircleY(circ1->y));

    double c2R = atof(getCircleRadius(circ2->radius));
    double c2X = atof(getCircleX(circ2->x));
    double c2Y = atof(getCircleY(circ2->y));

    //Eles vão se sobrepor quando a distancia entre os centros dos circulos for menor que a soma dos seus raios.
    double D = sqrt(pow((c2X - c1X), 2) + pow((c2Y - c1Y), 2)); //distancia entre os centros dos circulos:
    
    if(D < c1R + c2R) //Se sobrepõem:
        return 1;

    else //Não se sobrepõem:
        return 0;
}

double getNextestRectPointToCircCenter(double min, double max, double value);

int isThereOverlapBetweenCircleAndRectangle(Circle Circ, Rectangle Rect){
    if(Circ == NULL || Rect == NULL) return -1;

    circle *circ = (circle*) Circ;
    double cR = atof(circ->radius);
    double cX = atof(circ->x);
    double cY = atof(circ->y);
    
    double rx = atof(getRectangleX(Rect));
    double ry = atof(getRectangleY(Rect));
    double rw = atof(getRectangleWidth(Rect));
    double rh = atof(getRectangleHeight(Rect));


    double rectPointX = getNextestRectPointToCircCenter(rx, rx + rw, cX);
    double rectPointY = getNextestRectPointToCircCenter(ry, ry + rh, cY);                                                      

    //distancia entre o centro do circulo e o ponto do retangulo mais proximo dele:
    double D = sqrt(pow((rectPointX - cX), 2) + pow((rectPointY - cY), 2));

    if(D < cR){
        return 1;
    }else{
        return 0;
    }   
    
}

/*
* Pré-Condição: requer a coordenada inicial do retangulo(x ou y), a coordenada final do retangulo(x+w ou y+h) e por fim a coordenada (x ou y) do centro do circulo.
* Pós-Condição: retorna a coordenada (x ou y) do ponto do retangulo mais proximo do centro do circulo.
*/
double getNextestRectPointToCircCenter(double min, double max, double value){

    if(value < min){
        return min;
    }else if(value > max){
        return max;
    }else{
        return value;
    }
}

void printCircle(Circle Circ){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    printf("Circulo:\nId: %s\nradius: %s\nx: %s\ny: %s\ncorb: %s\ncorp: %s\ncw: %s\n\n\n", 
           circ->id, circ->radius, circ->x, circ->y, circ->corb, circ->corp, circ->cw);
}

void freeCircle(Circle Circ){
    if(Circ == NULL)
        return;
    circle *circ = (circle*) Circ;
    free(circ->id);  
    free(circ->radius);    
    free(circ->x); 
    free(circ->y); 
    free(circ->coordinates);
    free(circ->corb); 
    free(circ->corp); 
    free(circ->cw);   
    free(circ);
}