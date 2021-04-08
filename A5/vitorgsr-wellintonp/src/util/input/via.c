#include "../../include/headers.h"
#include "../../include/util.h"
#include "../../include/elements.h"

//numero maximo de partes que um comando vindo de um arquivo via pode ter
#define maxNumberOfViaCommandParts 8

//T5
void readVertex(char* command, char** commandParts, City Ct);
void readEdge(char* command, char** commandParts, City Ct);

void freeReadViaResources(char* command, char** commandParts);

void readVia(File via, City Ct){
                                             
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];
    char** commandParts = createCommandParts(maxNumberOfViaCommandParts);
    
    while(!feof(via)){
        if(fgets(command, commandMaxLength, via) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;
        
        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n')  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        
        sscanf(command, "%s ", commandType);

        if(commandType[0] == 'v') //lidando com vertices
            readVertex(command, commandParts, Ct);
            
        else if(commandType[0] == 'e') //lidando arestas
            readEdge(command, commandParts, Ct);
    }

    freeReadViaResources(command, commandParts);
}

void readVertex(char* command, char** commandParts, City Ct){
    sscanf(&command[2], "%s %s %s", commandParts[0], commandParts[1], commandParts[2]);
    

}

void readEdge(char* command, char** commandParts, City Ct){
    sscanf(&command[2], "%s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);   


}

void freeReadViaResources(char* command, char** commandParts){
    free(command);   

    for(int i = 0; i<8; i++)
        free(commandParts[i]);
    
    free(commandParts);
}