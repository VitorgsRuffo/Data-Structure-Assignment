#ifndef DRAWING_H
#define DRAWING_H

/*
* TAD desenho que vai conter as listas das entidades que serao desenhadas em um arquivo svg.
*/
typedef void* Drawing;

/*
* Pré-Condição: nenhuma.
* Pós-Condição: retorna um TAD desenho com as listas das entidades vazias.
*/
Drawing createDrawing();

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de circulos presente no TAD desenho.
*/
List getCircleList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de retangulo presente no TAD desenho.
*/
List getRectangleList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de textos presente no TAD desenho.
*/
List getTextList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de quadras presente no TAD desenho.
*/
List getBlockList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de hidrantes presente no TAD desenho.
*/
List getHydrantList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de rádio-bases presente no TAD desenho.
*/
List getBaseRadioList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de Semáfaros presente no TAD desenho.
*/
List getSemaphoreList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de elementos de query presente no TAD desenho.
*/
List getQueryElementsList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de postos de saude presente no TAD desenho.
*/
List getHealthCenterList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de regioes presente no TAD desenho.
*/
List getRegionList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: retorna uma referencia para a lista de casas presente no TAD desenho.
*/
List getHouseList(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho e uma referencia para uma string que contenha o tipo de um elemento.
* Pós-Condição: retorna a lista de elementos cujo tipo foi passado por parametro.
*/
List getListByElementType(Drawing Dr, char* elementType);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho, um id de um elemento (figura ou texto) a ser procurado nas listas do tad desenho, e um ponteiro para guardar o tipo da figura quando a encontrarmos (se encontrarmos).
* Pós-Condição: percorre as listas de figuras e a lista de texto em busca de um elemento que tenha o id especificado, se for encontrado retornamos o seu no e salvamos seu tipo no ponteiro passado, se nao for retornamos NULL.
*/
Node searchForFigureOrTextElementByIdentifier(Drawing Dr, char* idToSearch, char* figureElementType);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho, um cep de uma quadra a ser procurada.
* Pós-Condição: percorre a lista de quadras em busca de um no cuja informacao tenha o cep especificado, se for encontrado retornamos esse no, se nao for retornamos NULL.
*/
Node searchForBlockByCep(Drawing Dr, char* cepToSearch);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho, um id de um elemento urbano a ser procurado nas listas do tad desenho, e um ponteiro para guardar o tipo do elemento quando o encontrarmos (se encontrarmos).
* Pós-Condição: percorre as listas de elementos urbanos em busca de um no cuja informacao tenha o id especificado, se for encontrado retornamos esse no e salvamos seu tipo dessa informacao no ponteiro passado, se nao for retornamos NULL.
*/
Node searchForUrbanElementByIdentifier(Drawing Dr, char* idToSearch, char* urbanElementType);

/*
* Pré-Condição: requer o endereco de uma instancia de desenho.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printDrawing(Drawing Dr);

/*
* Pré-Condição: requer a referencia para uma instancia de TAD desenho.
* Pós-Condição: libera a memoria usada pela instancia de drawing que foi passada.
*/
void freeDrawing(Drawing Dr);

#endif