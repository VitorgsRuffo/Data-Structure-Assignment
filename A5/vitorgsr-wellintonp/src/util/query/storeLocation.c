#include "../../include/headers.h"
#include "storeLocation.h"
#include "../../elements/urban-elements/house.h"

char* buildLocationTag(char* reg, double x, double y);

void saveLocationByCpf(char* command, City Ct){

    char reg[5], cpf[15];
    sscanf(&command[4], "%s %s", reg, cpf);

    HashTable housesTable = getHousesTable(Ct);

    House house = getHashTableInfo(housesTable, cpf);
    if(house == NULL) 
        return;
    
    Address houseAddress = getHouseAddress(house);
    if(houseAddress == NULL) 
        return;

    Point addressCoordinates = getAddressCoordinates(houseAddress);

    double x = getPointX(addressCoordinates);
    double y = getPointY(addressCoordinates);

    Point* locations = getLocations(Ct);
    int index = atoi(&reg[1]);

    locations[index] = createPoint(x, y);

    char* locationTag = buildLocationTag(reg, x, y);
    List queryElements = getQueryElements(Ct);
    insert(queryElements, locationTag);
}

void saveLocationByAddress(char* command, City Ct){

    char reg[5], cep[15], face, num[10];
    sscanf(&command[4], "%s %s %c %s", reg, cep, &face, num);

    int number = atoi(num);
    Address address = createAddress(cep, face, number, "-", Ct);

    Point addressCoordinates = getAddressCoordinates(address);

    double x = getPointX(addressCoordinates);
    double y = getPointY(addressCoordinates);

    Point* locations = getLocations(Ct);
    int index = atoi(&reg[1]);

    locations[index] = createPoint(x, y);

    char* locationTag = buildLocationTag(reg, x, y);
    List queryElements = getQueryElements(Ct);
    insert(queryElements, locationTag);
}

char* buildLocationTag(char* reg, double x, double y){
    char* locationTag = (char*) malloc(300*sizeof(char));
    if(locationTag == NULL) return NULL;
    sprintf(locationTag, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"-100\" style=\"stroke:rgb(0,0,0);stroke-width:1.5\" />\t<text x=\"%lf\" y=\"-110\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %s </text>\n", x, y, x, x, reg);
    return locationTag;
}