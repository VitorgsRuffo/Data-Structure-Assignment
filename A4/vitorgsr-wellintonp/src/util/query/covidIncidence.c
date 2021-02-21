#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"
#include "../algorithm/convexhull.h"


typedef struct {
    List covidAddressesInCirc;
    Circle circumference;
    int thereIsHealthCenterInPolygon;
    int convexHullPointsAmount;
    Point* convexHullPoints; 
}Variables;

void determineCovidAddressesInsideCircumference(DataStructure CovidAddresses, Variables* variables);
char* buildBoundingCircumferenceTag(char* circumferenceX, char* circumferenceY, char* circumferenceRadius);
Point* getCovidAddressesInCircCoordinates(List covidAddressesInCirc, int covidAddressesInCircAmount);
int calculateTotalCovidCasesInRegion(List covidAddressesInCirc);
double calculateIncidenceRegionArea(Point* convexHullPoints, int convexHullPointsAmount);
double getIncidenceRegionDemographicDensity(City Ct, List covidAddressesInCirc);
char calculateIncidenceRegionCategory(int totalCovidCasesInRegion, int totalHabitantsInRegion);
char* buildIncidenceRegionTag(Point* points, int pointsAmount, char incidenceRegionCategory);
void suggestHealthCenterInRegionIfNeeded(DataStructure healthCenters, Variables* variables, List queryElementsList, double incidenceRegionArea);
void writeCovidIncidenceReportOnTxt(File txt, Point* points, int pointsAmount, int totalCovidCasesInRegion, double incidenceRegionArea, char incidenceRegionCategory, int totalHabitantsInRegion);


void executeCovidIncidenceReportInRegion(char* command, City Ct, File txt){

    char x[15], y[15], radius[15];
    sscanf(&command[3], "%s %s %s", x, y, radius);

    Variables variables;
    variables.circumference = createCircle("...", radius, x, y, "...", "...", "...");
    
    DataStructure covidAddresses = getCovidAddresses(Ct);
    variables.covidAddressesInCirc = createList();
    determineCovidAddressesInsideCircumference(covidAddresses, &variables);

    char* boundingCircumferenceTag = 
        buildBoundingCircumferenceTag(x, y, radius);
    List queryElementsList = getQueryElements(Ct);
    insert(queryElementsList, boundingCircumferenceTag);


    int covidAddressesInCircAmount = 
        length(variables.covidAddressesInCirc);

    if(covidAddressesInCircAmount <= 0){
        fprintf(txt, "Nao existem enderecos com casos de covid dentro do circulo.");
        freeCircle(variables.circumference);
        freeList(variables.covidAddressesInCirc, NULL);
        return;
    }

    Point* covidAddressesInCircCoordinates = 
        getCovidAddressesInCircCoordinates(variables.covidAddressesInCirc, 
                                           covidAddressesInCircAmount);
    
    Stack head =
        convexHull(covidAddressesInCircCoordinates, covidAddressesInCircAmount);

    if(head == NULL){
        fprintf(txt, "Erro: A quantidade de enderecos de covid sao insuficientes para formar regiao de incidencia (quantidade de enderecos < 3).");
        free(covidAddressesInCircCoordinates);
        freeCircle(variables.circumference);
        freeList(variables.covidAddressesInCirc, NULL); 
        return;    
    }
  
    variables.convexHullPointsAmount = stackLength(&head);
    variables.convexHullPoints = (Point*) stackToArray(&head); 
    
    int totalCovidCasesInRegion = calculateTotalCovidCasesInRegion(variables.covidAddressesInCirc);
    

    double incidenceRegionArea = calculateIncidenceRegionArea(variables.convexHullPoints, variables.convexHullPointsAmount);
    
    //double regionDemographicDensity = getIncidenceRegionDemographicDensity(Ct, variables.covidAddressesInCirc) * 1000000.00; //convertendo densidade demografica de km^2 para m^2.
    double regionDemographicDensity = 1000;

    int totalHabitantsInRegion = regionDemographicDensity * incidenceRegionArea;  

    char incidenceRegionCategory = calculateIncidenceRegionCategory(totalCovidCasesInRegion, totalHabitantsInRegion);
    if(incidenceRegionCategory == 'E'){
        DataStructure healthCenters = getHealthCenters(Ct); 
        suggestHealthCenterInRegionIfNeeded(healthCenters, &variables, queryElementsList, incidenceRegionArea);        
    }
    
    char* incidenceRegionTag = buildIncidenceRegionTag(variables.convexHullPoints, variables.convexHullPointsAmount, incidenceRegionCategory);
    insert(queryElementsList, incidenceRegionTag);

    writeCovidIncidenceReportOnTxt(txt, covidAddressesInCircCoordinates, covidAddressesInCircAmount, totalCovidCasesInRegion, incidenceRegionArea, incidenceRegionCategory, totalHabitantsInRegion);
   
    free(covidAddressesInCircCoordinates);
    free(variables.convexHullPoints);
    freeCircle(variables.circumference);
    freeList(variables.covidAddressesInCirc, NULL);  
}

