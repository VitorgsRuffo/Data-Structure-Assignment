#include "../include/headers.h"
#include "../include/util.h"
#include "rectangle.h"

typedef struct rectangle {
    char* id;
    char* width;
    char* height;
    char* x;
    char* y;
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
    strcpy(rect->corb, corb);
    strcpy(rect->corp, corp);
    strcpy(rect->rw, rw);

    return rect;
}

char* getRectangleId(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleId"))
        return NULL;

    rectangle *rect = (rectangle*) Rect;
    return rect->id;
}

char* getRectangleWidth(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleWidth"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->width;
}

char* getRectangleHeight(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleHeight"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->height;
}

char* getRectangleX(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleX"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->x;
}

char* getRectangleY(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleY"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->y;
}

char* getRectangleCorb(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleCorb"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->corb;
}

void setRectangleCorb(Rectangle Rect, char* corb){
    if(isElementNull(Rect, "retangulo", "setRectangleCorb"))
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->corb, corb);
}

char* getRectangleCorp(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleCorp"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->corp;
}

void setRectangleCorp(Rectangle Rect, char* corp){
    if(isElementNull(Rect, "retangulo", "setRectangleCorp"))
        return;
    rectangle *rect = (rectangle*) Rect;
    strcpy(rect->corp, corp);
}

char* getRectangleRw(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "getRectangleRw"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;
    return rect->rw;
}

char* rectangleToString(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "rectangleToString"))
        return NULL;
    rectangle *rect = (rectangle*) Rect;

    char* rectangleInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(rectangleInfoString, "Tipo: retangulo, id: %s, width: %s, height: %s, x: %s, y: %s, corb: %s, corp: %s, rw: %s", rect->id, rect->width, rect->height, rect->x, rect->y, rect->corb, rect->corp, rect->rw);
    return rectangleInfoString;
}

void printRectangle(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "printRectangle"))
        return;
    rectangle *rect = (rectangle*) Rect;
    printf("Retangulo:\nId: %s\nw: %s\nh: %s\nx: %s\ny: %s\ncorb: %s\ncorp: %s\nrw: %s\n\n\n",
           rect->id, rect->width, rect->height, rect->x, rect->y, rect->corb, rect->corp, rect->rw);
}

void freeRectangle(Rectangle Rect){
    if(isElementNull(Rect, "retangulo", "freeRectangle"))
        return;

    rectangle *rect = (rectangle*) Rect;
    free(rect->id);  
    free(rect->width);  
    free(rect->height);  
    free(rect->x); 
    free(rect->y); 
    free(rect->corb); 
    free(rect->corp);
    free(rect->rw);
    free(rect);
}