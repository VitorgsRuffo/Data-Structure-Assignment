#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../input/openInput.h"
#include "saveLocation.h"

char* buildLocationTag(char* reg, double x, double y);

void saveLocationByCpf(char* command, City Ct){

    char reg[5], cpf[15];
    sscanf(&command[4], "%s %s", reg, cpf);

    HashTable* housesTable = getHousesTable(Ct);

    Info house = getHashTableInfo(*housesTable, cpf);
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

    char reg[5], cep[15], face[10], num[10];
    sscanf(&command[4], "%s %s %s %s", reg, cep, face, num);

    int number = atoi(num);
    Address address = createAddress(cep, face[5], number, "-", Ct);

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


void saveUrbanEquipmentLocation(char* command, City Ct){
    
    char reg[5], id[50], equipmentType[20];
    sscanf(&command[4], "%s %s", reg, id);

    Node urbEquip = searchForUrbanElementByIdentifier(Ct, id, equipmentType);
    if(urbEquip == NULL) return;

    double x, y;
    Info info;
    
    if(equipmentType[0] == 'h'){

        info = getPQuadTreeNodeInfo(getHydrants(Ct), urbEquip);
        x = atof(getHydrantX(info)); y = atof(getHydrantY(info));

    }else if(equipmentType[0] == 's'){

        info = getPQuadTreeNodeInfo(getSemaphores(Ct), urbEquip);
        x = atof(getSemaphoreX(info)); y = atof(getSemaphoreY(info));

    }else if(equipmentType[0] == 'r'){

        info = getPQuadTreeNodeInfo(getBaseRadios(Ct), urbEquip);
        x = atof(getBaseRadioX(info)); y = atof(getBaseRadioY(info));

    }else return;

    Point* locations = getLocations(Ct);
    int index = atoi(&reg[1]);

    *(locations + index) = createPoint(x, y);

    char* locationTag = buildLocationTag(reg, x, y);
    List queryElements = getQueryElements(Ct);
    insert(queryElements, locationTag);
}


void saveLocation(char* command, City Ct){
    
    char reg[5]; double x, y;
    sscanf(&command[4], "%s %lf %lf", reg, &x, &y);

    Point* locations = getLocations(Ct);
    int index = atoi(&reg[1]);

    *(locations + index) = createPoint(x, y);

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