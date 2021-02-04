#include "../include/headers.h"
#include "../include/util.h"
#include "../include/query.h"
#include "../include/urbanElements.h"
#include "./drawing.h"
#include "../include/elements.h"

typedef struct drawing {
    PQuadTree circles;
    PQuadTree rectangles;
    PQuadTree texts;
    PQuadTree blocks;
    PQuadTree hydrants;
    PQuadTree baseRadios;
    PQuadTree semaphores;
    PQuadTree healthCenters;
    HashTable regions; 

    HashTable establishmentTypes;
    HashTable establishments;
    HashTable people;
    PQuadTree housesTree;
    HashTable housesTable;

    List queryElements;
    
}drawing;

Drawing createDrawing(){
    drawing *dr = (drawing*) malloc(sizeof(drawing));
    
    if(dr == NULL){
        printf("Erro ao alocar memória para a criação do TAD desenho\nFinalizando o programa...");
        exit(1);
    }
    
    dr->circles = createPQuadTree(getCircleId, getCircleCoordinates);
    dr->rectangles = createPQuadTree(getRectangleId, getRectangleCoordinates);
    dr->texts = createPQuadTree(getTextId, getTextCoordinates);
    dr->blocks = createPQuadTree(getBlockCep, getBlockCoordinates);
    dr->hydrants = createPQuadTree(getHydrantId, getHydrantCoordinates);
    dr->baseRadios = createPQuadTree(getBaseRadioId, getBaseRadioCoordinates);
    dr->semaphores = createPQuadTree(getSemaphoreId, getSemaphoreCoordinates);
    dr->healthCenters = createPQuadTree(getHealthCenterId, getHealthCenterCoordinates);
    dr->regions = createHashTable(X, getRegionId);

    
    //dr->establishmentTypes = createHashTable(X, getEstablishmentCode);
    //dr->establishments = createHashTable(X, getEstablishmentCnpj);
    //dr->people = createHashTable(X, getPersonCpf);
    dr->housesTree = createPQuadTree(getHouseCpf, getHouseCoordinates);
    //dr->housesTable = createHashTable(X, getHouseCpf);
    
    dr->queryElements = createList();

    return dr;
}


PQuadTree getCircles(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getCircles"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->circles;
}

PQuadTree getRectangles(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getRectangles"))
        return NULL;
    
    drawing *dr = (drawing*) Dr;
    return dr->rectangles;
}

PQuadTree getTexts(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getTexts"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->texts;
}

PQuadTree getBlocks(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getBlocks"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->blocks;
}

PQuadTree getHydrants(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getHydrants"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->hydrants;
}

PQuadTree getBaseRadios(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getBaseRadios"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->baseRadios;
}

PQuadTree getSemaphores(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getSemaphores"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->semaphores;
}

List getHealthCenters(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getHealthCenters"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->healthCenters;
}

PQuadTree getHousesTree(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getHousesTree"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->housesTree;
}
/*
HashTable getHousesTable(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getHousesTable"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->housesTable;
}
*/
List getQueryElements(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getQueryElements"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->queryElements;
}


HashTable getRegions(Drawing Dr){
    if(isElementNull(Dr, "drawing", "getRegions"))
        return NULL;

    drawing *dr = (drawing*) Dr;
    return dr->regions;
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

Node searchForBlockByCep(Drawing Dr, char* cepToSearch){
    drawing *dr = (drawing*) Dr;
    Node blockNode = NULL;

    blockNode = searchForElementByIdentifier(dr->blockList, &getBlockCep, cepToSearch);
    return blockNode;
}

Node searchForUrbanElementByIdentifier(Drawing Dr, char* idToSearch, char* urbanElementType){
    if(isElementNull(Dr, "drawing", "searchForUrbanElementByIdentifier"))
        return NULL;

    Node urbanElementNode;

    urbanElementNode = searchForBlockByCep(Dr, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "quadra");
        return urbanElementNode;
    }

    drawing *dr = (drawing*) Dr;

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
    freeList(dr->healthCenterList, &freeHealthCenter);
    freeList(dr->houseList, &freeHouse);
    freeRegion(dr->region);

    free(dr);
}