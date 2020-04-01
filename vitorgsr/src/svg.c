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
        
    sprintf(*tag, "<!--/%s -->\n     <circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"2.0\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"blue\" > %s </text> -->\n", i, x, y, rad, corb, corp, x, y, i);

}

    
void svg_build_rect_tag(char* *tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp){

    //example: <rect width="100" height="100" x="130.00" y="90.9" fill="rgb(0,0,255)" stroke-width="3" stroke="rgb(0,0,0)" />
        
    sprintf(*tag, "<!--/%s -->\n     <rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"1.5\" fill=\"%s\" /> <text x=\"%s\" y=\"%s\" fill=\"blue\" > %s </text> -->\n", i, w, h, x, y, corb, corp, x, y, i);
   
}


void svg_build_txt_tag(char* *tag, char* i, char* x, char* y, char* corb, char* corp, char* txt){

    //example: <text x="0" y="15" stroke="blue" stroke-width="0.3" fill="red">I love SVG!</text>

    sprintf(*tag, "<!--/%s -->\n     <text x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\" > %s </text> -->\n", i, x, y, corb, corp, txt);
    
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
                    commandElements[j] = (char*) malloc(80*sizeof(char)); //aloca 20 bytes para o texto a ser desenhado.
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

        char* tag = (char*) malloc(300 * sizeof(char)); //aqui estamos supondo que o tamanho de uma tag vai ser até 50 bytes.

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

            svg_build_txt_tag(&tag, commandElements[1], commandElements[2], commandElements[3], commandElements[4], commandElements[5], commandElements[6]);

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

    printf("\n%s\n", parameter->svgFullPath);
    
    
    free(svgFileName);
}



void buildSvgQryPath(Parameter *parameter){

    int outputDirLen = strlen(parameter->outputDir);
    int svgQryFileNameLen = strlen(parameter->geoFileName) + 2; //os 2 bytes extras sao pra acrescentar -q no nome do arquivo.

    char* svgQryFileName  = (char*) malloc((svgQryFileNameLen + 1) * sizeof(char));

    sprintf(svgQryFileName,"%s  ", parameter->geoFileName);


    for(int i = 0; i<svgQryFileNameLen; ++i){
        
        if(svgQryFileName[i] == '.'){
            svgQryFileName[i] = '-';
            svgQryFileName[i+1] = 'q';
            svgQryFileName[i+2] = '.';
            svgQryFileName[i+3] = 's';
            svgQryFileName[i+4] = 'v';
            svgQryFileName[i+5] = 'g';

            break;
        }

    }

    parameter->svgQryFullPath = (char*) malloc((outputDirLen + svgQryFileNameLen + 1) * sizeof(char));

    if(parameter->outputDir[outputDirLen-1] == '/'){

        sprintf(parameter->svgQryFullPath, "%s%s", parameter->outputDir, svgQryFileName);

    }else{

        sprintf(parameter->svgQryFullPath, "%s/%s", parameter->outputDir, svgQryFileName);

    }

    printf("\n%s\n", parameter->svgQryFullPath);
    
    
    free(svgQryFileName);
}


void svg_qry_create_txt(char* *txtFinalContent, Parameter *parameter){
    
    //contruindo o path do txt:

        int txtPathLen = strlen(parameter->svgQryFullPath);

        char* txtPath = (char*) malloc((txtPathLen + 1) * sizeof(char));

        sprintf(txtPath, "%s", parameter->svgQryFullPath);


        for(int i = 0; i<txtPathLen; i++){

            if(txtPath[i] == '.'){
                txtPath[i+1] = 't';
                txtPath[i+2] = 'x';
                txtPath[i+3] = 't';
                break;
            }

        }

        printf("\ntxt path: %s\n", txtPath);

    //criando o arquivo:

        FILE *txt;

        txt = fopen(txtPath, "w");

        if(!txt){
            printf("It was not possible to create o qry txt file.\nFinishing execution..\n");
            exit(1);
        }

        printf("\ntxt content:\n%s\n", *txtFinalContent);

        fprintf(txt, "%s", *txtFinalContent);

        fclose(txt);

   
}


