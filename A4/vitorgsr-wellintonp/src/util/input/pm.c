#include "../../include/headers.h"
#include "../../include/util.h"
#include "../../include/elements.h"

//numero maximo de partes que um comando vindo de um arquivo pm pode ter
#define maxNumberOfPmCommandParts 8

void readPeople(char* command, char** commandParts, City Ct);
void readPeopleAddress(char* command, char** commandParts, City Ct);
void freeReadPmResources(char* command, char** commandParts);

void readPm(File pm, City Ct){
                                             
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];
    char** commandParts = createCommandParts(maxNumberOfPmCommandParts);
    
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

    freeReadPmResources(command, commandParts);
}

void readPeople(char* command, char** commandParts, City Ct){

    sscanf(&command[2], "%s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2],commandParts[3],commandParts[4]);
    char gender = commandParts[3][0];
    Person person = createPerson(commandParts[0], commandParts[1], commandParts[2], gender, commandParts[4]);
    
    DataStructure* peopleTable = getPeople(Ct);
    insertHashTable((HashTable*) peopleTable, person);
}

void readPeopleAddress(char* command, char** commandParts, City Ct){
    
    sscanf(&command[2], "%s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4]);
    char face = commandParts[2][0];
    int number = atoi(commandParts[3]);
    House house = createHouse(commandParts[0], commandParts[1], face, number, commandParts[4], Ct);


    // Inserçao na HashTable
    DataStructure* housesTable = getHousesTable(Ct); 
    insertHashTable((HashTable*) housesTable, house);

    DataStructure housesTree = getHousesTree(Ct);
    insertPQuadTree(housesTree, getHouseCoordinates, house);
}

void freeReadPmResources(char* command, char** commandParts){
    free(command);   

    for(int i = 0; i<8; i++)
        free(commandParts[i]);
    
    free(commandParts);
}