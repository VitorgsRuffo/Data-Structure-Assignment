#include "../include/headers.h"
#include "../include/util.h"

typedef struct parameters {
    char* inputDirectory;   // -e: diretorio de entrada
    char* geoName;          // -f: nome + extensao do arquivo .geo
    char* qryName;          // -q: nome + extensao do arquivo .qry
    char* outputDirectory;  // -o: diretorio de saida
    char* ecName;           // -ec: nome + extensao do arquivo .ec
    char* pmName;           // -pm: nome + extensao do arquivo .pm
}parameters;

//Alocar memoria para o TAD que representa os parametros do programa
Parameters createParameters(){
    parameters *param = (parameters*) malloc(sizeof(parameters));
    
    if(param == NULL){
        printf("Erro ao alocar memória para o TAD dos parametros..\nFinalizando o programa..\n");
        exit(1);
    }

    //Limpando o lixo dos ponteiros alocados
    param->inputDirectory = NULL;
    param->geoName = NULL;
    param->qryName = NULL;
    param->outputDirectory = NULL;
    param->ecName = NULL;
    param->pmName = NULL;
    
    return param;
}

void setCurrentParameter(char** currentParam, char* currentArgv){
    *currentParam = (char*) malloc((strlen(currentArgv) + 1) * sizeof(char)); //Alocando memória para guardar a string referente ao parametro atual.
    
    if(*currentParam == NULL){
        printf("Erro ao alocar memoria para o parametro \"%s\"..\nFinalizando o programa..\n", currentArgv);
        exit(1);
    }
    
    strcpy(*currentParam, currentArgv);
}

//Alimentar o TAD com os parametros do terminal:
void setParameters(Parameters Param, char* argv[], int argc){
    int i = 1;
    parameters *param = (parameters*) Param; 
    
    while(i < argc){

        if(strcmp("-e", argv[i]) == 0){
            ++i;
            setCurrentParameter(&param->inputDirectory, argv[i]);
            
        }else if(strcmp("-f", argv[i]) == 0){
            ++i;
            setCurrentParameter(&param->geoName, argv[i]);

        }else if(strcmp("-q", argv[i]) == 0){
            ++i;
            setCurrentParameter(&param->qryName, argv[i]);

        }else if(strcmp("-o", argv[i]) == 0){
            ++i;
            setCurrentParameter(&param->outputDirectory, argv[i]);
            
        }else if(strcmp("-ec", argv[i]) == 0){
            ++i;
            setCurrentParameter(&param->ecName, argv[i]);

        }else if(strcmp("-pm", argv[i]) == 0){
            ++i;
            setCurrentParameter(&param->pmName, argv[i]);
        }

        i++;
    }

    //Se um diretorio de entrada não for especificado (-e), usaremos o diretorio atual:
    if(param->inputDirectory == NULL){ 
        param->inputDirectory = (char*) malloc(3 * sizeof(char));     
        strcpy(param->inputDirectory, "./");  
    }

    //Geo e out são obrigatorios!
    if(param->geoName == NULL){
        printf("O parametro -f, que e obrigatorio, esta ausente..\nFinalizando o programa..\n");
        exit(1);
    }

    if(param->outputDirectory == NULL){
        printf("O parametro -o, que e obrigatorio, esta ausente...\nFinalizando programa..\n");
        exit(1);
    }
}

char* getInputDirectory(Parameters Param){
    if(Param == NULL){
        printf("Erro: A instancia de Parametros nao existe..\nFinalizando o programa..\n");
        //***Desalocar memórias alocadas até o momentos***
        exit(1);
    }
    
    parameters *param = (parameters*) Param;
    return param->inputDirectory;
} 


char* getGeoName(Parameters Param){
    if(Param == NULL){
        printf("Erro: A instancia de Parametros nao existe..\nFinalizando o programa..\n");
        //***Desalocar memórias alocadas até o momentos***
        exit(1);
    }
    
    parameters *param = (parameters*) Param;
    return param->geoName;
}

char* getQryName(Parameters Param){
    
    if(Param == NULL){
        printf("Erro ao alocar memória para o atributo qryName..\nFinalizando o programa..\n");
        //***Desalocar memórias alocadas até o momentos***
        exit(1);
    }
    
    parameters *param = (parameters*) Param;
    return param->qryName;
} 

char* getOutputDirectory(Parameters Param){
    if(Param == NULL){
        printf("Erro ao alocar memória para o atributo inputDirectory..\nFinalizando o programa..\n");
        //***Desalocar memórias alocadas até o momentos***
        exit(1);
    }
    
    parameters *param = (parameters*) Param;
    return param->outputDirectory;
}

char* getEcName(Parameters Param){
    if(Param == NULL){
        printf("Erro ao alocar memória para o atributo ecName..\nFinalizando o programa..\n");
        //***Desalocar memórias alocadas até o momentos***
        exit(1);
    }
    
    parameters *param = (parameters*) Param;
    return param->ecName;
}

char* getPmName(Parameters Param){
    if(Param == NULL){
        printf("Erro ao alocar memória para o atributo pmName..\nFinalizando o programa..\n");
        //***Desalocar memórias alocadas até o momentos***
        exit(1);
    }
    
    parameters *param = (parameters*) Param;
    return param->pmName;
}

int isQryNull(Parameters Param){
    if(isElementNull(Param, "parameter", "isQryNull"))
        return 1;

    parameters *param = (parameters*) Param;
    
    if(param->qryName == NULL)
        return 1;
    else
        return 0;
}

int isEcNull(Parameters Param){
    if(isElementNull(Param, "parameter", "isEcNull"))
        return 1;

    parameters *param = (parameters*) Param;
    
    if(param->ecName == NULL)
        return 1;
    else
        return 0;
}

int isPmNull(Parameters Param){
    if(isElementNull(Param, "parameter", "isPmNull"))
        return 1;

    parameters *param = (parameters*) Param;
    
    if(param->pmName == NULL)
        return 1;
    else
        return 0;
}


void printParameters(Parameters Param){ 
    parameters *param = (parameters*) Param;

    printf("Input path (-e): %s\n", param->inputDirectory);
    printf("Geo name (-f): %s\n", param->geoName);
    printf("Query name (-q): %s\n", param->qryName);
    printf("Output path (-o): %s\n", param->outputDirectory);
}


void freeParameters(Parameters Param){
    parameters *param = (parameters*) Param;
    free(param->inputDirectory);
    free(param->geoName);
    free(param->qryName);
    free(param->outputDirectory);
    free(param);
}