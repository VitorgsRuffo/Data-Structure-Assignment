#include "../../include/headers.h"
#include "establishmentType.h"

typedef struct {
    char* code;
    char* description;
}establishmentType;


EstablishmentType createEstablishmentType(char* code, char* description){
    if(code == NULL || description == NULL) return NULL;

    establishmentType* et = (establishmentType*) malloc(sizeof(establishmentType));

    et->code = (char*) malloc((strlen(code) + 1) * sizeof(char));
    et->description = (char*) malloc((strlen(description) + 1) * sizeof(char));

    strcpy(et->code, code);
    strcpy(et->description, description);

    return et;
}

char* getEstablishmentTypeCode(EstablishmentType Et){
    if(Et == NULL) return NULL;
    establishmentType *et = (establishmentType*) Et;
    return et->code;
}

char* getEstablishmentTypeDescription(EstablishmentType Et){
    if(Et == NULL) return NULL;
    establishmentType *et = (establishmentType*) Et;
    return et->description;
}

void freeEstablishmentType(EstablishmentType Et){
    if(Et == NULL) return;

    establishmentType *et = (establishmentType*) Et;
    free(et->code);  
    free(et->description);  
    free(et);
}