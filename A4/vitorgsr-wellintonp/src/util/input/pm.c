#include "../include/headers.h"
#include "../include/util.h"
#include "../include/elements.h"

//numero maximo de partes que um comando vindo de um arquivo ec pode ter
#define maxNumberOfEcCommandParts 8

void readPeople(char* command, char** commandParts, City Ct);
void readPeopleAddress(char* command, char** commandParts, City Ct);
void freeReadEcResources(char* command, char** commandParts);

void readPm(File pm, City Ct){
                                             
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];
    char** commandParts = createCommandParts(maxNumberOfEcCommandParts);
    
    while(!feof(pm)){
        if(fgets(command, commandMaxLength, pm) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;
        
        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n')  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        
        sscanf(command, "%s ", commandType);

        if(!strcmp(commandType, "p")) //lidando com pessoas
            readPeople(command, commandParts, Ct);

        else if(!strcmp(commandType, "m")) //lidando endereço de pessoa
            readPeopleAddress(command, commandParts, Ct);
    }

    freeReadEcResources(command, commandParts);
}

void readPeople(char* command, char** commandParts, City Ct){

    sscanf(&command[2], "%s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2],commandParts[3],commandParts[4]);
    Person person = createPerson(commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4]);
    
    //Inserindo na HashTable
    DataStructure peopleTable = getPeopleTable(Ct);
    insertHashTable(peopleTable, person);
}

void readPeopleAddress(char* command, char** commandParts, City Ct){
    
    sscanf(&command[2], "%s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4]);
    House house = createHouse(commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], Ct);

    // Inserçao na HashTable (verificar se há necessidade)
    //DataStructure housesTable = getHousesTable(Ct); 
    //insertHashTable(housesTable, house);

    // Inserindo na quadTree
    DataStructure housesTree = getHousesTree(Ct);
    insertPQuadTree(housesTree, getHouseCoordinates, house);
}

void freeReadEcResources(char* command, char** commandParts){
    free(command);   

    for(int i = 0; i<8; i++)
        free(commandParts[i]);
    
    free(commandParts);
}