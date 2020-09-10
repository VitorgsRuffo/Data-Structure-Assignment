#include "../include/headers.h"
#include "../include/utils.h"

char* buildInputFilePath(char* inputDirectory, char* inputFileName);

File openInputFile(Parameters Param, char* fileType){ 
    
    char* inputDirectory = getInputDirectory(Param); 
    char* inputFileName;

    if(strcmp(fileType, "geo") == 0){
        inputFileName = getGeoName(Param); 
        
    }else if(strcmp(fileType, "qry") == 0){
        inputFileName = getQryName(Param);

    }else{
        printf("%s é um tipo invalido. Nao foi possivel abrir o arquivo ..\n", fileType);
        return NULL;
    }
    
    char* inputFilePath = buildInputFilePath(inputDirectory, inputFileName); 

    FILE* file = fopen(inputFilePath, "r");

    if(file == NULL){
        printf("Erro ao abrir o arquivo %s..\nFinalizando o programa..\n", fileType);
        exit(1);
    }
    printf("O arquivo %s foi aberto..\n", fileType);  //printf("caminho: %s.\n", inputFilePath);
    
    free(inputFilePath);
    return file;
}

//Funcao privada para contrucao do caminho do arquivo que sera aberto.
char* buildInputFilePath(char* inputDirectory, char* inputFileName){

    char* inputFilePath = (char*) malloc((strlen(inputDirectory) + strlen(inputFileName)) * sizeof(char) + 5);
    int inputDirectoryLength = strlen(inputDirectory);
       
    if((inputDirectory[inputDirectoryLength-1] != '/') && (inputFileName[0] != '/') //corrige o seguinte erro:  /home/ed/testes001.geo  -> dirarq
        && (inputFileName[0] != '.') ){

        sprintf(inputFilePath, "%s/%s", inputDirectory, inputFileName);

    }else if((inputDirectory[inputDirectoryLength-1] != '/') && (inputFileName[0] == '.')){ //corrige o seguinte erro: /home/ed/testes./001.geo -> dir./arq

        sprintf(inputFilePath, "%s/%s", inputDirectory, inputFileName);

    }else if((inputDirectory[inputDirectoryLength-1] == '/') && (inputFileName[0] == '/')){  //corrige o seguinte erro: /home/ed/testes//001.geo dir//arq

        sprintf(inputFilePath, "%s.%s", inputDirectory, inputFileName);

    }else{ //caso o path seja inserido corretamente: ././arq ;  dir/./arq ; 
        sprintf(inputFilePath, "%s%s", inputDirectory, inputFileName);
    }
    
    return inputFilePath;
}

void closeInputFile(File file){
    fclose(file);
}