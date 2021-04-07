#ifndef BLOCK_RESIDENTS_H
#define BLOCK_RESIDENTS_H

#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

/*
* Pré condição: requer uma referencia para a string do comando m?, uma referencia para uma instancia do TAD cidade, um arquivo txt. 
* Pós condição: Insere no txt todas as informações dos moradores da quadra passada por parametro.
*/
void executeBlockResidentsReport(char* command, City Ct, File txt);

#endif