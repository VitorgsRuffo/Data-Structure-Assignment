#ifndef PERSONAL_INFOMATION_H
#define PERSONAL_INFOMATION_H

/*
* Pré-Condição: requer uma referencia para a string do comando dm?, uma referencia para uma instancia do TAD cidade e um arquivo txt.
* Pós-Condição: escreve no arquivo .txt todas as informacoes da pessoa cujo cpf é especificado no comando. Cria uma tag svg de uma linha que vai do endereço da pessoa até a parte superior do mapa (nessa extremidade tambem se encontram as infomacoes da pessoa).
*/
void executePersonalInformationChecking(char* command, City Ct, File txt);

#endif