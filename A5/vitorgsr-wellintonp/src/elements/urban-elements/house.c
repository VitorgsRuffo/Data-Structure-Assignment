#include "../../include/headers.h"
#include "../../include/dataStructure.h"
#include "../urban-elements/block.h"
#include "house.h"

#define houseWidth 15
#define houseHeight 15

typedef struct {
    char* cpf;
    Address address;
    Point coordinates;
    double w, h;
}house;

void setHouseCoordinates(house* h);

House createHouse(char* cpf, char* cep, char face, int number, char* compl, City Ct){
    
    house *h = (house*) malloc(sizeof(house));
    if(h == NULL) return NULL;

    h->cpf = (char*) malloc((strlen(cpf) + 1) * sizeof(char));
    strcpy(h->cpf, cpf);
    h->address = createAddress(cep, face, number, compl, Ct);
    h->coordinates = createPoint(0,0);
    h->w = houseWidth;
    h->h = houseHeight;
    setHouseCoordinates(h);

    return h;
}

char* getHouseCpf(House H){
    if(H == NULL)
        return NULL;
    house *h = (house*) H;
    return h->cpf;
}

Address getHouseAddress(House H){
    if(H == NULL) 
        return NULL;
    house *h = (house*) H;
    return h->address;
}

int setHouseAddress(House H, Address newAddress){
    if(H == NULL)
        return 0;
    house *h = (house*) H;

    freeAddress(h->address);
    h->address = newAddress;
    
    return 1;
}


Point getHouseCoordinates(House H){
    if(H == NULL)
        return NULL;
    house *h = (house*) H;
    return h->coordinates;
}

double getHouseW(House H){
    if(H == NULL)
        return 0;
    house *h = (house*) H;
    return h->w;
}
double getHouseH(House H){
    if(H == NULL)
        return 0;
    house *h = (house*) H;
    return h->h;
}

Point getHouseCenterOfMass(House H){
    if(H == NULL)
        return NULL;
    house *h = (house*) H;
    return getAddressCoordinates(h->address);
}

char* houseToString(House H){
    if(H == NULL)
        return NULL;
    house *h = (house*) H;

    char* addressString = addressToString(h->address);
    double hx = getPointX(H);
    double hy = getPointY(H);

    char* string = (char*) malloc(200 * sizeof(char));
    sprintf(string, "Casa - cpf do dono: %s, %s, x: %.2lf, y: %.2lf.", h->cpf, addressString, hx, hy);
    
    free(addressString);
    return string;
}


void printHouse(House H){
    if(H == NULL)
        return;
    house *h = (house*) H;
    printf("Casa:\nCpf morador: %s\n%s\nw: %lf\nh: %lf\nx: %lf\ny: %lf\n\n",
            h->cpf, addressToString(h->address), h->w, h->h, getPointX(h->coordinates), getPointY(h->coordinates));
}

void freeHouse(House H){
    if(H == NULL)
        return;

    house *h = (house*) H;
    free(h->cpf);
    freeAddress(h->address);
    free(h->coordinates);
    free(h);
}


void setHouseCoordinates(house* h){
    
    double addressX = getAddressX(h->address);
    double addressY = getAddressY(h->address);

    setPointX(h->coordinates, addressX - (h->w / 2.0));
    setPointY(h->coordinates, addressY - (h->h / 2.0));
}