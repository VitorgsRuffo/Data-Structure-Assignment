#ifndef READINPUT_H
#define READINPUT_H

#include "../drawing/drawing.h"

/*  
* Pré-Condição: requer um arquivo de entrada geo e uma variavel do tipo desenho.
* Pós-Condição: percorre o arquivo geo lendo comandos. Ao ler um comando adiciona na lista apropriada um objeto que corresponda áquele comando.
*/
void readGeo(File geo, Drawing Dr);


#endif