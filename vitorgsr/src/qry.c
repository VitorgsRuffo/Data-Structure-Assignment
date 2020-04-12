#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "parameters.h"
#include "svg.h"
#include "geo.h"
#include "qry.h"


void qry_create_txt(char* *txtFinalContent, Parameter *parameter){
    
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

    //criando o arquivo:

        FILE *txt;

        txt = fopen(txtPath, "w");

        if(!txt){
            printf("It was not possible to create o qry txt file.\nFinishing execution..\n");
            exit(1);
        }

        fprintf(txt, "%s", *txtFinalContent);

        fclose(txt); free(txtPath);
}

void getDrawingInfo(char* jDrawing[], char* kDrawing[], char* commands[][8], int geo_lines_count, char* J, char* K){

    for(int i = 0; i < geo_lines_count; ++i){
                
        if(strcmp(commands[i][1], J) == 0){
                
            for(int y = 0; y<8; ++y){
                jDrawing[y] = commands[i][y];
            }

        }else if(strcmp(commands[i][1], K) == 0){
                
            for(int y = 0; y<8; ++y){
                kDrawing[y] = commands[i][y];
            }
        }
    }    
}


float qry_rect_point_next_to_circ_center(float min, float max, float value){

    if(value < min){
        return min;
    }else if(value > max){
        return max;
    }else{
        return value;
    }
}


int qry_o_circ_circ_collision(float jRadius, float jX, float jY, float kRadius, float kX, float kY){
    //Eles vão se sobrepor quando a distancia entre os centros dos circulos for menor que a soma dos seus raios.

    float D = sqrt(pow((kX - jX), 2) + pow((kY - jY), 2)); //distancia entre os centros dos circulos:

    if(D < jRadius + kRadius){ //Se sobrepõem:
        return 1;
    }else{ //Não se sobrepõem:
        return 0;
    }    
}

void qry_o_get_circCirc_rect_info(float jRadius, float jX, float jY, float kRadius, float kX, float kY, float *rectX, float *rectY, float *rectW, float *rectH){

    //X:
    if(jX - jRadius < kX - kRadius){
        *rectX = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois circulos.
    }else{
        *rectX = (kX - kRadius) - 10;
    }

    //Y:
    if(jY - jRadius < kY - kRadius){
        *rectY = (jY - jRadius) - 10;
    }else{
        *rectY = (kY - kRadius) - 10;
    }

    //W:
    if(jX + jRadius > kX + kRadius){
        *rectW = (jX + jRadius + 10) - *rectX;
    }else{
        *rectW = (kX + kRadius + 10) - *rectX;
    }

    //H:
    if(jY + jRadius > kY + kRadius){
        *rectH = (jY + jRadius + 10) - *rectY;
    }else{
        *rectH = (kY + kRadius + 10) - *rectY;
    }    
}


int qry_o_rect_rect_collision(float jX, float jY, float jW, float jH, float kX, float kY, float kW, float kH){
    
    //Eles vão se sobrepor quando pelo menos umas das condiçoes abaixo forem satisfeitas: 
    if( ((kY + kH > jY) && (kY < jY + jH)) ||
        ((kY < jY + jH) && (kY + kH > jY)) ||
        ((kX + kW > jX) && (kX < jX + jW)) ||
        ((kX < jX + jW) && (kX + kW > jX)) ){

        return 1;
    }else{
        return 0;
    }
}

void qry_o_get_rectRect_rect_info(float jX, float jY, float jW, float jH, float kX, float kY, float kW, float kH, float *rectX, float *rectY, float *rectW, float *rectH){
    
    if(jX < kX){//X:
        *rectX = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
    }else{
        *rectX = kX - 10;
    }

    if(jY < kY){ //Y:
        *rectY = jY - 10;
    }else{
        *rectY = kY - 10;
    }

    if(jX + jW > kX + kW){ //W:
        *rectW = (jX + jW + 10) - *rectX;
    }else{
        *rectW = (kX + kW + 10) - *rectX;
    }

    if(jY + jH > kY + kH){ //H:
        *rectH = (jY + jH + 10) - *rectY;
    }else{
        *rectH = (kY + kH + 10) - *rectY;
    }
}

