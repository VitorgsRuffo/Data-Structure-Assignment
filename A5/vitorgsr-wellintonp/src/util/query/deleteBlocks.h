#ifndef DELETE_BLOCKS_H
#define DELETE_BLOCKS_H

/*
* Pré-Condição: requer uma referencia para a string do comando dq, uma referencia para uma instancia do TAD desenho, um arquivo txt.
* Pós-Condição: deleta todas as quadras que estao dentro do raio de delicao especificado no comando. A cada delicao o resultado e escrito em um arquivo txt.
*/
void executeBlocksDeletion(char* command, City Ct, File txt);


#endif