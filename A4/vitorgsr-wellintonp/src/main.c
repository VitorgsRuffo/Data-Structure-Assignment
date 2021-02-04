#include "./include/headers.h"
#include "./include/util.h"
#include "./drawing/drawing.h"
#include "./query/qry.h"

/*to do list:

    0 - determinar tamanho da hashtable.
    1 - mudar drawing (-> city) ao longo do trabalho.
    3 - criar funcao para executar pintura das sombras das quadras (comando dd).

    4 - inserir novos tads nas estruturas.
    5 - planejamento para o query.

*/



int main(int argc, char* argv[]){
    
    //Criando o TAD parametros e obtendo os parametros de execução do programa.
    Parameters parameters = createParameters();
    setParameters(parameters, argv, argc);

    //Abrindo o arquivo de entrada (.geo)
    File geo = openInputFile(parameters, getGeoName);

    //Criando o TAD desenho:
    Drawing drawing = createDrawing();

    //Lendo o arquivo geo:
    readGeo(geo, drawing);
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
    geoSvg = createSvg(parameters, drawing, "geo");
    if(geoSvg != NULL){
        drawOnSvg(geoSvg, drawing);
        finishSvg(geoSvg);
    }

    
    if(!isQryNull(parameters)){
        //Abrindo o arquivo de entrada (.qry)
        File qry = openInputFile(parameters, "qry");

        //Lendo o arquivo qry e executando os comandos:
        executeQry(qry, drawing, parameters);
        closeInputFile(qry);

        //Criando SVG do qry:
        Svg qrySvg = NULL;
        qrySvg = createSvg(parameters, drawing, "qry");
        if(qrySvg != NULL){
            drawOnSvg(qrySvg, drawing);
            finishSvg(qrySvg);
        }
    }
    
    freeParameters(parameters);
    freeDrawing(drawing);
    return 0;
}

/*EXTRAS:

*  - Revisar os queries em busca de refatoracao. 
*  - Desalocar memoria em caso de erros (e.g, chamar o metodo de um tad passando null).
*  - Retirar mensagens de erro... (tratar erro no metodo chamador)
*  - Calcular a viewBox dos svg's.
*/