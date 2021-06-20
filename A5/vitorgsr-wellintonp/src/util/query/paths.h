#ifndef PATH_H
#define PATH_H

#include "../svg.h"
#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

/*
*  Executa comandos p? e sp?. Calcula o trajeto mais curto e o mais rapido entre a origem "r1" e o destino "r2". Caso esse seja um comando sp? (isSecure == 1) o trajeto evita toda a regiao com casos de covid.
*  Ambos os trajetos sao representados em um novo svg com as cores indicadas no comando e uma descrição textual dos trajetos é escrita no .txt.
*/
void findBestCarPath(int isSecure, int pathId, Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt);

/*
* Calcula o menor percurso das ciclovias partindo de r1 até r2 utilizando uma arvore geradora minima existente.
* Caso nao tenha uma arvore geradora minima ja criada, a funcao apenas printa essa ocorrencia no txt e faz o retorno.
* Apos fazer o calculo, faz uma descricao textual no txt e traça linhas no svg demarcando todo o trajeto.
*/
void findBestBikePath(int pathId, Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt);

#endif