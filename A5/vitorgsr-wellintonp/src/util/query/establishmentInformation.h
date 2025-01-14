#ifndef ESTABLISMENT_INFORMATION_H
#define ESTABLISMENT_INFORMATION_H

#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

/*
* Pré-Condição: requer uma referencia para a string do comando de?, uma referencia para uma instancia do TAD desenho, um arquivo txt.
* Pós-Condição: Printa no txt as informacoes do estabelecimento comercial referente ao cnpj lido do arquivo de entrada e do seu proprietário. 
*/
void executeEstablishmentInformationChecking(char* command, City Ct, File txt);

#endif