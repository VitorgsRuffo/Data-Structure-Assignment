#ifndef HOUSE_H
#define HOUSE_H

#include "./city.h"
#include "../point.h"

/*
*   Tipo abstrato de dado que representa o elemento urbano casa.
*/
typedef void* House;

/*  
* Pré-Condição: requer o cpf do dono da casa, o endereço da casa, o numero de casos de covid na casa e a cidade na qual a casa se localiza.
* Pós-Condição: retorna o endereco de uma nova instancia de casa que possui as informacoes passadas.
*/
House createHouse(char* cpf, char* cep, char face, int number, char* compl, int casesNumber, City Ct);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna o cpf do(a) proprietario(a) da casa passada.
*/
char* getHouseCpf(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna uma instancia de ponto que representa a localizacao da casa.
*/
Point getHouseCoordinates(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada w da casa passada.
*/
double getHouseW(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada h da casa passada.
*/
double getHouseH(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna uma instancia de ponto que representa o centro de massa da casa passada.
*/
Point getHouseCenterOfMass(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna o numero de casos de covid da casa passada.
*/
int getHouseCasesNumber(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: imprime as informacoes da casa.
*/
void printHouse(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: libera a memoria usada pela instancia de casa que foi passada.
*/
void freeHouse(House H);

#endif