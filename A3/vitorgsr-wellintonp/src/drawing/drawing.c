#include "../include/headers.h"
#include "../include/util.h"
#include "../include/query.h"
#include "drawing.h"
#include "../include/figures.h"
#include "../include/urbanElements.h"

typedef struct drawing {
    List circleList;
    List rectangleList;
    List textList;
    List blockList;
    List hydrantList;
    List baseRadioList;
    List semaphoreList;
    List queryElementsList;
}drawing;

Drawing createDrawing(){
    drawing *dr = (drawing*) malloc(sizeof(drawing));
    
    if(dr == NULL){
        printf("Erro ao alocar memória para a criação do TAD desenho\nFinalizando o programa...");
        exit(1);
    }
    
    dr->circleList = createList();
    dr->rectangleList = createList();
    dr->textList = createList();
    dr->blockList = createList();
    dr->hydrantList = createList();
    dr->baseRadioList = createList();
    dr->semaphoreList = createList();
    dr->queryElementsList = createList();

    return dr;
}


List getCircleList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getCircleList"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->circleList;
}

List getRectangleList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getRectangleList"))
        return NULL;
    
    drawing *dr = (drawing*) Dr;
    return dr->rectangleList;
}

List getTextList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getTextList"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->textList;
}

List getBlockList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getBlockList"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->blockList;
}

List getHydrantList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getHydrantList"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->hydrantList;
}

List getBaseRadioList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getBaseRadioList"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->baseRadioList;
}

List getSemaphoreList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getSemaphoreList"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->semaphoreList;
}

List getQueryElementsList(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getQueryElementsList"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->queryElementsList;
}

List getListByElementType(Drawing Dr, char* elementType){
    if(isElementNull(Dr, "drawing", "getListByElementType"))
        return NULL;
    
    List elementList = NULL;
    if(elementType[0] == 'c')
        elementList = getCircleList(Dr);
    
    else if(elementType[2] == 't')
        elementList = getRectangleList(Dr);
    
    else if(elementType[0] == 't')
        elementList = getTextList(Dr);
    
    else if(elementType[0] == 'q')
        elementList = getBlockList(Dr);

    else if(elementType[0] == 'h')
        elementList = getHydrantList(Dr);

    else if(elementType[0] == 's')
        elementList = getSemaphoreList(Dr);

    else if(elementType[1] == 'a')
        elementList = getBaseRadioList(Dr);    
    
    else
        return NULL;
    
    return elementList;
}

Node searchForFigureOrTextElementByIdentifier(Drawing Dr, char* idToSearch, char* figureElementType){
    if(isElementNull(Dr, "drawing", "searchForFigureOrTextElementByIdentifier"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    Node figureElementNode;

    figureElementNode = searchForElementByIdentifier(dr->circleList, &getCircleId, idToSearch);
    if(figureElementNode != NULL){
        strcpy(figureElementType, "circulo");
        return figureElementNode;
    }

    figureElementNode = searchForElementByIdentifier(dr->rectangleList, &getRectangleId, idToSearch);
    if(figureElementNode != NULL){
        strcpy(figureElementType, "retangulo");
        return figureElementNode;
    }

    figureElementNode = searchForElementByIdentifier(dr->textList, &getTextId, idToSearch);
    if(figureElementNode != NULL){
        strcpy(figureElementType, "texto");
        return figureElementNode;
    }

    printf("Erro: elemento cujo id e %s nao foi encontrado nas listas de figuras..\n", idToSearch);
    return NULL;
}

Node searchForUrbanElementByIdentifier(Drawing Dr, char* idToSearch, char* urbanElementType){
    if(isElementNull(Dr, "drawing", "searchForUrbanElementByIdentifier"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    Node urbanElementNode;

    urbanElementNode = searchForElementByIdentifier(dr->blockList, &getBlockCep, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "quadra");
        return urbanElementNode;
    }

    urbanElementNode = searchForElementByIdentifier(dr->hydrantList, &getHydrantId, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "hidrante");
        return urbanElementNode;
    }

    urbanElementNode = searchForElementByIdentifier(dr->semaphoreList, &getSemaphoreId, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "semaforo");
        return urbanElementNode;
    }

    urbanElementNode = searchForElementByIdentifier(dr->baseRadioList, &getBaseRadioId, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "radio-base");
        return urbanElementNode;
    }

    printf("Erro: o equipamento urbano cujo id e %s nao foi encontrado nas listas...\n", idToSearch);
    return NULL;
}

void printDrawing(Drawing Dr){
    if(isElementNull(Dr, "drawing", "printDrawing"))
        return;
    
    drawing *dr = (drawing*) Dr;

    printList(dr->circleList, &printCircle);
    printList(dr->rectangleList, &printRectangle);
    printList(dr->textList, &printText);
    printList(dr->blockList, &printBlock);
    printList(dr->hydrantList, &printHydrant);
    printList(dr->baseRadioList, &printBaseRadio);
    printList(dr->semaphoreList, &printSemaphore);
}

void freeDrawing(Drawing Dr){
    if(isElementNull(Dr, "drawing", "freeDrawing"))
        return;

    drawing *dr = (drawing*) Dr;

    freeList(dr->circleList, &freeCircle);
    freeList(dr->rectangleList, &freeRectangle);
    freeList(dr->textList, &freeText);
    freeList(dr->blockList, &freeBlock);
    freeList(dr->hydrantList, &freeHydrant);
    freeList(dr->baseRadioList, &freeBaseRadio);
    freeList(dr->semaphoreList, &freeSemaphore);
    freeList(dr->queryElementsList, &freeQueryElement);

    free(dr);
}