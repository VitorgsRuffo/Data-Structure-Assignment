#include "../../include/headers.h"
#include "covidAddress.h"

typedef struct {
    int id;
    Address address;
    int casesNumber;
}covidaddress;

CovidAddress createCovidAddress(int id, char* cep, char face, int number, int casesNumber, City Ct){
    covidaddress* ca = (covidaddress*) malloc(sizeof(covidaddress));
    if(ca == NULL) return NULL;

    ca->id = id;
    ca->address = createAdress(cep, face, number, "none", Ct);
    ca->casesNumber = casesNumber;
    return ca;
}

int getCovidAddressId(CovidAddress Ca){
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
    if(Ca == NULL) return NULL;

    covidaddress* ca = (covidaddress*) Ca;
    return ca->casesNumber;
}

Point getCovidAddressCoordinates(CovidAddress Ca){
    if(Ca == NULL) return NULL;

    covidaddress* ca = (covidaddress*) Ca;
    return getAddressCoordinates(ca->address);
}

void freeCovidAdress(CovidAddress Ca){
    if(Ca == NULL) return NULL;
    
    covidaddress* ca = (covidaddress*) Ca;
    freeAdress(ca->address);
    free(ca);
}