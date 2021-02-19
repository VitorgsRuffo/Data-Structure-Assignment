#include "../../include/headers.h"
#include "establishment.h"
#include "establishmentType.h"
#include "address.h"

#define establishmentWidth 50
#define establishmentHeight 30

typedef struct {
    char* name;
    char* cnpj;
    char* cpf;
    char* code;
    Address address;
    Point coordinates;
    double w, h;
}establishment;

void setEstablishmentCoordinates(establishment* est);

Establishment createEstablishment(char* cnpj, char* cpf, char* code, char* cep, char face, int number, char* name, City Ct){

    establishment* est = (establishment*) malloc(sizeof(establishment));
    
    est->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    est->cnpj = (char*) malloc((strlen(cnpj) + 1) * sizeof(char));
    est->cpf = (char*) malloc((strlen(cpf) + 1) * sizeof(char));
    est->code = (char*) malloc((strlen(code) + 1) * sizeof(char));
    est->address = createAddress(cep, face, number, "none", Ct);
    est->coordinates = createPoint(0,0);

    strcpy(est->name, name);
    strcpy(est->cnpj, cnpj);
    strcpy(est->cpf, cpf);
    strcpy(est->code, code);
    est->w = establishmentWidth;
    est->h = establishmentHeight;
    setEstablishmentCoordinates(est);

    return est;
}

void setEstablishmentCoordinates(establishment* est){
    
    double addressX = getAddressX(est->address);
    double addressY = getAddressY(est->address);

    setPointX(est->coordinates, addressX - (est->w / 2.0));
    setPointY(est->coordinates, addressY - (est->h / 2.0));
}


char* getEstablishmentName(Establishment Est){
    if(Est == NULL)
        return NULL;
 
    establishment* est = (establishment*) Est;
    return est->name;
}


char* getEstablishmentCnpj(Establishment Est){
    if(Est == NULL)
        return NULL;
 
    establishment* est = (establishment*) Est;
    return est->cnpj;
}


char* getEstablishmentCpf(Establishment Est){
    if(Est == NULL)
        return NULL;
 
    establishment* est = (establishment*) Est;
    return est->cpf;
}


char* getEstablishmentCode(Establishment Est){
    if(Est == NULL)
        return NULL;
 
    establishment* est = (establishment*) Est;
    return est->code;
}

Address getEstablishmentAddress(Establishment Est){
    if(Est == NULL)
        return NULL;
 
    establishment* est = (establishment*) Est;
    return est->address;
}

Point getEstablishmentCoordinates(Establishment Est){
    if(Est == NULL)
        return NULL;
 
    establishment* est = (establishment*) Est;
    return est->coordinates;
}

double getEstablishmentWidth(Establishment Est){
    if(Est == NULL)
        return -1;
 
    establishment* est = (establishment*) Est;
    return est->w;
}

double getEstablishmentHeight(Establishment Est){
    if(Est == NULL)
        return -1;
 
    establishment* est = (establishment*) Est;
    return est->h;
}

Point getEstablishmentCenterOfMass(Establishment Est){
    if(Est == NULL)
        return NULL;
    establishment* est = (establishment*) Est;
    return getAddressCoordinates(est->address);
}


char* establishmentToString(Establishment Est, EstablishmentType EstabType){
    if(Est == NULL || EstabType == NULL)
        return NULL;
    
    establishment *est = (establishment*) Est;
    
    char* establishmentInfoString = (char*) malloc(500 * sizeof(char)); 

    char* description = getEstablishmentTypeDescription(EstabType);
    char* address = addressToString(est->address);

    double x = getPointX(est->coordinates);
    double y = getPointY(est->coordinates);

    sprintf(establishmentInfoString, "Nome: %s\nCNPJ: %s\nDescricao: %s\nEndereco: %sx: %lf y:%lf width:%lf height:%lf\n", est->name, est->cnpj, description, address, x, y, est->w, est->h );
    
    return establishmentInfoString;
}

void freeEstablishment(Establishment Et){
    if(Et == NULL)
        return;
    
    establishment* est = (establishment*) Et;

    free(est->name);
    free(est->cnpj);
    free(est->cpf);
    free(est->code);
    freeAddress(est->address);
    free(est->coordinates);
    free(est);
}