//um circulo e um retangulo: para determinarmos isso precisamos, primeiramente, encontrar //o ponto do retangulo mais proximo do centro do circulo. Depois calculamos a distancia entre
int qry_o_circ_rect_collision(float jRadius, float jX, float jY, float kX, float kY, float kW, float kH){ //esses dois pontos e se ela for menor que o raio do circulo entao ha sobreposição.
                              
    float rectPointX = qry_rect_point_next_to_circ_center(kX, kX + kW, jX);
    float rectPointY = qry_rect_point_next_to_circ_center(kY, kY + kH, jY);                                                        

    //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:
    float D = sqrt(pow((rectPointX - jX), 2) + pow((rectPointY - jY), 2));

    if(D < jRadius){
        return 1;
    }else{
        return 0;
    }
}

void qry_o_get_circRect_rect_info(float jRadius, float jX, float jY, float kX, float kY, float kW, float kH, float *rectX, float *rectY, float *rectW, float *rectH){

    if(jX - jRadius < kX){ //X:
        *rectX = (jX - jRadius) - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
    }else{
        *rectX = kX - 10;
    }

    if(jY - jRadius < kY){ //Y:
        *rectY = (jY - jRadius) - 10;
    }else{
        *rectY = kY - 10;
    }

    if(jX + jRadius > kX + kW){//W:
        *rectW = (jX + jRadius + 10) - *rectX;
    }else{
        *rectW = (kX + kW + 10) - *rectX;
    }

    if(jY + jRadius > kY + kH){//H:
        *rectH = (jY + jRadius + 10) - *rectY;
    }else{
        *rectH = (kY + kH + 10) - *rectY;
    }
}

int qry_o_rect_circ_collision(float jX, float jY, float jW, float jH, float kRadius, float kX, float kY){
        
    float rectPointX = qry_rect_point_next_to_circ_center(jX, jX + jW, kX);
    float rectPointY = qry_rect_point_next_to_circ_center(jY, jY + jH, kY);

    float D = sqrt(pow((rectPointX - kX), 2) + pow((rectPointY - kY), 2)); //distancia entre o centro dos circulo e o ponto do retangulo mais proximo dele:

    if(D < kRadius){
        return 1;
    }else{
        return 0;
    }    
}

void qry_o_get_rectCirc_rect_info(float jX, float jY, float jW, float jH, float kRadius, float kX, float kY, float *rectX, float *rectY, float *rectW, float *rectH){

    if(jX < kX - kRadius){  //X:
        *rectX = jX - 10; //os 10px são para dar uma "folginha" entre o rect e os dois rect.
    }else{
        *rectX = (kX - kRadius) - 10;
    }

    if(jY < kY - kRadius){ //Y:
        *rectY = jY - 10;
    }else{
        *rectY = (kY - kRadius) - 10;
    }

    if(jX + jW > kX + kRadius){ //W:
        *rectW = (jX + jW + 10) - *rectX;
    }else{
        *rectW = (kX + kRadius + 10) - *rectX;
    }

    if(jY + jH > kY + kRadius){ //H:
        *rectH = (jY + jH + 10) - *rectY;
    }else{
        *rectH = (kY + kRadius + 10) - *rectY;
    }
}


//example: <rect width="100" height="100" x="130.00" y="90.9" fill="#044B94" fill-opacity="0.0" stroke-width="1.5" stroke="rgb(0,0,0)" stroke-dasharray="5,5" />
void qry_build_o_rect_tag(char* *tag, float w, float h, float x, float y, int isThereCollision){
   
    if(isThereCollision){
        sprintf(*tag, "     <rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" fill=\"#044B94\" fill-opacity=\"0.0\" stroke-width=\"1.5\" stroke=\"rgb(0,0,0)\" /> \n", w, h, x, y);
    }else{
        sprintf(*tag, "     <rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" fill=\"#044B94\" fill-opacity=\"0.0\" stroke-width=\"1.5\" stroke=\"rgb(0,0,0)\" stroke-dasharray=\"5,5\" /> \n", w, h, x, y);
    }  
}

