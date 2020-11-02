#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing/drawing.h"
#include "../include/query.h"
#include "../include/figures.h"


void determineHousesInsideCircumference(List houseList, List housesInsideCircList, Circle circle);
char* buildBoundingCircumferenceTag(char* circumferenceX, char* circumferenceY, char* circumferenceRadius);
void calculateConvexHull(List convexHullHousesList, List housesInsideCircList);

void executeCovidIncidenceReportInRegion(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeCovidIncidenceReportInRegion"))
        return;

    char x[15], y[15], radius[15];
    sscanf(&command[3], "%s %s %s", x, y, radius);

    Circle circ = createCircle("...", radius, x, y, "...", "...", "...");
    
    List houseList = getHouseList(Dr);
    List housesInsideCircList = createList();
    determineHousesInsideCircumference(houseList, housesInsideCircList, circ);

    printf("\nLista de casas: \n");
    printList(houseList, &printHouse);

    printf("\nLista de casas dentro do circulo: \n");
    printList(housesInsideCircList, &printHouse);
    
    char* boundingCircumferenceTag = buildBoundingCircumferenceTag(x, y, radius);
    List queryElementsList = getQueryElementsList(Dr);
    insert(queryElementsList, boundingCircumferenceTag);
    
    List convexHullHousesList = createList();
    calculateConvexHull(convexHullHousesList, housesInsideCircList);

    
    /* to do list

        X - interpret command.

        X - function: iterate over houseList, if the current house is inside the circumference we put it inside the other list.

        - calculate the (envoltoria convexa) 




        - determine the incidence region category. (???)

        - function: check if there is a health center inside the area of incidence. (circle and irregular polygon overlap)
            if it doesn't:
                create "HC" text string on the (centroide) of the area and insert it on queryElementsListi.


        X - create circumference tag and insert on queryElementsList;

        - function: create tag(s) for the incidence region // <polygon points="%lf,%lf %lf,%lf %lf,%lf" style="fill:%s;stroke:red;stroke-width:2" />
        
        - write results on txt.
    */

    freeCircle(circ);
    freeOnlyList(housesInsideCircList);
    freeOnlyList(convexHullHousesList);

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

void calculateConvexHull(List convexHullHousesList, List housesInsideCircList){

}