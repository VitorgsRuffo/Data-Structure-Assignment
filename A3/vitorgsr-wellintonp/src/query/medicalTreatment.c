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
    Address address;
    double x, y, w, h;
}House;

typedef struct {
    double x, y, w, h;    
}CovidBlock;

typedef struct {
    Info healthCenter;
    double distance;
}NearHealthCenter;

void readBlockAttributes(Info blockInfo, CovidBlock *block);
void calculateHouseLocation(CovidBlock *block, House *house);
char* buildBlueHouseTag(House* house);
char* buildLineSegmentTag(double x, double y, House* house);
void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance);


void executeMedicalTreatmentSearching(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeCovidCasesReport"))
        return;

    House house;
    int K;
    sscanf(&command[3], "%d %s %c %d", &K, house.address.cep, &house.address.face, &house.address.number);
    house.w = 15.0; house.h = 15.0;


    Node blockNode;
    blockNode = searchForBlockByCep(Dr, house.address.cep);
    if(isElementNull(blockNode, "blockNode", "searchForUrbanElementByIdentifier"))
        return;
    
    List blockList = getBlockList(Dr);
    Info blockInfo = get(blockList, blockNode);
    
    CovidBlock block;
    readBlockAttributes(blockInfo, &block);
    calculateHouseLocation(&block, &house);

    char* blueHouseTag = buildBlueHouseTag(&house);
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, blueHouseTag);
    
    
    //Sort:
        //get lista postos
        //tamanho lista postos
        //NearHealthCenter healthCentersDistance[listLength];
        //copiar infos dos nos da lista para o campo healthCenter dos elementos do vetor.
        //for no vetor pra calcular a distancia entre o meio da casa e o posto atual (guardar no campo distance do elemento atual do vetor)

        //sort no vetor considerando o campo distance do elemento do vetor.

    int healthCenterX, healthCenterY;
    char* lineSegmentTag;
    
    for(int i = 0; i < K; i++){

        healthCenterX = atof(getHealthCenterX(healthCenters[i]));
        healthCenterY = atof(getHealthCenterY(healthCenters[i]));
        lineSegmentTag = buildLineSegmentTag(healthCenterX, healthCenterY, &house);
        insert(queryElementsList, lineSegmentTag);
        writeHealthCenterCoordinatesOnTxt(txt, i, healthCenterX, healthCenterY, healthCenters[i].distance);
    }

    //Refatorar.

}

void readBlockAttributes(Info blockInfo, CovidBlock *block){
    
    block->x = atof(getBlockX(blockInfo));
    block->y = atof(getBlockY(blockInfo));
    block->w = atof(getBlockWidth(blockInfo));
    block->h = atof(getBlockHeight(blockInfo));

    return;
}

void calculateHouseLocationOnNorthFace(CovidBlock *block, House *house);
void calculateHouseLocationOnSouthFace(CovidBlock *block, House *house);
void calculateHouseLocationOnEastFace(CovidBlock *block, House *house);
void calculateHouseLocationOnWestFace(CovidBlock *block, House *house);


void calculateHouseLocation(CovidBlock *block, House *house){
    
    switch (house->address.face){
        case 'N':
        case 'n':
            calculateHouseLocationOnNorthFace(block, house);
            break;
            
        case 'S':
        case 's':
            calculateHouseLocationOnSouthFace(block, house);
            break;

        case 'L':
        case 'l':
            calculateHouseLocationOnEastFace(block, house);
            break;
        
        case 'O':
        case 'o':
            calculateHouseLocationOnWestFace(block, house);
            break;

        default:
            printf("A face da quadra (%s) e invalida.\n", house->address.cep);
    }

    return;
}

// Face Norte
void calculateHouseLocationOnNorthFace(CovidBlock *block, House *house){
    house->x = (block->x + house->address.number) - (house->w / 2.0);
    house->y = (block->y + block->h) - house->h;
}

// Face Sul
void calculateHouseLocationOnSouthFace(CovidBlock *block, House *house){
    house->x = (block->x + house->address.number) - (house->w / 2.0);
    house->y = block->y;
}

// Face Leste
void calculateHouseLocationOnEastFace(CovidBlock *block, House *house){
    house->x = block->x;
    house->y = (block->y + house->address.number) - (house->h/2);  
}

// Face Oeste
void calculateHouseLocationOnWestFace(CovidBlock *block, House *house){
    house->x = (block->x + block->w) - house->w;
    house->y = (block->y + house->address.number) - (house->h/2);
}

char* buildBlueHouseTag(House* house){

    char* houseTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(houseTag, "houseTag", "buildHouseTag"))
        return NULL;

    sprintf(houseTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"white\" stroke-width=\"1\" fill=\"lightblue\" />\n", house->w, house->h, house->x, house->y);

    return houseTag;
}

char* buildLineSegmentTag(double x, double y, House* house){

    char* LineSegmentTag = (char*) malloc(200 * sizeof(char));
    if(isElementNull(LineSegmentTag, "LineSegmentTag", "buildLineSegmentTag"))
        return NULL;

    double houseCenterX = house->x + (house->w/2.0);
    double houseCenterY = house->y + (house->h/2.0);

    sprintf(LineSegmentTag, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"0.8\" stroke-dasharray=\"5,5\"/>", houseCenterX, houseCenterY, x, y);
    return LineSegmentTag;
}

void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance){
    i++;
    fprintf(txt, "Posto de saude (%d) - x: %.2lf, y: %.2lf, distancia: %.2lf.\n\n", i, x, y, distance);
}