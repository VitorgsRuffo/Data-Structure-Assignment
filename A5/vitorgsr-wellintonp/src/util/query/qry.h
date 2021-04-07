#ifndef QRY_H
#define QRY_H

#include "../../include/util.h"

/*
* apontador para o inicio de uma string. Ela sera uma tag proveniente de um dos comandos de query e posteriormente sera adicionada em uma lista propria)
*/
typedef void* QueryElement; 

/*
* Pré-Condição: requer um arquivo de entrada query, a referencia para uma instancia de cidade e a referencia para uma instancia de Parametros.
* Pós-Condição: percorre o arquivo query, interpretando cada comando e executando-o. O tad cidade sera alterado com o resultado dos comandos query. Um arquivo txt sera criado para mostrar esses resultados de maneira textual.
*/
void executeQry(File qry, City Ct, Parameters Param);

/*
* Pré-Condição: requer um ponteiro para o inicio de uma tag (string) proveniente de uma consulta.
* Pós-Condição: libera a memoria usada pela string passada.
*/
void freeQueryElement(QueryElement queryElement);

#endif