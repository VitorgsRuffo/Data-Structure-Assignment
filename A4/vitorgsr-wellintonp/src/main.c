#include "./include/headers.h"
#include "./include/util.h"
#include "./elements/urban-elements/city.h"


/*to do list:

    - erros de include.
    - corrigir funcoes de overlap.

    - criar funcao para executar pintura das sombras das quadras (comando dd).
    - inserir novos tads nas estruturas. (como organizar as hashs)

    - planejamento para o query.
    - corrigir covidIncidence.c
*/



int main(int argc, char* argv[]){
    
    //Criando o TAD parametros e obtendo os parametros de execução do programa.
    Parameters parameters = createParameters();
    setParameters(parameters, argv, argc);

    //Abrindo o arquivo de entrada (.geo)
    File geo = openInputFile(parameters, getGeoName);

    //Criando o TAD cidade:
    City city = createCity();

    //Lendo o arquivo geo:
    readGeo(geo, city);
    closeInputFile(geo);
    
    if(!isEcNull(parameters)){
        //Abrindo o arquivo de entrada (.ec)
        File ec = openInputFile(parameters, getEcName);


        //Lendo arquivo ec:
    }

    if(!isPmNull(parameters)){
        //Abrindo o arquivo de entrada (.pm)
        File ec = openInputFile(parameters, getPmName);

        //Lendo arquivo pm:
    }


    //Criando SVG do geo:
    Svg geoSvg = NULL;
    geoSvg = createSvg(parameters, city, "geo");
    if(geoSvg != NULL){
        drawOnSvg(geoSvg, city);
        finishSvg(geoSvg);
    }

    
    if(!isQryNull(parameters)){
        //Abrindo o arquivo de entrada (.qry)
        File qry = openInputFile(parameters, "qry");

        //Lendo o arquivo qry e executando os comandos:
        executeQry(qry, city, parameters);
        closeInputFile(qry);

        //Criando SVG do qry:
        Svg qrySvg = NULL;
        qrySvg = createSvg(parameters, city, "qry");
        if(qrySvg != NULL){
            drawOnSvg(qrySvg, city);
            finishSvg(qrySvg);
        }
    }
    
    freeParameters(parameters);
    freeCity(city);
    return 0;
}

/*EXTRAS:

*  - Revisar os queries em busca de refatoracao. 
*  - Desalocar memoria em caso de erros (e.g, chamar o metodo de um tad passando null).
*  - Retirar mensagens de erro... (tratar erro no metodo chamador)
*  - Calcular a viewBox dos svg's.
*/