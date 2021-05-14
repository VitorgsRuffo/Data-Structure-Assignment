#include "../../include/headers.h"
#include "../../elements/urban-elements/city.h"
#include "./qry.h"

File openTxt(Parameters Param);
void closeTxt(File txt);

void freeExecuteQryResources(char* command);

void executeQry(File qry, City Ct, Parameters Param){
    if(qry == NULL || Ct == NULL || Param == NULL) return;
    
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];

    File txt = openTxt(Param);
    if(txt == NULL){
        free(command);
        return;
    }

    int uniqueId = 0;

    while(!(feof(qry))){

        if(fgets(command, commandMaxLength, qry) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;

        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n'){  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        }

        sscanf(command, "%s ", commandType);
        if(!strcmp(commandType, "o?"))
            executeOverlapTest(command, Ct, txt);
        
        else if(!strcmp(commandType, "i?"))
            executeInnerPointTest(command, Ct, txt);
    
        else if(!strcmp(commandType, "pnt") || !strcmp(commandType, "pnt*"))  
            executeElementPainting(command, Ct, txt, commandType);

        else if(!strcmp(commandType, "delf") || !strcmp(commandType, "delf*")) 
            executeElementDeletion(command, Ct, txt, commandType);        
        
        else if(!strcmp(commandType, "dq"))   
            executeBlocksDeletion(command, Ct, txt);
        
        else if(!strcmp(commandType, "del")) 
            executeUrbanElementDeletion(command, Ct, txt);
    
        else if(!strcmp(commandType, "cbq")) 
            executeBlocksBorderColorChanging(command, Ct, txt);

        else if(!strcmp(commandType, "crd?"))
            executeUrbanElementInformationChecking(command, Ct, txt);
        
        else if(!strcmp(commandType, "car"))
            executeUrbanElementsTotalAreaCalculationInRange(command, Ct, txt);

        else if(!strcmp(commandType, "cv"))
            executeCovidCasesReport(uniqueId, command, Ct);

        else if(!strcmp(commandType, "soc"))
            executeMedicalTreatmentSearching(command, Ct, txt);

        else if(!strcmp(commandType, "ci"))
            executeCovidIncidenceReportInRegion(command, Ct, txt);

        else if(!strcmp(commandType, "m?"))
            executeBlockResidentsReport(command, Ct, txt);

        else if(!strcmp(commandType, "dm?"))
            executePersonalInformationChecking(command, Ct, txt);

        else if(!strcmp(commandType, "de?"))
            executeEstablishmentInformationChecking(command, Ct, txt);

        else if(!strcmp(commandType, "mud"))
            executeChangeOfAddress(command, Ct, txt);

        else if(!strcmp(commandType, "eplg?"))
            executeHighlightEstablishmentInRange(command, Ct, txt);
        
        else if(!strcmp(commandType, "catac"))
            executeUrbanElementsDeletion(command, Ct, txt);
        
        else if(!strcmp(commandType, "dmprbt"))
            executeTreeStatePrinting(command, Ct, Param);

        else if(!strcmp(commandType, "@m?"))
            saveLocationByCpf(command, Ct);

        else if(!strcmp(commandType, "@e?"))
            saveLocationByAddress(command, Ct);




        uniqueId++;
    }
    
    closeTxt(txt);
    freeExecuteQryResources(command);
}

File openTxt(Parameters Param){
    char* txtPath = buildQryOutputPath(Param, NULL, "txt");
    File txt = fopen(txtPath, "a");
    if(txt == NULL)
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
    if(queryElement == NULL) return;

    char* qryElem = (char*) queryElement;
    free(qryElem);
}