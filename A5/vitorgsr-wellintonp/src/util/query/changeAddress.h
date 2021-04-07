#ifndef CHANGE_ADDRESS_H
#define CHANGE_ADDRESS_H

#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

/*
* Pré-Condição: requer uma referencia para a string do comando cbq, uma referencia para uma instancia do TAD cidade, um arquivo txt. 
* Pós-Condição: Altera o endereço da pessoa identificada pelo cpf para o endereço do parametro passado, printa os endereços (tanto antigo quanto o novo) no txt, desenha uma linha do endereço antigo ao endereço novo e desenha alguns circulos em ambos os endereços.
*/
void executeChangeOfAddress(char* command, City Ct, File txt);

#endif