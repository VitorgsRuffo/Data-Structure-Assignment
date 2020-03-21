#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"

int buildQryPath(Parameter *parameter, FILE *qry){

    parameter->qryFullPath = NULL;

    int lenInDir = strlen(parameter->inputDir);
    int lenQryName = strlen(parameter->qryFileName);

    //printf("%d %d", lenInDir, lenQryName);

    parameter->qryFullPath = (char*) malloc((lenInDir + lenQryName + 2) * sizeof(char));
    //obs: precisamos do '+2' para garantir espaço para o character nulo '\0' no final e
    //para um possivel charactere extra oriundo de um dos tratamentos de erro de path abaixo.


    //Tratando possiveis erros de path:

        //corrige o seguinte erro:  /home/ed/testes001.qry
        if((parameter->inputDir[lenInDir-1] != '/') && (parameter->qryFileName[0] != '/')
            && (parameter->qryFileName[0] != '.') ){

            sprintf(parameter->qryFullPath, "%s/%s", parameter->inputDir, parameter->qryFileName);

        //corrige o seguinte erro: /home/ed/testes./001.qry
        }else if((parameter->inputDir[lenInDir-1] != '/') && (parameter->qryFileName[0] == '.')){ 

            sprintf(parameter->qryFullPath, "%s/%s", parameter->inputDir, parameter->qryFileName);

        //corrige o seguinte erro: /home/ed/testes//001.qry
        }else if((parameter->inputDir[lenInDir-1] == '/') && (parameter->qryFileName[0] == '/')){

            sprintf(parameter->qryFullPath, "%s.%s", parameter->inputDir, parameter->qryFileName);

        //caso o path seja inserido corretamente:
        }else{
            sprintf(parameter->qryFullPath, "%s%s", parameter->inputDir, parameter->qryFileName);
        }

    
    printf("\n%s\n", parameter->qryFullPath);

}