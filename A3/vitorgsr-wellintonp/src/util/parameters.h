#ifndef PARAMETERS_H
#define PARAMETERS_H

/*
* apontador void que representa o TAD parameters
*/
typedef void* Parameters;

/*
* Pré-Condição: nenhuma.
* Pós-Condição: retorna um TAD vazio que será composto pelos parametros de execuçao do siguel.
*/
Parameters createParameters();

/*
* Pré-Condição: requer um TAD parametros e os parametros da main argv e argc.
* Pós-Condição: preenche o TAD com os parametros de execucao do siguel.
*/
void setParameters(Parameters Param, char* argv[], int argc);

/*
* Pré-Condição: requer um TAD parametros.
* Pós-Condição: escreve na saida padrão os valores que compoem TAD parametros.
*/
void printParameters(Parameters Param);

/*
* Pré-Condição: requer um TAD parametros.
* Pós-Condição: retorna o valor do campo "diretorio de entrada" do TAD parametros.
*/
char* getInputDirectory(Parameters Param);

/*
* Pré-Condição: requer um TAD parametros.
* Pós-Condição: retorna o valor do campo "nome do geo" do TAD parametros
*/
char* getGeoName(Parameters Param);

/*
* Pré-Condição: requer um TAD parametros.
* Pós-Condição: retorna o valor do campo "nome do qry" do TAD parametros
*/
char* getQryName(Parameters Param);

/*
* Pré-Condição: requer um TAD parametros.
* Pós-Condição: retorna o valor do campo "diretorio de saida" do TAD parametros
*/
char* getOutputDirectory(Parameters Param);

/*
* Pré-Condição: requer um TAD parametros.
* Pós-Condição: retorna 1 se o arquivo query nao foi especificado nos parametros do siguel, ou 0 caso ele tenha sido especificado.
*/
int isQryNull(Parameters Param);

/*
* Pré-Condição: requer um TAD parametros.
* Pós-Condição: libera a memoria usada pelos parametros do funcionamento do programa.
*/
void freeParameters(Parameters Param);

#endif