void qry_o(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent){

    //Conseguindo o ID das figuras a serem testadas: 

        char* J = (char*) malloc((6) * sizeof(char));
        char* K = (char*) malloc((6) * sizeof(char));

        sscanf(&qryCommand[0][3], "%s %s", J, K);

        char* jType = (char*) malloc(10 * sizeof(char));
        char* kType = (char*) malloc(10 * sizeof(char));

    //extraindo as informaçoes de cada uma das duas figuras:

        char* jShape[8]; char* kShape[8];
        
        getDrawingInfo(jShape, kShape, commands, geo_lines_count, J, K);

    //determinando se ha uma sopreposiçao:

        int isThereCollision;  float rectX, rectY, rectW, rectH;

        if(*jShape[0] == 'c' && *kShape[0] == 'c'){ //dois circulos:
            
            strcpy(jType, "Circulo");  strcpy(kType, "Circulo");

            float jRadius = strtof(jShape[2], NULL); 
            float kRadius = strtof(kShape[2], NULL);
            float jX = strtof(jShape[3], NULL), jY = strtof(jShape[4], NULL);
            float kX = strtof(kShape[3], NULL), kY = strtof(kShape[4], NULL);

            isThereCollision = qry_o_circ_circ_collision(jRadius, jX, jY, kRadius, kX, kY);

            //calculando as informaçoes do retangulo que vai envolve-los:
                qry_o_get_circCirc_rect_info(jRadius, jX, jY, kRadius, kX, kY, &rectX, &rectY, &rectW, &rectH);

        }else if(*jShape[0] == 'r' && *kShape[0] == 'r'){  //dois retangulos:
            
            strcpy(jType, "Retangulo");  strcpy(kType, "Retangulo");
            
            float jW = strtof(jShape[2], NULL), jH = strtof(jShape[3], NULL);
            float kW = strtof(kShape[2], NULL), kH = strtof(kShape[3], NULL);
            float jX = strtof(jShape[4], NULL), jY = strtof(jShape[5], NULL);
            float kX = strtof(kShape[4], NULL), kY = strtof(kShape[5], NULL);
            
            isThereCollision = qry_o_rect_rect_collision(jX, jY, jW, jH, kX, kY, kW, kH);

            //calculando as informaçoes do retangulo que vai envolve-los:
                qry_o_get_rectRect_rect_info(jX, jY, jW, jH, kX, kY, kW, kH, &rectX, &rectY, &rectW, &rectH);
                
        }else if((*jShape[0] == 'c' && *kShape[0] == 'r')){ 
            
            strcpy(jType, "Circulo");  strcpy(kType, "Retangulo");
            
            float jRadius = strtof(jShape[2], NULL);                
            float jX = strtof(jShape[3], NULL), jY = strtof(jShape[4], NULL);
            float kW = strtof(kShape[2], NULL), kH = strtof(kShape[3], NULL);
            float kX = strtof(kShape[4], NULL), kY = strtof(kShape[5], NULL);

            isThereCollision = qry_o_circ_rect_collision(jRadius, jX, jY, kX, kY, kW, kH);

            //calculando as informaçoes do retangulo que vai envolve-los:
                qry_o_get_circRect_rect_info(jRadius, jX, jY, kX, kY, kW, kH, &rectX, &rectY, &rectW, &rectH);

        }else if((*jShape[0] == 'r' && *kShape[0] == 'c')){ //um retangulo e um ciculo:

            strcpy(jType, "Retangulo");  strcpy(kType, "Circulo");
 
            float jW = strtof(jShape[2], NULL), jH = strtof(jShape[3], NULL);
            float jX = strtof(jShape[4], NULL), jY = strtof(jShape[5], NULL);
            float kRadius = strtof(kShape[2], NULL);
            float kX = strtof(kShape[3], NULL), kY = strtof(kShape[4], NULL);

            isThereCollision = qry_o_rect_circ_collision(jX, jY, jW, jH, kRadius, kX, kY);

            //calculando as informaçoes do retangulo que vai envolve-los:
                qry_o_get_rectCirc_rect_info(jX, jY, jW, jH, kRadius, kX, kY, &rectX, &rectY, &rectW, &rectH);
        }

    //Criando a tag para mostrar visualmente o resultado desta consulta:
    //(ABSTRAIR)
        char* rectTag = (char*) malloc(250 * sizeof(char));

        qry_build_o_rect_tag(&rectTag, rectW, rectH, rectX, rectY, isThereCollision);

        //Anexando a tag do retangulo na string final:
            
            char* svgFinalDocumentQry2 = NULL;
                
            svg_append_content_to_final_document(&rectTag, svgFinalDocumentQry, &svgFinalDocumentQry2);

            free(svgFinalDocumentQry2);  free(rectTag);

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:
    //(ABSTRAIR)
        char* result = (char*) malloc(5*sizeof(char));

        if(isThereCollision){
            strcpy(result, "SIM");
        }else{
            strcpy(result, "NAO");
        }

        char* txtContent = (char*) malloc(100 * sizeof(char));

        sprintf(txtContent,"%s\n%s: %s  %s: %s  %s\n\n", *qryCommand, J, jType, K, kType, result);

        char* txtFinalContent2 = NULL;

        svg_append_content_to_final_document(&txtContent, txtFinalContent, &txtFinalContent2);


    free(J);  free(K);  free(jType);  free(kType);  free(result);  free(txtContent);  free(txtFinalContent2);
}

