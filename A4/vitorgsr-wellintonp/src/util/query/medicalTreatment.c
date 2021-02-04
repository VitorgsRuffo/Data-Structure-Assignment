#include "../include/headers.h"
#include "../include/urbanElements.h"
#include "../input/openInput.h"

typedef struct {
    HealthCenter healthCenter;
    double distance;
}NearHealthCenter;

void shellSort(NearHealthCenter* A, int length){
    NearHealthCenter temp;
    int i;

    for(int gap = length/2; gap > 0; gap /= 2){

        for(int j = gap; j<length; j+=1){

            temp = A[j];
            i = 0;
            
            for(i = j; i>=gap && A[i-gap].distance>temp.distance; i -= gap){
                A[i] = A[i-gap];
            }

            A[i] = temp;
        }
    }
}

void displayIntegerArray(NearHealthCenter *A, int end){
    for(int i = 0; i<end; i++){
        printf("%.2lf ", A[i].distance);
    }
    printf("\n");
}


char* buildBlueHouseTag(House H);
void copyHealthCenterListNodesInfoToArray(List healthCenterList, NearHealthCenter* nearHealthCenters);
void calculateDistanceFromHouseToHealthCenters(House H, NearHealthCenter* nearHealthCenters, int healthCentersAmount);
char* buildLineSegmentTag(double x, double y, House H);
void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance);


void executeMedicalTreatmentSearching(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeCovidCasesReport"))
        return;

    int K; char cep[30]; char face; int number;

    sscanf(&command[4], "%d %s %c %d", &K, cep, &face, &number);

    House house = createHouse(cep, face, number, 0); 
    setHouseBlock(house, Dr);       
    setHouseLocation(house);

    char* blueHouseTag = buildBlueHouseTag(house);
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, blueHouseTag);

    List healthCenterList = getHealthCenterList(Dr);
    int healthCentersAmount = length(healthCenterList);
    NearHealthCenter nearHealthCenters[healthCentersAmount];
    copyHealthCenterListNodesInfoToArray(healthCenterList, nearHealthCenters);
    calculateDistanceFromHouseToHealthCenters(house, nearHealthCenters, healthCentersAmount);
    
    //ordenar o vetor de acordo com o campo distance do elemento do vetor. (substituir por shell sort)
        printf("Unsorted array:\n");
        displayIntegerArray(nearHealthCenters, healthCentersAmount);

        shellSort(nearHealthCenters, healthCentersAmount);

        printf("Sorted array:\n");
        displayIntegerArray(nearHealthCenters, healthCentersAmount);

    int healthCenterX, healthCenterY;
    char* lineSegmentTag;
    
    if(K > healthCentersAmount)
        K = healthCentersAmount;
    
    for(int i = 0; i < K; i++){

        healthCenterX = atof(getHealthCenterX(nearHealthCenters[i].healthCenter));
        healthCenterY = atof(getHealthCenterY(nearHealthCenters[i].healthCenter));
        lineSegmentTag = buildLineSegmentTag(healthCenterX, healthCenterY, house);
        insert(queryElementsList, lineSegmentTag);
        writeHealthCenterCoordinatesOnTxt(txt, i, healthCenterX, healthCenterY, nearHealthCenters[i].distance);
    }

    freeHouse(house);
}

char* buildBlueHouseTag(House H){

    char* houseTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(houseTag, "houseTag", "buildBlueHouseTag"))
        return NULL;

    double x = getHouseX(H);
    double y = getHouseY(H);
    double w = getHouseW(H);
    double h = getHouseH(H);

    sprintf(houseTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"white\" stroke-width=\"1\" fill=\"lightblue\" />\n", w, h, x, y);
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

void calculateDistanceFromHouseToHealthCenters(House H, NearHealthCenter* nearHealthCenters, int healthCentersAmount){
    
    double healthCenterX, healthCenterY;  

    double houseCenterOfMassX = getHouseCenterOfMassX(H);
    double houseCenterOfMassY = getHouseCenterOfMassY(H);
  

    for(int i = 0; i<healthCentersAmount; i++){
        healthCenterX = atof(getHealthCenterX(nearHealthCenters[i].healthCenter));
        healthCenterY = atof(getHealthCenterY(nearHealthCenters[i].healthCenter));
        
        nearHealthCenters[i].distance = sqrt(pow((healthCenterX - houseCenterOfMassX), 2) + pow((healthCenterY - houseCenterOfMassY), 2));
    }
}

char* buildLineSegmentTag(double x, double y, House H){

    char* lineSegmentTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(lineSegmentTag, "lineSegmentTag", "buildLineSegmentTag"))
        return NULL;

    double houseCenterOfMassX = getHouseCenterOfMassX(H);
    double houseCenterOfMassY = getHouseCenterOfMassY(H);

    sprintf(lineSegmentTag, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"0.8\" stroke-dasharray=\"5,5\"/>", houseCenterOfMassX, houseCenterOfMassY, x, y);
    return lineSegmentTag;
}

void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance){
    i++;
    fprintf(txt, "Posto de saude (%d) - x: %.2lf, y: %.2lf, distancia: %.2lf.\n\n", i, x, y, distance);
}