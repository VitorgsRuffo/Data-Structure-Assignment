#include "../include/headers.h"
#include "../include/utils.h"
#include "../include/urbanElements.h"

int isElementNull(Element element, char* elementName, char* functionName){
    if(element == NULL){
        printf("Erro: A instancia de %s nao existe..\n(Funcao: %s.)\n", elementName,functionName);
        return 1;
    }
    return 0;
}

char** createCommandParts(int numberOfParts){
    char** commandParts = (char**) malloc(sizeof(char*) * numberOfParts);
    
    for(int i = 0; i<numberOfParts; i++){
        if(i==6){ // se i for igual a 6 aloca memoria extra caso este comando seja de texto (pois, na parte 7 de um comando de texto vem uma string relativamente grande)
            commandParts[i] = (char*) malloc(51 * sizeof(char));
        }else{
            commandParts[i] = (char*) malloc(16 * sizeof(char));
        }
    }
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

int isBlockInCircleRange(Info blockInfo, double x, double y, double radius){ /*isBlockInCircleRange*/
    double blockX = atof(getBlockX(blockInfo));
    double blockY = atof(getBlockY(blockInfo));
    
    double blockWidth = atof(getBlockWidth(blockInfo));
    double blockHeight = atof(getBlockHeight(blockInfo));
    
    //os 4 pontos devem estar dentro da regiao do circulo cujo centro é o mesmo do equipamento urbano
    int blockXIsInside = (int)((blockX < x + radius) && (blockX > x - radius));
    int blockYIsInside = (int)((blockY < y + radius) && (blockY > y - radius));
    int blockXPlusWidthIsInside = (int)((blockX + blockWidth < x + radius) && (blockX + blockWidth > x - radius));
    int blockYPlusHeightIsInside = (int)((blockY + blockHeight < y + radius) && (blockY + blockHeight > y - radius));
    
    if((blockXIsInside && blockYIsInside) &&
       (blockXPlusWidthIsInside && blockYIsInside) &&
       (blockXIsInside && blockYPlusHeightIsInside) &&
       (blockXPlusWidthIsInside && blockYPlusHeightIsInside)){
        
        return 1;
    }else{
        return 0;
    }
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