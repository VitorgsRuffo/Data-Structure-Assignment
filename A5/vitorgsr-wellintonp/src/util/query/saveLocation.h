#ifndef SAVE_LOCATION_H
#define SAVE_LOCATION_H

/*
* Pré-Condição: requer uma referencia para a string do comando de salvar localizacao @xy, uma referencia para uma instancia do TAD cidade e um arquivo txt.
* Pós-Condição: salva a localizacao especificada no comando no tad cidade. 
*/
void saveLocation(char* command, City Ct);

/*
* Pré-Condição: requer uma referencia para a string do comando de salvar localizacao @g?, uma referencia para uma instancia do TAD cidade e um arquivo txt.
* Pós-Condição: salva a localizacao do equipamento especificado no comando no tad cidade. 
*/
void saveUrbanEquipmentLocation(char* command, City Ct);

#endif