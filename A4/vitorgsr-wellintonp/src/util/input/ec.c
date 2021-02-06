#include "../include/headers.h"
#include "../include/util.h"
#include "../include/elements.h"


/*

//numero maximo de partes que um comando vindo de um arquivo ec pode ter

#define maxNumberOfEcCommandParts 8

void freeReadEcResources(char* command, char** commandParts);

void readEc(File ec, City Ct){
    
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];

    char** commandParts;
    commandParts = createCommandParts(maxNumberOfEcCommandParts);
    

    while(!feof(ec)){
        if(fgets(command, commandMaxLength, ec) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;
        
        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n')  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        

        sscanf(command, "%s ", commandType);

        if(!strcmp(commandType, "t")) //lidando com tipos de estabelecimentos comerciais
            readEstablishmentType(command, commandParts, Dr);

        else if(!strcmp(commandType, "e"))//lidando com estabelecimentos comerciais.
            readEstablishment(command, commandParts, Dr);

       
    }

    freeReadEcResources(command, commandParts);
}


void readEstablishmentType(char* command, char** commandParts, Drawing Dr){

    sscanf(&command[2], "%s %s", commandParts[0], commandParts[1]);
    EstablishmentType et = createEstablishmentType(commandParts[0], commandParts[1]);
    HashTable etTable = getEstablishmentTypeTable(Dr);
    insertHashTable(etTable, et);
}


void readCircle(char* command, char** commandParts, Drawing Dr, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    Circle circle = createCircle(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6], getFiguresCwCustomization(elementsCustom));
    List circleList = getCircleList(Dr);
    insert(circleList, circle);
}


void readEstablishment(char* command, char** commandParts, Drawing Dr){
    sscanf(&command[2], "%s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    // new estabelecimento
    // Add na estrutura
}



void freeReadEcResources(char* command, char** commandParts){
    free(command);   

    for(int i = 0; i<8; i++)
        free(commandParts[i]);
    
    free(commandParts);
}
*/