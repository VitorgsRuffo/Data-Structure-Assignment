#ifndef PM_H
#define PM_H

#include "../drawing/drawing.h"

/*  
* Pré-Condição: requer um arquivo de entrada pm e uma variavel do tipo desenho.
* Pós-Condição: percorre o arquivo pm lendo comandos. Ao ler um comando adiciona na estrutura de dados apropriada um objeto que corresponda áquele comando.
*/
void readPm(File ec, Drawing Dr);


#endif