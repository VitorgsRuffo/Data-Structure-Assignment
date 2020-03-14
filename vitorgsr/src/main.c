#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void deal_with_parameters();

int main (int argc, char* argv[]){

    char* inputDir = NULL;
    char* geoFileName = NULL;
    char* qryFileName = NULL;

    char* outputDIr = NULL;

    deal_with_parameters(argc, argv, inputDir, geoFileName, qryFileName, outputDIr);

    return 0;
}


void deal_with_parameters(int paraNum, char* parameters[], char* inputDir, char* geoFileName, char* qryFileName, char* outputDir){

    int i = 1;


    while(i < paraNum){

        if(strcmp("-e", parameters[i]) == 0){

            //A proxima string vai ser o caminho para o diretório base de entrada:
            ++i;

            //Alocando memória para guardar a string referente ao nome diretório base de entrada:
            inputDir = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char));
            //obs: o +1 serve para garantirmos um lugar para o character nulo (i.e, '\0') no final da string.
            
            strcpy(inputDir, parameters[i]);

        }else if(strcmp("-f", parameters[i]) == 0){
            
            //A proxima string vai ser o nome do arquivo .geo:
            ++i;

            //Alocando memória para guardar a string referente ao nome do arquivo .geo:
            geoFileName = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char));

            strcpy(geoFileName, parameters[i]);

        }else if(strcmp("-q", parameters[i]) == 0){

            //A proxima string vai ser o nome do arquivo .qry:
            ++i;

            // ''    ''    ''
            qryFileName = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char)); 

            strcpy(qryFileName, parameters[i]);

        }else if(strcmp("-o", parameters[i]) == 0){

            //A proxima string vai ser o nome do diretorio de arquivos de saida:
            ++i;

            // ''    ''   ''
            outputDir = (char*) malloc((strlen(parameters[i]) + 1) * sizeof(char)); 

            strcpy(outputDir, parameters[i]);

        }

        i++;
    }

    printf("%s\n%s\n%s\n%s", inputDir, geoFileName, qryFileName, outputDir);

}