#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void svg_interpret_command(char* *command, char* *commandElements, int commandNum);

void svg_append_tag_to_final_document(char* *finalTag, char* *svgFinalDocument, char* *svgFinalDocument2);

void svg_finalize_final_document(char* *svgFinalDocument);

void svg_draw_shape(char* *command, char* *svgFinalDocument, int commandNum);



void svg_build_circ_tag(char* *tag, char* i, char* rad, char* x, char* y, char* corb, char* corp);

void svg_build_rect_tag(char* *tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp);



int count_file_lines(FILE *file);



int main (void){

    FILE *file;

    file = fopen("g.geo", "r");

    if(file == NULL){
        printf("File error!");
        exit(1);
    }

    //precisamos contar quantas linhas (comandos) temos no arquivo de entrada .geo:
    int file_lines_count = count_file_lines(file);

    printf("%d\n",file_lines_count );

    //vetor de strings onde cada string é um comando lido do arquivo;
    char* commands[file_lines_count];
    
   
    for(int j = 0; j<file_lines_count; j++){
        commands[j] = (char*) malloc(100 * sizeof(char));  //100 == tamanho maximo de um comando

        if(commands[j] == NULL){
            printf("Error allocating memory for commands string array.\nFinishing execution..");
            exit(1);
        }
    }

    

    int i = 0;
    int commLen;

    while(!feof(file)){
        
        if(fgets(commands[i], 100, file)){

            //remover \n do final:
            commLen = strlen(commands[i]);

            commands[i][commLen-1] = '\0';

            printf("%s\n", commands[i]);

            if(i < file_lines_count)
                ++i;
            
        }
        
    }
        

    for(int j = 0; j<file_lines_count; ++j){
        
        printf("%s\n", commands[j]);

    }



    //string que vai conter todas as tags referentes aos comandos do arquivo e que vai ser printada em um arquivo svg.
    char* svgFinalDocument = (char*) malloc((strlen("<svg></svg>") + 1) * sizeof(char));

    strcpy(svgFinalDocument, "<svg>");
    



    for(int j = 0; j<file_lines_count; ++j){

        switch(commands[j][0]){
            case 'c':
                svg_draw_shape(&commands[j], &svgFinalDocument, 7); 
                break;
            case 'r':
                svg_draw_shape(&commands[j], &svgFinalDocument, 8);
                break;
            case 't':
                //svg_draw_txt(commands[j);
                break;
            case 'n':
                //svg_nx_command(commands[j);
                break;
        }
    
    }

    svg_finalize_final_document(&svgFinalDocument);

    printf("\n\n%s\n\n", svgFinalDocument);
    
    FILE *svg;

    svg = fopen("geo.svg", "w");
    if(svg == NULL){
        printf("Error: opening svg.\n");
    }

    fprintf(svg, "%s", svgFinalDocument);


    free(svgFinalDocument);

    for(int j = 0; j<file_lines_count; j++){
        free(commands[j]);
    }


    fclose(svg);


    return 0;
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




//SVG FUNCTIONS:

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

        }

        for(int j = 0; j<commandNum; ++j){
            printf("%s\n", commandElements[j]);
        }

    }

    void svg_draw_shape(char* *command, char* *svgFinalDocument, int commandNum){

        //Separando as partes do comando:

            //recebemos o comando. Agora devemos dividir suas partes.
            
            //matriz de strings onde cada string é uma parte do comando:
            char* commandElements[commandNum]; //commandNum == 7 para circulos e 8 para retangulos

            for(int j = 0; j<commandNum; ++j){
                commandElements[j] = (char*) malloc(15*sizeof(char)); //Supomos que 15 == tamanho máx de um pedaço do comando

                if(commandElements[j] == NULL){
                    printf("Error allocating memory for commandElements array.\nFinishing execution..");
                    exit(1);
                }
            }

            //Separando, de fato, as partes do comando:
            svg_interpret_command(command, commandElements, commandNum);


        //Criando a tag da figura a partir do comando:

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


        //Anexando a tag da figura na string final:
            
            char* svgFinalDocument2 = NULL;
            
            svg_append_tag_to_final_document(&finalTag, svgFinalDocument, &svgFinalDocument2);


        //Limpando o resto de memoria:
            
            free(svgFinalDocument2);

            for(int j = 0; j<7; ++j){

                free(commandElements[j]);
            }

            free(finalTag);
    }



//CIRCLE FUNCTIONS:

    void svg_build_circ_tag(char* *tag, char* i, char* rad, char* x, char* y, char* corb, char* corp){

        //example: <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" />
        
        sprintf(*tag, " <circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"2.0\" fill=\"%s\" /> ", x, y, rad, corb, corp);

    }

    

//RECTANGLE FUNCTIONS:

    void svg_build_rect_tag(char* *tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp){

        //example: <rect width="100" height="100" x="130.00" y="90.9" fill="rgb(0,0,255)" stroke-width="3" stroke="rgb(0,0,0)" />
        
        sprintf(*tag, " <rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"1.5\" fill=\"%s\" /> ", w, h, x, y, corb, corp);

    }





