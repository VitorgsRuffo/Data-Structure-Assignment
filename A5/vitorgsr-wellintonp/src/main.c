#include "./include/headers.h"
#include "./elements/urban-elements/city.h"
#include "./include/util.h"
//#include "./elements/urban-elements/street.h"

/* To do list:

    - queries dos registradores.

    - demais queries.
    - atualizar soc.
    
*/

int main(int argc, char* argv[]){
    
    //Criando o TAD parametros e obtendo os parametros de execução do programa.
    Parameters parameters = createParameters();
    setParameters(parameters, argv, argc);

    //Criando o TAD cidade:
    City city = createCity();


    //Abrindo o arquivo de entrada (.geo)
    File geo = openInputFile(parameters, getGeoName);
    if(geo == NULL){
        printf("Erro: nao foi possivel abrir o arquivo .geo\n");
        return 1;
    }
    
    //Lendo o arquivo .geo:
    readGeo(geo, city);
    closeInputFile(geo);
    

    //Lendo e abrindo arquivos de entrada extras:
    if(!isEcNull(parameters)){
        //Abrindo o arquivo de entrada (.ec)
        File ec = openInputFile(parameters, getEcName);
       
        //Lendo arquivo ec:
        readEc(ec, city);
        closeInputFile(ec);
    }

    if(!isPmNull(parameters)){
        //Abrindo o arquivo de entrada (.pm)
        File pm = openInputFile(parameters, getPmName);
    
        //Lendo arquivo pm:
        readPm(pm, city);
        closeInputFile(pm);
    }

    if(!isViaNull(parameters)){
        //Abrindo o arquivo de entrada (.via)
        File via = openInputFile(parameters, getViaName);
    
        //Lendo arquivo via:
        readVia(via, city);
        closeInputFile(via);
    }

    //printGraph(getRoadSystem(city), printPoint, printStreet);
    //getchar();

    //Criando SVG do geo:
    Svg geoSvg = NULL;
    geoSvg = createSvg(parameters, city, "geo", NULL);
    if(geoSvg != NULL){
        drawOnSvg(geoSvg, city);
        finishSvg(geoSvg);
    }

    
    if(!isQryNull(parameters)){
        //Abrindo o arquivo de entrada (.qry)
        File qry = openInputFile(parameters, getQryName);

        //Lendo o arquivo qry e executando os comandos:
        executeQry(qry, city, parameters);
        closeInputFile(qry);

        //Criando SVG do qry:
        Svg qrySvg = NULL;
        qrySvg = createSvg(parameters, city, "qry", NULL);   
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

    - Revisar os queries em busca de refatoracao. 
    - Desalocar memoria em caso de erros (e.g, chamar o metodo de um tad passando null).
    - pquadtree:
        //1 - fix getObjectIfItsInsideShape. (we should not traverse the whole tree!!).
        
        //2 - is our current remove method maintaining the tree balanced? .
*/