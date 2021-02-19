#ifndef ESTABLISHMENT_H
#define ESTABLISHMENT_H

#include "city.h"
#include "address.h"
#include "../point.h"
#include "establishmentType.h"

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
* Pós-Condição: retorna a cor que é usada no svg para representar o estabelecimento comercial.
*/
char* getEstablishmentColor(Establishment Est);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial e uma string informando a nova cor do estabelecimento.
* Pós-Condição: Altera a cor do estabelecimento comercial. Retorna 0 caso de algum erro, caso contrário retorna 1.
*/
int setEstablishmentColor(Establishment Est, char* color);

/*  
* Pré-Condição: requer uma instancia de uma instancia de estabelecimento e uma instancia de tipo de estabelecimento.
* Pós-Condição: retorna uma string com todas as informacoes da instancia de estabelecimento passada.
*/
char* establishmentToString(Establishment Est, EstablishmentType EstabType);

/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: libera a memoria usada pela instancia de estabelecimento comercial que foi passada.
*/
void freeEstablishment(Establishment Et);

#endif