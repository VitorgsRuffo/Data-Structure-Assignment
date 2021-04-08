#ifndef VIA_H
#define VIA_H

#include "../../elements/urban-elements/city.h"
#include "./openInput.h"

/*  
* Pré-Condição: requer um arquivo de entrada via e uma variavel do tipo cidade.
* Pós-Condição: percorre o arquivo via lendo comandos. Ao ler um comando adiciona na estrutura de dados apropriada um objeto que corresponda aquele comando.
*/
void readVia(File via, City Ct);


#endif