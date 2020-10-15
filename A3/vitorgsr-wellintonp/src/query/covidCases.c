#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing/drawing.h"
#include "../include/query.h"


char* buildHouseTag(House house);

void executeCovidCasesReport(char* command, Drawing Dr){
    if(isElementNull(Dr, "drawing", "executeCovidCasesReport"))
        return;

    int casesNumber; char cep[10]; char face; int number;
    
    sscanf(&command[3], "%d %s %c %d", &casesNumber, cep, &face, &number);
    
    House house = createHouse(cep, face, number, casesNumber); 
    setHouseBlock(house, Dr);       
    setHouseLocation(house);

    List houseList = getHouseList(Dr);
    insert(houseList, house);
}