#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../util/query/qry.h"
#include "../../include/dataStructure.h"

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



DataStructure getDataStructureByElementType(City Ct, char* elementType){
    if(Ct == NULL) return NULL;
    
    DataStructure elements = NULL;
    
    if(elementType[0] == 'c')
        elements = getCircles(Ct);
    
    else if(elementType[2] == 't')
        elements = getRectangles(Ct);
    
    else if(elementType[0] == 't')
        elements = getTexts(Ct);
    
    else if(elementType[0] == 'q')
        elements = getBlocks(Ct);

    else if(elementType[0] == 'h')
        elements = getHydrants(Ct);

    else if(elementType[0] == 's')
        elements = getSemaphores(Ct);

    else if(elementType[1] == 'a')
        elements = getBaseRadios(Ct);    
    
    else
        return NULL;
    
    return elements;
}


Node searchForFigureOrTextElementByIdentifier(City Ct, char* idToSearch, char* figureElementType){
    if(Ct == NULL || idToSearch == NULL)
        return NULL;

    city *ct = (city*) Ct;
    Node elementNode;

    elementNode = searchForObjectByKeyInPQuadTree(ct->circles, idToSearch);
    if(elementNode != NULL){
        strcpy(figureElementType, "circulo");
        return elementNode;
    }

    elementNode = searchForObjectByKeyInPQuadTree(ct->rectangles, idToSearch);
    if(elementNode != NULL){
        strcpy(figureElementType, "retangulo");
        return elementNode;
    }

    elementNode = searchForObjectByKeyInPQuadTree(ct->texts, idToSearch);
    if(elementNode != NULL){
        strcpy(figureElementType, "texto");
        return elementNode;
    }

    return NULL;
}


Node searchForUrbanElementByIdentifier(City Ct, char* idToSearch, char* urbanElementType){
    if(Ct == NULL)
        return NULL;

    Node urbanElementNode;

    urbanElementNode = searchForBlockByCep(Ct, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "quadra");
        return urbanElementNode;
    }

    city *ct = (city*) Ct;

    urbanElementNode = searchForObjectByKeyInPQuadTree(ct->hydrants, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "hidrante");
        return urbanElementNode;
    }

    urbanElementNode = searchForObjectByKeyInPQuadTree(ct->semaphores, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "semaforo");
        return urbanElementNode;
    }

    urbanElementNode = searchForObjectByKeyInPQuadTree(ct->baseRadios, idToSearch);
    if(urbanElementNode != NULL){
        strcpy(urbanElementType, "radio-base");
        return urbanElementNode;
    }

    return NULL;
}

Node searchForBlockByCep(City Ct, char* cepToSearch){
    city *ct = (city*) Ct;
    Node blockNode = searchForObjectByKeyInPQuadTree(ct->blocks, cepToSearch);
    return blockNode;
}

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