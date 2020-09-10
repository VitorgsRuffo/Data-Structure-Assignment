#ifndef QRY_H
#define QRY_H

/*
* apontador para o inicio de uma string. Ela sera uma tag proveniente de um dos comandos de query e posteriormente sera adicionada em uma lista propria)
*/
typedef void* QueryElement; 

/*
* Pré-Condição: requer um arquivo de entrada query, a referencia para uma instancia de Desenho e a referencia para uma instancia de Parametros.
* Pós-Condição: percorre o arquivo query, interpretando cada comando e executando-o. O tad Desenho sera alterado com o resultado dos comandos query. Um arquivo txt sera criado para mostrar esses resultados de maneira textual.
*/
void executeQry(File qry, Drawing Dr, Parameters Param);

/*
* Pré-Condição: requer um ponteiro para o inicio de uma tag (string) proveniente de uma consulta.
* Pós-Condição: libera a memoria usada pela string passada.
*/
void freeQueryElement(QueryElement queryElement);

#endif