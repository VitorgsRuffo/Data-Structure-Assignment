#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../input/openInput.h"

void writePersonalInformationOnTxt(File txt, char* personalInformation);
char* buildPersonalInformationLineTag(Address houseAddress, char* personalInformation);

void executePersonalInformationChecking(char* command, City Ct, File txt){

    char cpf[30];
    sscanf(&command[4], "%s", cpf);

    DataStructure* people = getPeople(Ct);
    DataStructure* houses = getHousesTable(Ct);

    Info person = getHashTableInfo(*people, cpf);
    if(person == NULL) return;

    Info house = getHashTableInfo(*houses, cpf);
    if(house == NULL) return;

    Address houseAddress = getHouseAddress(house);


    char* personString = personToString(person);
    char* addressString = addressToString(houseAddress);
    char personalInformation[220];
    sprintf(personalInformation, "Relatorio pessoal:\n%s\n%s\n\n", 
                                                    personString, 
                                                    addressString);
    

    writePersonalInformationOnTxt(txt, personalInformation);
    char* lineTag = buildPersonalInformationLineTag(houseAddress, personalInformation);
    insert(getQueryElements(Ct), lineTag);

    free(personString);
    free(addressString);
}

void writePersonalInformationOnTxt(File txt, char* personalInformation){

    fprintf(txt, "%s", personalInformation);
}

char* buildPersonalInformationLineTag(Address houseAddress, char* personalInformation){
    char* lineTag = (char*) malloc(500 * sizeof(char));
    if(lineTag == NULL) return NULL;
    
    Point addressCoordinates = getAddressCoordinates(houseAddress);
    double addX = getPointX(addressCoordinates);
    double addY = getPointY(addressCoordinates);

    sprintf(lineTag, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"-100\" style=\"stroke:rgb(0,0,0);stroke-width:1.5\" />\t<text x=\"%lf\" y=\"-110\" stroke=\"2.0\" stroke-width=\"0.3\" fill=\"black\" > %s </text>\n", addX, addY, addX, addX, personalInformation);
    return lineTag;
}