void insertCovidAddressInListIfItsInsideCircumference(Info covidAddress, ExtraInfo extraInfo);

void determineCovidAddressesInsideCircumference(DataStructure CovidAddresses, Variables* variables){

    levelOrderTraversal(CovidAddresses, insertCovidAddressInListIfItsInsideCircumference, variables);
}

void insertCovidAddressInListIfItsInsideCircumference(Info covidAddress, ExtraInfo extraInfo){
    
    Variables* variables = (Variables*) extraInfo;

    if(isPointInsideCirc(variables->circumference, getCovidAddressCoordinates(covidAddress)))
        insert(variables->covidAddressesInCirc, covidAddress);
}

char* buildBoundingCircumferenceTag(char* circumferenceX, char* circumferenceY, char* circumferenceRadius){
    char* boundingCircumferenceTag = (char*) malloc(300 * sizeof(char));
    if(boundingCircumferenceTag == NULL)
        return NULL;

    sprintf(boundingCircumferenceTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"green\" stroke-width=\"3\" fill=\"black\" fill-opacity=\"0.0\" />\n", circumferenceX, circumferenceY, circumferenceRadius);
    return boundingCircumferenceTag;
}

Point* getCovidAddressesInCircCoordinates(List covidAddressesInCirc, int covidAddressesInCircAmount){

    Point* points = (Point*) malloc(sizeof(Point) * covidAddressesInCircAmount);

    Node currentNode = getFirst(covidAddressesInCirc);
    if(currentNode == NULL) return NULL;
    
    Info covidAddress = NULL;

    int i = 0;
    while(currentNode != NULL){

        covidAddress = get(covidAddressesInCirc, currentNode);

        *(points + i) = getCovidAddressCoordinates(covidAddress);
        
        currentNode = getNext(covidAddressesInCirc, currentNode);
        i++;   
    }

    return points;
}


int calculateTotalCovidCasesInRegion(List covidAddressesInCirc){
    Node currentNode = getFirst(covidAddressesInCirc);
    if(currentNode == NULL) return -1;
    
    int totalCases = 0;
    Info covidAddress = NULL;

    while(currentNode != NULL){
        covidAddress = get(covidAddressesInCirc, currentNode);
        totalCases += getCovidAddressCasesNumber(covidAddress);
        currentNode = getNext(covidAddressesInCirc, currentNode);
    }

    return totalCases;
}

char calculateIncidenceRegionCategory(int totalCovidCasesInRegion, int totalHabitantsInRegion){
    /*Logica:

        casos: 1    | habitantes: 15,897

        fator multiplicativo: x6   -> fator = 100000/totalDeHabitantes

        casos: 6 | 100000
 
        Portanto, essa regiao (onde temos 1 caso em 15,897 habitantes) tem a mesma categoria que uma regiao com 6 casos em 100000 habitantes, ou seja, categoria C.
    */

    double factor = 100000 / totalHabitantsInRegion;
    double totalCovidCases = totalCovidCasesInRegion * factor;

    if(totalCovidCases < 0.1){
        return 'A';        
    }else if(totalCovidCases < 5){
        return 'B';
    }else if(totalCovidCases < 10){
        return 'C';
    }else if(totalCovidCases < 20){
        return 'D';
    }else if(totalCovidCases >= 20){
        return 'E'; 
    }
    else
        return 'Z';
}

//calcular area de poligono irregular:
double calculateIncidenceRegionArea(Point* convexHullPoints, int convexHullPointsAmount){

    double area = 0, sum1 = 0, sum2 = 0;
    
    for(int i = convexHullPointsAmount-1; i > -1; i--){
        if(i == 0){
            sum1 += getPointX(*(convexHullPoints + i))  *  getPointY(*(convexHullPoints + convexHullPointsAmount-1));
            break;
        }
        sum1 += getPointX(*(convexHullPoints + i))  *  getPointY(*(convexHullPoints + i - 1));   
    }

    for(int i = convexHullPointsAmount-1; i > -1; i--){
        if(i == 0){
            sum2 += getPointY(*(convexHullPoints + i))  *  getPointX(*(convexHullPoints + convexHullPointsAmount-1));
            break;
        }
        sum2 +=   getPointY(*(convexHullPoints + i))  *  getPointX(*(convexHullPoints + i - 1));
    }

   area = (sum1 - sum2) / 2;
   return area;
}

