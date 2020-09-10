#ifndef OPENINPUT_H
#define OPENINPUT_H

/*
* Definindo um ponteiro para arquivo.
*/
typedef FILE* File;

/*
* Pré-Condição: requer objeto com os argumentos recebidos no terminal e tipo do arquivo a ser aberto 
* Pós-Condição: retorna uma referencia para o arquivo de entrada que foi aberto.
*/
File openInputFile(Parameters Param, char* fileType);

/*
* Pré-Condição: requer uma referencia para um arquivo aberto.
* Pós-Condição: fecha o arquivo recebido como parametro.
*/
void closeInputFile(File file);

#endif