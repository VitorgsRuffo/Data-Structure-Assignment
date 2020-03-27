#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"
#include "geo.h"
#include "qry.h"
#include "svg.h"


//refactor note: to build a struct containing all the vars that are created and used in main :
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
    
    //Tratando o arquivo .geo:

        //precisamos contar quantas comandos (linhas) temos no arquivo de entrada .geo:
        int geo_lines_count = count_file_lines(geo);

        printf(".geo commands(lines) number: %d\n", geo_lines_count);
    
        //vetor de strings onde cada string é um comando lido do arquivo:
        char* command[geo_lines_count];
    
        for(int j = 0; j<geo_lines_count; j++){
            command[j] = (char*) malloc(110 * sizeof(char));  //Supomos que 110 == tamanho maximo de um comando (linha)

            if(command[j] == NULL){
                printf("Error allocating memory for commands array.\nFinishing execution..\n");
                exit(1);
            }
        }

        //Lendo o arquivo:
        printf(".geo content:\n");

        int i = 0;
        int commandLen;

        while(!feof(geo)){
        
            if(fgets(command[i], 110, geo)){

                //remover \n do final de cada comando:
                commandLen = strlen(command[i]);

                command[i][commandLen-1] = '\0';

                printf("%s\n", command[i]);

                if(i < geo_lines_count){
                    ++i;
                }

            }
        
        }


        //String que vai conter todas as tags referentes aos comandos do arquivo e que vai ser printada em um arquivo svg.
        char* svgFinalDocument = (char*) malloc((strlen("<svg></svg>") + 1) * sizeof(char));

        strcpy(svgFinalDocument, "<svg>");

        //Tratando um comando por vez: construir a tag relativa ao comando e anexa-la a string final.
        for(int j = 0; j<geo_lines_count; ++j){

            switch(command[j][0]){
                case 'c':
                    svg_draw(&command[j], &svgFinalDocument, 7); 
                    break;
                case 'r':
                    svg_draw(&command[j], &svgFinalDocument, 8);
                    break;
                case 't':
                    svg_draw(&command[j], &svgFinalDocument, 7);
                    break;
                case 'n':
                    //svg_nx_command(commands[j);
                    break;
                default:
                    printf("%d.o command is invalid.\n", j + 1);
                    break;
            }
    
        }
    


    //Tratando o arquivo .qry (se necessário):   (limpar memoria!!!)

        if(parameter.qryFileName != NULL){

            //Matriz dos comandos geo: cada linha representa um comando e cada coluna uma parte daquele comando.
            char* commands[geo_lines_count][8]; //file_lines_count == numero de comandos (figuras) 
                                                //8 == numero maximo de partes de um comando. (informacoes da figura)

            for(int i = 0; i<geo_lines_count; ++i){
                for(int j = 0; j<8; ++j){
                    commands[i][j] = (char*) malloc(20 * sizeof(char)); //fica determinado, portanto, que cada parte de comando pode ter até 20 bytes.
                }
            }

            //prenchendo a matriz corretamente:
            for(int i = 0; i<geo_lines_count; ++i){

                sscanf(command[i], "%s %s %s %s %s %s %s %s", commands[i][0], commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6], commands[i][7]);

            }

            printf("\n\nMatriz content:\n");

            for(int i = 0; i<geo_lines_count; ++i){
        
                for(int j = 0; j<8; ++j){
            
                    printf("%s ", commands[i][j]);

        
                }

                    printf("\n");
            }

            //Vetor para guardar o ID dos elementos excluidos por delf / delf*, ou sobrepostos na operaçao de pintura (pnt/pnt*):
            int delKeepTracker[geo_lines_count];

            //Vetor para guardar o ID dos elementos que forem afetados por um comando qry:
            int qryKeepTracker[geo_lines_count];

            //inicializando os vetores:
            for(int j = 0; j<geo_lines_count; ++j){
                delKeepTracker[j] = -1;
                qryKeepTracker[j] = -1;
            }
        

            int qry_lines_count = count_file_lines(qry);
        
            printf("\n.qry commands(lines) number: %d\n", qry_lines_count);

            //vetor de strings onde cada string é um comando lido do arquivo .qry:
            char* qryCommand[qry_lines_count];

            for(int j = 0; j<qry_lines_count; j++){
                qryCommand[j] = (char*) malloc(20 * sizeof(char));  //Supomos que 20 == tamanho maximo de um comando (linha)

                if(qryCommand[j] == NULL){
                    printf("Error allocating memory for commands array.\nFinishing execution..\n");
                    exit(1);
                }
            }

            //Lendo o arquivo:
            printf("\n.qry content:\n");

            i = 0;
            
            while(!feof(qry)){
            
                if(fgets(qryCommand[i], 110, qry)){

                    //remover \n do final de cada comando:
                    commandLen = strlen(qryCommand[i]);

                    qryCommand[i][commandLen-1] = '\0';

                    printf("%s\n", qryCommand[i]);

                    if(i < qry_lines_count){
                        ++i;
                    }

                }
        
            }


            //String que vai conter todas as tags referentes aos comandos do arquivo e que vai ser printada em um arquivo svg.
            char* svgFinalDocumentQry = (char*) malloc((strlen("<svg></svg>") + 1) * sizeof(char));

            strcpy(svgFinalDocumentQry, "<svg>");


            //Tratando um comando por vez.
            for(int j = 0; j<qry_lines_count; ++j){

                switch(qryCommand[j][0]){
                    case 'o':
                        svg_qry_o(&qryCommand[j], commands, geo_lines_count);
                        break;
                    case 'i':
                        svg_qry_i(&qryCommand[j], commands, geo_lines_count);
                        break;
                    case 'p':

                        if(qryCommand[j][3] == '*'){
                            //svg_qry_pnt2();
                        }else{
                            //svg_qry_pnt();
                        }
                        
                        break;
                    case 'd':

                        if(qryCommand[j][4] == '*'){
                            //svg_qry_delf2();
                        }else{
                            //svg_qry_delf();
                        }
                        
                        break;
                    default:
                        printf("%d.o command is invalid.\n", j + 1);
                        break;
                }
    
            }

            /*

            //Finalizando .svg referente ao .qry:

                //Terminando a string para então podermos printa-la em um .svg:
                svg_finalize_final_document(&svgFinalDocumentQry);


                //Criando .svg:
                FILE *svgQry;

                buildSvgQryPath(&parameter);

                svgQry = fopen(parameter.svgQryFullPath, "w");
                if(svgQry == NULL){
                    printf("Error: opening svgQry.\n");
                }

                fprintf(svgQry, "%s", svgFinalDocumentQry);

            //Criando .txt:

            */

        }


    //Finalizando .svg referente ao .geo:

        //Terminando a string para então podermos printa-la em um .svg:
        svg_finalize_final_document(&svgFinalDocument);


        //Criando .svg:
        FILE *svg;

        buildSvgPath(&parameter);

        svg = fopen(parameter.svgFullPath, "w");
        if(svg == NULL){
            printf("Error: opening svg.\n");
        }

        fprintf(svg, "%s", svgFinalDocument);


    //Liberando a memoria e finalizando o programa:

        freeMemory(geo, qry, &parameter, command, geo_lines_count, svgFinalDocument, svg);

        return 0;
}


void freeMemory(FILE *geo, FILE* qry, Parameter *parameter, char* *command, int geo_lines_count, char* svgFinalDocument, FILE* svg){
    
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

    for(int j = 0; j<geo_lines_count; j++){
        free(command[j]);
    }

    free(svgFinalDocument);
    free(parameter->svgFullPath);
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