void svg_append_txt_content(char* *txtContent, char* *txtFinalContent, char* *txtFinalContent2){

    //Vamos precisar de mais espaço na string txtFinalContent, pois vamos anexar mais conteudo nela:
    int txtFinalContentLen = strlen(*txtFinalContent);
    int txtContentLen = strlen(*txtContent);

    
    *txtFinalContent2 = (char*) malloc((txtFinalContentLen + txtContentLen + 1) * sizeof(char));

    sprintf(*txtFinalContent2, "%s%s", *txtFinalContent, *txtContent);

    char* aux = *txtFinalContent;

    *txtFinalContent = *txtFinalContent2;

    *txtFinalContent2 = aux;

}

void svg_o_build_rect_tag(char* *tag, float w, float h, float x, float y, int isThereCollision){

    //example: <rect width="100" height="100" x="130.00" y="90.9" fill="#044B94" fill-opacity="0.0" stroke-width="1.5" stroke="rgb(0,0,0)" stroke-dasharray="5,5" />

    if(isThereCollision){
        sprintf(*tag, "     <rect width=\"%g\" height=\"%g\" x=\"%g\" y=\"%g\" fill=\"#044B94\" fill-opacity=\"0.0\" stroke-width=\"1.5\" stroke=\"rgb(0,0,0)\" /> \n", w, h, x, y);
    }else{
        sprintf(*tag, "     <rect width=\"%g\" height=\"%g\" x=\"%g\" y=\"%g\" fill=\"#044B94\" fill-opacity=\"0.0\" stroke-width=\"1.5\" stroke=\"rgb(0,0,0)\" stroke-dasharray=\"5,5\" /> \n", w, h, x, y);
    }  

}

float svg_rect_point_next_to_circ_center(float min, float max, float value){

    if(value < min){
        return min;
    }else if(value > max){
        return max;
    }else{
        return value;
    }

}

