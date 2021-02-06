#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../util/query/qry.h"

typedef struct city {
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
}city;

City createCity(){
    city *ct = (city*) malloc(sizeof(city));
    
    if(ct == NULL){
        printf("Erro ao alocar memória para a criação do TAD cidade\nFinalizando o programa...");
        exit(1);
    }
    
    ct->circles = createPQuadTree(getCircleId, getCircleCoordinates);
    ct->rectangles = createPQuadTree(getRectangleId, getRectangleCoordinates);
    ct->texts = createPQuadTree(getTextId, getTextCoordinates);
    ct->blocks = createPQuadTree(getBlockCep, getBlockCoordinates);
    ct->hydrants = createPQuadTree(getHydrantId, getHydrantCoordinates);
    ct->baseRadios = createPQuadTree(getBaseRadioId, getBaseRadioCoordinates);
    ct->semaphores = createPQuadTree(getSemaphoreId, getSemaphoreCoordinates);
    ct->healthCenters = createPQuadTree(getHealthCenterId, getHealthCenterCoordinates);
    ct->regions = createHashTable(HASH_TABLE_INITIAL_SIZE, getRegionId);

    
    //ct->establishmentTypes = createHashTable(HASH_TABLE_INITIAL_SIZE, getEstablishmentCode);
    //ct->establishments = createHashTable(HASH_TABLE_INITIAL_SIZE, getEstablishmentCnpj);
    //ct->people = createHashTable(HASH_TABLE_INITIAL_SIZE, getPersonCpf);
    ct->housesTree = createPQuadTree(getHouseCpf, getHouseCoordinates);
    //ct->housesTable = createHashTable(HASH_TABLE_INITIAL_SIZE, getHouseCpf);
    
    ct->queryElements = createList();

    return ct;
}


PQuadTree getCircles(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->circles;
}

PQuadTree getRectangles(City Ct){
    if(Ct == NULL)
        return NULL;
    
    city *ct = (city*) Ct;
    return ct->rectangles;
}

PQuadTree getTexts(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->texts;
}

PQuadTree getBlocks(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->blocks;
}

PQuadTree getHydrants(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->hydrants;
}

PQuadTree getBaseRadios(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->baseRadios;
}

PQuadTree getSemaphores(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->semaphores;
}

List getHealthCenters(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->healthCenters;
}

PQuadTree getHousesTree(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->housesTree;
}
/*
HashTable getHousesTable(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->housesTable;
}
*/
List getQueryElements(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->queryElements;
}


HashTable getRegions(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->regions;
}

/*

List getListByElementType(Drawing Dr, char* elementType){
    if(Ct == NULL)
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
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    Node figureElementNode;

    figureElementNode = searchForElementByIdentifier(dr->circles, &getCircleId, idToSearch);
    if(figureElementNode != NULL){
        strcpy(figureElementType, "circulo");
        return figureElementNode;
    }

    figureElementNode = searchForElementByIdentifier(dr->rectangles, &getRectangleId, idToSearch);
    if(figureElementNode != NULL){
        strcpy(figureElementType, "retangulo");
        return figureElementNode;
    }

    figureElementNode = searchForElementByIdentifier(dr->texts, &getTextId, idToSearch);
    if(figureElementNode != NULL){
        strcpy(figureElementType, "texto");
        return figureElementNode;
    }

    printf("Erro: elemento cujo id e %s nao foi encontrado nas listas de figuras..\n", idToSearch);
    return NULL;
}

Node searchForBlockByCep(Drawing Dr, char* cepToSearch){
    city *ct = (city*) Ct;
    Node blockNode = NULL;

    blockNode = searchForElementByIdentifier(dr->blocks, &getBlockCep, cepToSearch);
    return blockNode;
}

Node searchForUrbanElementByIdentifier(Drawing Dr, char* idToSearch, char* urbanElementType){
    if(Ct == NULL)
        return NULL;

    Node urbanElementNode;

    urbanElementNode = searchForBlockByCep(Dr, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "quadra");
        return urbanElementNode;
    }

    city *ct = (city*) Ct;

    urbanElementNode = searchForElementByIdentifier(dr->hydrants, &getHydrantId, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "hidrante");
        return urbanElementNode;
    }

    urbanElementNode = searchForElementByIdentifier(dr->semaphores, &getSemaphoreId, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "semaforo");
        return urbanElementNode;
    }

    urbanElementNode = searchForElementByIdentifier(dr->baseRadios, &getBaseRadioId, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "radio-base");
        return urbanElementNode;
    }

    printf("Erro: o equipamento urbano cujo id e %s nao foi encontrado nas listas...\n", idToSearch);
    return NULL;
}

*/

void printCity(City Ct){
    if(Ct == NULL)
        return;
    
    city *ct = (city*) Ct;

    printPQuadTree(ct->circles);
    printPQuadTree(ct->rectangles);
    printPQuadTree(ct->texts);
    printPQuadTree(ct->blocks);
    printPQuadTree(ct->hydrants);
    printPQuadTree(ct->baseRadios);
    printPQuadTree(ct->semaphores);
    printPQuadTree(ct->healthCenters);
    printHashTable(ct->regions, printRegion);

    printPQuadTree(ct->housesTree);
}

void freeCity(City Ct){
    if(Ct == NULL)
        return;

    city *ct = (city*) Ct;

    freePQuadTree(ct->circles, freeCircle);
    freePQuadTree(ct->rectangles, freeRectangle);
    freePQuadTree(ct->texts, freeText);
    freePQuadTree(ct->blocks, freeBlock);
    freePQuadTree(ct->hydrants, freeHydrant);
    freePQuadTree(ct->baseRadios, freeBaseRadio);
    freePQuadTree(ct->semaphores, freeSemaphore);
    freePQuadTree(ct->healthCenters, freeHealthCenter);
    freeHashTable(ct->regions, freeRegion);

    freePQuadTree(ct->housesTree, freeHouse);

    freeList(ct->queryElements, freeQueryElement);
    free(ct);
}