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
    int casesNumber;
}House;

typedef struct {
    double x, y, w, h;    
}CovidBlock;

void readBlockAttributes(Info blockInfo, CovidBlock *block);
void calculateHouseLocation(CovidBlock *block, House *house);
char* buildHouseTag(House* house);

void executeCovidCasesReport(char* command, Drawing Dr){
    if(isElementNull(Dr, "drawing", "executeCovidCasesReport"))
        return;

    House house;
    sscanf(&command[3], "%d %s %c %d", &house.casesNumber, house.address.cep, &house.address.face, &house.address.number);
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

    char* houseTag = buildHouseTag(&house);
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, houseTag);
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

char* buildHouseTag(House* house){

    char* houseTag = (char*) malloc(400 * sizeof(char));
    if(isElementNull(houseTag, "houseTag", "buildHouseTag"))
        return NULL;
    
    double casesNumberX = house->x + (house->w / 2.0);
    double casesNumberY = house->y + (house->h / 2.0);

    sprintf(houseTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"darkorange\" stroke-width=\"1\" fill=\"orange\" />\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> %d </text>\n", house->w, house->h, house->x, house->y, casesNumberX, casesNumberY, house->casesNumber);

    return houseTag;
}