#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing/drawing.h"
#include "../include/query.h"
#include "../include/figures.h"

typedef struct { 
    double x, y; 
}Point; 

Point p0; 

void determineHousesInsideCircumference(List houseList, List housesInsideCircList, Circle circle);
char* buildBoundingCircumferenceTag(char* circumferenceX, char* circumferenceY, char* circumferenceRadius);
Point* getHousesInsideCircCenterOfMass(List housesInsideCircList, int housesInsideCircListLength);
Stack convexHull(Point points[], int n);
char* pointToString(void* P);
int calculateTotalCovidCasesInRegion(List housesInsideCircList);
double calculateIncidenceRegionArea(Point** convexHullPoints, int convexHullPointsAmount);
char calculateIncidenceRegionCategory(int totalCovidCasesInRegion, int totalHabitantsInRegion);
char* buildIncidenceRegionTag(Point** points, int pointsAmount, char incidenceRegionCategory);
void suggestHealthCenterInRegionIfNeeded(List healthCenterList, List queryElementsList, Point** convexHullPoints, int convexHullPointsAmount, double incidenceRegionArea);
void writeCovidIncidenceReportOnTxt(File txt, Point* points, int pointsAmount, int totalCovidCasesInRegion, double incidenceRegionArea, char incidenceRegionCategory, int totalHabitantsInRegion);


void executeCovidIncidenceReportInRegion(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeCovidIncidenceReportInRegion"))
        return;

    char x[15], y[15], radius[15];
    sscanf(&command[3], "%s %s %s", x, y, radius);

    Circle circ = createCircle("...", radius, x, y, "...", "...", "...");
    
    List houseList = getHouseList(Dr);
    List housesInsideCircList = createList();
    determineHousesInsideCircumference(houseList, housesInsideCircList, circ);

    char* boundingCircumferenceTag = buildBoundingCircumferenceTag(x, y, radius);
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, boundingCircumferenceTag);
    
    
    int housesInsideCircListLength = length(housesInsideCircList);
    Point* points = getHousesInsideCircCenterOfMass(housesInsideCircList, housesInsideCircListLength);
	
    int pointsAmount = housesInsideCircListLength;  
	Stack head = convexHull(points, pointsAmount);
    if(head == NULL){
        fprintf(txt, "Erro: A quantidade de casas sao insuficientes para formar regiao de incidencia (quantidade de casas < 3).");
        free(points);
        freeCircle(circ);
        freeList(housesInsideCircList, NULL); 
        return;    
    }
  
    int convexHullPointsAmount = stackLength(&head);
    Point** convexHullPoints = (Point**) stackToArray(&head); 
    
    int totalCovidCasesInRegion = calculateTotalCovidCasesInRegion(housesInsideCircList);

    double incidenceRegionArea = calculateIncidenceRegionArea(convexHullPoints, convexHullPointsAmount);
    Region region = getRegion(Dr);
    double regionDemographicDensity = (getRegionDemographicDensity(region)) / 1000000.00; //convertendo densidade demografica de km^2 para m^2.
    int totalHabitantsInRegion = regionDemographicDensity * incidenceRegionArea;  

    char incidenceRegionCategory = calculateIncidenceRegionCategory(totalCovidCasesInRegion, totalHabitantsInRegion);
    if(incidenceRegionCategory == 'E'){
        List healthCenterList = getHealthCenterList(Dr);
        suggestHealthCenterInRegionIfNeeded(healthCenterList, queryElementsList, convexHullPoints, convexHullPointsAmount, incidenceRegionArea);        
    }
   
    char* incidenceRegionTag = buildIncidenceRegionTag(convexHullPoints, convexHullPointsAmount, incidenceRegionCategory);
    insert(queryElementsList, incidenceRegionTag);

    writeCovidIncidenceReportOnTxt(txt, points, pointsAmount, totalCovidCasesInRegion, incidenceRegionArea, incidenceRegionCategory, totalHabitantsInRegion);

    free(convexHullPoints);
    free(points);
    freeCircle(circ);
    freeList(housesInsideCircList, NULL);  
}

