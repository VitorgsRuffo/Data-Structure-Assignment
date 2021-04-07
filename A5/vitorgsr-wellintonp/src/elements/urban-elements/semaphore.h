#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "../point.h"

/*
*   Tipo abstrato de dado que representa o elemento urbano semaforo.
*/
typedef void* Semaphore;


/*  
* Pré-Condição: requer os dados (strings) que compoem uma semaforo.
* Pós-Condição: retorna o endereco de uma nova instancia de semaforo que possui as informacoes passadas.
*/
Semaphore createSemaphore(char* id, char* x, char* y, char* sw, char* cfill, char* cstrk);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o id do semaforo passado.
*/
char* getSemaphoreId(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o X do semaforo passado.
*/
char* getSemaphoreX(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o Y do semaforo passado.
*/
char* getSemaphoreY(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o raio do semaforo passado.
*/
char* getSemaphoreRadius(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna uma instancia de ponto que representa a localizacao desse semaforo.
*/
Point getSemaphoreCoordinates(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o sw do semaforo passado.
*/
char* getSemaphoreSw(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo e uma espessura.
* Pós-Condição: atribui a espessura passada a borda da semaforo.
*/
void setSemaphoreSw(Semaphore Semap, char* sw);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o cfill do semaforo passado.
*/
char* getSemaphoreCfill(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o cstrk do semaforo passado.
*/
char* getSemaphoreCstrk(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna o valor da area da semaforo.
*/
double getSemaphoreArea(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: retorna uma string com todas as informacoes da instancia de semaforo passada.
*/
char* semaphoreToString(Semaphore Semap);

/*
* Pré-Condição: requer o endereco de uma instancia de Semaforo.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printSemaphore(Semaphore Semap);

/*  
* Pré-Condição: requer o endereco de uma instancia de semaforo.
* Pós-Condição: libera a memoria usada pela instancia de semaforo que foi passada.
*/
void freeSemaphore(Semaphore Semap);


#endif