void svg_qry_o(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent){

    //Conseguindo o ID das figuras a serem testadas: 

        char* J = (char*) malloc((6) * sizeof(char));
        char* K = (char*) malloc((6) * sizeof(char));

        sscanf(&qryCommand[0][3], "%s %s", J, K);

        char* jType = (char*) malloc(10 * sizeof(char));
        char* kType = (char*) malloc(10 * sizeof(char));

    //extraindo as informaçoes de cada uma das duas figuras:

        char* jShape[8];
        char* kShape[8];
        
        for(int i = 0; i < geo_lines_count; ++i){
            
            if(strcmp(commands[i][1], J) == 0){
                
                for(int y = 0; y<8; ++y){

                    jShape[y] = (char*) malloc((strlen(commands[i][y]) + 1) * sizeof(char));  

                    strcpy(jShape[y], commands[i][y]);

                    printf("\n%s\n", jShape[y]);
                }

            }else if(strcmp(commands[i][1], K) == 0){
                
                for(int y = 0; y<8; ++y){

                    kShape[y] = (char*) malloc((strlen(commands[i][y]) + 1) * sizeof(char));

                    strcpy(kShape[y], commands[i][y]);

                    printf("\n%s\n", kShape[y]);
                }

            }

        }

    //determinando se ha uma sopreposiçao:

        int isThereCollision;

        float rectX, rectY, rectW, rectH;

        //Temos 4 possibilidades, podemos estar testando:  

        //dois circulos:
        //Eles vão se sobrepor quando a distancia entre os centros dos circulos for menor que a soma dos seus raios.
        if(*jShape[0] == 'c' && *kShape[0] == 'c'){

            strcpy(jType, "Circulo");
            strcpy(kType, "Circulo");

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

            //calculando as informaçoes do retangulo que vai envolve-los:

                //X:
                if(jX - jRadius < kX - kRadius){
                    rectX = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois circulos.
                }else{
                    rectX = (kX - kRadius) - 10;
                }

                //Y:
                if(jY - jRadius < kY - kRadius){
                    rectY = (jY - jRadius) - 10;
                }else{
                    rectY = (kY - kRadius) - 10;
                }

                //W:
                if(jX + jRadius > kX + kRadius){
                    rectW = (jX + jRadius + 10) - rectX;
                }else{
                    rectW = (kX + kRadius + 10) - rectX;
                }

                //H:
                if(jY + jRadius > kY + kRadius){
                    rectH = (jY + jRadius + 10) - rectY;
                }else{
                    rectH = (kY + kRadius + 10) - rectY;
                }


        //dois retangulos:
        }else if(*jShape[0] == 'r' && *kShape[0] == 'r'){

            strcpy(jType, "Retangulo");
            strcpy(kType, "Retangulo");

            float jW = strtof(jShape[2], NULL), jH = strtof(jShape[3], NULL);
            float kW = strtof(kShape[2], NULL), kH = strtof(kShape[3], NULL);

            float jX = strtof(jShape[4], NULL), jY = strtof(jShape[5], NULL);
            float kX = strtof(kShape[4], NULL), kY = strtof(kShape[5], NULL);

            //Eles vão se sobrepor quando pelo menos umas das condiçoes abaixo forem satisfeitas: 
            if( ((kY + kH > jY) && (kY < jY + jH)) ||
                ((kY < jY + jH) && (kY + kH > jY)) ||
                ((kX + kW > jX) && (kX < jX + jW)) ||
                ((kX < jX + jW) && (kX + kW > jX)) ){

                isThereCollision = 1;
            }else{
                isThereCollision = 0;
            }

            //calculando as informaçoes do retangulo que vai envolve-los:

                //X:
                if(jX < kX){
                    rectX = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
                }else{
                    rectX = kX - 10;
                }

                //Y:
                if(jY < kY){
                    rectY = jY - 10;
                }else{
                    rectY = kY - 10;
                }

                //W:
                if(jX + jW > kX + kW){
                    rectW = (jX + jW + 10) - rectX;
                }else{
                    rectW = (kX + kW + 10) - rectX;
                }

                //H:
                if(jY + jH > kY + kH){
                    rectH = (jY + jH + 10) - rectY;
                }else{
                    rectH = (kY + kH + 10) - rectY;
                }


        //um circulo e um retangulo: para determinarmos isso precisamos, primeiramente, encontrar
        //o ponto do retangulo mais proximo do centro do circulo. Depois calculamos a distancia entre
        //esses dois pontos e se ela for menor que o raio do circulo entao ha sobreposição.
        }else if((*jShape[0] == 'c' && *kShape[0] == 'r')){

            strcpy(jType, "Circulo");
            strcpy(kType, "Retangulo");
            

            float jRadius = strtof(jShape[2], NULL);
            float jX = strtof(jShape[3], NULL), jY = strtof(jShape[4], NULL);

            float kW = strtof(kShape[2], NULL), kH = strtof(kShape[3], NULL);
            float kX = strtof(kShape[4], NULL), kY = strtof(kShape[5], NULL);

            float rectPointX = svg_rect_point_next_to_circ_center(kX, kX + kW, jX);
            float rectPointY = svg_rect_point_next_to_circ_center(kY, kY + kH, jY);

            //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:
            float D = sqrt(pow((rectPointX - jX), 2) + pow((rectPointY - jY), 2));

            if(D < jRadius){
                isThereCollision = 1;
            }else if(D >= jRadius){
                isThereCollision = 0;
            }

            //calculando as informaçoes do retangulo que vai envolve-los:
                
                //X:
                if(jX - jRadius < kX){
                    rectX = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
                }else{
                    rectX = kX - 10;
                }

                //Y:
                if(jY - jRadius < kY){
                    rectY = (jY - jRadius) - 10;
                }else{
                    rectY = kY - 10;
                }

                //W:
                if(jX + jRadius > kX + kW){
                    rectW = (jX + jRadius + 10) - rectX;
                }else{
                    rectW = (kX + kW + 10) - rectX;
                }

                //H:
                if(jY + jRadius > kY + kH){
                    rectH = (jY + jRadius + 10) - rectY;
                }else{
                    rectH = (kY + kH + 10) - rectY;
                }

        

        //um retangulo e um ciculo:
        }else if((*jShape[0] == 'r' && *kShape[0] == 'c')){

            strcpy(jType, "Retangulo");
            strcpy(kType, "Circulo");

            float jW = strtof(jShape[2], NULL), jH = strtof(jShape[3], NULL);
            float jX = strtof(jShape[4], NULL), jY = strtof(jShape[5], NULL);

            float kRadius = strtof(kShape[2], NULL);
            float kX = strtof(kShape[3], NULL), kY = strtof(kShape[4], NULL);
            
            float rectPointX = svg_rect_point_next_to_circ_center(jX, jX + jW, kX);
            float rectPointY = svg_rect_point_next_to_circ_center(jY, jY + jH, kY);

            //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:
            float D = sqrt(pow((rectPointX - kX), 2) + pow((rectPointY - kY), 2));

            if(D < kRadius){
                isThereCollision = 1;
            }else if(D >= kRadius){
                isThereCollision = 0;
            }

            //calculando as informaçoes do retangulo que vai envolve-los:

                //X:
                if(jX < kX - kRadius){
                    rectX = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
                }else{
                    rectX = (kX - kRadius) - 10;
                }

                //Y:
                if(jY < kY - kRadius){
                    rectY = jY - 10;
                }else{
                    rectY = (kY - kRadius) - 10;
                }

                //W:
                if(jX + jW > kX + kRadius){
                    rectW = (jX + jW + 10) - rectX;
                }else{
                    rectW = (kX + kRadius + 10) - rectX;
                }

                //H:
                if(jY + jH > kY + kRadius){
                    rectH = (jY + jH + 10) - rectX;
                }else{
                    rectH = (kY + kRadius + 10) - rectX;
                }

        }

        printf("\n\nisThereCollision: %d\n\n", isThereCollision);

    //Criando a tag para mostrar visualmente o resultado desta consulta:

        char* tag = (char*) malloc(150 * sizeof(char));

        svg_o_build_rect_tag(&tag, rectW, rectH, rectX, rectY, isThereCollision);

        int tagSize = strlen(tag);

        char* rectTag = (char*) malloc((tagSize + 1) * sizeof(char));

        strcpy(rectTag, tag);

        free(tag);

        printf("\nrect tag:\n%s\n", rectTag);

        //Anexando a tag do retangulo na string final:
            
            char* svgFinalDocumentQry2 = NULL;
                
            svg_append_tag_to_final_document(&rectTag, svgFinalDocumentQry, &svgFinalDocumentQry2);

            free(svgFinalDocumentQry2);


    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:

        char* result = (char*) malloc(5*sizeof(char));

        if(isThereCollision){
            strcpy(result, "SIM");
        }else{
            strcpy(result, "NAO");
        }

        char* txtContent = (char*) malloc(70 * sizeof(char));

        sprintf(txtContent,"%s\n%s: %s  %s: %s  %s\n\n", *qryCommand, J, jType, K, kType, result);

        char* txtFinalContent2 = NULL;

        svg_append_txt_content(&txtContent, txtFinalContent, &txtFinalContent2);

        free(result);

        free(txtContent);

        free(txtFinalContent2);

    //Limpando a de memoria:

}