void determineHousesInsideCircumference(List houseList, List housesInsideCircList, Circle circ){

    Node NODE = getFirst(houseList);
    if(isElementNull(NODE, "NODE", "determineHousesInsideCircumference | getFirst"))
        return;
    
    Info houseInfo = NULL;
    char houseX[15], houseY[15], houseW[15], houseH[15];
    double aux;

    while(NODE != NULL){

        houseInfo = get(houseList, NODE);

        aux = getHouseX(houseInfo);
        sprintf(houseX, "%lf", aux);
        aux = getHouseY(houseInfo);
        sprintf(houseY, "%lf", aux);
        aux = getHouseW(houseInfo);
        sprintf(houseW, "%lf", aux);
        aux = getHouseH(houseInfo);
        sprintf(houseH, "%lf", aux);

        Rectangle rect = createRectangle("...", houseW, houseH, houseX, houseY, "...", "...", "...");

        if(checkRectCircOverlap(rect, circ))
            insert(housesInsideCircList, houseInfo);


        freeRectangle(rect);
        NODE = getNext(houseList, NODE);
    }
}

char* buildBoundingCircumferenceTag(char* circumferenceX, char* circumferenceY, char* circumferenceRadius){
    char* boundingCircumferenceTag = (char*) malloc(300 * sizeof(char));
    if(isElementNull(boundingCircumferenceTag, "boundingCircumferenceTag", "buildBoundingCircumferenceTag"))
        return NULL;

    sprintf(boundingCircumferenceTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"green\" stroke-width=\"3\" fill=\"black\" fill-opacity=\"0.0\" />\n", circumferenceX, circumferenceY, circumferenceRadius);
    return boundingCircumferenceTag;
}


Point* getHousesInsideCircCenterOfMass(List housesInsideCircList, int housesInsideCircListLength){

    Point* points = (Point*) malloc(sizeof(Point)*housesInsideCircListLength);

    Node NODE = getFirst(housesInsideCircList);
    if(isElementNull(NODE, "NODE", "getHousesInsideCircCenterOfMass | getFirst"))
        return NULL;
    
    Info house = NULL;

    int i = 0;
    while(NODE != NULL){

        house = get(housesInsideCircList, NODE);
        points[i].x = getHouseCenterOfMassX(house);
        points[i].y = getHouseCenterOfMassY(house);
        
        NODE = getNext(housesInsideCircList, NODE);
        i++;   
    }

    return points;
}


//---------------------------------Convex Hull--------------------------------//

char* pointToString(void* P){
    Point* p = (Point*) P;
    char* pointString = (char*) malloc(50*sizeof(char));

    sprintf(pointString, "X: %.2f  Y: %.2f \n", p->x, p->y);     

    return pointString;    
}

Point* nextToTop(Stack* PointerToHead) {
    Point* p = (Point*) stackTop(PointerToHead);
    stackPop(PointerToHead);
    
    Point* res = (Point*) stackTop(PointerToHead);
    stackPush(PointerToHead, p);
    return res; 
}

void swap(Point* p1, Point* p2) { 
    Point temp;
    temp.x = p1->x;
    temp.y = p1->y;
    
    p1->x = p2->x;
    p1->y = p2->y; 

    p2->x = temp.x;
    p2->y = temp.y;    
} 

double distSq(Point p1, Point p2) { 
    return (p1.x - p2.x)*(p1.x - p2.x) + 
        (p1.y - p2.y)*(p1.y - p2.y); 
} 

int orientation(Point* p, Point* q, Point* r){ 
    double val = (q->y - p->y) * (r->x - q->x) - 
            (q->x - p->x) * (r->y - q->y); 

    if (((int) val) == 0) return 0;
    return (((int) val) > 0)? 1 : 2;
} 

int compare(const void *vp1, const void *vp2) { 
    Point *p1 = (Point *)vp1; 
    Point *p2 = (Point *)vp2; 

    int o = orientation(&p0, p1, p2); 
    if (o == 0) 
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 

    return (o == 2)? -1: 1; 
}