//example: <circle cx="50" cy="50" r="40" stroke="black" stroke-width="3" fill="red" />     <line x1="0" y1="0" x2="200" y2="200" stroke="rgb(255,100,110)" stroke-width="2" />
void qry_build_i_dot_line_tag(char* *tag, float pX, float pY, float cmX, float cmY, int isInside){

    if(isInside){
        sprintf(*tag,"     <circle cx=\"%f\" cy=\"%f\" r=\"1.0\" stroke=\"blue\" stroke-width=\"3\" fill=\"blue\" /> <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"blue\" stroke-width=\"0.8\" /> \n" , pX, pY, pX, pY, cmX, cmY);
    }else{
        sprintf(*tag,"     <circle cx=\"%f\" cy=\"%f\" r=\"1.0\" stroke=\"magenta\" stroke-width=\"3\" fill=\"magenta\" /> <line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"magenta\" stroke-width=\"0.8\" /> \n" , pX, pY, pX, pY, cmX, cmY); 
    }  
}

void qry_i(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent){

    //Conseguindo o ID da figura e as coordenadas do ponto:  
        
        char* J = (char*) malloc(6 * sizeof(char));
        float pX, pY;

        sscanf(&qryCommand[0][3], "%s %f %f", J, &pX, &pY);

    //Extraindo as informaçoes da figura:

        char* jShape[8];

        getDrawingInfo(jShape, NULL, commands, geo_lines_count, J, NULL);

    //Determinando se o ponto é interno a figura:

        int isInside;   float cmX, cmY;    char* jType = (char*) malloc(10 * sizeof(char));
       
        if(*jShape[0] == 'c'){  //Se J for um circulo: 
                               //(Sera interno se a distancia entre o ponto e o centro do circulo for menor que o raio.)
            strcpy(jType, "Circulo");

            float jRadius = strtof(jShape[2], NULL);
            float jX = strtof(jShape[3], NULL);
            float jY = strtof(jShape[4], NULL);

            float D = sqrt(pow((pX - jX), 2) + pow((pY - jY), 2)); //distancia entre o centro dos circulo e o ponto:

            if(D < jRadius){
                isInside = 1;
            }else if (D >= jRadius){
                isInside = 0;
            }

            cmX = jX;  cmY = jY;   //determinando o centro de massa da figura:

        }else if(*jShape[0] == 'r'){   //Se J for um retangulo:

            strcpy(jType, "Retangulo");

            float jW = strtof(jShape[2], NULL);
            float jH = strtof(jShape[3], NULL);
            float jX = strtof(jShape[4], NULL);
            float jY = strtof(jShape[5], NULL);


            if(pX < jX + jW && pX > jX && pY < jY + jH && pY > jY){    //sera interno se as condiçoes a seguir forem atendidas:
                isInside = 1;
            }else{
                isInside = 0;
            }

            cmX = jX + (jW / 2.0);  cmY = jY + (jH / 2.0);  //determinando o centro de massa da figura:
        }

    //Criando a tag para mostrar visualmente o resultado desta consulta: 
    //(ABSTRAIR)
        char* dotLineTag = (char*) malloc(300 * sizeof(char));

        qry_build_i_dot_line_tag(&dotLineTag, pX, pY, cmX, cmY, isInside);

        //Anexando a tag do ponto(mini circulo) e da linha na string final:
            
            char* svgFinalDocumentQry2 = NULL;
                
            svg_append_content_to_final_document(&dotLineTag, svgFinalDocumentQry, &svgFinalDocumentQry2);

            free(svgFinalDocumentQry2);  free(dotLineTag);

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:
    //(ABSTRAIR)
        char* result = (char*) malloc(12*sizeof(char));

        if(isInside){
            strcpy(result, "INTERNO");
        }else{
            strcpy(result, "NAO INTERNO");
        }    

        char* txtContent = (char*) malloc(100 * sizeof(char));

        sprintf(txtContent, "%s\n%s: %s %s\n\n", *qryCommand, J, jType, result);

        char* txtFinalContent2 = NULL;

        svg_append_content_to_final_document(&txtContent, txtFinalContent, &txtFinalContent2);

        free(J); free(jType); free(result);  free(txtContent);  free(txtFinalContent2);
}