void svg_i_build_dot_line_tag(char* *tag, float pX, float pY, float cmX, float cmY, int isInside){

    //example: <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" /> 
    //                                          <line x1="0" y1="0" x2="200" y2="200" stroke="rgb(255,100,110)" stroke-width="2" />

    if(isInside){

        sprintf(*tag,"     <circle cx=\"%f\" cy=\"%f\" r=\"1.0\" stroke=\"blue\" stroke-width=\"3\" fill=\"blue\" /> <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"blue\" stroke-width=\"0.8\" /> \n" , pX, pY, pX, pY, cmX, cmY);

    }else{

        sprintf(*tag,"     <circle cx=\"%f\" cy=\"%f\" r=\"1.0\" stroke=\"magenta\" stroke-width=\"3\" fill=\"magenta\" /> <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"magenta\" stroke-width=\"0.8\" /> \n" , pX, pY, pX, pY, cmX, cmY); 

    }  
}


void svg_qry_i(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent){


    //Conseguindo o ID da figura e as coordenadas do ponto:  
        
       
        char* J = (char*) malloc(6 * sizeof(char));
        float pX, pY;
        

        sscanf(&qryCommand[0][3], "%s %f %f", J, &pX, &pY);

        printf("J, pX, pY: %s %f %f", J, pX, pY);


        char* jType = (char*) malloc(10 * sizeof(char));

    //Extraindo as informaçoes da figura:

        char* jShape[8];

        for(int i = 0; i < geo_lines_count; ++i){

            if(strcmp(commands[i][1], J) == 0){

                printf("J: %s", J);

                for(int k = 0; k<6; ++k){

                    jShape[k] = (char*) malloc((strlen(commands[i][k]) + 1) * sizeof(char));

                    strcpy(jShape[k], commands[i][k]);

                    printf("\njShape[%d]:%s\n", k, jShape[k]);

                } 

            }

        }

    //Determinando se o ponto é interno a figura:

        int isInside;
        float cmX, cmY;


        //Se J for um circulo: 
        //(Sera interno se a distancia entre o ponto e o centro do circulo for menor que o raio.)
        if(*jShape[0] == 'c'){

            strcpy(jType, "Circulo");

            float jRadius = strtof(jShape[2], NULL);
            float jX = strtof(jShape[3], NULL);
            float jY = strtof(jShape[4], NULL);
        
            //printf("\njR:%f jX:%f jY:%f\n", jRadius, jX, jY);

            //distancia entre o centro dos circulo e o ponto:
            float D = sqrt(pow((pX - jX), 2) + pow((pY - jY), 2));

            if(D < jRadius){
                isInside = 1;
            }else if (D >= jRadius){
                isInside = 0;
            }

            //determinando o centro de massa da figura:
            cmX = jX; cmY = jY;


        //Se J for um retangulo:
        }else if(*jShape[0] == 'r'){

            strcpy(jType, "Retangulo");

            float jW = strtof(jShape[2], NULL);
            float jH = strtof(jShape[3], NULL);
            float jX = strtof(jShape[4], NULL);
            float jY = strtof(jShape[5], NULL);

            //printf("\njW:%f jH:%f jX:%f jY:%f\n", jW, jH, jX, jY);

            //sera interno se as condiçoes a seguir forem atendidas:
            if(pX < jX + jW && pX > jX && pY < jY + jH && pY > jY){
                isInside = 1;
            }else{
                isInside = 0;
            }

            //determinando o centro de massa da figura:
            cmX = jX + (jW / 2.0); cmY = jY + (jH / 2.0); 

        }

    //Criando a tag para mostrar visualmente o resultado desta consulta:

        char* tag = (char*) malloc(300 * sizeof(char));

        svg_i_build_dot_line_tag(&tag, pX, pY, cmX, cmY, isInside);

        int tagSize = strlen(tag);

        char* dotLineTag = (char*) malloc((tagSize + 1) * sizeof(char));

        strcpy(dotLineTag, tag);

        free(tag);

        printf("\ndotLine tag:\n%s\n", dotLineTag);

        //Anexando a tag do ponto(mini circulo) e da linha na string final:
            
            char* svgFinalDocumentQry2 = NULL;
                
            svg_append_tag_to_final_document(&dotLineTag, svgFinalDocumentQry, &svgFinalDocumentQry2);

            free(svgFinalDocumentQry2);


    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:

        char* result = (char*) malloc(12*sizeof(char));

        if(isInside){
            strcpy(result, "INTERNO");
        }else{
            strcpy(result, "NAO INTERNO");
        }    

        char* txtContent = (char*) malloc(50 * sizeof(char));

        sprintf(txtContent, "%s\n%s: %s %s\n\n", *qryCommand, J, jType, result);

        printf("\ni? txt content:\n%s\n", txtContent);

        char* txtFinalContent2 = NULL;

        svg_append_txt_content(&txtContent, txtFinalContent, &txtFinalContent2);

        free(result);

        free(txtContent);

        free(txtFinalContent2);

    //Limpando a de memoria:


}


