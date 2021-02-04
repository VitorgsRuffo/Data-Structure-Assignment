#ifndef URBAN_DELETION_H
#define URBAN_DELETION_H

/*
* Pré-Condição: requer uma referencia para a string do comando del, uma referencia para uma instancia do TAD desenho e um arquivo txt.
* Pós-Condição: deleta o elemento urbano cujo id/cep foi especificado no comando.
*/
void executeUrbanElementDeletion(char* command, Drawing Dr, File txt);

#endif