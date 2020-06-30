#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parameters.h"

void deal_with_parameters(int paraNum, char* parameters[], Parameter *parameter){

    int i = 1;

    parameter->inputDir = NULL;
    parameter->geoFileName = NULL;
    parameter->qryFileName = NULL;
    parameter->outputDir = NULL;

    while(i < paraNum){

        if(strcmp("-e", parameters[i]) == 0){

            ++i; //A proxima string vai ser o caminho para o diretório base de entrada:

            //Alocando memória para guardar a string referente ao nome diretório base de entrada:
            parameter->inputDir = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char));
            //obs: o +1 serve para garantirmos um lugar para o character nulo (i.e, '\0') no final da string.
            
            strcpy(parameter->inputDir, parameters[i]);

        }else if(strcmp("-f", parameters[i]) == 0){
            
            ++i; //A proxima string vai ser o nome do arquivo .geo:

            //Alocando memória para guardar a string referente ao nome do arquivo .geo:
            parameter->geoFileName = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char));
            strcpy(parameter->geoFileName, parameters[i]);

        }else if(strcmp("-q", parameters[i]) == 0){

            ++i;  //A proxima string vai ser o nome do arquivo .qry:

            parameter->qryFileName = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char)); 
            strcpy(parameter->qryFileName, parameters[i]);

        }else if(strcmp("-o", parameters[i]) == 0){

            ++i;  //A proxima string vai ser o nome do diretorio de arquivos de saida:

            parameter->outputDir = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char)); 
            strcpy(parameter->outputDir, parameters[i]);
        }

        i++;
    }

    //se um diretorio de entrada não for especificado, usaremos o diretorio atual:
    if(parameter->inputDir == NULL){ 
        parameter->inputDir = (char*) malloc(3 * sizeof(char));     
        strcpy(parameter->inputDir, "./");  
    }
}

void buildInputFilePath(Parameter *parameter, char* which){

    int lenInDir = strlen(parameter->inputDir);
    char* inputFileName;
    int lenInputFileName;

    if(strcmp(which, "geo") == 0){ //building geo full path
        lenInputFileName = strlen(parameter->geoFileName);
        inputFileName = (char*) malloc((lenInputFileName + 1) * sizeof(char));
        strcpy(inputFileName, parameter->geoFileName);

    }else if(strcmp(which, "qry") == 0){//building qry full path

        lenInputFileName = strlen(parameter->qryFileName);
        inputFileName = (char*) malloc((lenInputFileName + 1) * sizeof(char));
        strcpy(inputFileName, parameter->qryFileName);

    }

    char* inputFileFullPath = (char*) malloc((lenInDir + lenInputFileName + 2) * sizeof(char)); //obs: precisamos do '+2' para garantir espaço para o character nulo '\0' no final e para um possivel charactere extra oriundo de um dos tratamentos de erro de path abaixo.

    //Tratando possiveis erros de path:
            
        if((parameter->inputDir[lenInDir-1] != '/') && (inputFileName[0] != '/') //corrige o seguinte erro:  /home/ed/testes001.geo
            && (inputFileName[0] != '.') ){

            sprintf(inputFileFullPath, "%s/%s", parameter->inputDir, inputFileName);

        }else if((parameter->inputDir[lenInDir-1] != '/') && (inputFileName[0] == '.')){ //corrige o seguinte erro: /home/ed/testes./001.geo

            sprintf(inputFileFullPath, "%s/%s", parameter->inputDir, inputFileName);

        }else if((parameter->inputDir[lenInDir-1] == '/') && (inputFileName[0] == '/')){  //corrige o seguinte erro: /home/ed/testes//001.geo

            sprintf(inputFileFullPath, "%s.%s", parameter->inputDir, inputFileName);

        }else{ //caso o path seja inserido corretamente:
            sprintf(inputFileFullPath, "%s%s", parameter->inputDir, inputFileName);
        }

    if(strcmp(which, "geo") == 0){
        parameter->geoFullPath = inputFileFullPath;
    }else if(strcmp(which, "qry") == 0){
        parameter->qryFullPath = inputFileFullPath;
    }
        
    free(inputFileName);    
}