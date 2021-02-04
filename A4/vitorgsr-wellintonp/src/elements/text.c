#include "../include/headers.h"
#include "../include/util.h"
#include "text.h"

typedef struct text {
    char* id;
    char* x;
    char* y;
    Point coordinates;
    char* corb;
    char* corp;
    char* textContent;
}text;

Text createText(char* id, char* x, char* y, char* corb, char* corp, char* textContent){
    text *txt = (text*) malloc(sizeof(text));
    txt->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    txt->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    txt->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    txt->corb = (char*) malloc((strlen(corb) + 1) * sizeof(char));
    txt->corp = (char*) malloc((strlen(corp) + 1) * sizeof(char));
    txt->textContent = (char*) malloc((strlen(textContent) + 1) * sizeof(char));

    strcpy(txt->id, id);
    strcpy(txt->x, x);
    strcpy(txt->y, y);
    txt->coordinates = createPoint(atof(x), atof(y));
    strcpy(txt->corb, corb);
    strcpy(txt->corp, corp);
    strcpy(txt->textContent, textContent);

    return txt;
}

char* getTextId(Text Txt){
    if(isElementNull(Txt, "Texto", "getTextId"))
        return NULL;

    text *txt = (text*) Txt;
    return txt->id;
}

char* getTextX(Text Txt){
    if(isElementNull(Txt, "Texto", "getTextX"))
        return NULL;

    text *txt = (text*) Txt;
    return txt->x;
}

char* getTextY(Text Txt){
    if(isElementNull(Txt, "Texto", "getTextY"))
        return NULL;
    text *txt = (text*) Txt;
    return txt->y;
}

Point getTextCoordinates(Text Txt){
    text *txt = (text*) Txt;
    return txt->coordinates;
}

char* getTextCorb(Text Txt){
    if(isElementNull(Txt, "Texto", "getTextCorb"))
        return NULL;
    text *txt = (text*) Txt;
    return txt->corb;
}

void setTextCorb(Text Txt, char* corb){
    if(isElementNull(Txt, "Texto", "setTextCorb"))
        return;
    text *txt = (text*) Txt;
    strcpy(txt->corb, corb);
}

char* getTextCorp(Text Txt){
    if(isElementNull(Txt, "Texto", "getTextCorp"))
        return NULL;
    text *txt = (text*) Txt;
    return txt->corp;
}

void setTextCorp(Text Txt, char* corp){
    if(isElementNull(Txt, "Texto", "setTextCorp"))
        return;
    text *txt = (text*) Txt;
    strcpy(txt->corp, corp);
}

char* getTextContent(Text Txt){
    if(isElementNull(Txt, "Texto", "getTextContent"))
        return NULL;
    text *txt = (text*) Txt;
    return txt->textContent;
}

char* textToString(Text Txt){
    if(isElementNull(Txt, "Texto", "textToString"))
        return NULL;
    text *txt = (text*) Txt;

    char* textInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(textInfoString, "Tipo: texto, id: %s, x: %s, y: %s, corb: %s, corp: %s, textContent: %s", txt->id, txt->x, txt->y, txt->corb, txt->corp, txt->textContent);
    return textInfoString;
}

void printText(Text Txt){
    if(isElementNull(Txt, "Texto", "printText"))
        return;
    text *txt = (text*) Txt;
    printf("Texto:\nId: %s\nx: %s\ny: %s\ncorb: %s\ncorp: %s\ntextContent: %s\n\n\n", 
           txt->id, txt->x, txt->y, txt->corb, txt->corp, txt->textContent);
}

void freeText(Text Txt){
    if(isElementNull(Txt, "Texto", "freeText"))
        return;

    text *txt = (text*) Txt;
    free(txt->id);   
    free(txt->x); 
    free(txt->y);
    free(txt->coordinates); 
    free(txt->corb); 
    free(txt->corp);
    free(txt->textContent);
    free(txt);
}