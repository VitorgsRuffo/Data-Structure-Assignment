#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"

char* buildHouseTag(House house);

void executeCovidCasesReport(int id, char* command, City Ct){
    if(command == NULL || Ct == NULL)
        return;

    int casesNumber; char cep[30]; char face; int number;
    
    sscanf(&command[3], "%d %s %c %d", &casesNumber, cep, &face, &number);
    
    CovidAddress covidAddress = NULL;
    covidAddress = createCovidAddress(id, cep, face, number, casesNumber, Ct);

    DataStructure covidAddresses = getCovidAddresses(Ct);
    insertPQuadTree(covidAddresses, getCovidAddressCoordinates(covidAddress), covidAddress);

    DataStructure blocks = getBlocks(Ct);
    Block blk = getPQuadTreeNodeInfo(blocks, searchForBlockByCep(Ct, cep));

    if(blk == NULL)
        return;
    
    incrementBlockCovidCases(blk, face, casesNumber);
}