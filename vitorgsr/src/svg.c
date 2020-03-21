#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
                    commandElements[j] = (char*) malloc(50*sizeof(char)); //aloca 50 bytes para o texto a ser desenhado.
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