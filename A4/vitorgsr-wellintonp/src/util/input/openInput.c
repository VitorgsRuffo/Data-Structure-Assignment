#include "../../include/headers.h"
#include "openInput.h"
#include "parameters.h"

char* buildInputFilePath(char* inputDirectory, char* inputFileName);

File openInputFile(Parameters Param, getParameterName get){ 
    
    if(Param == NULL || get == NULL)
        return NULL;

    char* inputDirectory = getInputDirectory(Param); 
    char* inputFileName = (*get)(Param);

    char* inputFilePath = buildInputFilePath(inputDirectory, inputFileName); 

    FILE* file = fopen(inputFilePath, "r");

    if(file == NULL)
       return NULL;
        
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