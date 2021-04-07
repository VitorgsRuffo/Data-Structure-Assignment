#include "../../include/headers.h"
#include "blockResidents.h"
#include "../data-structure/list.h"
#include "../../elements/urban-elements/block.h"
#include "../../elements/urban-elements/house.h"
#include "../../elements/urban-elements/person.h"

void writePersonInformationOnTxt(File txt, char* personString, char* houseAddressString);

void executeBlockResidentsReport(char* command, City Ct, File txt){

    char cep[30];
    sscanf(&command[3], "%s", cep);

    DataStructure* blocksTable = getBlocksTable(Ct);
    Info blocksInfo = getHashTableInfo(*blocksTable, cep);

    if(blocksInfo == NULL){  // Caso nao exista o cep na tabela de quadras escrevemos no txt o aviso e finalizamos a função.
        fprintf(txt, "Nao existe uma quadra com cep %s na cidade.\n\n", cep);
        return;
    }

    List listOfHousesInBlock = getListOfHousesInBlock(blocksInfo);
    
    Node currentHouse = getFirst(listOfHousesInBlock);
    if(currentHouse == NULL) // Lista de casas dentro daquela quadra está vazia, portanto nao há nenhum morador para printar
        return;

    DataStructure* peopleTable = getPeople(Ct);

    while(currentHouse != NULL){

        Info houseInfo = get(listOfHousesInBlock, currentHouse);
        char* houseAddressString = addressToString(getHouseAddress(houseInfo));
        char* cpf = getHouseCpf(houseInfo);

        Info personInfo = getHashTableInfo(*peopleTable, cpf);
        char* personString = personToString(personInfo);

        writePersonInformationOnTxt(txt, personString, houseAddressString);

        currentHouse = getNext(listOfHousesInBlock, currentHouse);

        free(personString);
    }
}

void writePersonInformationOnTxt(File txt, char* personString, char* houseAddressString){
    fprintf(txt, "%s\n", personString);
    fprintf(txt, "%s\n\n", houseAddressString);
}