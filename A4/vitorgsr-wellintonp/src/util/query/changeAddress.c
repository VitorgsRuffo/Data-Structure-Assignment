#include "../../include/headers.h"
#include "changeAddress.h"
#include "../../elements/urban-elements/address.h"
#include "../../elements/urban-elements/person.h"
#include "../../elements/urban-elements/house.h"

void writeAdressesOnTxt(char* oldAddressString, char* newAddressString, Info personInfo, File txt);
char* buildLineBetweenAddresses(Point oldAddressCoordinates, Point newAddressCoordinates);
char* buildAddressCircumference(Point addressCoordinates, char* color);

void executeChangeOfAddress(char* command, City Ct, File txt){

    char cpf[15]; char cep[15]; char face[3]; char num[15]; char compl[15];
    sscanf(&command[4], "%s %s %s %s %s", cpf, cep, face, num, compl);

    DataStructure peopleTable = getPeople(Ct);
    Info personInfo = getHashTableInfo(peopleTable, cpf);

    DataStructure houseTable = getHousesTable(Ct);
    Info houseInfo = getHashTableInfo(houseTable, cpf);

    Address oldAddress = getHouseAddress(houseInfo);
    char* oldAddressString = addressToString(oldAddress);
    Point oldAddressCoordinates = getHouseCoordinates(houseInfo); // Esse point vai ser freelado junto com o endereço antigo, portanto é criado um point abaixo com essas informaçoes
    Point oldAddressPoint = createPoint(getPointX(oldAddressCoordinates), getPointY(oldAddressCoordinates));

    Address newAddress = createAddress(cep, face[0], atof(num), compl, Ct);

    setHouseAddress(houseInfo, newAddress);
    char* newAddressString = addressToString(newAddress);
    Point newAddressCoordinates = getHouseCoordinates(houseInfo);

    writeAdressesOnTxt(oldAddressString, newAddressString, personInfo, txt);

    char* line = buildLineBetweenAddresses(oldAddressPoint, newAddressCoordinates);
    char* oldAddressCircumference = buildAddressCircumference(oldAddressPoint, "red");
    char* newAddressCircumference = buildAddressCircumference(newAddressCoordinates, "blue");

    List queryElements = getQueryElements(Ct);
    insert(queryElements, line);
    insert(queryElements, oldAddressCircumference);
    insert(queryElements, newAddressCircumference);

    free(oldAddressCoordinates);
}

void writeAdressesOnTxt(char* oldAddressString, char* newAddressString, Info personInfo, File txt){

    //char* personString = personToString(personInfo);

    fprintf(txt, "Endereco antigo: %s", oldAddressString);
    fprintf(txt, "Novo endereco: %s", newAddressString);
    //fprintf(txt, "Dados do morador: %s", personString);

    free(oldAddressString);
    free(newAddressString);
    //free(personString);
}

char* buildLineBetweenAddresses(Point oldAddressCoordinates, Point newAddressCoordinates){

    double oldX = getPointX(oldAddressCoordinates);
    double oldY = getPointY(oldAddressCoordinates);
    double newX = getPointX(newAddressCoordinates);
    double NewY = getPointY(newAddressCoordinates);

    char* lineTag = (char*) malloc(200 * sizeof(char));
    if(lineTag == NULL)
        return NULL;

    sprintf(lineTag, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"5.0\" />", oldX, oldY, newX, NewY);

    return lineTag;
}

char* buildAddressCircumference(Point addressCoordinates, char* color){

    char* addressCircumference = (char*) malloc(200 * sizeof(char));
    
    if(addressCircumference == NULL)
        return NULL;

    double x = getPointX(addressCoordinates);
    double y = getPointY(addressCoordinates);

    sprintf(addressCircumference, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"30\" stroke=\"white\" stroke-width=\"7.0\" fill=\"%s\" fill-opacity=\"0.8\"/>\n", x, y, color);

    return addressCircumference;
}