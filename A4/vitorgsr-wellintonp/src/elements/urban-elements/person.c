#include "../../include/headers.h"
#include "person.h"


typedef struct {
    char* cpf;
    char* name;
    char* lastName;
    char gender;
    char* birthdate;
}person;


Person createPerson(char* cpf, char* name, char* lastName, char gender, char* birthdate){

    person* pe = (person*) malloc(sizeof(person));

    pe->cpf = (char*) malloc((strlen(cpf) + 1) * sizeof(char));
    pe->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    pe->lastName = (char*) malloc((strlen(lastName) + 1) * sizeof(char));
    pe->birthdate = (char*) malloc((strlen(birthdate) + 1) * sizeof(char));

    strcpy(pe->cpf, cpf);
    strcpy(pe->name, name);
    strcpy(pe->lastName, lastName);
    pe->gender = gender;
    strcpy(pe->birthdate, birthdate);

    return pe;
}

char* getPersonCpf(Person Pe){
    if(Pe == NULL)
        return NULL;
 
    person* pe = (person*) Pe;
    return pe->cpf;
}

char* getPersonName(Person Pe){
    if(Pe == NULL)
        return NULL;
    
    person* pe = (person*) Pe;
    return pe->name;
}

char* getPersonLastName(Person Pe){
    if(Pe == NULL)
        return NULL;
    
    person* pe = (person*) Pe;
    return pe->lastName;
}

char getPersonGender(Person Pe){
    if(Pe == NULL)
        return 'Z'; // Nesse caso é obrigatorio o retorno de um caracter, portanto retornará Z quando house algum erro
    
    person* pe = (person*) Pe;
    return pe->gender;
}

char* getPersonBirthdate(Person Pe){
    if(Pe == NULL)
        return NULL;
    
    person* pe = (person*) Pe;
    return pe->birthdate;
}

void freePerson(Person Pe){
    person* pe = (person*) Pe;

    free(pe->cpf);
    free(pe->name);
    free(pe->lastName);
    free(pe->birthdate);
    free(pe);
}