void svg_qry_delf(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count){
    
    //Conseguindo o ID da figura/texto que sera excluida: 

        char* J =  (char*) malloc((strlen(&qryCommand[0][5]) + 1) * sizeof(char));

        sscanf(&qryCommand[0][5], "%s", J);


    //Buscando pela(o) figura/texto a ser excluida e excluindo-a(o):
    //OBS: a(o) figura/texto sera excluida(o) porque vamos comentar a sua tag. Assim, ela nao vai ser renderizada.

        int stringLen = strlen(*svgFinalDocumentQry);

        char* searchJ = (char*) malloc((strlen(J) + 1) * sizeof(char));


        for(int i = 11; i<stringLen; ++i){

            if((*svgFinalDocumentQry)[i - 1] == '/' && (*svgFinalDocumentQry)[i - 2] == '-'){
                

                sscanf(&((*svgFinalDocumentQry)[i]), "%s", searchJ);


                if(strcmp(J, searchJ) == 0){
                    
                    for(int j = i + 1; j<stringLen; ++j){
                        
                        if((*svgFinalDocumentQry)[j] == '\n'){

                            (*svgFinalDocumentQry)[j+1] = '<';
                            (*svgFinalDocumentQry)[j+2] = '!';
                            (*svgFinalDocumentQry)[j+3] = '-';
                            (*svgFinalDocumentQry)[j+4] = '-';

                            break;
                        }
                    }

                    break;
                }
            }
        }


    printf("after delf:\n%s\n", *svgFinalDocumentQry);

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:

    if(txtFinalContent != NULL){

        char* txtContent = (char*) malloc(300 * sizeof(char));

        char* txtFinalContent2 = NULL;

        for(int i = 0; i < geo_lines_count; ++i){

            if(strcmp(commands[i][1], J) == 0){
                
                if(commands[i][0][0] == 'c'){

                    sprintf(txtContent, "%s\ntipo: circulo, id: %s, raio: %s, x: %s, y: %s, corb: %s, corp: %s\n\n", 
                                        *qryCommand, commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);

                }else if(commands[i][0][0] == 'r'){

                    sprintf(txtContent, "%s\ntipo: retangulo, id: %s, w: %s, h: %s, x: %s, y: %s, corb: %s, corp: %s\n\n", 
                                        *qryCommand, commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6], commands[i][7]);

                }

                printf("\ndelf txt content:\n%s\n", txtContent);

                svg_append_txt_content(&txtContent, txtFinalContent, &txtFinalContent2);

                break;
            }
        }

        free(txtContent);
        free(txtFinalContent2);
    }

    //Limpando a de memoria:

}


