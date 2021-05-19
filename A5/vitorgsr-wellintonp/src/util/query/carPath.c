#include "../../include/headers.h"
#include "../svg.h"
#include "carPath.h"

void findBestCarPath(Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt){
    
    char sufix[20], r1[20], r2[20], cmc[20], cmr[20];
    sscanf(&command[3], "%s %s %s %s %s", sufix, r1, r2, cmc, cmr);

    //preparando svg para receber os resultados visuais:
    if(strcmp(sufix, "-") == 0)
        if(*minimumPaths == NULL)
            return;
    else{
        finishSvg(*minimumPaths);
        *minimumPaths = createSvg(Param, Ct, "qry", sufix);
    }

    // Pegar coordenadas de r1 e r2
    // Associar aos vertices mais proximos
    
    // Chamar dijkstra para calcular caminho mais curto
    // Chamar dijkstra para calcular caminho mais rapido


    //desenhando os resultados no svg:
    drawOnSvg(*minimumPaths, Ct);
    
}