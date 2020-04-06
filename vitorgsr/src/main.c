#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"
#include "geo.h"
#include "qry.h"
#include "svg.h"

#define command_max_length 100


//refactor note: to build a struct containing all the vars that are created and used in main :
void freeMemory(FILE *geo, FILE* qry, Parameter *parameter, char* *commands, int file_lines_count, char* svgFinalDocument, FILE* svg);

int count_file_lines(FILE *file);

int get_nx(FILE *file);


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

        //conseguindo o valor de nx no arquivo geo (se nao existir usaremos 1000 como default):
        int nx = get_nx(geo);
        
        printf("\nnx: %d\n", nx);

        //vetor de strings onde cada string é um comando lido do arquivo:
        char* command[nx];


        //precisamos contar quantas comandos (linhas) temos no arquivo de entrada .geo:
        int geo_lines_count = count_file_lines(geo);

        printf("\n.geo commands(lines) number: %d\n", geo_lines_count);
    
        for(int j = 0; j<geo_lines_count; j++){
            command[j] = (char*) malloc(command_max_length * sizeof(char));  //Supomos que 100 == tamanho maximo de um comando (linha)

            if(command[j] == NULL){
                printf("Error allocating memory for commands array.\nFinishing execution..\n");
                exit(1);
            }
        }

        //Lendo o arquivo:
            printf("\n.geo content:\n");

            int x = 0;
            int commandLen;

            while(!feof(geo)){
            
                if(fgets(command[x], 110, geo)){

                    //remover \n do final de cada comando:
                    commandLen = strlen(command[x]);

                    command[x][commandLen-1] = '\0';

                    printf("%s\n", command[x]);

                    if(x < geo_lines_count){
                        ++x;
                    }

                }
            
            }

        //Refinando os nossos dados para facilitar o acesso:
        //(Os dados do geo serao organizados da seguinte maneira: matriz de ponteiros.
        // Cala linha representa um comando, cada coluna uma parte deste comando.)
           
            char* commands[geo_lines_count][8]; //geo_lines_count == numero exato de comandos (figuras/textos) 
                                                //8 == numero maximo de partes de um comando. (informacoes da figura)

            for(int i = 0; i<geo_lines_count; ++i){
                for(int j = 0; j<8; ++j){
                    if(j == 6){
                        //deixamos um espaço extra na posicao 6, pois é la que vai ser guardado o texto caso o comando seja do tipo textual.
                        commands[i][j] = (char*) malloc(50 * sizeof(char)); //fica determinado, portanto, que esta parte de comando pode ter até 50 bytes.

                    }else{
                        commands[i][j] = (char*) malloc(30 * sizeof(char)); //fica determinado, portanto, que cada parte de comando pode ter até 30 bytes.

                    }
                }
            }

            printf("\nmatrix content: \n");
            //preenchendo a matriz:
            for(int i = 0; i<geo_lines_count; ++i){
                svg_interpret_command(command[i], commands, i);
            }


        //Precisamos configurar a view box do svg que vai ser gerado para evitarmos que algumas figuras aparecam cortadas:
            float X = 1000, Y = 1000, W = 0, H = 0;

            svg_set_view_box(&X, &Y, &W, &H, commands, geo_lines_count);

            char* openingSvgTag = (char*) malloc(100 * sizeof(char));

            sprintf(openingSvgTag, "<svg viewBox=\"%f %f %f %f\">\n", X, Y, W, H);

        //String que vai conter todas as tags referentes aos comandos do arquivo e que vai ser printada em um arquivo svg.
        char* svgFinalDocument = (char*) malloc((strlen(openingSvgTag) + 1) * sizeof(char));
        strcpy(svgFinalDocument, openingSvgTag);

        free(openingSvgTag);


        char* closeTag = (char*) malloc((strlen("</svg>") + 1) * sizeof(char));
        strcpy(closeTag, "</svg>");


        //Tratando um comando por vez: construir a tag relativa ao comando e anexa-la a string final.
        for(int i = 0; i<geo_lines_count; ++i){

            switch(commands[i][0][0]){
                case 'c':
                    svg_draw(commands, i, &svgFinalDocument); 
                    break;
                case 'r':
                    svg_draw(commands, i, &svgFinalDocument);
                    break;
                case 't':
                    svg_draw(commands, i, &svgFinalDocument);
                    break;
                case 'n':

                    break;
                default:
                    printf("%d.o command is invalid.\n", i + 1);
                    break;
            }
    
        }
 


    //Tratando o arquivo .qry (se necessário):  

        if(parameter.qryFileName != NULL){
                
            int qry_lines_count = count_file_lines(qry);
        
            printf("\n.qry commands(lines) number: %d\n", qry_lines_count);

            //vetor de strings onde cada string é um comando lido do arquivo .qry:
            char* qryCommand[qry_lines_count];

            for(int j = 0; j<qry_lines_count; j++){
                qryCommand[j] = (char*) malloc(40 * sizeof(char));  //Supomos que 40 == tamanho maximo de um comando (linha)

                if(qryCommand[j] == NULL){
                    printf("Error allocating memory for commands array.\nFinishing execution..\n");
                    exit(1);
                }
            }

            //Lendo o arquivo:
            printf("\n.qry content:\n");

            int i = 0;
            
            while(!feof(qry)){
            
                if(fgets(qryCommand[i], 100, qry)){

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
            char* svgFinalDocumentQry = (char*) malloc((strlen(svgFinalDocument) + 1) * sizeof(char));

            strcpy(svgFinalDocumentQry, svgFinalDocument);


            buildSvgQryPath(&parameter);
            

            //String que vai conter todos textos referentes aos comandos do arquivo e que vai ser printada em um arquivo de saida txt.
            char* txtFinalContent = (char*) malloc(2 * sizeof(char));


            //Tratando um comando por vez.
            for(int j = 0; j<qry_lines_count; ++j){

                switch(qryCommand[j][0]){
                    case 'o':
                        svg_qry_o(&qryCommand[j], commands, geo_lines_count, &svgFinalDocumentQry, &txtFinalContent);
                        break;
                    case 'i':
                        svg_qry_i(&qryCommand[j], commands, geo_lines_count, &svgFinalDocumentQry, &txtFinalContent);
                        break;
                    case 'p':

                        if(qryCommand[j][3] == '*'){
                            svg_qry_pnt2(&qryCommand[j], commands, geo_lines_count, &svgFinalDocumentQry, &txtFinalContent);
                        }else{
                            svg_qry_pnt(&qryCommand[j], commands, geo_lines_count, &svgFinalDocumentQry, &txtFinalContent, NULL);
                        }
                        
                        break;
                    case 'd':

                        if(qryCommand[j][4] == '*'){
                            svg_qry_delf2(&qryCommand[j], &svgFinalDocumentQry, &txtFinalContent, commands, geo_lines_count);
                        }else{
                            svg_qry_delf(&qryCommand[j], &svgFinalDocumentQry, &txtFinalContent, commands, geo_lines_count);
                        }
                        
                        break;
                    default:
                        printf("%d.o command is invalid.\n", j + 1);
                        break;
                }
    
            }

            for(int i = 0; i<geo_lines_count; ++i){
                for(int j = 0; j<8; ++j){
                    free(commands[i][j]);
                }
            }

            for(int j = 0; j<qry_lines_count; j++){
                free(qryCommand[j]);
            }

            //Finalizando .svg referente ao .qry:

                //Terminando a string para então podermos printa-la em um .svg:

                char* svgFinalDocumentQry2 = NULL;

                svg_append_tag_to_final_document(&closeTag, &svgFinalDocumentQry, &svgFinalDocumentQry2);

                free(svgFinalDocumentQry2);

                printf("\n.svgQry content:\n");
                //printf("%s\n", svgFinalDocumentQry);


                //Criando .svg:
                FILE *svgQry;

                printf("\nsvgQryFullPath: %s\n", parameter.svgQryFullPath);

                svgQry = fopen(parameter.svgQryFullPath, "w");
                if(svgQry == NULL){
                   printf("Error: opening svgQry file.\n");
                    }

                fprintf(svgQry, "%s", svgFinalDocumentQry);
            
            //Criando txt:

            svg_qry_create_txt(&txtFinalContent, &parameter);

            free(txtFinalContent);

        }

    //Finalizando .svg referente ao .geo:

        //Terminando a string para então podermos printa-la em um .svg:
 
        char* svgFinalDocument2 = NULL;

        svg_append_tag_to_final_document(&closeTag, &svgFinalDocument, &svgFinalDocument2);

        free(svgFinalDocument2);
        free(closeTag);


        printf("\n.svg content:\n");
        //printf("%s\n", svgFinalDocument);

        //Criando .svg:
        FILE *svg;

        buildSvgPath(&parameter);
        printf("\nsvgFullPath: %s\n", parameter.svgFullPath);


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
    //free(parameter->svgFullPath);
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



int get_nx(FILE *file){

    char* nxCommand = (char*) malloc(command_max_length * sizeof(char));

    fgets(nxCommand, command_max_length, file);

    fseek(file, 0, SEEK_SET);

    if(nxCommand[0] == 'n'){

        int nx = strtol(&nxCommand[3], NULL, 10);

        free(nxCommand);

        return nx;

    }else{

        free(nxCommand);

        //como não temos um comando nx na primeira linha vamos usar o valor 1000 como default para nx.
        return 1000;
        
    }

}
