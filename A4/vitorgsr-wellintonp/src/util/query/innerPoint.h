#ifndef INNER_POINT_H
#define INNER_POINT_H

/*
* Pré-Condição: requer uma referencia para a string do comando i?, uma referencia para uma instancia do TAD desenho e um arquivo txt.
* Pós-Condição: testa se o ponto especificadas no commando passado é interno a figura tambem no comando, 
*               cria e salva uma tag de um ponto e de uma linha que vai do ponto criado até centro de massa da figura e escreve o resultado no arquivo txt.
*/
void executeInnerPointTest(char* command, Drawing Dr, File txt);

#endif