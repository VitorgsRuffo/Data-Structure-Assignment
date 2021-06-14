#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../util/query/qry.h"
#include "../../include/dataStructure.h"

#define LOCATIONS_AMOUNT 11

typedef struct city {
    PQuadTree circles;
    PQuadTree rectangles;
    PQuadTree texts;
    PQuadTree blocks;
    HashTable blocksTable;
    PQuadTree hydrants;
    PQuadTree baseRadios;
    PQuadTree semaphores;
    PQuadTree healthCenters;
    PQuadTree covidAddresses;
    List regions;
    HashTable establishmentTypes;
    HashTable establishmentsTable;
    PQuadTree establishmentsTree;
    HashTable people;
    PQuadTree housesTree;
    HashTable housesTable;
    Graph roadSystem;
    PQuadTree roadIntersections;
    Graph bikePath;
    Point* locations;
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
    ct->blocksTable = createHashTable(HASH_TABLE_INITIAL_SIZE, getBlockCep);
    ct->hydrants = createPQuadTree(getHydrantId, getHydrantCoordinates);
    ct->baseRadios = createPQuadTree(getBaseRadioId, getBaseRadioCoordinates);
    ct->semaphores = createPQuadTree(getSemaphoreId, getSemaphoreCoordinates);
    ct->healthCenters = createPQuadTree(getHealthCenterId, getHealthCenterCoordinates);
    ct->covidAddresses = createPQuadTree(getCovidAddressId, getCovidAddressCoordinates);
    ct->regions = createList();

    ct->establishmentTypes = createHashTable(HASH_TABLE_INITIAL_SIZE, getEstablishmentTypeCode);
    ct->establishmentsTable = createHashTable(HASH_TABLE_INITIAL_SIZE, getEstablishmentCnpj);
    ct->establishmentsTree = createPQuadTree(getEstablishmentCnpj, getEstablishmentCoordinates);
    ct->people = createHashTable(HASH_TABLE_INITIAL_SIZE, getPersonCpf);
    ct->housesTree = createPQuadTree(getHouseCpf, getHouseCoordinates);
    ct->housesTable = createHashTable(HASH_TABLE_INITIAL_SIZE, getHouseCpf);
    
    ct->roadSystem = NULL;
    ct->roadIntersections = createPQuadTree(getIdedPointId, getIdedPointCoordinates);
    ct->bikePath = NULL;
    ct->locations = (Point*) malloc(LOCATIONS_AMOUNT * sizeof(Point));

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

HashTable* getBlocksTable(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return &ct->blocksTable;
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

PQuadTree getHealthCenters(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->healthCenters;
}

PQuadTree getCovidAddresses(City Ct){
  if(Ct == NULL)
        return NULL;

  city *ct = (city*) Ct;
  return ct->covidAddresses;
}

List getRegions(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->regions;
}

HashTable* getEstablishmentTypes(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return &ct->establishmentTypes;
}


HashTable* getEstablishmentsTable(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return &ct->establishmentsTable;
}

PQuadTree getEstablishmentsTree(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->establishmentsTree;
}

HashTable* getPeople(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return &ct->people;
}

PQuadTree getHousesTree(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->housesTree;
}

HashTable* getHousesTable(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return &ct->housesTable;
}

Graph getRoadSystem(City Ct){
    if(Ct == NULL)
        return NULL;
    
    city *ct = (city*) Ct;
    return ct->roadSystem;
}

void setRoadSystem(City Ct, Graph roadSystem){
    if(Ct == NULL || roadSystem == NULL)
        return;
    
    city *ct = (city*) Ct;
    ct->roadSystem = roadSystem;
}


PQuadTree getRoadIntersections(City Ct){
    if(Ct == NULL)
            return NULL;
        
    city *ct = (city*) Ct;
    return ct->roadIntersections;
}


Graph getBikePath(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->bikePath;
} 

void setBikePath(City Ct, Graph bikePath){
    if(Ct == NULL || bikePath == NULL)
        return;
    
    city *ct = (city*) Ct;
    ct->bikePath = bikePath;
}

Point* getLocations(City Ct){
    if(Ct == NULL) return NULL;

    city *ct = (city*) Ct;
    return ct->locations;
}

List getQueryElements(City Ct){
    if(Ct == NULL)
        return NULL;

    city *ct = (city*) Ct;
    return ct->queryElements;
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

    printPQuadTree(ct->establishmentsTree);
    printPQuadTree(ct->housesTree);
    
}

void freeCity(City Ct){
    if(Ct == NULL)
        return;

    city *ct = (city*) Ct;

    freePQuadTree(ct->circles, freeCircle);
    freePQuadTree(ct->rectangles, freeRectangle);
    freePQuadTree(ct->texts, freeText);

    freeHashTable(ct->blocksTable, NULL);
    freePQuadTree(ct->blocks, freeBlock);
    freePQuadTree(ct->hydrants, freeHydrant);
    freePQuadTree(ct->baseRadios, freeBaseRadio);
    freePQuadTree(ct->semaphores, freeSemaphore);
    freePQuadTree(ct->healthCenters, freeHealthCenter);
    freePQuadTree(ct->covidAddresses, freeCovidAddress);
    freeList(ct->regions, freeRegion);

    freeHashTable(ct->establishmentTypes, freeEstablishmentType);
    freePQuadTree(ct->establishmentsTree, freeEstablishment);
    freeHashTable(ct->establishmentsTable, NULL);
    freeHashTable(ct->people, freePerson);
    freeHashTable(ct->housesTable, NULL);
    freePQuadTree(ct->housesTree, freeHouse);

    freeGraph(ct->roadSystem, freePoint, 1);
    freePQuadTree(ct->roadIntersections, freeIdedPoint);
    freeGraph(ct->bikePath, NULL, 0);
    free(ct->locations);

    freeList(ct->queryElements, freeQueryElement);
    free(ct);
}