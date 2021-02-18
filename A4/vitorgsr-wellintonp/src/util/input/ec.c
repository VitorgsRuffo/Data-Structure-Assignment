#include "../../include/headers.h"
#include "../../include/util.h"
#include "../../include/elements.h"


//numero maximo de partes que um comando vindo de um arquivo ec pode ter

#define maxNumberOfEcCommandParts 8

//T4
void readEstablishmentType(char* command, char** commandParts, City Ct);
void readEstablishment(Stack* establishments, char* command, char** commandParts, City Ct);

void freeReadEcResources(char* command, char** commandParts);

void readEc(File ec, City Ct){
    
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];
    char** commandParts = createCommandParts(maxNumberOfEcCommandParts);
    
    // Os dados incluidos na stack vão ser pre-processados antes de serem inseridos na estrutura. (p-quadtree)
    Stack establishments = createStack();

    while(!feof(ec)){
        if(fgets(command, commandMaxLength, ec) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;
        
        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n')  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        
        sscanf(command, "%s ", commandType);

        if(!strcmp(commandType, "t")) //lidando com tipos de estabelecimentos comerciais
            readEstablishmentType(command, commandParts, Ct);

        else if(!strcmp(commandType, "e"))//lidando com estabelecimentos comerciais.
            readEstablishment(&establishments, command, commandParts, Ct);
    }

    balancedlyInsertObjectsInPQuadTree(getEstablishmentsTree(Ct), establishments);

    freeReadEcResources(command, commandParts);
}

void readEstablishmentType(char* command, char** commandParts, City Ct){

    sscanf(&command[2], "%s %s", commandParts[0], commandParts[1]);
    EstablishmentType et = createEstablishmentType(commandParts[0], commandParts[1]);

    DataStructure* establishmentTypes = getEstablishmentTypes(Ct);
    insertHashTable((HashTable*) establishmentTypes, et);
}

void readEstablishment(Stack* establishments, char* command, char** commandParts, City Ct){
    
    sscanf(&command[2], "%s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    char face = commandParts[4][0]; 
    int number = atoi(commandParts[5]);
    
    Establishment est = createEstablishment(commandParts[0], commandParts[1], commandParts[2], commandParts[3], face, number, commandParts[6], Ct);
    
    stackPush(establishments, est);

    DataStructure* establishmentHashTable = getEstablishmentsTable(Ct); 
    insertHashTable((HashTable*) establishmentHashTable, est);
}

void freeReadEcResources(char* command, char** commandParts){
    free(command);   

    for(int i = 0; i<8; i++)
        free(commandParts[i]);
    
    free(commandParts);
}