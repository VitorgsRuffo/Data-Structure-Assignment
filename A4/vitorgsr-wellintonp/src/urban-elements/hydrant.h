#ifndef HYDRANT_H
#define HYDRANT_H

/*
*   Tipo abstrato de dado que representa o elemento urbano hidrante.
*/
typedef void* Hydrant;


/*  
* Pré-Condição: requer os dados (strings) que compoem uma hidrante.
* Pós-Condição: retorna o endereco de uma nova instancia de hidrante que possui as informacoes passadas.
*/
Hydrant createHydrant(char* id, char* x, char* y, char* sw, char* cfill, char* cstrk);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o id do hidrante passado.
*/
char* getHydrantId(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o X do hidrante passado.
*/
char* getHydrantX(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o Y do hidrante passado.
*/
char* getHydrantY(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o raio do hidrante passado.
*/
char* getHydrantRadius(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o sw do hidrante passado.
*/
char* getHydrantSw(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante e um valor para borda.
* Pós-Condição: atribui o tamanho da borda ao equipamento urbano hidrante.
*/
void setHydrantSw(Hydrant Hyd, char* sw);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o cfill do hidrante passado.
*/
char* getHydrantCfill(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o cstrk do hidrante passado.
*/
char* getHydrantCstrk(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna o valor da area da hidrante.
*/
double getHydrantArea(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: retorna uma string com todas as informacoes da instancia de hidrante passada.
*/
char* hydrantToString(Hydrant Hyd);

/*
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printHydrant(Hydrant Hyd);

/*  
* Pré-Condição: requer o endereco de uma instancia de hidrante.
* Pós-Condição: libera a memoria usada pela instancia de hidrante que foi passada.
*/
void freeHydrant(Hydrant Hyd);


#endif