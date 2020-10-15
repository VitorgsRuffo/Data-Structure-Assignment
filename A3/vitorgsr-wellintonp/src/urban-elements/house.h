#ifndef HOUSE_H
#define HOUSE_H

/*
*   Tipo abstrato de dado que representa o elemento urbano casa.
*/
typedef void* House;

/*  
* Pré-Condição: requer o endereço da casa e o numero de casos de covid na casa.
* Pós-Condição: retorna o endereco de uma nova instancia de casa que possui as informacoes passadas.
*/
House createHouse(char* cep, char face, int number, int casesNumber);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa e desenho.
* Pós-Condição: atribui como sendo quadra da casa a quadra cujo cep esta contido no endereço da casa.
*/
void setHouseBlock(House H, Drawing Dr);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa e desenho.
* Pós-Condição: atribui valores as posiçoes x e y da casa e seu centro de massa.
*/
void setHouseLocation(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada x da casa passada.
*/
double getHouseX(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada y da casa passada.
*/
double getHouseY(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada w da casa passada.
*/
double getHouseWidth(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada h da casa passada.
*/
double getHouseHeight(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada x do centro de massa da casa passada.
*/
double getHouseCenterOfMassX(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna a coordenada y do centro de massa da casa passada.
*/
double getHouseCenterOfMassY(House H);

/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: retorna o numero de casos de covid da casa passada.
*/
double getHouseCasesNumber(House H);
/*  
* Pré-Condição: requer o endereco de uma instancia de casa.
* Pós-Condição: libera a memoria usada pela instancia de casa que foi passada.
*/
void freeHouse(House H);

#endif