#ifndef ESTABLISHMENT_TYPE_H
#define ESTABLISHMENT_TYPE_H


/*
*   Tipo abstrato de dado que representa o elemento urbano tipo de estabelecimento.
*/
typedef void* EstablishmentType;


/*  
* Pré-Condição: requer os dados (strings) que compoem um tipo de estabelecimento comercial.
* Pós-Condição: retorna o endereco de uma nova instancia de tipo de estabelecimento comercial contendo as informacoes passadas.
*/
EstablishmentType createEstablishmentType(char* code, char* description);
/*  
* Pré-Condição: requer o endereco de uma instancia de tipo de estabelecimento comercial.
* Pós-Condição: retorna o codigo referente ao instancia de tipo de estabelecimento comercial.
*/
char* getEstablishmentTypeCode(EstablishmentType Et);
/*  
* Pré-Condição: requer o endereco de uma instancia de tipo de estabelecimento comercial.
* Pós-Condição: retorna a descrição da instancia de tipo de estabelecimento comercial.
*/
char* getEstablishmentTypeDescription(EstablishmentType Et);
/*  
* Pré-Condição: requer o endereco de uma instancia de estabelecimento comercial.
* Pós-Condição: libera a memoria usada pela instancia de tipo de estabelecimento comercial que foi passada.
*/
void freeEstablishmentType(EstablishmentType Et);

#endif