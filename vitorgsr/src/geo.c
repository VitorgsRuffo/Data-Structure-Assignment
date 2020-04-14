#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"
#include "svg.h"


//example: <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" />
void geo_build_circ_tag(char* *tag, char* i, char* rad, char* x, char* y, char* corb, char* corp){

    sprintf(*tag, "<!--/%s -->\n     <circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"2.0\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"red\" > %s </text> -->\n", i, x, y, rad, corb, corp, x, y, i);
}

//example: <rect width="100" height="100" x="130.00" y="90.9" fill="rgb(0,0,255)" stroke-width="3" stroke="rgb(0,0,0)" />  
void geo_build_rect_tag(char* *tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp){
        
    sprintf(*tag, "<!--/%s -->\n     <rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"1.5\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"red\" > %s </text> -->\n", i, w, h, x, y, corb, corp, x, y, i);
}

//example: <text x="0" y="15" stroke="blue" stroke-width="0.3" fill="red">I love SVG!</text>
void geo_build_txt_tag(char* *tag, char* i, char* x, char* y, char* corb, char* corp, char* txt){

    sprintf(*tag, "<!--/%s -->\n     <text x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\" > %s </text> -->\n", i, x, y, corb, corp, txt);
}

 //ex of circ command:   c 1 50.00 50.00 30.00 grey magenta ;  ex of rect command:   r 4 10.0 150.0 90.0 40.0 cyan yellow
void geo_interpret_command(char* command, char* commands[][8], int i){
   
    if(command[0] == 'c'){ //lidando com circulo: 

        sscanf(command, "%s %s %s %s %s %s %s", commands[i][0], commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);

    }else if(command[0] == 'r'){ //lidando com retangulo:

        sscanf(command, "%s %s %s %s %s %s %s %s", commands[i][0], commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6], commands[i][7]);

    }else if(command[0] == 't'){ //lidando com texto:
            
        sscanf(command, "%s %s %s %s %s %s %[^\n]s", commands[i][0], commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);
    
    }else if(command[0] == 'n'){
        strcpy(commands[i][0], " "); strcpy(commands[i][1], ""); strcpy(commands[i][2], ""); strcpy(commands[i][3], ""); strcpy(commands[i][4], ""); strcpy(commands[i][5], ""); strcpy(commands[i][6], ""); strcpy(commands[i][7], "");
    }
}

void geo_draw(char* commands[][8], int geo_lines_count, char* *svgFinalDocument){
    
    int k;
    //se houver nx no .geo vamos ignorar o primeiro comando iniciando o i em 1:
    if(commands[0][0][0] == ' ') k = 1; else k = 0;

    printf("%d", k);

    for(int i = k; i<geo_lines_count; ++i){

        //Criando a tag da figura/txt e a tag do ID da figura/txt a partir do comando atual:

            char* tag = (char*) malloc(300 * sizeof(char)); //aqui estamos supondo que o tamanho de uma tag vai ser até 300 bytes.

            if(tag == NULL){
                printf("Error! could not allocate memory for tag..");
                exit(1);
            }
                
            if(commands[i][0][0] == 'c'){ //lidando com circulos:

                geo_build_circ_tag(&tag, commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);

            }else if(commands[i][0][0] == 'r'){  //lidando com retangulos:

                geo_build_rect_tag(&tag, commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6], commands[i][7]);
                
            }else if(commands[i][0][0] == 't'){ //lidando com texto:

                geo_build_txt_tag(&tag, commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);
            }

        //Anexando a tag da figura e a tag do ID da figura na string final:
                
            char* svgFinalDocument2 = NULL;
                
            svg_append_content_to_final_document(&tag, svgFinalDocument, &svgFinalDocument2);

            free(tag); 
    } 
}