void svg_qry_delf2(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count){

    //Conseguindo o intevalo de IDs das figuras/textos que seram excluidas: 

        char* J = (char*) malloc(6 * sizeof(char));
        char* K = (char*) malloc(6 * sizeof(char));

        sscanf(&qryCommand[0][6], "%s %s", J, K);

        printf("%s %s", J, K);

    //Buscando pelas(os) figuras/textos a serem excluidas e excluindo-as(os):

        int stringLen = strlen(*svgFinalDocumentQry);

        char* searchId = (char*) malloc(6 * sizeof(char));


        for(int i = 11; i<stringLen; ++i){

            if((*svgFinalDocumentQry)[i - 1] == '/' && (*svgFinalDocumentQry)[i - 2] == '-'){
                

                sscanf(&((*svgFinalDocumentQry)[i]), "%s", searchId);


                if(strtof(searchId, NULL) >= strtof(J, NULL) && strtof(searchId, NULL) <= strtof(K, NULL)){
                    
                    for(int j = i + 1; j<stringLen; ++j){
                        
                        if((*svgFinalDocumentQry)[j] == '\n'){

                            (*svgFinalDocumentQry)[j+1] = '<';
                            (*svgFinalDocumentQry)[j+2] = '!';
                            (*svgFinalDocumentQry)[j+3] = '-';
                            (*svgFinalDocumentQry)[j+4] = '-';

                            break;
                        }
                    }

                }
            }
        }

    printf("\nafter delf*:\n%s\n", *svgFinalDocumentQry);

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:

        char* txtContent = (char*) malloc(100 * sizeof(char));

        char* txtFinalContent2 = NULL;

        sprintf(txtContent, "%s\n", *qryCommand);

        svg_append_txt_content(&txtContent, txtFinalContent, &txtFinalContent2);

        for(int i = 0; i < geo_lines_count; ++i){

            if(strtof(commands[i][1], NULL) >= strtof(J, NULL) && strtof(commands[i][1], NULL) <= strtof(K, NULL)){
                
                if(commands[i][0][0] == 'c'){

                    sprintf(txtContent, "tipo: circulo, id: %s, raio: %s, x: %s, y: %s, corb: %s, corp: %s\n\n", 
                                         commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);

                }else if(commands[i][0][0] == 'r'){

                    sprintf(txtContent, "tipo: retangulo, id: %s, w: %s, h: %s, x: %s, y: %s, corb: %s, corp: %s\n\n", 
                                         commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6], commands[i][7]);

                }

                printf("\ndelf* %d txt content:\n%s\n", i, txtContent);

                txtFinalContent2 = NULL;

                svg_append_txt_content(&txtContent, txtFinalContent, &txtFinalContent2);

            }
        }

        free(txtContent);
        free(txtFinalContent2);


    //Limpar memoria:


}


