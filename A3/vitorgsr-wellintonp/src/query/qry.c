#include "../include/headers.h"
#include "../include/util.h"
#include "../drawing/drawing.h"
#include "../include/query.h"

File openTxt(Parameters Param);
void closeTxt(File txt);

void freeExecuteQryResources(char* command);

void executeQry(File qry, Drawing Dr, Parameters Param){
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];

    File txt = openTxt(Param);

    while(!(feof(qry))){

        if(fgets(command, commandMaxLength, qry) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;

        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n'){  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        }

        sscanf(command, "%s ", commandType);
        if(!strcmp(commandType, "o?"))
            executeOverlapTest(command, Dr, txt);
        
        else if(!strcmp(commandType, "i?"))
            executeInnerPointTest(command, Dr, txt);
    
        else if(!strcmp(commandType, "pnt") || !strcmp(commandType, "pnt*"))  
            executeElementPainting(command, Dr, txt, commandType);

        else if(!strcmp(commandType, "delf") || !strcmp(commandType, "delf*")) 
            executeElementDeletion(command, Dr, txt, commandType);        
        
        else if(!strcmp(commandType, "dq"))   
            executeBlocksDeletion(command, Dr, txt);
        
        else if(!strcmp(commandType, "del")) 
            executeUrbanElementDeletion(command, Dr, txt);
    
        else if(!strcmp(commandType, "cbq")) 
            executeBlocksBorderColorChanging(command, Dr, txt);

        else if(!strcmp(commandType, "crd?"))
            executeUrbanElementInformationChecking(command, Dr, txt);
        
        else if(!strcmp(commandType, "car"))
            executeUrbanElementsTotalAreaCalculationInRange(command, Dr, txt);

        else if(!strcmp(commandType, "cv"))
            executeCovidCasesReport(command, Dr);
    }
    
    closeTxt(txt);
    freeExecuteQryResources(command);
}

File openTxt(Parameters Param){
    char* txtPath = buildQryOutputPath(Param, "txt");
    File txt = fopen(txtPath, "a");
    if(isElementNull(txt, "txt", "openTxt"))
        return NULL;
    
    free(txtPath);
    return txt;
}

void closeTxt(File txt){
    fclose(txt);
}

void freeExecuteQryResources(char* command){
    free(command);   
}

void freeQueryElement(QueryElement queryElement){
    if(isElementNull(queryElement, "query", "freeQueryElement"))
        return;

    char* qryElem = (char*) queryElement;
    free(qryElem);
}