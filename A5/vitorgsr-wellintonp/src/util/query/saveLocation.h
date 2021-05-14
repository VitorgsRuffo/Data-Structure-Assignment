#ifndef SAVE_LOCATION_H
#define SAVE_LOCATION_H

/*
* Pré-Condição: requer uma referencia para a string do comando de salvar localizacao @m?, uma referencia para uma instancia do TAD cidade.
* Pós-Condição: salva a localizacao da casa/estabelecimento comercial (cujo morador/proprietario seja dono do cpf do paramtro) no tad cidade. 
*/
void saveLocationByCpf(char* command, City Ct);

/*
* Pré-Condição: requer uma referencia para a string do comando de salvar localizacao @e?, uma referencia para uma instancia do TAD cidade.
* Pós-Condição: salva a localizacao do endereco especificado no tad cidade. 
*/
void saveLocationByAddress(char* command, City Ct);

/*
* Pré-Condição: requer uma referencia para a string do comando de salvar localizacao @g?, uma referencia para uma instancia do TAD cidade.
* Pós-Condição: salva a localizacao do equipamento especificado no comando no tad cidade. 
*/
void saveUrbanEquipmentLocation(char* command, City Ct);

/*
* Pré-Condição: requer uma referencia para a string do comando de salvar localizacao @xy, uma referencia para uma instancia do TAD cidade.
* Pós-Condição: salva a localizacao especificada no comando no tad cidade. 
*/
void saveLocation(char* command, City Ct);


#endif