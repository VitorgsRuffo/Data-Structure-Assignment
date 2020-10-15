#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing/drawing.h"
#include "../include/query.h"

typedef struct {
    char cep[10]; 
    char face;
    int number;
}Address;

typedef struct {
    double x;
    double y;
}CenterOfMass;

typedef struct {
    Address address;
    double x, y, w, h;
    CenterOfMass centerOfMass;
}House;

typedef struct {
    double x, y, w, h;    
}CovidBlock;

typedef struct {
    HealthCenter healthCenter;
    double distance;
}NearHealthCenter;

// Sort ///////////////////////////////////////////////////////////
void swap(NearHealthCenter *X, NearHealthCenter *Y){
    NearHealthCenter aux = *X;
    *X = *Y;
    *Y = aux;
}

int partition(NearHealthCenter *A, int start, int end){
    NearHealthCenter pivot = A[end];
    int partitionIndex = start;

    for(int i = start; i<end; i++){
        if(A[i].distance <= pivot.distance){
            swap(&A[i], &A[partitionIndex]);
            partitionIndex++;
        }
    }

    swap(&A[partitionIndex], &A[end]);
    return partitionIndex;
}

void quickSort(NearHealthCenter *A, int start, int end){
    if(start < end){
        int partitionIndex = partition(A, start, end);
        quickSort(A, start, partitionIndex-1);
        quickSort(A, partitionIndex+1, end);
    }
}

void displayIntegerArray(NearHealthCenter *A, int end){
    for(int i = 0; i<end; i++){
        printf("%.2lf ", A[i].distance);
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////

void readBlockAttributes2(Info blockInfo, CovidBlock *block);
void calculateHouseLocation2(CovidBlock *block, House *house);
char* buildBlueHouseTag(House* house);
void copyHealthCenterListNodesInfoToArray(List healthCenterList, NearHealthCenter* nearHealthCenters);
void calculateDistanceFromHouseToHealthCenters(House* house, NearHealthCenter* nearHealthCenters, int healthCentersAmount);
char* buildLineSegmentTag(double x, double y, House* house);
void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance);


void executeMedicalTreatmentSearching(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeCovidCasesReport"))
        return;

    House house;
    int K;
    sscanf(&command[4], "%d %s %c %d", &K, house.address.cep, &house.address.face, &house.address.number);
    house.w = 15.0; house.h = 15.0;

    Node blockNode = searchForBlockByCep(Dr, house.address.cep);
    if(isElementNull(blockNode, "blockNode", "searchForUrbanElementByIdentifier"))
        return;
    
    List blockList = getBlockList(Dr);
    Info blockInfo = get(blockList, blockNode);
    
    CovidBlock block;
    readBlockAttributes2(blockInfo, &block);
    calculateHouseLocation2(&block, &house);




    char* blueHouseTag = buildBlueHouseTag(&house);
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, blueHouseTag);

    List healthCenterList = getHealthCenterList(Dr);
    int healthCentersAmount = length(healthCenterList);
    NearHealthCenter nearHealthCenters[healthCentersAmount];
    copyHealthCenterListNodesInfoToArray(healthCenterList, nearHealthCenters);
    calculateDistanceFromHouseToHealthCenters(&house, nearHealthCenters, healthCentersAmount);
    
    //ordenar o vetor de acordo com o campo distance do elemento do vetor. (substituir por shell sort)
        printf("Unsorted array:\n");
        displayIntegerArray(nearHealthCenters, healthCentersAmount);

        quickSort(nearHealthCenters, 0, (healthCentersAmount-1));

        printf("Sorted array:\n");
        displayIntegerArray(nearHealthCenters, healthCentersAmount);

    int healthCenterX, healthCenterY;
    char* lineSegmentTag;
    
    if(K > healthCentersAmount)
        K = healthCentersAmount;
    
    for(int i = 0; i < K; i++){

        healthCenterX = atof(getHealthCenterX(nearHealthCenters[i].healthCenter));
        healthCenterY = atof(getHealthCenterY(nearHealthCenters[i].healthCenter));
        lineSegmentTag = buildLineSegmentTag(healthCenterX, healthCenterY, &house);
        insert(queryElementsList, lineSegmentTag);
        writeHealthCenterCoordinatesOnTxt(txt, i, healthCenterX, healthCenterY, nearHealthCenters[i].distance);
    }

}




