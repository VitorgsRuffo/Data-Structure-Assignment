#include "../include/headers.h"
#include "customization.h"

typedef struct blockCustomization {
    char* sw;
    char* cfill;
    char* cstrk;
}blockCustomization;

typedef struct hydrantCustomization {
    char* sw;
    char* cfill;
    char* cstrk;
}hydrantCustomization;

typedef struct baseRadioCustomization {
    char* sw;
    char* cfill;
    char* cstrk;
}baseRadioCustomization;

typedef struct semaphoreCustomization {
    char* sw;
    char* cfill;
    char* cstrk;
}semaphoreCustomization;

typedef struct figuresCustomization{
    char* cw;
    char* rw;
}figuresCustomization;

typedef struct elementsCustomization {
    blockCustomization* blockCustom;
    hydrantCustomization* hydrantCustom;
    baseRadioCustomization* baseRadioCustom;
    semaphoreCustomization* semaphoreCustom;
    figuresCustomization* figuresCustom;
}elementsCustomization;

ElementsCustomization createElementsCustomization(){

    elementsCustomization *custom = (elementsCustomization*) malloc(sizeof(elementsCustomization));

    custom->blockCustom = (blockCustomization*) malloc(sizeof(blockCustomization));
    custom->hydrantCustom = (hydrantCustomization*) malloc(sizeof(hydrantCustomization));
    custom->baseRadioCustom = (baseRadioCustomization*) malloc(sizeof(baseRadioCustomization));
    custom->semaphoreCustom = (semaphoreCustomization*) malloc(sizeof(semaphoreCustomization));
    custom->figuresCustom = (figuresCustomization*) malloc(sizeof(figuresCustomization));

    custom->blockCustom->sw = (char*) malloc(10 * sizeof(char));
    custom->blockCustom->cfill = (char*) malloc(20 * sizeof(char));
    custom->blockCustom->cstrk = (char*) malloc(20 * sizeof(char));
    
    custom->hydrantCustom->sw = (char*) malloc(10 * sizeof(char));
    custom->hydrantCustom->cfill = (char*) malloc(20 * sizeof(char));
    custom->hydrantCustom->cstrk = (char*) malloc(20 * sizeof(char));

    custom->baseRadioCustom->sw = (char*) malloc(10 * sizeof(char));
    custom->baseRadioCustom->cfill = (char*) malloc(20 * sizeof(char));
    custom->baseRadioCustom->cstrk = (char*) malloc(20 * sizeof(char));

    custom->semaphoreCustom->sw = (char*) malloc(10 * sizeof(char));
    custom->semaphoreCustom->cfill = (char*) malloc(20 * sizeof(char));
    custom->semaphoreCustom->cstrk = (char*) malloc(20 * sizeof(char));

    custom->figuresCustom->cw = (char*) malloc(10 * sizeof(char));
    custom->figuresCustom->rw = (char*) malloc(10 * sizeof(char));

    strcpy(custom->blockCustom->sw, "3.0");
    strcpy(custom->blockCustom->cfill, "blueviolet");
    strcpy(custom->blockCustom->cstrk, "yellow");

    strcpy(custom->hydrantCustom->sw, "2.0");
    strcpy(custom->hydrantCustom->cfill, "blueviolet");
    strcpy(custom->hydrantCustom->cstrk, "yellow");

    strcpy(custom->baseRadioCustom->sw, "2.0");
    strcpy(custom->baseRadioCustom->cfill, "blueviolet");
    strcpy(custom->baseRadioCustom->cstrk, "yellow");

    strcpy(custom->semaphoreCustom->sw, "2.0");
    strcpy(custom->semaphoreCustom->cfill, "blueviolet");
    strcpy(custom->semaphoreCustom->cstrk, "yellow");

    strcpy(custom->figuresCustom->cw, "1.5");
    strcpy(custom->figuresCustom->rw, "1.5");

    return custom;
}

char* getBlockSwCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->blockCustom->sw;
}

char* getBlockCfillCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->blockCustom->cfill;
}

char* getBlockCstrkCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->blockCustom->cstrk;
}

char* getHydrantSwCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->hydrantCustom->sw;
}

char* getHydrantCfillCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->hydrantCustom->cfill;
}

char* getHydrantCstrkCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->hydrantCustom->cstrk;
}

char* getBaseRadioSwCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->baseRadioCustom->sw;
}

char* getBaseRadioCfillCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->baseRadioCustom->cfill;
}

char* getBaseRadioCstrkCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->baseRadioCustom->cstrk;
}

char* getSemaphoreSwCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->semaphoreCustom->sw;
}

char* getSemaphoreCfillCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->semaphoreCustom->cfill;
}

char* getSemaphoreCstrkCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->semaphoreCustom->cstrk;
}

char* getFiguresCwCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->figuresCustom->cw;
}

char* getFiguresRwCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return NULL;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    return custom->figuresCustom->rw;
}

void setBlockSwCustomization(ElementsCustomization Custom, char* sw){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->blockCustom->sw, sw);
}

void setBlockCfillCustomization(ElementsCustomization Custom, char* cfill){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->blockCustom->cfill, cfill);
}

void setBlockCstrkCustomization(ElementsCustomization Custom, char* cstrk){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->blockCustom->cstrk, cstrk);
}

void setBaseRadioSwCustomization(ElementsCustomization Custom, char* sw){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->baseRadioCustom->sw, sw);
}

void setBaseRadioCfillCustomization(ElementsCustomization Custom, char* cfill){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->baseRadioCustom->cfill, cfill);
}

void setBaseRadioCstrkCustomization(ElementsCustomization Custom, char* cstrk){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->baseRadioCustom->cstrk, cstrk);
}


void setHydrantSwCustomization(ElementsCustomization Custom, char* sw){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->hydrantCustom->sw, sw);
}

void setHydrantCfillCustomization(ElementsCustomization Custom, char* cfill){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->hydrantCustom->cfill, cfill);
}

void setHydrantCstrkCustomization(ElementsCustomization Custom, char* cstrk){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->hydrantCustom->cstrk, cstrk);
}

void setSemaphoreSwCustomization(ElementsCustomization Custom, char* sw){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->semaphoreCustom->sw, sw);
}

void setSemaphoreCfillCustomization(ElementsCustomization Custom, char* cfill){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->semaphoreCustom->cfill, cfill);
}

void setSemaphoreCstrkCustomization(ElementsCustomization Custom, char* cstrk){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->semaphoreCustom->cstrk, cstrk);
}

void setFiguresCwCustomization(ElementsCustomization Custom, char* cw){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->figuresCustom->cw, cw);
}

void setFiguresRwCustomization(ElementsCustomization Custom, char* rw){
    if(Custom == NULL)
        return;
    elementsCustomization *custom = (elementsCustomization*) Custom;
    strcpy(custom->figuresCustom->rw, rw);
}

void freeElementsCustomization(ElementsCustomization Custom){
    if(Custom == NULL)
        return;

    elementsCustomization *custom = (elementsCustomization*) Custom;

    free(custom->blockCustom->sw);
    free(custom->blockCustom->cfill);
    free(custom->blockCustom->cstrk);

    free(custom->hydrantCustom->sw);
    free(custom->hydrantCustom->cfill);
    free(custom->hydrantCustom->cstrk);
    
    free(custom->baseRadioCustom->sw);
    free(custom->baseRadioCustom->cfill);
    free(custom->baseRadioCustom->cstrk);
    
    free(custom->semaphoreCustom->sw);
    free(custom->semaphoreCustom->cfill);
    free(custom->semaphoreCustom->cstrk);

    free(custom->figuresCustom->cw);
    free(custom->figuresCustom->rw);

    free(custom->blockCustom);
    free(custom->baseRadioCustom);
    free(custom->hydrantCustom);
    free(custom->semaphoreCustom);
    free(custom->figuresCustom);

    free(custom);
}