/*
double getIncidenceRegionDemographicDensity(City Ct, List covidAddressesInCirc){

    Node firstNode = getFirst(covidAddressesInCirc);
    Info covidAddress = get(covidAddressesInCirc, firstNode);

    Address address = getCovidAddress(covidAddress);
    char* blockCep = getAddressCep(address);

    DataStructure* blocksTable = getBlocksTable(Ct);
    Block block = getHashTableInfo(*blocksTable, blockCep);

    double demographicDensity = getBlockDemographicDensity(block);
    return demographicDensity;
}
*/
char* determineIncidenceRegionColor(char incidenceRegionCategory);

char* buildIncidenceRegionTag(Point* points, int pointsAmount, char incidenceRegionCategory){
    char* incidenceRegionTag = (char*) malloc(1000 * sizeof(char));
    if(incidenceRegionTag == NULL) return NULL;
    
    int stringLength = strlen("\t<polygon points=\"");
    sprintf(incidenceRegionTag, "\t<polygon points=\"");

    char* aux = incidenceRegionTag + stringLength;
    char pointX[10], pointY[10];
    
    for(int i = 0; i<pointsAmount; i++){
        sprintf(aux, "%.2f,%.2f ", getPointX(*(points + i)), getPointY(*(points + i)));
        sprintf(pointX, "%.2f", getPointX(*(points + i)));
        sprintf(pointY, "%.2f", getPointY(*(points + i)));
        aux += (strlen(pointX) + strlen(pointY) + 2);
    }

    char* incidenceRegionColor = determineIncidenceRegionColor(incidenceRegionCategory); 

    sprintf(aux,"\" style=\"fill:%s;stroke:red;stroke-width:2;fill-opacity:0.6\" />\n", incidenceRegionColor);

    return incidenceRegionTag;
}


char* determineIncidenceRegionColor(char incidenceRegionCategory){

    switch (incidenceRegionCategory){
        case 'A':
            return "#00FFFF";
            
        case 'B':
            return "#008080";
            
        case 'C':
            return "#FFFF00";
            
        case 'D':
            return "#FF0000";
             
        case 'E':
            return "#800080";           
    }

    return "black"; 
}

void checkIfHealthCenterIsInsidePolygon(Info healthCenterInfo, ExtraInfo extraInfo);
int checkPointIrregularPolygonOverlap(Point healthCenterCoordinates, Point* convexHullPoints, int convexHullPointsAmount);
Point calculatePolygonCentroid(Point* convexHullPoints, int convexHullPointsAmount, double incidenceRegionArea);
char* buildHealthCenterSuggestionTag(Point polygonCentroid);

void suggestHealthCenterInRegionIfNeeded(DataStructure healthCenters, Variables* variables, List queryElementsList, double incidenceRegionArea){
    
    variables->thereIsHealthCenterInPolygon = 0;
    
    levelOrderTraversal(healthCenters, checkIfHealthCenterIsInsidePolygon, variables);
    
    if(variables->thereIsHealthCenterInPolygon)
        return; //se em algum momento houve overlap entre um posto e a regiao de incidencia saimos da funcao sem sugerir um posto.
        
    //não foi encontrado nenhuma posto de saude dentro do poligono e, portanto, precisamos sugerir a construcao de um.
    Point polygonCentroid = calculatePolygonCentroid(variables->convexHullPoints, variables->convexHullPointsAmount, incidenceRegionArea);
  
    char* healthCenterSuggestionTag = buildHealthCenterSuggestionTag(polygonCentroid);
    insert(queryElementsList, healthCenterSuggestionTag);  
}

void checkIfHealthCenterIsInsidePolygon(Info healthCenterInfo, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;

    Point healthCenterCoordinates = getHealthCenterCoordinates(healthCenterInfo);
    
    if(checkPointIrregularPolygonOverlap(healthCenterCoordinates, variables->convexHullPoints, variables->convexHullPointsAmount))
        variables->thereIsHealthCenterInPolygon = 1;

}

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

