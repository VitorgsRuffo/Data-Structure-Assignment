#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing/drawing.h"
#include "../include/query.h"
#include "../include/figures.h"

void determineHousesInsideCircumference(List houseList, List housesInsideCircList, Circle circle);

void executeCovidIncidenceReportInRegion(char* command, Drawing Dr, File txt){
    if(isElementNull(Dr, "drawing", "executeCovidIncidenceReportInRegion"))
        return;

    char x[15], y[15], radius[15];
    sscanf(&command[3], "%s %s %s", x, y, radius);

    Circle circle = createCircle("...", radius, x, y, "...", "...", "...");
    
    List houseList = getHouseList(Dr);
    List housesInsideCircList = createList();
    determineHousesInsideCircumference(houseList, housesInsideCircList, circle);
    
    
    /* to do list

        X - interpret command.

        - function: iterate over houseList, if the current house is inside the circumference we put it inside the other list.
            (intanciar retangulo e passar as funçoes do overlap para o tools)

        - calculate the (envoltoria convexa) (should we save the center of mass when the house occurs to be part of the (envoltoria convexa)) (create a list of points)   

        - determine the incidence region category. (???)

        - function: check if there is a health center inside the area of incidence. (circle x irregular polygon overlap)
            if it doesn't:
                create "HC" text string on the (centroide) of the area and insert it on queryElementsListi.

        - create circumference tag and insert on queryElementsList;

        - function: create tag(s) for the incidence region // <polygon points="%lf,%lf %lf,%lf %lf,%lf" style="fill:%s;stroke:red;stroke-width:2" />
        
        - write results on txt.
    */
}

void determineHousesInsideCircumference(List houseList, List housesInsideCircList, Circle circle){

    Node NODE = getFirst(houseList);
    if(isElementNull(NODE, "NODE", "determineHousesInsideCircumference | getFirst"))
        return;
    
    Info houseInfo = NULL;
    double houseX, houseY, houseW, houseH;

    while(NODE != NULL){

        houseInfo = get(houseList, NODE);
        houseX = getHouseX(houseInfo);
        houseY = getHouseY(houseInfo);
        houseW = getHousew(houseInfo);
        houseH = getHouseH(houseInfo);

        //Rectangle rect = createRectangle();

        if(checkRectCircOverlap(rect, circle))
            insert(housesInsideCircList, houseInfo);


        //freeRectangle(rect);
        NODE = getNext(houseList, NODE);
    }
}