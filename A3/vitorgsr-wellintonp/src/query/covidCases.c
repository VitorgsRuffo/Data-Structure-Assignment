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
}Block;

void readBlockAttributes(Info blockInfo, Block *block);
void calculateHouseLocation(Block *block, House *house);
    
void executeCovidCasesReport(char* command, Drawing Dr){
    if(isElementNull(Dr, "drawing", "executeCovidCasesReport"))
        return;

    House house;
    sscanf(&command[3], "%d %s %c %d", &house.casesNumber, house.address.cep, &house.address.face, &house.address.number);
    
    Node blockNode;
    blockNode = searchForBlockByCep(Dr, house.address.cep);
    if(isElementNull(blockNode, "blockNode", "searchForUrbanElementByIdentifier"))
        return;
    
    List blockList = getBlockList(Dr);
    Info blockInfo = get(blockList, blockNode);
    
    Block block;
    readBlockAttributes(blockInfo, &block);
    calculateHouseLocation(&block, &house);



    /* to do list:

        x - interpret the command. (create TAD address)

        x get block node (searchForUrbanElementByIdentifier)
        x get block list
        x get block info ( + get each attribute and assign to a block struct)

        x create house info struct

        - call function that will calculate the house attributes based on the side of the block.
                -if side == N
                    call function that will calculate the house attributes on side N.
                
                -if side == S
                    ...

        - create house tag

        - get query elements list

        - insert
    */
}

void readBlockAttributes(Info blockInfo, Block *block){
    
    block->x = atof(getBlockX(blockInfo));
    block->y = atof(getBlockY(blockInfo));
    block->w = atof(getBlockWidth(blockInfo));
    block->h = atof(getBlockHeight(blockInfo));

    return;
}

void calculateHouseLocation(Block *block, House *house){
    
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

void calculateHouseLocationOnNorthFace(Block *block, House *house){
    
}

void calculateHouseLocationOnSouthFace(Block *block, House *house){
    
}

void calculateHouseLocationOnEastFace(Block *block, House *house){
    
}

void calculateHouseLocationOnWestFace(Block *block, House *house){
    
}