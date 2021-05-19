#ifndef ISOLATE_STREET_H
#define ISOLATE_STREET_H

#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"


/*
* Pré-Condição: requer uma referencia para a string do comando de isolar ruas (i.e, bf), uma referencia para uma instancia do TAD cidade e o arquivo de texto de saida.
* Pós-Condição: isola todas as ruas da cidade onde existem mais que max (especificado em bf) casos de covid em pelo menos uma das duas faces de quadra dessa rua. 
*/
void executeStreetIsolation(char* command, City Ct, File txt);


#endif