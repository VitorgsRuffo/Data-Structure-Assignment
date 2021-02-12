#include "../../include/headers.h"
#include "covidAddress.h"

typedef struct {
    char* id;
    Address address;
    int casesNumber;
}covidaddress;

CovidAddress createCovidAddress(int id, char* cep, char face, int number, int casesNumber, City Ct){
    covidaddress* ca = (covidaddress*) malloc(sizeof(covidaddress));
    if(ca == NULL) return NULL;

    char idString[5];
    sprintf(idString, "%d", id);

    ca->id = (char*) malloc(6 * sizeof(char));
    strcpy(ca->id, idString);
    ca->address = createAddress(cep, face, number, "none", Ct);
    ca->casesNumber = casesNumber;
    return ca;
}

char* getCovidAddressId(CovidAddress Ca){
    if(Ca == NULL) return NULL;

    covidaddress* ca = (covidaddress*) Ca;
    return ca->id;
}

Address getCovidAddress(CovidAddress Ca){
    if(Ca == NULL) return NULL;

    covidaddress* ca = (covidaddress*) Ca;
    return ca->address;
}

int getCovidAddressCasesNumber(CovidAddress Ca){
    if(Ca == NULL) return -1;

    covidaddress* ca = (covidaddress*) Ca;
    return ca->casesNumber;
}

Point getCovidAddressCoordinates(CovidAddress Ca){
    if(Ca == NULL) return NULL;

    covidaddress* ca = (covidaddress*) Ca;
    return getAddressCoordinates(ca->address);
}

void freeCovidAddress(CovidAddress Ca){
    if(Ca == NULL) return;
    
    covidaddress* ca = (covidaddress*) Ca;
    free(ca->id);
    freeAddress(ca->address);
    free(ca);
}