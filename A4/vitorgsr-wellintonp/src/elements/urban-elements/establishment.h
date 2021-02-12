#ifndef ESTABLISHMENT_H
#define ESTABLISHMENT_H

#include "city.h"
#include "point.h"
#include "address.h"

/*
*   Tipo abstrato de dado que representa o elemento urbano estabelecimento comercial.
*/
typedef void* Establishment;

/*  
* Pré-Condição: requer os dados (strings) que compoem um estabelecimento comercial.
* Pós-Condição: retorna o endereco de uma nova instancia de estabelecimento comercial contendo as informacoes passadas.
*/
Establishment createEstablishment(char* cnpj, char* cpf, char* code, char* cep, char face, int number, char* name, City Ct);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna o nome do estabelecimento comercial passado.
*/
char* getEstablishmentName(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna o CNPJ do estabelecimento comercial passado.
*/
char* getEstablishmentCnpj(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna o CPF do proprietario do estabelecimento comercial passado.
*/
char* getEstablishmentCpf(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna o codigo referente ao tipo do estabelecimento comercial passado.
*/
char* getEstablishmentCode(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna uma instancia de endereço que representa a localizacao desse estabelecimento comercial.
*/
Address getEstablishmentAddress(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna uma instancia de ponto que representa a localizacao desse estabelecimento comercial.
*/
Point getEstablishmentCoordinates(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna a largura do estabelecimento comercial passado.
*/
double getEstablishmentWidth(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna a altura do estabelecimento comercial passado.
*/
double getEstablishmentHeight(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: retorna um Point contendo x e y do centro de massa do estabelecimento comercial passado.
*/
Point getEstablishmentCenterOfMass(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: libera a memoria usada pela instancia de estabelecimento comercial que foi passada.
*/
void freeEstablishment(Establishment Et);

#endif