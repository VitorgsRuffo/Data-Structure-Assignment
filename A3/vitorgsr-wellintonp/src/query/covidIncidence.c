#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing/drawing.h"
#include "../include/query.h"

typedef struct {
    double x, y;
    double radius;
}Circumference;


void executeCovidIncidenceReportInRegion(char* command, Drawing Dr, File txt){
    /* to do list

        - interpret command.

        - function: iterate over houseList, if the current house is inside the circumference we put it inside the other list.
        
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