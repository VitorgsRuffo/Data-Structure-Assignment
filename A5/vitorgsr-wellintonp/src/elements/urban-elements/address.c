#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../include/dataStructure.h"

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
void setAddressCoordinates(address* add);

Address createAddress(char* cep, char face, int number, char* compl, City Ct){
    if(cep == NULL || compl == NULL || Ct == NULL) 
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

char* getAddressCep(Address Add){
    if(Add == NULL) return NULL;
    address *add = (address*) Add;
    return add->cep;
}

char getAddressFace(Address Add){
    if(Add == NULL) return -1;
    address *add = (address*) Add;
    return add->face;
}

int getAddressNumber(Address Add){
    if(Add == NULL) return -1;
    address *add = (address*) Add;
    return add->number;
}

char* getAddressCompl(Address Add){
    if(Add == NULL) return NULL;
    address *add = (address*) Add;
    return add->compl;
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

char* addressToString(Address Add){
     if(Add == NULL)
        return NULL;
    address *add = (address*) Add;

    char* string = (char*) malloc(200 * sizeof(char));
    sprintf(string, "endereco - cep: %s, face: %c, num: %d, compl: %s.",
                    add->cep, add->face, add->number, add->compl);
    return string;
}

void freeAddress(Address Add){
    if(Add == NULL) return;
    address *add = (address*) Add;

    free(add->compl);
    freeRectangle(add->block);
    free(add->coordinates);
    free(add);
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

void setAddressCoordinatesOnNorthFace(address* add, double bx, double by, double bw, double bh);
void setAddressCoordinatesOnSouthFace(address* add, double bx, double by, double bw, double bh);
void setAddressCoordinatesOnEastFace(address* add, double bx, double by, double bw, double bh);
void setAddressCoordinatesOnWestFace(address* add, double bx, double by, double bw, double bh);

void setAddressCoordinates(address* add){

    double bx = atof(getRectangleX(add->block));
    double by = atof(getRectangleY(add->block));
    double bw = atof(getRectangleWidth(add->block));
    double bh = atof(getRectangleHeight(add->block));

    switch (add->face){
        case 'N':
        case 'n':
            setAddressCoordinatesOnNorthFace(add, bx, by, bw, bh);
            break;
            
        case 'S':
        case 's':
            setAddressCoordinatesOnSouthFace(add, bx, by, bw, bh);
            break;

        case 'L':
        case 'l':
            setAddressCoordinatesOnEastFace(add, bx, by, bw, bh);
            break;
        
        case 'O':
        case 'o':
            setAddressCoordinatesOnWestFace(add, bx, by, bw, bh);
            break;
    }

    return;
}

// Face Norte
void setAddressCoordinatesOnNorthFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, bx + add->number);
    setPointY(add->coordinates, (by + bh) - ADDRESS_DISTANCE_FROM_BLOCK_BORDER);
}
// Face Sul
void setAddressCoordinatesOnSouthFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, (bx + add->number));
    setPointY(add->coordinates, (by + ADDRESS_DISTANCE_FROM_BLOCK_BORDER));
}
// Face Leste
void setAddressCoordinatesOnEastFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, (bx + ADDRESS_DISTANCE_FROM_BLOCK_BORDER));
    setPointY(add->coordinates, (by + add->number));  
}
// Face Oeste
void setAddressCoordinatesOnWestFace(address* add, double bx, double by, double bw, double bh){
    setPointX(add->coordinates, (bx + bw - ADDRESS_DISTANCE_FROM_BLOCK_BORDER));
    setPointY(add->coordinates, (by + add->number));
}