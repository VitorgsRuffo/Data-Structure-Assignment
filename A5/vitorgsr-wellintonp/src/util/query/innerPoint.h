#ifndef INNER_POINT_H
#define INNER_POINT_H

/*
* Pré-Condição: requer uma referencia para a string do comando i?, uma referencia para uma instancia do TAD cidade e um arquivo txt.
* Pós-Condição: testa se o ponto é interno a figura cujo indice é j (ambos estao especificados no comando).
*               cria e salva uma tag de um ponto e de uma linha que vai do ponto criado até centro de massa da figura e escreve o resultado no arquivo txt.
*/
void executeInnerPointTest(char* command, City Ct, File txt);

#endif