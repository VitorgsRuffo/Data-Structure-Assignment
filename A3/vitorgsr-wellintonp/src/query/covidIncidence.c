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
char* buildIncidenceRegionTag(Point** points, int pointsAmount);

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
    int convexHullPointsAmount = stackLength(&head);
    printf("\nstackLength: %d\n", convexHullPointsAmount);
    getchar();
    Point** convexHullPoints = (Point**) stackToArray(&head); 
    
    /* to do list

        X - interpret command.

        X - function: iterate over houseList, if the current house is inside the circumference we put it inside the other list.

        X - calculate the (envoltoria convexa) 




        - determine the incidence region category. (???)

        - function: check if there is a health center inside the area of incidence. (circle and irregular polygon overlap)
            if it doesn't:
                create "HC" text string on the (centroide) of the area and insert it on queryElementsListi.


        X - create circumference tag and insert on queryElementsList;

        x function: create tag(s) for the incidence region // <polygon points="%lf,%lf %lf,%lf %lf,%lf" style="fill:%s;stroke:red;stroke-width:2" />
        
        - write results on txt.
    */
   
    char* incidenceRegionTag = buildIncidenceRegionTag(convexHullPoints, convexHullPointsAmount);
    insert(queryElementsList, incidenceRegionTag);

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

char* buildIncidenceRegionTag(Point** points, int pointsAmount){
    char* incidenceRegionTag = (char*) malloc(1000 * sizeof(char));
    if(isElementNull(incidenceRegionTag, "incidenceRegionTag", "buildIncidenceRegionTag"))
        return NULL;
    
    int stringLength = strlen("\t<polygon points=\"");
    sprintf(incidenceRegionTag, "\t<polygon points=\"");

    char* aux = incidenceRegionTag + stringLength;
    char pointX[10], pointY[10];

    printf("\n\nPointsAmout: %d\n\n", pointsAmount);
    getchar();
    
    for(int i = 0; i<pointsAmount; i++){
        sprintf(aux, "%.2f,%.2f ", (**(points + i)).x, (**(points + i)).y);
        sprintf(pointX, "%.2f", (**(points + i)).x);
        sprintf(pointY, "%.2f", (**(points + i)).y);
        aux += (strlen(pointX) + strlen(pointY) + 2);
    }

    sprintf(aux,"\" style=\"fill:red;stroke:black;stroke-width:2;fill-opacity:0.3\" />\n");

    return incidenceRegionTag;
}