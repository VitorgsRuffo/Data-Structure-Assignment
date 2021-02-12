#include "../../include/headers.h"
#include "establishment.h"

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
    est->address = createAddress(cep, face, number, "..", Ct);
    est->coordinates = createPoint(0,0);

    strcpy(est->name, name);
    strcpy(est->cnpj, cnpj);
    strcpy(est->cpf, cpf);
    strcpy(est->code, code);
    setEstablishmentCoordinates(est);
    est->w = establishmentWidth;
    est->h = establishmentHeight;

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
        return;
 
    establishment* est = (establishment*) Est;
    return est->name;
}


char* getEstablishmentCnpj(Establishment Est){
    if(Est == NULL)
        return;
 
    establishment* est = (establishment*) Est;
    return est->cnpj;
}


char* getEstablishmentCpf(Establishment Est){
    if(Est == NULL)
        return;
 
    establishment* est = (establishment*) Est;
    return est->cpf;
}


char* getEstablishmentCode(Establishment Est){
    if(Est == NULL)
        return;
 
    establishment* est = (establishment*) Est;
    return est->code;
}

Address getEstablishmentAddress(Establishment Est){
    if(Est == NULL)
        return;
 
    establishment* est = (establishment*) Est;
    return est->address;
}


Point getEstablishmentCoordinates(Establishment Est){
    if(Est == NULL)
        return;
 
    establishment* est = (establishment*) Est;
    return est->coordinates;
}


double getEstablishmentWidth(Establishment Est){
    if(Est == NULL)
        return;
 
    establishment* est = (establishment*) Est;
    return est->w;
}


double getEstablishmentHeight(Establishment Est){
    if(Est == NULL)
        return;
 
    establishment* est = (establishment*) Est;
    return est->h;
}


void freeEstablishment(Establishment Et){
    if(Et == NULL)
        return;
    
    establishment* est = (establishment*) Et;

    free(est->name);
    free(est->cnpj);
    free(est->cpf);
    free(est->code);
    freeAdress(est->address);
    free(est->coordinates);
    free(est);
}