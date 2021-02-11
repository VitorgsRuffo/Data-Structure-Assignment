#ifndef COVID_ADDRESS_H
#define COVID_ADDRESS_H

#include "../urban-elements/address.h"

/*
    TAD que representa um endereço que possui casos de covid.
*/
typedef void* CovidAddress;

/*  
* Pré-Condição: requer o endereço da incidencia dos casos, o numero de casos de covid e a cidade na qual a casa se localiza.
* Pós-Condição: retorna o endereco de uma nova instancia de um endereço que possui casos de covid.
*/
CovidAddress createCovidAddress(int id, char* cep, char face, int number, int casesNumber, City Ct);

/*  
* Pré-Condição: requer uma instancia de um endereço que possui casos de covid.
* Pós-Condição: retorna o identificador do endereço.
*/
int getCovidAddressId(CovidAddress Ca);

/*  
* Pré-Condição: requer uma instancia de um endereço que possui casos de covid.
* Pós-Condição: retorna uma instancia de endereço.
*/
Address getCovidAddress(CovidAddress Ca);

/*  
* Pré-Condição: requer uma instancia de um endereço que possui casos de covid.
* Pós-Condição: retorna o ponto que localiza o endereço.
*/
Point getCovidAddressCoordinates(CovidAddress Ca);

/*  
* Pré-Condição: requer uma instancia de um endereço que possui casos de covid.
* Pós-Condição: desaloca a memoria usada pelo tad.
*/
void freeCovidAdress(CovidAddress Ca);

#endif