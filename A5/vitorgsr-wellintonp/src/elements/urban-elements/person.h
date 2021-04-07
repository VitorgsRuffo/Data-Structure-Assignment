#ifndef PERSON_H
#define PERSON_H

/*
*   Tipo abstrato de dado que representa as pessoas.
*/
typedef void* Person;

/*  
* Pré-Condição: requer os dados (strings) que compoem uma pessoa.
* Pós-Condição: retorna o endereco de uma nova instancia de pessoa que possui as informacoes passadas.
*/
Person createPerson(char* cpf, char* name, char* lastName, char gender, char* birthdate);

/*  
* Pré-Condição: requer o endereco de uma instancia de pessoa.
* Pós-Condição: retorna o cpf da pessoa passada.
*/
char* getPersonCpf(Person Pe);

/*  
* Pré-Condição: requer o endereco de uma instancia de pessoa.
* Pós-Condição: retorna o nome da pessoa passada.
*/
char* getPersonName(Person Pe);

/*  
* Pré-Condição: requer o endereco de uma instancia de pessoa.
* Pós-Condição: retorna o sobrenome da pessoa passada.
*/
char* getPersonLastName(Person Pe);

/*  
* Pré-Condição: requer o endereco de uma instancia de pessoa.
* Pós-Condição: retorna o sexo da pessoa passada.
*/
char getPersonGender(Person Pe);

/*  
* Pré-Condição: requer o endereco de uma instancia de pessoa.
* Pós-Condição: retorna a data de nascimento da pessoa passada.
*/
char* getPersonBirthdate(Person Pe);


/*  
    Pré-Condição: requer o endereco de uma instancia de pessoa.
    Pós-Condição: aloca e retorna uma string com as informacoes da instancia de pessoa.
*/
char* personToString(Person Pe);

/*  
* Pré-Condição: requer o endereco de uma instancia de pessoa.
* Pós-Condição: libera a memoria usada pela instancia de pessoa que foi passada.
*/
void freePerson(Person Pe);

#endif