Stack convexHull(Point points[], int n) { 

    int ymin = points[0].y, min = 0; 
    for (int i = 1; i < n; i++) { 
        int y = points[i].y; 

        
        if ((y < ymin) || (ymin == y && 
            points[i].x < points[min].x)) 
            ymin = points[i].y, min = i; 
    } 


    swap(&points[0], &points[min]); 


    p0 = points[0]; 
    qsort(&points[1], n-1, sizeof(Point), compare); 

    
    int m = 1; 
    for (int i=1; i<n; i++) { 
    
        while (i < n-1 && orientation(&p0, &points[i], &points[i+1]) == 0) 
            i++; 

        points[m] = points[i]; 
        m++; 
    } 


    if (m < 3) 
        return NULL; 


    Stack head = createStack();
    stackPush(&head, &points[0]);
    stackPush(&head, &points[1]);
    stackPush(&head, &points[2]);


    for (int i = 3; i < m; i++) { 
        while (orientation(nextToTop(&head), stackTop(&head), &points[i]) != 2) 
            stackPop(&head); 
        
        stackPush(&head, &points[i]);
    } 

    return head;
} 
//------------------------------------------------------------------------------//


int calculateTotalCovidCasesInRegion(List housesInsideCircList){
    Node NODE = getFirst(housesInsideCircList);
    if(isElementNull(NODE, "NODE", "calculateTotalCovidCasesInRegion | getFirst"))
        return -1;
    
    int totalCases = 0;
    Info house = NULL;

    while(NODE != NULL){
        house = get(housesInsideCircList, NODE);
        totalCases += getHouseCasesNumber(house);
        NODE = getNext(housesInsideCircList, NODE);
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
    else{
        // Fazer tratamentos ******
        return 'Z';
    }
}

double calculateIncidenceRegionArea(Point** convexHullPoints, int convexHullPointsAmount){

    double area = 0;
    double sum1 = 0;
    double sum2 = 0;
    
    for(int i = convexHullPointsAmount-1; i > -1; i--){
        if(i == 0){
            sum1 += ((**(convexHullPoints + i)).x) * ((**(convexHullPoints + convexHullPointsAmount-1)).y);
            break;
        }
        
        sum1 += ((**(convexHullPoints + i)).x) * ((**(convexHullPoints + i - 1)).y);   
    }

    for(int i = convexHullPointsAmount-1; i > -1; i--){
        if(i == 0){
            sum2 += ((**(convexHullPoints + i)).y) * ((**(convexHullPoints + convexHullPointsAmount-1)).x);
            break;
        }
        
        sum2 += ((**(convexHullPoints + i)).y) * ((**(convexHullPoints + i - 1)).x);
    }

   area = (sum1 - sum2) / 2;
   return area;
}


char* determineIncidenceRegionColor(char incidenceRegionCategory);

char* buildIncidenceRegionTag(Point** points, int pointsAmount, char incidenceRegionCategory){
    char* incidenceRegionTag = (char*) malloc(1000 * sizeof(char));
    if(isElementNull(incidenceRegionTag, "incidenceRegionTag", "buildIncidenceRegionTag"))
        return NULL;
    
    int stringLength = strlen("\t<polygon points=\"");
    sprintf(incidenceRegionTag, "\t<polygon points=\"");

    char* aux = incidenceRegionTag + stringLength;
    char pointX[10], pointY[10];
    
    for(int i = 0; i<pointsAmount; i++){
        sprintf(aux, "%.2f,%.2f ", (**(points + i)).x, (**(points + i)).y);
        sprintf(pointX, "%.2f", (**(points + i)).x);
        sprintf(pointY, "%.2f", (**(points + i)).y);
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

int checkCircleIrregularPolygonOverlap(double x, double y, double radius, Point** convexHullPoints);
Point calculatePolygonCentroid(Point** convexHullPoints, int convexHullPointsAmount, double incidenceRegionArea);
char* buildHealthCenterSuggestionTag(Point polygonCentroid);

void suggestHealthCenterInRegionIfNeeded(List healthCenterList, List queryElementsList, Point** convexHullPoints, int convexHullPointsAmount, double incidenceRegionArea){
    Node NODE = getFirst(healthCenterList);
    if(isElementNull(NODE, "NODE", "suggestHealthCenterInRegionIfNeeded | getFirst"))
        return;
    
    Info healthCenter = NULL;
    double x, y, radius;

    while(NODE != NULL){
        healthCenter = get(healthCenterList, NODE);
        x = atof(getHealthCenterX(healthCenter));
        y = atof(getHealthCenterY(healthCenter));
        radius = atof(getHealthCenterRadius(healthCenter));
        
        if(checkCircleIrregularPolygonOverlap(x, y, radius, convexHullPoints))
            return; //se em algum momento houver overlap entre um posto e a regiao de incidencia saimos da funcao sem sugerir um posto.

        NODE = getNext(healthCenterList, NODE);
    }

    // Caso finalize o loop sem retorno, significa que não foi encontrado nenhuma posto de saude dentro do poligono e precisamos sugerir a construcao de um.
    Point polygonCentroid = calculatePolygonCentroid(convexHullPoints, convexHullPointsAmount, incidenceRegionArea);
    
    char* healthCenterSuggestionTag = buildHealthCenterSuggestionTag(polygonCentroid);
    insert(queryElementsList, healthCenterSuggestionTag);  
}

int checkCircleIrregularPolygonOverlap(double x, double y, double radius, Point** convexHullPoints){
    
    
    
    
    return 0;
}

Point calculatePolygonCentroid(Point** convexHullPoints, int convexHullPointsAmount, double incidenceRegionArea){
    Point point;
    double sum1 = 0, sum2 = 0;
    double xi, yi, xi1, yi1;

    for(int i = 0; i<convexHullPointsAmount; i++){
        xi = (**(convexHullPoints + i)).x;
        yi = (**(convexHullPoints + i)).y;

        if(i == convexHullPointsAmount-1){
            xi1 = (**(convexHullPoints)).x;
            yi1 = (**(convexHullPoints)).y;
        }else{
            xi1 = (**(convexHullPoints + i + 1)).x;
            yi1 = (**(convexHullPoints + i + 1)).y;
        }

        sum1 += ( (xi + xi1) * (xi*yi1 - xi1*yi) )  ;
    }

    point.x = (1 / (6 * incidenceRegionArea)) * sum1;

    for(int i = 0; i<convexHullPointsAmount; i++){
        xi = (**(convexHullPoints + i)).x;
        yi = (**(convexHullPoints + i)).y;

        if(i == convexHullPointsAmount-1){
            xi1 = (**(convexHullPoints)).x;
            yi1 = (**(convexHullPoints)).y;
        }else{
            xi1 = (**(convexHullPoints + i + 1)).x;
            yi1 = (**(convexHullPoints + i + 1)).y;
        }

        sum2 += (yi + yi1) * (xi*yi1 - xi1*yi);
    }   
    point.y = (1 / (6 * incidenceRegionArea)) * sum2;
    
    return point;
}

char* buildHealthCenterSuggestionTag(Point polygonCentroid){
    char* healthCenterSuggestionTag = (char*) malloc(500 * sizeof(char));
    if(isElementNull(healthCenterSuggestionTag, "healthCenterSuggestionTag", "buildHealthCenterSuggestionTag"))
        return NULL;
    
    sprintf(healthCenterSuggestionTag, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"10\" stroke=\"black\" stroke-width=\"1\" fill=\"black\" fill-opacity=\"0.0\"/>\n\t<text x=\"%lf\" y=\"%lf\" fill=\"black\" text-anchor=\"middle\" dy=\".3em\"> HC </text>\n", polygonCentroid.x, polygonCentroid.y, polygonCentroid.x, polygonCentroid.y);
    return healthCenterSuggestionTag;
}

void writeCovidIncidenceReportOnTxt(File txt, Point* points, int pointsAmount, int totalCovidCasesInRegion, double incidenceRegionArea, char incidenceRegionCategory, int totalHabitantsInRegion){

    fprintf(txt, "Coordenadas dos pontos dentro do circulo:\n");
    for(int i = 0; i<pointsAmount; i++)
        fprintf(txt, "\t(%d) x: %.2f, y: %.2f\n", (i+1), points[i].x, points[i].y);
    
    fprintf(txt, "\nTotal de habitantes: %d\n", totalHabitantsInRegion);
    fprintf(txt, "\nNumero total de casos: %d\n", totalCovidCasesInRegion);
    fprintf(txt, "\nArea dentro da envoltoria convexa: %.2f\n", incidenceRegionArea);
    fprintf(txt, "\nCategoria da regiao de incidencia: %c\n", incidenceRegionCategory);
}