void svg_qry_pnt(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent, char* *pnt2){

    //Interpretar o comando query:

        char* J = (char*) malloc(8 * sizeof(char));
        char* newCorb = (char*) malloc(8 * sizeof(char));
        char* newCorp = (char*) malloc(8 * sizeof(char));

        sscanf(&qryCommand[0][4], "%s %s %s", J, newCorb, newCorp);

        //printf("\npnt: %s %s %s\n", J, newCorb, newCorp);
        
        //essas variaveis vao guardar as cores originais da borda e preenchimento. (Para mais tarde imprimirmos-as no txt do pnt)
        char* originalCorb = (char*) malloc(15 * sizeof(char));
        char* originalCorp = (char*) malloc(15 * sizeof(char));


    //Extrair os dados da figura/txt a ser pintada:

        char* jDrawing[8];

        for(int i = 0; i < geo_lines_count; ++i){

            if(strcmp(commands[i][1], J) == 0){

                printf("J: %s", J);

                for(int k = 0; k<8; ++k){

                    jDrawing[k] = (char*) malloc((strlen(commands[i][k]) + 1) * sizeof(char));

                    strcpy(jDrawing[k], commands[i][k]);

                    printf("\njDrawing[%d]:%s\n", k, jDrawing[k]);

                } 

            }

        }

    


    //Excluir a figura/txt do svgFinalDocumentQry:

        char* delfCommand = (char*) malloc(15 * sizeof(char));

        sprintf(delfCommand, "delf %s", J);

        svg_qry_delf(&delfCommand, svgFinalDocumentQry, NULL, NULL, 0);

        free(delfCommand);


    //Construir uma nova tag para essa figura/txt com a nova cor de borda e preenchimento:

        char* tag = (char*) malloc(200 * sizeof(char));


        if(*jDrawing[0] == 'c'){

            svg_build_circ_tag(&tag, jDrawing[1], jDrawing[2], jDrawing[3], jDrawing[4], newCorb, newCorp);
            
            sprintf(originalCorb, "%s", jDrawing[5]);
            sprintf(originalCorp, "%s", jDrawing[6]);
        
        }else if(*jDrawing[0] == 'r'){

            svg_build_rect_tag(&tag, jDrawing[1], jDrawing[2], jDrawing[3], jDrawing[4], jDrawing[5], newCorb, newCorp);
            
            sprintf(originalCorb, "%s", jDrawing[6]);
            sprintf(originalCorp, "%s", jDrawing[7]);        
        
        }else if(*jDrawing[0] == 't'){
            
            svg_build_txt_tag(&tag, jDrawing[1], jDrawing[2], jDrawing[3], newCorb, newCorp ,jDrawing[6]);
            
            sprintf(originalCorb, "%s", jDrawing[4]);
            sprintf(originalCorp, "%s", jDrawing[5]);        
        }

        int tagSize = strlen(tag);

        char* newTag = (char*) malloc((tagSize + 1) * sizeof(char));

        strcpy(newTag, tag);

        free(tag);

        printf("\nnewTag:\n%s\n", newTag);

    //Anexar a nova figura no svgFinalDocumentQry:

        char* svgFinalDocumentQry2 = NULL;
                
        svg_append_tag_to_final_document(&newTag, svgFinalDocumentQry, &svgFinalDocumentQry2);

        free(svgFinalDocumentQry2);

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:

        char* txtContent = (char*) malloc(100 * sizeof(char));

        if(pnt2 == NULL){

            sprintf(txtContent, "%s\ncorb original: %s, corp original: %s\n\n", *qryCommand, originalCorb, originalCorp);
       
        }else{

            sprintf(txtContent, "%s\ni: %s, corb original: %s, corp original: %s\n\n", *pnt2, J, originalCorb, originalCorp);


        }

        printf("\npnt txt content:\n%s\n", txtContent);

        char* txtFinalContent2 = NULL;

        svg_append_txt_content(&txtContent, txtFinalContent, &txtFinalContent2);

        free(txtContent);

        free(txtFinalContent2);

    //Limpando a de memoria:





    printf("\nafter pnt:\n%s\n", *svgFinalDocumentQry);

}


