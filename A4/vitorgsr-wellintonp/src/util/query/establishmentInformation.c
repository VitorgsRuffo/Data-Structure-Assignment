#include "../../include/headers.h"
#include "establishmentInformation.h"
#include "../../include/dataStructure.h"
#include "../../elements/urban-elements/establishment.h"
#include "../../elements/urban-elements/person.h"
#include "../../elements/urban-elements/address.h"

void writeEstablishmentInfosOnTxt(File txt, Info establishmentInfo, Info personInfo);

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
    
    writeEstablishmentInfosOnTxt(txt, establishmentInfo, personInfo);
}

void writeEstablishmentInfosOnTxt(File txt, Info estabInfo, Info personInfo){

    Address estabAddress = getEstablishmentAddress(estabInfo);
    Point estabCoordinates = getEstablishmentCoordinates(estabInfo);
    char* addressString = addressToString(estabAddress);
    
    fprintf(txt, "Nome: %s\nCNPJ: %s\nCodigo: %s\n", getEstablishmentName(estabInfo), getEstablishmentCnpj(estabInfo), getEstablishmentCode(estabInfo));
    fprintf(txt, "Address: %s\n", addressString);
    fprintf(txt, "x:%lf y:%lf width:%lf height:%lf\n", getPointX(estabCoordinates), getPointY(estabCoordinates), getEstablishmentWidth(estabInfo), getEstablishmentHeight(estabInfo));
    fprintf(txt, "Dados do proprietario:\n");
    fprintf(txt, "CPF: %s\n", getPersonCpf(personInfo));
    fprintf(txt, "Nome: %s\n", getPersonName(personInfo));
    fprintf(txt, "Sobrenome: %s\n", getPersonLastName(personInfo));
    fprintf(txt, "Sexo: %c\n", getPersonGender(personInfo));
    fprintf(txt, "Data de nascimento: %s\n", getPersonBirthdate(personInfo));

    free(addressString);
}