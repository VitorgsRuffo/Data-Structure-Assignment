#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"
#include "geo.h"
#include "qry.h"
#include "svg.h"


void freeMemory(FILE *geo, FILE* qry, Parameter *parameter, char* *commands, int file_lines_count, char* svgFinalDocument, FILE* svg);

int count_file_lines(FILE *file);


int main (int argc, char* argv[]){

    Parameter parameter;
    

    deal_with_parameters(argc, argv, &parameter);


    //abrindo o aquivo .geo:
        FILE *geo = NULL; 

        buildGeoPath(&parameter);
        
        geo = fopen(parameter.geoFullPath, "r");

        if(geo == NULL){
            printf("Error: It was not possible to open .geo file.\nFinishing the program..\n");
            exit(1);
        }else{
            printf("Success opening .geo..\n");
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
                printf("Success opening .qry..\n");
            }
            
        }
    
    //Tratando o aquivo .geo:

        //precisamos contar quantas comandos (linhas) temos no arquivo de entrada .geo:
        int file_lines_count = count_file_lines(geo);

        printf(".geo commands(lines) number: %d\n", file_lines_count);
    
        //vetor de strings onde cada string é um comando lido do arquivo:
        char* commands[file_lines_count];
    
        for(int j = 0; j<file_lines_count; j++){
            commands[j] = (char*) malloc(110 * sizeof(char));  //Supomos que 110 == tamanho maximo de um comando (linha)

            if(commands[j] == NULL){
                printf("Error allocating memory for commands array.\nFinishing execution..\n");
                exit(1);
            }
        }

        //Lendo o arquivo:
        printf(".geo content:\n");

        int i = 0;
        int commandLen;

        while(!feof(geo)){
        
            if(fgets(commands[i], 110, geo)){

                //remover \n do final de cada comando:
                commandLen = strlen(commands[i]);

                commands[i][commandLen-1] = '\0';

                printf("%s\n", commands[i]);

                if(i < file_lines_count){
                    ++i;
                }

            }
        
        }


        //String que vai conter todas as tags referentes aos comandos do arquivo e que vai ser printada em um arquivo svg.
        char* svgFinalDocument = (char*) malloc((strlen("<svg></svg>") + 1) * sizeof(char));

        strcpy(svgFinalDocument, "<svg>");

        //Tratando um comando por vez: construir a tag relativa ao comando e anexa-la a string final.
        for(int j = 0; j<file_lines_count; ++j){

            switch(commands[j][0]){
                case 'c':
                    svg_draw(&commands[j], &svgFinalDocument, 7); 
                    break;
                case 'r':
                    svg_draw(&commands[j], &svgFinalDocument, 8);
                    break;
                case 't':
                    svg_draw(&commands[j], &svgFinalDocument, 7);
                    break;
                case 'n':
                    //svg_nx_command(commands[j);
                    break;
                default:
                    printf("%d.o command is invalid.\n", j + 1);
                    break;
            }
    
        }

        
        //Terminando a string para então podermos printa-la em um .svg:
        svg_finalize_final_document(&svgFinalDocument);


        //Criando .svg:
        FILE *svg;

        svg = fopen(parameter.outputDir, "w");
        if(svg == NULL){
            printf("Error: opening svg.\n");
        }

        fprintf(svg, "%s", svgFinalDocument);
    



    //Tratando o aquivo .qry (se necessario):





    //Liberando a memoria e finalizando o programa:

        freeMemory(geo, qry, &parameter, commands, file_lines_count, svgFinalDocument, svg);

        return 0;
}


void freeMemory(FILE *geo, FILE* qry, Parameter *parameter, char* *commands, int file_lines_count, char* svgFinalDocument, FILE* svg){
    
    free(parameter->inputDir);
    free(parameter->outputDir);

    free(parameter->geoFileName);
    free(parameter->geoFullPath);
    fclose(geo);

    if(qry != NULL){    
        free(parameter->qryFileName);
        free(parameter->qryFullPath);
        fclose(qry);
    }

    for(int j = 0; j<file_lines_count; j++){
        free(commands[j]);
    }

    free(svgFinalDocument);
    fclose(svg);
}


int count_file_lines(FILE *file){

    char ch;
    int lines_count = 0;

    while(!feof(file)){

        ch = fgetc(file);

        if(ch == '\n'){
            ++lines_count;
        }
    }

    fseek(file, 0, SEEK_SET);

    return lines_count;
}

