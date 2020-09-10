#include "../include/headers.h"
#include "../include/util.h"
#include "../include/figures.h"
#include "../include/urbanElements.h"
#include "../drawing.h"
#include "../customization.h"

/*
* numero maximo de partes que um comando vindo de um arquivo geo pode ter
*/
#define maxNumberOfGeoCommandParts 8

void readCircle(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom);
void readRectangle(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom);
void readText(char* command, char** commandParts, Drawing Dr);
void readBlock(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom);
void readHydrant(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom);
void readSemaphore(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom);
void readBaseRadio(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom);

void readFiguresCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readBlockCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readHydrantCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readSemaphoreCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readBaseRadioCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);

void freeReadGeoResources(char* command, char** commandParts, ElementsCustomization elementsCustom);

void readGeo(File geo, Drawing Dr){
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];

    char** commandParts;
    commandParts = createCommandParts(maxNumberOfGeoCommandParts);
    
    ElementsCustomization elementsCustom = createElementsCustomization();

    while(!feof(geo)){
        if(fgets(command, commandMaxLength, geo) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;
        
        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n'){  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        }

        sscanf(command, "%s ", commandType);
        if(!strcmp(commandType, "c")) //lidando com circulo:
            readCircle(command, commandParts, Dr, elementsCustom);

        else if(!strcmp(commandType, "r")) //lidando com retangulo:
            readRectangle(command, commandParts, Dr, elementsCustom);

        else if(!strcmp(commandType, "t")) //lidando com texto:   
            readText(command, commandParts, Dr);
            
        else if(!strcmp(commandType, "q")) //lidando com quadra: 
            readBlock(command, commandParts, Dr, elementsCustom);

        else if(!strcmp(commandType, "h")) //lidando com hidrante:
            readHydrant(command, commandParts, Dr, elementsCustom);

        else if(!strcmp(commandType, "s")) //lidando com semaforos:   
            readSemaphore(command, commandParts, Dr, elementsCustom);            

        else if(!strcmp(commandType, "rb")) //lidando com radio-bases:    
            readBaseRadio(command, commandParts, Dr, elementsCustom);

        else if(!strcmp(commandType, "sw")) //lidando com as novas estilizacoes de circulo e retangulo:
            readFiguresCustomization(command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "cq")) //lidando com as novas estilizacoes de quadra:
            readBlockCustomization(command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "ch")) //lidando com as novas estilizacoes de hidrante:
            readHydrantCustomization(command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "cs"))//lidando com as novas estilizacoes de semaforo:
            readSemaphoreCustomization(command, commandParts, elementsCustom);
        
        else if(!strcmp(commandType, "cr"))//lidando com as novas estilizacoes de radio-base: 
            readBaseRadioCustomization(command, commandParts, elementsCustom);
    }

    freeReadGeoResources(command, commandParts, elementsCustom);
}

void readCircle(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    Circle circle = createCircle(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6], getFiguresCwCustomization(elementsCustom));
    List circleList = getCircleList(Dr);
    insert(circleList, circle);
}

void readRectangle(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6], commandParts[7]);
    Rectangle rectangle = createRectangle(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6], commandParts[7], getFiguresRwCustomization(elementsCustom));
    List rectangleList = getRectangleList(Dr);
    insert(rectangleList, rectangle); 
}

void readText(char* command, char** commandParts, Drawing Dr){
    sscanf(command, "%s %s %s %s %s %s %[^\n]s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    Text text = createText(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    List textList = getTextList(Dr);
    insert(textList, text);
}

void readBlock(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5]);
    Block block = createBlock(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], getBlockSwCustomization(elementsCustom), getBlockCfillCustomization(elementsCustom), getBlockCstrkCustomization(elementsCustom));
    List blockList = getBlockList(Dr);
    insert(blockList, block);
}

void readHydrant(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    Hydrant hydrant = createHydrant(commandParts[1], commandParts[2], commandParts[3], getHydrantSwCustomization(elementsCustom), getHydrantCfillCustomization(elementsCustom), getHydrantCstrkCustomization(elementsCustom));
    List hydrantList = getHydrantList(Dr);
    insert(hydrantList, hydrant);
}

void readSemaphore(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    Semaphore semaphore = createSemaphore(commandParts[1], commandParts[2], commandParts[3], getSemaphoreSwCustomization(elementsCustom), getSemaphoreCfillCustomization(elementsCustom), getSemaphoreCstrkCustomization(elementsCustom));
    List semaphoreList = getSemaphoreList(Dr);
    insert(semaphoreList, semaphore);
}

void readBaseRadio(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    BaseRadio baseR = createBaseRadio(commandParts[1], commandParts[2], commandParts[3], getBaseRadioSwCustomization(elementsCustom), getBaseRadioCfillCustomization(elementsCustom), getBaseRadioCstrkCustomization(elementsCustom));
    List baseRadioList = getBaseRadioList(Dr);
    insert(baseRadioList, baseR);
}

void readFiguresCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s", commandParts[0], commandParts[1], commandParts[2]);
    setFiguresCwCustomization(elementsCustom, commandParts[1]);
    setFiguresRwCustomization(elementsCustom, commandParts[2]);
}

void readBlockCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';
    
    setBlockSwCustomization(elementsCustom, commandParts[1]);
    setBlockCfillCustomization(elementsCustom, commandParts[2]);
    setBlockCstrkCustomization(elementsCustom, commandParts[3]);
}

void readHydrantCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';

    setHydrantSwCustomization(elementsCustom, commandParts[1]);
    setHydrantCfillCustomization(elementsCustom, commandParts[2]);
    setHydrantCstrkCustomization(elementsCustom, commandParts[3]);
}

void readSemaphoreCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';

    setSemaphoreSwCustomization(elementsCustom, commandParts[1]);
    setSemaphoreCfillCustomization(elementsCustom, commandParts[2]);
    setSemaphoreCstrkCustomization(elementsCustom, commandParts[3]);
}

void readBaseRadioCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';

    setBaseRadioSwCustomization(elementsCustom, commandParts[1]);
    setBaseRadioCfillCustomization(elementsCustom, commandParts[2]);
    setBaseRadioCstrkCustomization(elementsCustom, commandParts[3]);
}

void freeReadGeoResources(char* command, char** commandParts, ElementsCustomization elementsCustom){
    free(command);   
    for(int i = 0; i<8; i++){
        free(commandParts[i]);
    } 
    free(commandParts);
    freeElementsCustomization(elementsCustom);
}