//colocar no tad point
int checkPointIrregularPolygonOverlap(Point healthCenterCoordinates, Point* convexHullPoints, int convexHullPointsAmount){
    
    int counter = 0;
    int i;
    double xinters;
    Point p1, p2;
    p1 = *convexHullPoints;

    for (i=1; i<=convexHullPointsAmount; i++) {
        p2 = *(convexHullPoints + (i % convexHullPointsAmount));

        if (getPointY(healthCenterCoordinates) > MIN(getPointY(p1), getPointY(p2))) {
            
            if (getPointY(healthCenterCoordinates)  <= MAX(getPointY(p1), getPointY(p2))) {
                
                if (getPointX(healthCenterCoordinates) <= MAX(getPointX(p1), getPointX(p2))) {
                    
                    if (getPointY(p1) != getPointY(p2)) {
                        
                        xinters = (getPointY(healthCenterCoordinates) - getPointY(p1)) * 
                                  (getPointX(p2)-getPointX(p1))/(getPointY(p2)-getPointY(p1)) + getPointX(p1);
                        if (getPointX(p1) == getPointX(p2) || getPointX(healthCenterCoordinates) <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    if (counter % 2 == 0)
        return 0; // O ponto esta fora
    else
        return 1; // O ponto esta dentro.
}

//obs: colocar no tad point
Point calculatePolygonCentroid(Point* convexHullPoints, int convexHullPointsAmount, double incidenceRegionArea){
    Point point = createPoint(0,0);
    double sum1 = 0, sum2 = 0;
    double xi, yi, xi1, yi1;

    for(int i = 0; i<convexHullPointsAmount; i++){
        xi = getPointX(*(convexHullPoints + i));
        yi = getPointY(*(convexHullPoints + i));

        if(i == convexHullPointsAmount-1){
            xi1 = getPointX(*(convexHullPoints));
            yi1 = getPointY(*(convexHullPoints));

        }else{
            xi1 = getPointX(*(convexHullPoints + i + 1));
            yi1 = getPointY(*(convexHullPoints + i + 1));

        }

        sum1 += ( (xi + xi1) * (xi*yi1 - xi1*yi) )  ;
    }

    setPointX(point, -1 * ((1 / (6 * incidenceRegionArea)) * sum1));

    for(int i = 0; i<convexHullPointsAmount; i++){
        xi = getPointX(*(convexHullPoints + i));
        yi = getPointY(*(convexHullPoints + i));

        if(i == convexHullPointsAmount-1){
            xi1 = getPointX(*(convexHullPoints));

            yi1 = getPointY(*(convexHullPoints));
        }else{
            xi1 = getPointX(*(convexHullPoints + i + 1));

            yi1 = getPointY(*(convexHullPoints + i + 1));
        }

        sum2 += (yi + yi1) * (xi*yi1 - xi1*yi);
    } 

    setPointY(point, -1 * ((1 / (6 * incidenceRegionArea)) * sum2));
    
    return point;
}

char* buildHealthCenterSuggestionTag(Point polygonCentroid){
    char* healthCenterSuggestionTag = (char*) malloc(500 * sizeof(char));
    if(healthCenterSuggestionTag == NULL) return NULL;
    
    sprintf(healthCenterSuggestionTag, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"10\" stroke=\"white\" stroke-width=\"1\" fill=\"white\" fill-opacity=\"0.0\"/>\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> HC </text>\n", getPointX(polygonCentroid), getPointY(polygonCentroid), getPointX(polygonCentroid), getPointY(polygonCentroid));
    return healthCenterSuggestionTag;
}

void writeCovidIncidenceReportOnTxt(File txt, Point* points, int pointsAmount, int totalCovidCasesInRegion, double incidenceRegionArea, char incidenceRegionCategory, int totalHabitantsInRegion){

    fprintf(txt, "Coordenadas dos enderecos de covid dentro do circulo:\n");
    for(int i = 0; i<pointsAmount; i++)
        fprintf(txt, "\t(%d) x: %.2f, y: %.2f\n", (i+1), getPointX(*(points + i)), getPointY(*(points + i)));
        
    fprintf(txt, "\nTotal de habitantes: %d\n", totalHabitantsInRegion);
    fprintf(txt, "\nNumero total de casos: %d\n", totalCovidCasesInRegion);
    fprintf(txt, "\nArea dentro da envoltoria convexa: %.2f\n", incidenceRegionArea);
    fprintf(txt, "\nCategoria da regiao de incidencia: %c\n", incidenceRegionCategory);
}