void qry_delf(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count){
    
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

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:
    //(ABSTRAIR)
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
                }else if(commands[i][0][0] == 't'){

                    sprintf(txtContent, "%s\ntipo: texto, id: %s, x: %s, y: %s, corb: %s, corp: %s, texto: %s\n\n", 
                                        *qryCommand, commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);                    
                }

                svg_append_content_to_final_document(&txtContent, txtFinalContent, &txtFinalContent2);
                break;
            }
        }

    free(J); free(searchJ); free(txtContent); free(txtFinalContent2);
}

void qry_delf2(char* *qryCommand, char* *svgFinalDocumentQry, char* *txtFinalContent, char* commands[][8], int geo_lines_count){

    //Conseguindo o intevalo de IDs das figuras/textos que seram excluidas: 

        char* J = (char*) malloc(6 * sizeof(char));
        char* K = (char*) malloc(6 * sizeof(char));

        sscanf(&qryCommand[0][6], "%s %s", J, K);

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

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:
    //(ABSTRAIR)
        char* txtContent = (char*) malloc(300 * sizeof(char));

        char* txtFinalContent2 = NULL;

        sprintf(txtContent, "%s\n", *qryCommand);

        svg_append_content_to_final_document(&txtContent, txtFinalContent, &txtFinalContent2);

        for(int i = 0; i < geo_lines_count; ++i){

            if(strtof(commands[i][1], NULL) >= strtof(J, NULL) && strtof(commands[i][1], NULL) <= strtof(K, NULL)){
                
                if(commands[i][0][0] == 'c'){

                    sprintf(txtContent, "tipo: circulo, id: %s, raio: %s, x: %s, y: %s, corb: %s, corp: %s\n\n", 
                                         commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);

                }else if(commands[i][0][0] == 'r'){

                    sprintf(txtContent, "tipo: retangulo, id: %s, w: %s, h: %s, x: %s, y: %s, corb: %s, corp: %s\n\n", 
                                         commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6], commands[i][7]);

                }else if(commands[i][0][0] == 't'){

                    sprintf(txtContent, "tipo: texto, id: %s, x: %s, y: %s, corb: %s, corp: %s, texto: %s\n\n", 
                                         commands[i][1], commands[i][2], commands[i][3], commands[i][4], commands[i][5], commands[i][6]);                    

                }

                txtFinalContent2 = NULL;

                svg_append_content_to_final_document(&txtContent, txtFinalContent, &txtFinalContent2);
            }
        }

        free(txtContent); free(txtFinalContent2);
    
        free(J); free(K); free(searchId);
}

