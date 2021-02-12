#include "../../include/headers.h"
#include "address.h"
#include "../point.h"
#include "../figures/rectangle.h"
#include "../../include/dataStructure.h"
#include "city.h"

typedef struct {
    char cep[30]; 
    char face;
    int number;
    char* compl;
    Rectangle block;
    Point coordinates;
}address;

//essa é a distancia que um endereco tem (no eixo y ou x) da borda da quadra na qual o endereco pertence.
#define ADDRESS_DISTANCE_FROM_BLOCK_BORDER 7.5

int setAddressBlock(address* add, City Ct);
void setAdressCoordinates(address* add);

Address createAdress(char* cep, char face, int number, char* compl, City Ct){
    if(cep == NULL || face == NULL || number == NULL || Ct == NULL) 
        return NULL;

    address *add = (address*) malloc(sizeof(address));
    
    add->compl = (char*) malloc((strlen(compl) + 1) * sizeof(char));
    add->coordinates = createPoint(0,0);
    add->block = NULL;

    strcpy(add->cep, cep);
    add->face = face;
    add->number = number;
    strcpy(add->compl, compl);
    
    if(!setAddressBlock(add, Ct)){
        free(add->compl);
        free(add->coordinates);
        free(add);
        return NULL;
    }

    setAddressCoordinates(add);

    return add;
}


Point getAddressCoordinates(Address Add){
    if(Add == NULL) return NULL;
    address *add = (address*) Add;
    return add->coordinates;
}

double getAddressX(Address Add){

    if(Add == NULL)
        return -1;

    address *add = (address*) Add;
    return getPointX(add->coordinates);
}

double getAddressY(Address Add){

    if(Add == NULL)
        return -1;

    address *add = (address*) Add;
    return getPointY(add->coordinates);
}


void readBlockAttributes(Info blockInfo, Rectangle* block);

int setAddressBlock(address* add, City Ct){

    Node blockNode = searchForBlockByCep(Ct, add->cep);
    if(blockNode == NULL) return 0; 
    
    DataStructure blocks = getBlocks(Ct);
    Info blockInfo = getPQuadTreeNodeInfo(blocks, blockNode);
    readBlockAttributes(blockInfo, &add->block); 
    return 1;   
}

void readBlockAttributes(Info blockInfo, Rectangle* block){
    
    char* x = getBlockX(blockInfo);
    char* y = getBlockY(blockInfo);
    char* w = getBlockWidth(blockInfo);
    char* h = getBlockHeight(blockInfo);

    *block = createRectangle("..", w, h, x, y, "..", "..", "..");
    return;
}

void setAdressCoordinatesOnNorthFace(address* add, double bx, double by, double bw, double bh);
void setAdressCoordinatesOnSouthFace(address* add, double bx, double by, double bw, double bh);
void setAdressCoordinatesOnEastFace(address* add, double bx, double by, double bw, double bh);
void setAdressCoordinatesOnWestFace(address* add, double bx, double by, double bw, double bh);

void setAdressCoordinates(address* add){

    double bx = atof(getRectangleX(add->block));
    double by = atof(getRectangleY(add->block));
    double bw = atof(getRectangleWidth(add->block));
    double bh = atof(getRectangleHeight(add->block));

    switch (add->face){
        case 'N':
        case 'n':
            setAdressCoordinatesOnNorthFace(add, bx, by, bw, bh);
            break;
            
        case 'S':
        case 's':
            setAdressCoordinatesOnSouthFace(add, bx, by, bw, bh);
            break;

        case 'L':
        case 'l':
            setAdressCoordinatesOnEastFace(add, bx, by, bw, bh);
            break;
        
        case 'O':
        case 'o':
            setAdressCoordinatesOnWestFace(add, bx, by, bw, bh);
            break;
    }

    return;
}

// Face Norte
void setAdressCoordinatesOnNorthFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, bx + add->number);
    setPointY(add->coordinates, (by + bh) - ADDRESS_DISTANCE_FROM_BLOCK_BORDER);
}
// Face Sul
void setAdressCoordinatesOnSouthFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, (bx + add->number));
    setPointY(add->coordinates, (by + ADDRESS_DISTANCE_FROM_BLOCK_BORDER));
}
// Face Leste
void setAdressCoordinatesOnEastFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, (bx + ADDRESS_DISTANCE_FROM_BLOCK_BORDER));
    setPointY(add->coordinates, (by + add->number));  
}
// Face Oeste
void setAdressCoordinatesOnWestFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, (bx + bw - ADDRESS_DISTANCE_FROM_BLOCK_BORDER));
    setPointY(add->coordinates, (by + add->number));
}


void freeAdress(Address Add){
    if(Add == NULL) return;
    address *add = (address*) Add;

    free(add->compl);
    freeRectangle(add->block);
    free(add->coordinates);
    free(add);
}