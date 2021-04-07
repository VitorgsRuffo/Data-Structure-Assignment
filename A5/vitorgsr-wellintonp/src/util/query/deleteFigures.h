#ifndef DELETE_FIGURES_H
#define DELETE_FIGURES_H

/*
* Pré-Condição: requer uma referencia para a string do comando delf, uma referencia para uma instancia do TAD cidade, um arquivo txt e o tipo do delete (delf ou delf*).
* Pós-Condição: deleta um elemento ou um conjunto de elementos de acordo com o(s) id(s) passado(s) no comando. No final escreve o resultado em um arquivo txt.
*/
void executeElementDeletion(char* command, City Ct, File txt, char* deletionType);

#endif