#ifndef PM_H
#define PM_H

#include "../../elements/urban-elements/city.h"

/*  
* Pré-Condição: requer um arquivo de entrada pm e uma variavel do tipo cidade.
* Pós-Condição: percorre o arquivo pm lendo comandos. Ao ler um comando adiciona na estrutura de dados apropriada um objeto que corresponda aquele comando.
*/
void readPm(File ec, City Ct);


#endif