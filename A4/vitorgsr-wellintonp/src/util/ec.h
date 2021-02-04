#ifndef EC_H
#define EC_H

#include "../drawing/drawing.h"

/*  
* Pré-Condição: requer um arquivo de entrada ec e uma variavel do tipo desenho.
* Pós-Condição: percorre o arquivo ec lendo comandos. Ao ler um comando adiciona na estrutura de dados apropriada um objeto que corresponda áquele comando.
*/
void readEc(File ec, Drawing Dr);


#endif