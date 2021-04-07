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
Region createRegion(int id, double x, double y, double w, double h, double demographicDensity);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna o identificador da regiao passada.
*/
double getRegionId(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a coordenada x da regiao passada.
*/
double getRegionX(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a coordenada y da regiao passada.
*/
double getRegionY(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a largura da regiao passada.
*/
double getRegionWidth(Region Reg);

/*  
* Pré-Condição: requer o endereco de uma instancia de regiao.
* Pós-Condição: retorna a altura da quadra passada.
*/
double getRegionHeight(Region Reg);

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