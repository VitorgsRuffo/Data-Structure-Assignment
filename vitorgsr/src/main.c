#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"
#include "geo.h"
#include "qry.h"


void freeMemory(FILE *geo, Parameter *parameter);
void freeQryMemory(FILE *qry, Parameter *parameter);


int main (int argc, char* argv[]){

    Parameter parameter;
    

    deal_with_parameters(argc, argv, &parameter);

    
    //se um diretorio de entrada não for especificado, usaremos o diretorio atual:
    if(parameter.inputDir == NULL){ 
        parameter.inputDir = (char*) malloc(3 * sizeof(char));     
        strcpy(parameter.inputDir, "./");  
    }

    //abrindo o aquivo .geo:
        FILE *geo = NULL; 

        buildGeoPath(&parameter);
        
        geo = fopen(parameter.geoFullPath, "r");

        if(geo == NULL){
            printf("Error: It was not possible to open .geo file.\nFinishing the program..\n");
            exit(1);
        }else{
            printf("Success opening .geo..");
        }


    //Abrindo o arquivo .qry (se especificado):
        FILE *qry = NULL;

        if(parameter.qryFileName != NULL){

            buildQryPath(&parameter);

            qry = fopen(parameter.qryFullPath, "r");

            if(qry == NULL){
                printf("Error: It was not possible to open .qry file.\nFinishing the program..\n");
                exit(1);
            }else{
                printf("Success opening .qry..");
            }
            
        }




    

    

            



    freeMemory(geo, &parameter);

    if(qry != NULL){
        freeQryMemory(qry, &parameter);
    }

    return 0;
}


void freeMemory(FILE *geo, Parameter *parameter){
    
    free(parameter->inputDir);
    free(parameter->geoFileName);
    
    free(parameter->outputDir);

    free(parameter->geoFullPath);

    fclose(geo);

}

void freeQryMemory(FILE *qry, Parameter *parameter){

    free(parameter->qryFileName);
    free(parameter->qryFullPath);

    fclose(qry);
}

