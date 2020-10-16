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
        
        - calculate the (envoltoria convexa) (should we save the house or just its center of mass when the house occurs to be part of the (envoltoria convexa)) (create a list of the houses or points)
            
        - determine the incidence region category.

        - function: check if there is a health center inside the area of incidence.
            if it doesn't:
                instantiate a new one on the (centroide) of the area and insert on its list.

        - create circumference tag and insert on queryElementsList;

        - function: create tag(s) for the incidence region
        
        - write results on txt.
    */
}