#ifndef ADDRESS_H
#define ADDRESS_H

#include "city.h"

/*
*   Tipo abstrato de dado que representa o elemento urbano endereco.
*/
typedef void* Address;

/*  
    Pré-Condição: requer os dados (strings) que compoem um endereço.
    Pós-Condição: retorna uma nova instancia de "address" na qual possui as informacoes passadas.
*/
Address createAddress(char* cep, char face, int number, char* compl, City Ct);

/*  
    Pré-Condição: requer uma referencia de uma instancia de endereço.
    Pós-Condição: retorna as coordenadas do endereço passado por parametro.
*/
Point getAddressCoordinates(Address Add);

/*  
    Pré-Condição: requer uma referencia de uma instancia de endereço.
    Pós-Condição: retorna o valor de X referente a cordenada do endereço passado por parametro.
*/
double getAddressX(Address Add);

/*  
    Pré-Condição: requer uma referencia de uma instancia de endereço.
    Pós-Condição: retorna o valor de Y referente a cordenada do endereço passado por parametro.
*/
double getAddressY(Address Add);

/*
    Pré-Condição: requer uma referencia de uma instancia de endereco.
    Pós-Condição: libera a memoria usada pela instancia de endereco que foi passada.
*/
void freeAddress(Address Add);

#endif