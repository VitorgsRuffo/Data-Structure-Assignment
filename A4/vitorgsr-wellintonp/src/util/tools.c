#include "../include/headers.h"
#include "../include/elements.h"
#include "./data-structure/stack.h"
#include "tools.h"

void swapInformations(Info* info1, Info* info2) { 
    Info temp;

    temp = *info1;
    *info1 = *info2;
    *info2 = temp;  
} 

char** createCommandParts(int numberOfParts){
    char** commandParts = (char**) malloc(sizeof(char*) * numberOfParts);
    
    for(int i = 0; i<numberOfParts; i++)
        commandParts[i] = (char*) malloc(60 * sizeof(char));
    
    return commandParts;
}

char* getFileNameWithoutPathAndExtension(char* fullFileName){ //Retorna somente o nome do arquivo, retirando possiveis caminho e a sua extensão.
    
    int j = 0;
    int fullFileNameLength = strlen(fullFileName); 

    char* fileNameWithoutExtension;

    for(int i = 0; i<fullFileNameLength; ++i){  

        if(fullFileName[i] == '/'){
            j = i + 1;
        }

        if(fullFileName[i] == '.' && fullFileName[i+1] != '/'){ //corrige o erro ./dir/arq.extension
            
            fullFileName[i] = ' ';
            fileNameWithoutExtension = (char*) malloc((strlen(&fullFileName[j]) - 3) * sizeof(char));
            sscanf(&fullFileName[j],"%s", fileNameWithoutExtension);
            fullFileName[i] = '.';
            break;
        }
    }
    return fileNameWithoutExtension;
}

char* buildQryOutputPath(Parameters Param, char* extension){
    char* outputDirectory = getOutputDirectory(Param);
    int outputDirectoryLength = strlen(outputDirectory);

    char* fullGeoName = getGeoName(Param);
    char* geoNameWithoutPathAndExtension = getFileNameWithoutPathAndExtension(fullGeoName);
    
    char* fullQryName = getQryName(Param);
    char* qryNameWithoutPathAndExtension = getFileNameWithoutPathAndExtension(fullQryName);

    int qryOutputPathLength = strlen(outputDirectory) + strlen(geoNameWithoutPathAndExtension) + strlen(qryNameWithoutPathAndExtension) + strlen(".ext") + 5;
    char* qryOutputPath = (char*) malloc(qryOutputPathLength * sizeof(char));

    if(outputDirectory[outputDirectoryLength - 1] == '/'){
        sprintf(qryOutputPath, "%s%s-%s.%s", outputDirectory, geoNameWithoutPathAndExtension, qryNameWithoutPathAndExtension, extension);    
    }else{
        sprintf(qryOutputPath, "%s/%s-%s.%s", outputDirectory, geoNameWithoutPathAndExtension, qryNameWithoutPathAndExtension, extension);    
    }

    free(geoNameWithoutPathAndExtension);
    free(qryNameWithoutPathAndExtension);
    return qryOutputPath;
}

char* getUrbanElementToString(Info urbanElementInfo, char* urbanElementType){
    char* urbanElementToString = NULL;

    if(urbanElementType[0] == 'q')
        urbanElementToString = blockToString(urbanElementInfo);

    else if(urbanElementType[0] == 'h')
        urbanElementToString = hydrantToString(urbanElementInfo);
        
    else if(urbanElementType[0] == 's')
        urbanElementToString = semaphoreToString(urbanElementInfo);
        
    else if(urbanElementType[0] == 'r') 
        urbanElementToString = baseRadioToString(urbanElementInfo);
       
    return urbanElementToString;
}