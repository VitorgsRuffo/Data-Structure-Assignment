#ifndef HIGHLIGHT_ESTABLISHMENT_H
#define HIGHLIGHT_ESTABLISHMENT_H

#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

/*
* Pré-Condição: requer uma referencia para a string do comando eplg?, uma referencia para uma instancia do TAD desenho, um arquivo txt.
* Pós-Condição: Printa no txt as informacoes dos estabelecimentos comerciais (incluindo nome do proprietário) que estão inteiramente dentro de uma regiao especificada pelo arquivo de entrada.
*/
void executeHighlightEstablishmentInRange(char* command, City Ct, File txt);


#endif