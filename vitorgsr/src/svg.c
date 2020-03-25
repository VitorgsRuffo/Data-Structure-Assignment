#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "parameters.h"

void svg_append_tag_to_final_document(char* *finalTag, char* *svgFinalDocument, char* *svgFinalDocument2){

    //Vamos precisar de mais espaço na string svgFinalDocument, pois vamos anexar a circle tag nela:
    int finalDocLen = strlen(*svgFinalDocument);
    int finalTagLen = strlen(*finalTag);

    
    *svgFinalDocument2 = (char*) malloc((finalDocLen + finalTagLen + 1) * sizeof(char));

    sprintf(*svgFinalDocument2, "%s%s", *svgFinalDocument, *finalTag);

    char* aux = *svgFinalDocument;

    *svgFinalDocument = *svgFinalDocument2;

    *svgFinalDocument2 = aux;

}


void svg_finalize_final_document(char* *svgFinalDocument){

    strcat(*svgFinalDocument, "</svg>");

    printf("\n.svg content:\n");
    printf("%s\n", *svgFinalDocument);

}



void svg_build_circ_tag(char* *tag, char* i, char* rad, char* x, char* y, char* corb, char* corp){

    //example: <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" />
        
    sprintf(*tag, " <circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"2.0\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"blue\" > %s </text> ", x, y, rad, corb, corp, x, y, i);

}

    
void svg_build_rect_tag(char* *tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp){

    //example: <rect width="100" height="100" x="130.00" y="90.9" fill="rgb(0,0,255)" stroke-width="3" stroke="rgb(0,0,0)" />
        
    sprintf(*tag, " <rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"1.5\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"blue\" > %s </text> ", w, h, x, y, corb, corp, x, y, i);

}


void svg_build_txt_tag(char* *tag, char* x, char* y, char* corb, char* corp, char* txt){

    //example: <text x="0" y="15" stroke="blue" stroke-width="0.3" fill="red">I love SVG!</text>

    sprintf(*tag, " <text x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\" > %s </text> ", x, y, corb, corp, txt);

}



void svg_interpret_command(char* *command, char* *commandElements, int commandNum){
        
    //ex of circ command:   c 1 50.00 50.00 30.00 grey magenta

    //ex of rect command:   r 4 10.0 150.0 90.0 40.0 cyan yellow

    /*ex of command elements:
            c 
            50.00 
            50.0
            30.00
            grey 
            magenta
    */

    //lidando com circulos:
    if(*(command[0]) == 'c'){

        sscanf(*command, "%s %s %s %s %s %s %s", commandElements[0], commandElements[1], commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6]);

    //lidando com retangulos:
    }else if(*(command[0]) == 'r'){

        sscanf(*command, "%s %s %s %s %s %s %s %s", commandElements[0], commandElements[1], commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6], commandElements[7]);

    }else if(*(command[0]) == 't'){
            
        sscanf(*command, "%s %s %s %s %s %s %s", commandElements[0], commandElements[1], commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6]);

    }

    for(int j = 0; j<commandNum; ++j){
        printf("%s\n", commandElements[j]);
    }

}


void svg_draw(char* *command, char* *svgFinalDocument, int commandNum){

    //Separando as partes do comando:

        //recebemos o comando. Agora devemos dividir suas partes.
            
        //matriz de strings onde cada string é uma parte do comando:
        char* commandElements[commandNum]; //commandNum == 7 para circulos e texto e 8 para retangulos

        if(*(command[0]) == 'c' || *(command[0]) == 'r'){

            for(int j = 0; j<commandNum; ++j){

                commandElements[j] = (char*) malloc(15*sizeof(char)); //Supomos que 15 == tamanho máx de um pedaço do comando

                if(commandElements[j] == NULL){
                    printf("Error allocating memory for commandElements array.\nFinishing execution..");
                    exit(1);
                }
            }
            
        }else if(*(command[0]) == 't'){

            for(int j = 0; j<commandNum; ++j){

                if(j != commandNum-1){
                    commandElements[j] = (char*) malloc(15*sizeof(char)); //Supomos que 15 == tamanho máx de um pedaço do comando
                }else{
                    commandElements[j] = (char*) malloc(20*sizeof(char)); //aloca 20 bytes para o texto a ser desenhado.
                }


                if(commandElements[j] == NULL){
                    printf("Error allocating memory for commandElements array.\nFinishing execution..");
                    exit(1);
                }
            }

        }

        //Separando, de fato, as partes do comando:
        svg_interpret_command(command, commandElements, commandNum);


    //Criando a tag da figura e a tag do ID da figura a partir do comando:

        char* tag = (char*) malloc(300 * sizeof(char)); //aqui estamos supondo que o tamanho de uma tag vai ser até 300 bytes.

        if(tag == NULL){
            printf("Error! could not allocate memory for tag..");
            exit(1);
        }

            
        //lidando com circulos:
        if(*(command[0]) == 'c'){

            svg_build_circ_tag(&tag, commandElements[1], commandElements[2], commandElements[3], commandElements[4],commandElements[5], commandElements[6]);

        //lidando com retangulos:
        }else if(*(command[0]) == 'r'){

            svg_build_rect_tag(&tag, commandElements[1], commandElements[2], commandElements[3], commandElements[4],commandElements[5], commandElements[6], commandElements[7]);
            
        //lidando com texto:
        }else if(*(command[0]) == 't'){

            svg_build_txt_tag(&tag, commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6]);

        }

        int tagSize = strlen(tag);

        char* finalTag;

        finalTag = (char*) malloc((tagSize + 1) * sizeof(char));

        if(finalTag == NULL){
            printf("Error! could not allocate memory for finalTag..");
            exit(1);
        }

        strcpy(finalTag, tag);

        free(tag);

            
    //Anexando a tag da figura e a tag do ID da figura na string final:
            
        char* svgFinalDocument2 = NULL;
            
        svg_append_tag_to_final_document(&finalTag, svgFinalDocument, &svgFinalDocument2);

    //Limpando o resto de memoria:
            
        free(svgFinalDocument2);

        for(int j = 0; j<commandNum; ++j){

            free(commandElements[j]);
        }

        free(finalTag);
    
}


