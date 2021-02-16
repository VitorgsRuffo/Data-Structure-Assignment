#include "../../include/headers.h"
#include "establishmentInformation.h"
#include "../../include/dataStructure.h"
#include "../../elements/urban-elements/establishment.h"
#include "../../elements/urban-elements/person.h"
#include "../../elements/urban-elements/address.h"
#include "../../elements/urban-elements/establishmentType.h"

void writeEstablishmentInfosOnTxt(File txt, Info estabInfo,Info personInfo, Info estabType);

void executeEstablishmentInformationChecking(char* command, City Ct, File txt){

    char cnpj[20];
    sscanf(&command[4], "%s", cnpj);

    // Pegando informações do estabelecimento comercial
    DataStructure establishmentTable = getEstablishmentsTable(Ct);
    Info establishmentInfo = getHashTableInfo(establishmentTable, cnpj);
    char* ownerCpf = getEstablishmentCpf(establishmentInfo);

    // Pegando as informações do proprietario do estabelecimento comercial
    DataStructure peoples = getPeople(Ct);
    Info personInfo = getHashTableInfo(peoples, ownerCpf);

    // Pegando a tabela de descrição de tipos de estabelecimentos
    DataStructure establishmentsTypes = getEstablishmentTypes(Ct);
    Info establishmentType = getHashTableInfo(establishmentsTypes, getEstablishmentCode(establishmentInfo));

    writeEstablishmentInfosOnTxt(txt, establishmentInfo, personInfo, establishmentType);
}

void writeEstablishmentInfosOnTxt(File txt, Info estabInfo,Info personInfo, Info estabType){

    char* establishmentString = establishmentToString(estabInfo, estabType);

    fprintf(txt, "%s", establishmentString);
    fprintf(txt, "Dados do proprietario:\n");
    //Chamar toString do Person
    fprintf(txt, "CPF: %s\n", getPersonCpf(personInfo));
    fprintf(txt, "Nome: %s\n", getPersonName(personInfo));
    fprintf(txt, "Sobrenome: %s\n", getPersonLastName(personInfo));
    fprintf(txt, "Sexo: %c\n", getPersonGender(personInfo));
    fprintf(txt, "Data de nascimento: %s\n", getPersonBirthdate(personInfo));
    fprintf(txt, "\n\n");

    free(establishmentString);
}