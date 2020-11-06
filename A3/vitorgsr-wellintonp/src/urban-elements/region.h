#ifndef REGION_H
#define REGION_H

/*
*   Tipo abstrato de dado que representa o elemento urbano regiao.
*/
typedef void* Region;

/*  
* Pré-Condição: requer os dados (strings) que compoem uma regiao.
* Pós-Condição: retorna o endereco de uma nova instancia de regiao que possui as informacoes passadas.
*/
Region createRegion(char* x, char* y, char* w, char* h, char* demographicDensity);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a cordenada x da regiao passada.
*/
char* getRegionX(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a coordenada y da regiao passada.
*/
char* getRegionY(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a largura da regiao passada.
*/
char* getRegionWidth(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a altura da quadra passada.
*/
char* getRegionHeight(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a densidade demografica da regiao passada.
*/
double getRegionDemographicDensity(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: libera a memoria usada pela instancia de regiao que foi passada.
*/
void freeRegion(Region Reg);

#endif