void buildSvgPath(Parameter *parameter){

    int outputDirLen = strlen(parameter->outputDir);
    int svgFileNameLen = strlen(parameter->geoFileName);

    char* svgFileName  = (char*) malloc((svgFileNameLen + 1) * sizeof(char));

    strcpy(svgFileName, parameter->geoFileName);

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
    
    parameter->svgFullPath = (char*) malloc((outputDirLen + svgFileNameLen + 1) * sizeof(char));

    if(parameter->outputDir[outputDirLen-1] == '/'){

        sprintf(parameter->svgFullPath, "%s%s", parameter->outputDir, svgFileName);

    }else{

        sprintf(parameter->svgFullPath, "%s/%s", parameter->outputDir, svgFileName);

    }

    free(svgFileName);

    printf("\n%s\n", parameter->svgFullPath);

}



//void buildSvgQryPath(Parameter *parameter){

//}



void svg_qry_o(char* *qryCommand, char* commands[][8], int geo_lines_count){

    //Conseguindo o ID das figuras a serem testadas:
    char J = qryCommand[0][3];
    char K = qryCommand[0][5];

    char* jShape[8];
    char* kShape[8];

    int isThereCollision;


    //extraindo as informaçoes de cada uma das duas figuras:
    for(int i = 0; i < geo_lines_count; ++i){
        
        if(*commands[i][1] == J){
            
            for(int y = 0; y<8; ++y){

                jShape[y] = (char*) malloc((strlen(commands[i][y]) + 1) * sizeof(char));  

                strcpy(jShape[y], commands[i][y]);

                printf("\n%s\n", jShape[y]);
            }

        }else if(*commands[i][1] == K){
            
            for(int y = 0; y<8; ++y){

                kShape[y] = (char*) malloc((strlen(commands[i][y]) + 1) * sizeof(char));

                strcpy(kShape[y], commands[i][y]);

                printf("\n%s\n", kShape[y]);
            }

        }

    }

    //Temos 3 possibilidades, podemos estar testando:  

    //dois circulos:
    //Eles vão se sobrepor quando a distancia entre os centros dos circulos for menor que a soma dos seus raios.
    if(*jShape[0] == 'c' && *kShape[0] == 'c'){

        float jRadius = strtof(jShape[2], NULL); 
        float kRadius = strtof(kShape[2], NULL);
        
        //printf("\njR:%f kR:%f\n", jRadius, kRadius);

        float jX = strtof(jShape[3], NULL), jY = strtof(jShape[4], NULL);
        float kX = strtof(kShape[3], NULL), kY = strtof(kShape[4], NULL);

        //printf("\njX:%f jY:%f\nkX:%f kY:%f\n", jX, jY, kX, kY);


        //distancia entre os centros dos circulos:
        float D = sqrt(pow((kX - jX), 2) + pow((kY - jY), 2));

        //Se sobrepõem:
        if(D < jRadius + kRadius){
            isThereCollision = 1;
        //Não se sobrepõem:
        }else if (D >= jRadius + kRadius){
            isThereCollision = 0;
        }

        printf("\nOs circulos se sobrepoem? %d.\n", isThereCollision);

    //dois retangulos:
    }else if(*jShape[0] == 'r' && *kShape[0] == 'r'){

    //um circulo e um retangulo:
    }else if((*jShape[0] == 'c' && *kShape[0] == 'r') || (*jShape[0] == 'r' && *kShape[0] == 'c')){

    }



    
    

}


void svg_qry_i(){
    
}


void  svg_qry_pnt(){

}


void svg_qry_delf(){

}


void svg_qry_delf2(){

}