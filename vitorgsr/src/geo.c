#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"

void buildGeoPath(Parameter *parameter){

    parameter->geoFullPath = NULL;

    int lenInDir = strlen(parameter->inputDir);
    int lenGeoName = strlen(parameter->geoFileName);

    //printf("%d %d", lenInDir, lenGeoName);

    parameter->geoFullPath = (char*) malloc((lenInDir + lenGeoName + 10) * sizeof(char));
    //obs: precisamos do '+2' para garantir espaço para o character nulo '\0' no final e
    //para um possivel charactere extra oriundo de um dos tratamentos de erro de path abaixo.

    //Tratando possiveis erros de path:
            
        //corrige o seguinte erro:  /home/ed/testes001.geo
        if((parameter->inputDir[lenInDir-1] != '/') && (parameter->geoFileName[0] != '/')
            && (parameter->geoFileName[0] != '.') ){

            sprintf(parameter->geoFullPath, "%s/%s", parameter->inputDir, parameter->geoFileName);


        //corrige o seguinte erro: /home/ed/testes./001.geo
        }else if((parameter->inputDir[lenInDir-1] != '/') && (parameter->geoFileName[0] == '.')){ 

            sprintf(parameter->geoFullPath, "%s/%s", parameter->inputDir, parameter->geoFileName);


        //corrige o seguinte erro: /home/ed/testes//001.geo
        }else if((parameter->inputDir[lenInDir-1] == '/') && (parameter->geoFileName[0] == '/')){

            sprintf(parameter->geoFullPath, "%s.%s", parameter->inputDir, parameter->geoFileName);

        //caso o path seja inserido corretamente:
        }else{
            sprintf(parameter->geoFullPath, "%s%s", parameter->inputDir, parameter->geoFileName);
        }

    printf("\n%s\n", parameter->geoFullPath);    

}