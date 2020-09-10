#ifndef TOOLS_H
#define TOOLS_H

/* 
* Definicao do tamanho maximo de uma linha de comando de um arquivo de entrada (linha do geo/qry) 
*/
#define commandMaxLength 150

/*
* apontador para void que representa qualquer TAD do programa.
*/
typedef void* Element;

/*
* Pré-condição: requer a referencia para uma instancia de algum TAD, o nome do seu tipo, e o nome da funcao que quer checar se a referencia para aquele TAD é NULL.
* Pós-condição: retorna 1 se a intancia do TAD for NULL, ou 0 se nao for.
*/
int isElementNull(Element element, char* elementName, char* functionName);

/*
* Pré-condição: nenhuma.
* Pós-condição: aloca memoria dinamicamente para um vetor de ponteiros para char e retorna o endereco do vetor.
*/
char** createCommandParts();

/*
* Pré-Condição: requer um caminho (svg ou geo) contendo uma possivel extensao.
* Pós-Condição: retorna somente o nome do arquivo, retirando possivel caminho e a sua extensão.
*/
char* getFileNameWithoutPathAndExtension(char* fullFileName);

/*
* Pré-Condição: requer um TAD parametros, e a extensao de um arquivo de saida (svg ou txt).
* Pós-Condição: constroi o caminho de saida para uma arquivo de output do query, seja ele um svg ou txt. Esse caminho e retornado.
*/
char* buildQryOutputPath(Parameters Param, char* extension);

/*
* Pré-Condição: requer um TAD quadra, o centro e o raio de um circulo.
* Pós-Condição: retorna 1 se a quadra estiver inteiramente dentro do circulo, se nao, retorna 0;
*/
int isBlockInCircleRange(Info blockInfo, double x, double y, double radius);

/*
* Pré-Condição: requer um TAD que seja um elemento urbano e o tipo desse elemento.
* Pós-Condição: retorna a string que informa todas as informacoes do elemento urbano passado.
*/
char* getUrbanElementToString(Info urbanElementInfo, char* urbanElementType);

#endif 