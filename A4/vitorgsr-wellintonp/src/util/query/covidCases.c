#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"

char* buildHouseTag(House house);

void executeCovidCasesReport(char* command, City Ct){
    if(command == NULL || Ct == NULL)
        return;

    int casesNumber; char cep[30]; char face; int number;
    
    sscanf(&command[3], "%d %s %c %d", &casesNumber, cep, &face, &number);
    
    House house = createHouse(cep, face, number, casesNumber); 
    setHouseBlock(house, Ct);       
    setHouseLocation(house);

    DataStructure houses = getHousesTree(Ct);
    insertPQuadTree(houses, getHouseCoordinates(house), house);
}