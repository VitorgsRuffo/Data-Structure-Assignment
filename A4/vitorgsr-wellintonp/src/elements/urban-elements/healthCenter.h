#ifndef HEALTH_CENTER_H
#define HEALTH_CENTER_H

/*
*   Tipo abstrato de dado que representa o elemento urbano posto de saude.
*/
typedef void* HealthCenter;

/*  
* Pré-Condição: requer os dados (strings) que compoem um posto de saude.
* Pós-Condição: retorna o endereco de uma nova instancia de posto de saude que possui as informacoes passadas.
*/
HealthCenter createHealthCenter(int id, char* x, char* y);

/*  
* Pré-Condição: requer o endereco de uma instancia de Posto.
* Pós-Condição: retorna o id do Posto passado.
*/
int getHealthCenterId(HealthCenter HealthC);

/*  
* Pré-Condição: requer o endereco de uma instancia de Posto.
* Pós-Condição: retorna a coordenada x do posto passado.
*/
char* getHealthCenterX(HealthCenter HealthC);

/*  
* Pré-Condição: requer o endereco de uma instancia de Posto.
* Pós-Condição: retorna a coordenada y do posto passado.
*/
char* getHealthCenterY(HealthCenter HealthC);

/*  
* Pré-Condição: requer o endereco de uma instancia de Posto.
* Pós-Condição: retorna uma instancia de ponto que representa a localizacao desse Posto.
*/
Point getHealthCenterCoordinates(HealthCenter HealthC);

/*  
* Pré-Condição: requer o endereco de uma instancia de Posto.
* Pós-Condição: retorna o raio do posto passado.
*/
char* getHealthCenterRadius(HealthCenter HealthC);

/*  
* Pré-Condição: requer o endereco de uma instancia de posto.
* Pós-Condição: libera a memoria usada pela instancia de posto que foi passada.
*/
void freeHealthCenter(HealthCenter HealthC);

#endif