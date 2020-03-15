#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"


void freeMemory(FILE *geo, FILE *qry, Parameter *parameter);


int main (int argc, char* argv[]){

    Parameter parameter;
    

    deal_with_parameters(argc, argv, &parameter);

    
    //se um diretorio de entrada não for especificado, usaremos o diretorio atual:
    if(parameter.inputDir == NULL){      
        parameter.inputDir = "./";  
    }
    

    //Abrir o arquivo .geo:

        parameter.geoFullPath = NULL;
        int lenInDir = strlen(parameter.inputDir);
        int lenGeoName = strlen(parameter.geoFileName);

        parameter.geoFullPath = (char*) malloc((lenInDir + lenGeoName + 4) * sizeof(char));
        //obs: precisamos do '+2' para garantir espaço para o character nulo '\0' no final e
        //para um possivel charactere extra oriundo de um dos tratamentos de erro de path abaixo.

        //Tratando possiveis erros de path:
            
            //corrige o seguinte erro:  /home/ed/testes001.geo
            if((parameter.inputDir[lenInDir-1] != '/') && (parameter.geoFileName[0] != '/')
                && (parameter.geoFileName[0] != '.') ){

                sprintf(parameter.geoFullPath, "%s/%s", parameter.inputDir, parameter.geoFileName);


            //corrige o seguinte erro: /home/ed/testes./001.geo
            }else if((parameter.inputDir[lenInDir-1] != '/') && (parameter.geoFileName[0] == '.')){ 

                sprintf(parameter.geoFullPath, "%s/%s", parameter.inputDir, parameter.geoFileName);


            //corrige o seguinte erro: /home/ed/testes//001.geo
            }else if((parameter.inputDir[lenInDir-1] == '/') && (parameter.geoFileName[0] == '/')){

                sprintf(parameter.geoFullPath, "%s.%s", parameter.inputDir, parameter.geoFileName);

            //caso o path seja inserido corretamente:
            }else{
                sprintf(parameter.geoFullPath, "%s%s", parameter.inputDir, parameter.geoFileName);
            }

        FILE *geo;

        geo = fopen(parameter.geoFullPath, "r");

        printf("\n%s\n", parameter.geoFullPath);

        if(geo == NULL){
            printf("Error: It was not possible to open .geo file.\nFinishing the program..\n");
            exit(1);
        }else{
            printf("Success opening .geo..");
        }

    //Abrir o arquivo .qry (se especificado):

        FILE *qry;

        if(parameter.qryFileName != NULL){

            parameter.qryFullPath = NULL;
            int lenQryName = strlen(parameter.qryFileName);

            parameter.qryFullPath = (char*) malloc((lenInDir + lenQryName + 2) * sizeof(char));
            //obs: precisamos do '+2' para garantir espaço para o character nulo '\0' no final e
            //para um possivel charactere extra oriundo de um dos tratamentos de erro de path abaixo.


            //Tratando possiveis erros de path:

                //corrige o seguinte erro:  /home/ed/testes001.qry
                if((parameter.inputDir[lenInDir-1] != '/') && (parameter.qryFileName[0] != '/')
                    && (parameter.qryFileName[0] != '.') ){

                    sprintf(parameter.qryFullPath, "%s/%s", parameter.inputDir, parameter.qryFileName);


                //corrige o seguinte erro: /home/ed/testes./001.qry
                }else if((parameter.inputDir[lenInDir-1] != '/') && (parameter.qryFileName[0] == '.')){ 

                    sprintf(parameter.qryFullPath, "%s/%s", parameter.inputDir, parameter.qryFileName);


                //corrige o seguinte erro: /home/ed/testes//001.qry
                }else if((parameter.inputDir[lenInDir-1] == '/') && (parameter.qryFileName[0] == '/')){

                    sprintf(parameter.qryFullPath, "%s.%s", parameter.inputDir, parameter.qryFileName);

                //caso o path seja inserido corretamente:
                }else{
                    sprintf(parameter.qryFullPath, "%s%s", parameter.inputDir, parameter.qryFileName);
                }


            qry = fopen(parameter.qryFullPath, "r");

            printf("\n%s\n", parameter.qryFullPath);

            if(qry == NULL){
                printf("Error: It was not possible to open .qry file.\nFinishing the program..\n");
                exit(1);
            }else{
                printf("Success opening .qry..");
            }

        }

        
        







    //freeMemory(geo, qry, &parameter);

    return 0;
}


void freeMemory(FILE *geo, FILE *qry, Parameter *parameter){

    free(parameter->inputDir);
    free(parameter->geoFileName);
    free(parameter->qryFileName);
    free(parameter->outputDir);

    free(parameter->geoFullPath);
    free(parameter->qryFullPath);

    fclose(geo);
    fclose(qry);

}

