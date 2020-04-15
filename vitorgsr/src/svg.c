#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parameters.h"

void svg_set_view_box(float* X, float* Y, float* W, float* H, char* commands[][8], int geo_lines_count){

    float commX, commY;
    float commRadius; float commW, commH; 

    float largerW = 0, largerH = 0;
    
    for(int i = 0; i<geo_lines_count; ++i){

        if(commands[i][0][0] == 'c'){ // r 2  x 3  y 4

            commRadius = strtof(commands[i][2], NULL);
            commX = strtof(commands[i][3], NULL);
            commY = strtof(commands[i][4], NULL);

            if(commX - commRadius < *X ){
                *X = commX - commRadius ;
            }

            if(commY - commRadius < *Y ){ 
                *Y = commY - commRadius;
            }

            if(commX + commRadius > largerW ){
                largerW = commX + commRadius;

            }

            if(commY + commRadius > largerH){
                largerH = commY + commRadius;
            }
            
        }else if(commands[i][0][0] == 'r'){ // w 2 h 3 x 4 y 5

            commW = strtof(commands[i][2], NULL);
            commH = strtof(commands[i][3], NULL);
            commX = strtof(commands[i][4], NULL);
            commY = strtof(commands[i][5], NULL);         
        
            if(commX < *X){
                *X = commX;
            }

            if(commY < *Y){ 
                *Y = commY;
            }

            if(commX + commW > largerW){
                largerW = commX + commW;
            }

            if(commY + commH > largerH){
                largerH = commY + commH;
            }

        }else if(commands[i][0][0] == 't'){ //x 2 y 3
            
            commX = strtof(commands[i][2], NULL);
            commY = strtof(commands[i][3], NULL);

            if(commX < *X){ 
                *X = commX;
            }

            if(commY < *Y){ 
                *Y = commY;
            }

            largerW = 500; largerH = 500;
        }
    }

    *X -= 50;  *Y -= 50;
   
    *W = largerW + (-1*(*X)) + 50;   *H = largerH + (-1*(*Y)) + 50;
}

void svg_append_content_to_final_document(char* content, char* *finalDocument){
   
    strcat(*finalDocument, content);
}

void getFileName(char* fileName, int fileNameLen, char* *fileFinalName, int stopAtDot){
    
    int j = 0;

    for(int i = 0; i<fileNameLen; ++i){  //REP2

        if(fileName[i] == '/'){
            j = i + 1;
        }

        if(fileName[i] == '.'){
            if(stopAtDot)
                fileName[i] = ' ';

            sscanf(&fileName[j],"%s", *fileFinalName);

            fileName[i] = '.';
            
            break;
        }
    }
}

void buildSvgPath(Parameter *parameter){ //erros de path se a opção -f tiver um diretorio ou + antes do arquivo geo.

    int outputDirLen = strlen(parameter->outputDir);

    int geoFileNameLen = strlen(parameter->geoFileName);

    char* geoFileName = (char*) malloc((geoFileNameLen + 1) * sizeof(char));
    
    //Ha a possibilidade de o nome do arquivo geo for um caminho relativo (e.g, testes/g.geo). O trecho de cod abaixo trata o problema que isso causa retornando apenas o nome do .geo.  
        getFileName(parameter->geoFileName, geoFileNameLen, &geoFileName, 0);

    int svgFileNameLen = strlen(geoFileName);

    char* svgFileName  = (char*) malloc((svgFileNameLen + 1) * sizeof(char));

    strcpy(svgFileName, geoFileName);

    int aux = 0;

    for(int i = 0; i<svgFileNameLen; ++i){

        if(svgFileName[i] == '.')
            aux = 1;

        if(aux){
            
            if(svgFileName[i] == 'g'){
                svgFileName[i] = 's';
            }else if(svgFileName[i] == 'e'){
                svgFileName[i] = 'v';
            }else if(svgFileName[i] == 'o'){
                svgFileName[i] = 'g';
            }
        }
    }
   
    parameter->svgFullPath = (char*) malloc((outputDirLen + svgFileNameLen + 2) * sizeof(char));

    if(parameter->outputDir[outputDirLen-1] == '/'){
        sprintf(parameter->svgFullPath, "%s%s", parameter->outputDir, svgFileName);
    }else{
        sprintf(parameter->svgFullPath, "%s/%s", parameter->outputDir, svgFileName);
    }

    free(svgFileName); free(geoFileName);
}

void buildSvgQryPath(Parameter *parameter){

    int outputDirLen = strlen(parameter->outputDir);

    int geoFileNameLen = strlen(parameter->geoFileName); 
    int qryFileNameLen = strlen(parameter->qryFileName);
    int svgQryFileNameLen = (geoFileNameLen + qryFileNameLen) + 5 - 8; // + 5 pois precisamos de espaço para o '-' e para '.svg'. //-8 pois estamos desconsiderando as substrings .geo e .qry

    char* geoFileName = (char*) malloc((geoFileNameLen + 1) * sizeof(char));
    char* qryFileName = (char*) malloc((qryFileNameLen + 1) * sizeof(char));

    //Ha a possibilidade de o nome do arquivo geo/qry for um caminho relativo (e.g, testes/g.geo). O trecho de cod abaixo trata o problema que isso causa retornando apenas o nome do .geo/.qry.
        getFileName(parameter->geoFileName, geoFileNameLen, &geoFileName, 1);
        getFileName(parameter->qryFileName, qryFileNameLen, &qryFileName, 1);

    char* svgQryFileName = (char*) malloc((svgQryFileNameLen + 1) * sizeof(char));
    sprintf(svgQryFileName, "%s-%s.svg", geoFileName, qryFileName);

    parameter->svgQryFullPath = (char*) malloc((outputDirLen + svgQryFileNameLen + 1) * sizeof(char));

    if(parameter->outputDir[outputDirLen-1] == '/'){

        sprintf(parameter->svgQryFullPath, "%s%s", parameter->outputDir, svgQryFileName);

    }else{

        sprintf(parameter->svgQryFullPath, "%s/%s", parameter->outputDir, svgQryFileName);
    }
    
    free(svgQryFileName); free(geoFileName); free(qryFileName);
}