void qry_pnt(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent, char* *pnt2){

    //Interpretar o comando query:

        char* J = (char*) malloc(8 * sizeof(char));
        char* newCorb = (char*) malloc(8 * sizeof(char));
        char* newCorp = (char*) malloc(8 * sizeof(char));

        sscanf(&qryCommand[0][4], "%s %s %s", J, newCorb, newCorp);
        
    //Extrair os dados da figura/txt a ser pintada:

        char* jDrawing[8];

        //getDrawingInfo(jDrawing, NULL, commands, geo_lines_count, J, NULL);

        for(int i = 0; i < geo_lines_count; i++){
    
            if(strcmp(commands[i][1], J) == 0){

                for(int k = 0; k<8; ++k){
                    jDrawing[k] = commands[i][k];
                } 

                break;
            }
        }

    //Construir uma nova tag para essa figura/txt com a nova cor de borda e preenchimento (ela sera printada por cima da antiga), e anexa-la na string final.

        char* tag = (char*) malloc(200 * sizeof(char));
        //essas variaveis vao guardar as cores originais da borda e preenchimento. (Para mais tarde imprimirmos-as no txt do pnt)
        char* originalCorb = (char*) malloc(15 * sizeof(char));
        char* originalCorp = (char*) malloc(15 * sizeof(char));

        if(*(jDrawing[0]) == 'c'){

            geo_build_circ_tag(&tag, jDrawing[1], jDrawing[2], jDrawing[3], jDrawing[4], newCorb, newCorp);
            sprintf(originalCorb, "%s", jDrawing[5]);
            sprintf(originalCorp, "%s", jDrawing[6]);
        
        }else if(*(jDrawing[0]) == 'r'){
            
            geo_build_rect_tag(&tag, jDrawing[1], jDrawing[2], jDrawing[3], jDrawing[4], jDrawing[5], newCorb, newCorp);
            sprintf(originalCorb, "%s", jDrawing[6]);
            sprintf(originalCorp, "%s", jDrawing[7]);        
            
        }else if(*(jDrawing[0]) == 't'){
            
            geo_build_txt_tag(&tag, jDrawing[1], jDrawing[2], jDrawing[3], newCorb, newCorp ,jDrawing[6]);
            sprintf(originalCorb, "%s", jDrawing[4]);
            sprintf(originalCorp, "%s", jDrawing[5]);        
        }   

        char* svgFinalDocumentQry2 = NULL;
                
        svg_append_content_to_final_document(&tag, svgFinalDocumentQry, &svgFinalDocumentQry2);

        free(svgFinalDocumentQry2); free(tag);

    //Anexando o texto referente ao comando atual no conteudo final a ser escrito no arquivo txt de saida:
    //(ABSTRAIR)
        char* txtContent = (char*) malloc(100 * sizeof(char));

        if(pnt2 == NULL){
            sprintf(txtContent, "%s\ncorb original: %s, corp original: %s\n\n", *qryCommand, originalCorb, originalCorp);
        }else{
            sprintf(txtContent, "%s\ni: %s, corb original: %s, corp original: %s\n\n", *pnt2, J, originalCorb, originalCorp);
        }

        char* txtFinalContent2 = NULL;

        svg_append_content_to_final_document(&txtContent, txtFinalContent, &txtFinalContent2);

        free(txtContent); free(txtFinalContent2);

        free(J); free(newCorb); free(newCorp); free(originalCorb); free(originalCorp);       
}

void qry_pnt2(char* *qryCommand, char* commands[][8], int geo_lines_count, char* *svgFinalDocumentQry, char* *txtFinalContent){
    
    //Interpretar o comando query:

        char* J = (char*) malloc(8 * sizeof(char));
        char* K = (char*) malloc(8 * sizeof(char));
        char* newCorb = (char*) malloc(8 * sizeof(char));
        char* newCorp = (char*) malloc(8 * sizeof(char));

        sscanf(&qryCommand[0][5], "%s %s %s %s", J, K, newCorb, newCorp);

    //Chamar a funçao svg_qry_pnt para casa uma das entidades cujo id esta entre J e K:

        char* pntCommand = (char*) malloc(30 * sizeof(char));

        for(int i = strtol(J, NULL, 10); i<=strtol(K, NULL, 10); ++i){

            for(int z = 0; z<geo_lines_count; ++z){

                if(strtol(commands[z][1], NULL, 10) == i){
                    
                    sprintf(pntCommand, "pnt %d %s %s", i, newCorb, newCorp);

                    qry_pnt(&pntCommand, commands, geo_lines_count, svgFinalDocumentQry, txtFinalContent, qryCommand);

                    break;
 
                }         
            }
        }

        free(pntCommand); free(J); free(K); free(newCorb); free(newCorp);
}