#ifndef ESTABLISHMENT_H
#define ESTABLISHMENT_H

#include "city.h"

/*
*   Tipo abstrato de dado que representa o elemento urbano estabelecimento comercial.
*/
typedef void* Establishment;


Establishment createEstablishment(char* cnpj, char* cpf, char* code, char* cep, char face, int number, char* name, City Ct);


void freeEstablishment(Establishment Et);

#endif