#ifndef STREET
#define STREET

/*
* Representa uma rua da cidade.
*/
typedef void* Street;

/*
*   Cria e retorna uma nova rua com as informacoes passadas.
*/
Street createStreet(char* name, char* rightCep, char* leftCep, double length, double avgSpeed);

/*
*   Retorna o nome da rua.
*/
char* getStreetName(Street St);

/*
*   Retorna o cep da quadra á direita da rua.
*/
char* getStreetRightCep(Street St);

/*
*   Retorna o cep da quadra á esquerda da rua.
*/
char* getStreetLeftCep(Street St);

/*
*   Retorna o comprimento (metros) da rua.
*/
double getStreetLength(Street St);

/*
*   Retorna a velocidade media (metros/seg) em que os veiculos trafegam nesta rua.
*/
double getStreetAvgSpeed(Street St);

/*
*   Retorna o tempo medio (seg) que leva para percorrer toda a rua.
*/
double getStreetDisplacementTime(Street St);

/*
* Imprime a rua na saida padrao.
*/
void printStreet(Street St);

/*
*   Desaloca a memoria usada pela rua.
*/
void freeStreet(Street St);

#endif