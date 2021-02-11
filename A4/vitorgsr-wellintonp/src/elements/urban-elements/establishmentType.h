#ifndef ESTABLISHMENT_TYPE_H
#define ESTABLISHMENT_TYPE_H


/*
*   Tipo abstrato de dado que representa o elemento urbano tipo de estabelecimento.
*/
typedef void* EstablishmentType;


EstablishmentType createEstablishmentType(char* code, char* description);


char* getEstablishmentTypeCode(EstablishmentType Et);

char* getEstablishmentTypeDescription(EstablishmentType Et);

void freeEstablishmentType(EstablishmentType Et);

#endif