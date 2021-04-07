#ifndef OVERLAP_H
#define OVERLAP_H

/*
* Pré-Condição: requer uma referencia para a string do comando o?, uma referencia para uma instancia do TAD desenho e um arquivo txt.
* Pós-Condição: testa se as duas figuras especificadas no commando passado se sobrepoem, cria e salva uma tag de retangulo que envolvera as figuras e escreve o resultado no arquivo txt.
*/
void executeOverlapTest(char* command, City Ct, File txt);

#endif