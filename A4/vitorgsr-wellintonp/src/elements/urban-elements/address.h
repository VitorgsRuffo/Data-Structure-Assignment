#ifndef ADRESS_H
#define ADRESS_H

#include "city.h"

/*
*   Tipo abstrato de dado que representa o elemento urbano endereco.
*/
typedef void* Address;

/*  
    Pré-Condição: requer os dados (strings) que compoem um endereço.
    Pós-Condição: retorna uma nova instancia de "address" na qual possui as informacoes passadas.
*/
Address createAdress(char* cep, char face, int number, char* compl, City Ct);

/*  
    Pré-Condição: requer o endereco de uma instancia de endereço.
    Pós-Condição: retorna as coordenadas do endereço passado por parametro.
*/
Point getAddressCoordinates(Address Add);

/*
    Pré-Condição: requer o endereco de uma instancia de endereco.
    Pós-Condição: libera a memoria usada pela instancia de endereco que foi passada.
*/
void freeAdress(Address Add);

#endif