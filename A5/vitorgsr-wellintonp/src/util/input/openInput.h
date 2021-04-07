#ifndef OPENINPUT_H
#define OPENINPUT_H

#include "parameters.h"

/*
* Definindo um ponteiro para arquivo.
*/
typedef FILE* File;
typedef char* (*getParameterName)(Parameters);

/*
* Pré-Condição: requer objeto com os argumentos recebidos no terminal e uma funcao para pegar o nome do arquivo a ser aberto.
* Pós-Condição: retorna uma referencia para o arquivo de entrada que foi aberto.
*/
File openInputFile(Parameters Param, getParameterName get);

/*
* Pré-Condição: requer uma referencia para um arquivo aberto.
* Pós-Condição: fecha o arquivo recebido como parametro.
*/
void closeInputFile(File file);

#endif
