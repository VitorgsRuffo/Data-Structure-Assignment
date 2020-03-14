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
        parameter.inputDir = "/current directory/";  //work on that later..
    }
    

    //Abrir o arquivo .geo:

        parameter.geoFullPath = NULL;

        parameter.geoFullPath = (char*) malloc((strlen(parameter.inputDir) + strlen(parameter.geoFileName) + 1) * sizeof(char));
        //obs: precisamos do '+1' para garantir espaço para o character nulo '\0' no final.

        sprintf(parameter.geoFullPath, "%s%s", parameter.inputDir, parameter.geoFileName);

        FILE *geo;

        geo = fopen(parameter.geoFullPath, "r");

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

            parameter.qryFullPath = (char*) malloc((strlen(parameter.inputDir) + strlen(parameter.qryFileName) + 1) * sizeof(char));
            //obs: precisamos do '+1' para garantir espaço para o character nulo '\0' no final.

            sprintf(parameter.qryFullPath, "%s%s", parameter.inputDir, parameter.qryFileName);

            qry = fopen(parameter.qryFullPath, "r");

            if(qry == NULL){
                printf("Error: It was not possible to open .qry file.\nFinishing the program..\n");
                exit(1);
            }else{
                printf("Success opening .qry..");
            }

        }

        
        







    freeMemory(geo, qry, &parameter);

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

