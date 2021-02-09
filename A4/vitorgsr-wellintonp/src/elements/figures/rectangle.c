#include "../include/headers.h"
#include "rectangle.h"
#include "../point.h"

typedef struct rectangle {
    char* id;
    char* width;
    char* height;
    char* x;
    char* y;
    Point coordinates;
    char* corb;
    char* corp;
    char* rw;
}rectangle;

Rectangle createRectangle(char* id, char* width, char* height, char* x, char* y, char* corb, char* corp, char* rw){
    rectangle *rect = (rectangle*) malloc(sizeof(rectangle));
    rect->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    rect->width = (char*) malloc((strlen(width) + 1) * sizeof(char));
    rect->height = (char*) malloc((strlen(height) + 1) * sizeof(char));
    rect->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    rect->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    rect->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    rect->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    rect->rw = (char*) malloc((strlen(rw) + 1) * sizeof(char));

    strcpy(rect->id, id);
    strcpy(rect->width, width);
    strcpy(rect->height, height);
    strcpy(rect->x, x);
    strcpy(rect->y, y);
    rect->coordinates = createPoint(atof(x), atof(y));
    strcpy(rect->corb, corb);
    strcpy(rect->corp, corp);
    strcpy(rect->rw, rw);

    return rect;
}

char* getRectangleId(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->id;
}

char* getRectangleWidth(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->width;
}

void setRectangleWidth(Rectangle Rect, char* width){
    if(Rect == NULL)
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->width, width);
}

char* getRectangleHeight(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->height;
}

void setRectangleHeight(Rectangle Rect, char* height){
    if(Rect == NULL)
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->height, height);
}

char* getRectangleX(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->x;
}

void setRectangleX(Rectangle Rect, char* x){
    if(Rect == NULL)
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->x, x);
    setPointX(rect->coordinates, atof(x));
}

char* getRectangleY(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->y;
}

void setRectangleY(Rectangle Rect, char* y){
    if(Rect == NULL)
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->y, y);
    setPointY(rect->coordinates, atof(y));
}


Point getRectangleCoordinates(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->coordinates;
}

char* getRectangleCorb(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->corb;
}

void setRectangleCorb(Rectangle Rect, char* corb){
    if(Rect == NULL)
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->corb, corb);
}

char* getRectangleCorp(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->corp;
}

void setRectangleCorp(Rectangle Rect, char* corp){
    if(Rect == NULL)
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->corp, corp);
}

char* getRectangleRw(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->rw;
}

char* rectangleToString(Rectangle Rect){
    if(Rect == NULL)
        return NULL;
    rectangle *rect = (rectangle*) Rect;

    char* rectangleInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(rectangleInfoString, "Tipo: retangulo, id: %s, width: %s, height: %s, x: %s, y: %s, corb: %s, corp: %s, rw: %s", rect->id, rect->width, rect->height, rect->x, rect->y, rect->corb, rect->corp, rect->rw);
    return rectangleInfoString;
}

int isPointInsideRect(Rectangle Rect, Point P){
   
    rectangle *rect = (rectangle*) Rect;
   
    double pointX = getPointX(P);
    double pointY = getPointY(P);

    double rectX = atof((*rect).x);
    double rectY = atof((*rect).y);
    double rectW = atof((*rect).width);
    double rectH = atof((*rect).height);

    if( pointX > rectX          &&
        pointX < rectX + rectW  &&
        pointY > rectY          &&
        pointY < rectY + rectH     )

        return 1;
    else
        return 0;
}

/*  
* Pré-Condição: requer o endereco de duas instancias de retangulo.
* Pós-Condição: retorna 1 se um retangulo se sobrepõe com o outro, retorna 0 se nao.
*/
int isThereRectanglesOverlap(Rectangle Rect1, Rectangle Rect2){ 
    rectangle *rect1 = (rectangle*) Rect1;
    rectangle *rect2 = (rectangle*) Rect2;

    double r1X = atof(rect1->x);
    double r1Y = atof(rect1->y);
    double r1Width = atof(rect1->width);
    double r1Height = atof(rect1->height);
    
    double r2X = atof(rect2->x);
    double r2Y = atof(rect2->y);
    double r2Width = atof(rect2->width);
    double r2Height = atof(rect2->height);
        
    //Eles vão se sobrepor quando pelo menos umas das condiçoes abaixo forem satisfeitas: 
    if( ((r2Y + r2Height > r1Y) && (r2Y < r1Y + r1Height)) ||
        ((r2Y < r1Y + r1Height) && (r2Y + r2Height > r1Y)) ||
        ((r2X + r2Width > r1X)  && (r2X < r1X + r1Width))  ||
        ((r2X < r1X + r1Width)  && (r2X + r2Width > r1X))  ){
        return 1;
    }
    else
        return 0;
}

void printRectangle(Rectangle Rect){
    if(Rect == NULL)
        return;
    rectangle *rect = (rectangle*) Rect;
    printf("Retangulo:\nId: %s\nw: %s\nh: %s\nx: %s\ny: %s\ncorb: %s\ncorp: %s\nrw: %s\n\n\n",
           rect->id, rect->width, rect->height, rect->x, rect->y, rect->corb, rect->corp, rect->rw);
}

void freeRectangle(Rectangle Rect){
    if(Rect == NULL)
        return;

    rectangle *rect = (rectangle*) Rect;
    free(rect->id);  
    free(rect->width);  
    free(rect->height);  
    free(rect->x); 
    free(rect->y); 
    free(rect->coordinates);
    free(rect->corb); 
    free(rect->corp);
    free(rect->rw);
    free(rect);
}