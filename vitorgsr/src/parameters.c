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

            //A proxima string vai ser o caminho para o diretório base de entrada:
            ++i;

            //Alocando memória para guardar a string referente ao nome diretório base de entrada:
            parameter->inputDir = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char));
            //obs: o +1 serve para garantirmos um lugar para o character nulo (i.e, '\0') no final da string.
            
            strcpy(parameter->inputDir, parameters[i]);

        }else if(strcmp("-f", parameters[i]) == 0){
            
            //A proxima string vai ser o nome do arquivo .geo:
            ++i;

            //Alocando memória para guardar a string referente ao nome do arquivo .geo:
            parameter->geoFileName = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char));

            strcpy(parameter->geoFileName, parameters[i]);

        }else if(strcmp("-q", parameters[i]) == 0){

            //A proxima string vai ser o nome do arquivo .qry:
            ++i;

            // ''    ''    ''
            parameter->qryFileName = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char)); 

            strcpy(parameter->qryFileName, parameters[i]);

        }else if(strcmp("-o", parameters[i]) == 0){

            //A proxima string vai ser o nome do diretorio de arquivos de saida:
            ++i;

            // ''    ''   ''
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

    printf("%s\n%s\n%s\n%s\n", parameter->inputDir, parameter->geoFileName, parameter->qryFileName, parameter->outputDir);

}