void svg_qry_pnt2(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent){
    
    //Interpretar o comando query:

        char* J = (char*) malloc(8 * sizeof(char));
        char* K = (char*) malloc(8 * sizeof(char));
        char* newCorb = (char*) malloc(8 * sizeof(char));
        char* newCorp = (char*) malloc(8 * sizeof(char));

        sscanf(&qryCommand[0][5], "%s %s %s %s", J, K, newCorb, newCorp);

        //printf("\npnt*: %s %s %s %s\n", J, K, newCorb, newCorp);

    //Chamar a funçao svg_qry_pnt para casa uma das entidades cujo id esta entre J e K:

        int aux = 0;

        char* pntCommand = (char*) malloc(30 * sizeof(char));

        for(int i = strtol(J, NULL, 10); i<=strtol(K, NULL, 10); ++i){
            //verificar se o id i(que esta entre J e K) existe antes de chamar a funçao:
            for(int z = 0; z<geo_lines_count; ++z){

                if(strtol(commands[z][1], NULL, 10) == i){
                    
                    sprintf(pntCommand, "pnt %d %s %s", i, newCorb, newCorp);

                    svg_qry_pnt(&pntCommand, commands, geo_lines_count, svgFinalDocumentQry, txtFinalContent, qryCommand);

                    break;
                }
            }

        }

}