void readBlockAttributes2(Info blockInfo, CovidBlock *block){
    
    block->x = atof(getBlockX(blockInfo));
    block->y = atof(getBlockY(blockInfo));
    block->w = atof(getBlockWidth(blockInfo));
    block->h = atof(getBlockHeight(blockInfo));

    return;
}

void calculateHouseLocationOnNorthFace2(CovidBlock *block, House *house);
void calculateHouseLocationOnSouthFace2(CovidBlock *block, House *house);
void calculateHouseLocationOnEastFace2(CovidBlock *block, House *house);
void calculateHouseLocationOnWestFace2(CovidBlock *block, House *house);


void calculateHouseLocation2(CovidBlock *block, House *house){
    
    switch (house->address.face){
        case 'N':
        case 'n':
            calculateHouseLocationOnNorthFace2(block, house);
            break;
            
        case 'S':
        case 's':
            calculateHouseLocationOnSouthFace2(block, house);
            break;

        case 'L':
        case 'l':
            calculateHouseLocationOnEastFace2(block, house);
            break;
        
        case 'O':
        case 'o':
            calculateHouseLocationOnWestFace2(block, house);
            break;

        default:
            printf("A face da quadra (%s) e invalida.\n", house->address.cep);
    }

    house->centerOfMass.x = house->x + (house->w / 2.0);
    house->centerOfMass.y = house->y + (house->h / 2.0);

    return;
}

// Face Norte
void calculateHouseLocationOnNorthFace2(CovidBlock *block, House *house){
    house->x = (block->x + house->address.number) - (house->w / 2.0);
    house->y = (block->y + block->h) - house->h;
}

// Face Sul
void calculateHouseLocationOnSouthFace2(CovidBlock *block, House *house){
    house->x = (block->x + house->address.number) - (house->w / 2.0);
    house->y = block->y;
}

// Face Leste
void calculateHouseLocationOnEastFace2(CovidBlock *block, House *house){
    house->x = block->x;
    house->y = (block->y + house->address.number) - (house->h/2);  
}

// Face Oeste
void calculateHouseLocationOnWestFace2(CovidBlock *block, House *house){
    house->x = (block->x + block->w) - house->w;
    house->y = (block->y + house->address.number) - (house->h/2);
}






char* buildBlueHouseTag(House* house){

    char* houseTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(houseTag, "houseTag", "buildBlueHouseTag"))
        return NULL;

    sprintf(houseTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"white\" stroke-width=\"1\" fill=\"lightblue\" />\n", house->w, house->h, house->x, house->y);
    return houseTag;
}

void copyHealthCenterListNodesInfoToArray(List healthCenterList, NearHealthCenter* nearHealthCenters){
    Node NODE = getFirst(healthCenterList);
    if(isElementNull(NODE, "NODE", "copyHealthCenterListNodeInfoToArray | getFirst"))
        return;
    
    Info healthCenterInfo = NULL;

    int i = 0;
    while(NODE != NULL){

        healthCenterInfo = get(healthCenterList, NODE);
        nearHealthCenters[i].healthCenter = healthCenterInfo;

        NODE = getNext(healthCenterList, NODE);
        i++;   
    }
      
}

void calculateDistanceFromHouseToHealthCenters(House* house, NearHealthCenter* nearHealthCenters, int healthCentersAmount){
    double healthCenterX, healthCenterY;  

    for(int i = 0; i<healthCentersAmount; i++){
        healthCenterX = atof(getHealthCenterX(nearHealthCenters[i].healthCenter));
        healthCenterY = atof(getHealthCenterY(nearHealthCenters[i].healthCenter));
        
        nearHealthCenters[i].distance = sqrt(pow((healthCenterX - house->centerOfMass.x), 2) + pow((healthCenterY - house->centerOfMass.y), 2));
    }
}

char* buildLineSegmentTag(double x, double y, House* house){

    char* lineSegmentTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(lineSegmentTag, "lineSegmentTag", "buildLineSegmentTag"))
        return NULL;

    sprintf(lineSegmentTag, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"0.8\" stroke-dasharray=\"5,5\"/>", house->centerOfMass.x, house->centerOfMass.y, x, y);
    return lineSegmentTag;
}

void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance){
    i++;
    fprintf(txt, "Posto de saude (%d) - x: %.2lf, y: %.2lf, distancia: %.2lf.\n\n", i, x, y, distance);
}