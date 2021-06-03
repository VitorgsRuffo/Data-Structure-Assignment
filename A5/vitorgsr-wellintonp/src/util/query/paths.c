#include "../../include/headers.h"
#include "../input/parameters.h"
#include "../svg.h"
#include "paths.h"
#include "../data-structure/list.h"
#include "../algorithm/sort.h"
#include "../algorithm/dijkstra.h"
#include "../../elements/urban-elements/street.h"


typedef struct {
    char id[50];
    Point point;
    double distance;
}PossibleVertex;

List getInRangeVerticesIds(PQuadTree tree, Point location, double radius);
char* getNearestVertexId(List possibleVerticesIds, Graph graph, Point location);
int comparePossibleVertices(Info pVertex1, Info pVertex2);
void drawPath(int pathId, Graph roadSystem, Point origin, Point destination, Svg minimumPaths, File txt, Stack path, char* pathColor, char weightType);

void findBestCarPath(int pathId, Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt){
    
    char sufix[20], r1[5], r2[5], cmc[20], cmr[20];
    sscanf(&command[3], "%s %s %s %s %s", sufix, r1, r2, cmc, cmr);

    //preparando svg para receber os resultados visuais:
    if(strcmp(sufix, "-") == 0){
        if(*minimumPaths == NULL)
            return;
    }else{
        finishSvg(*minimumPaths);
        *minimumPaths = createSvg(Param, Ct, "qry", sufix);
    }

    Graph roadSystem = getRoadSystem(Ct);
    
    //
    Point* locations = getLocations(Ct);
    int index1 = atoi(&r1[1]);
    int index2 = atoi(&r2[1]);
    
    Point origin = locations[index1];
    Point destination = locations[index2];

    //
    PQuadTree roadIntersections = getRoadIntersections(Ct);
    double radius = 50;

    List possibleOriginVerticesIds = getInRangeVerticesIds(roadIntersections, origin, radius);
    if(length(possibleOriginVerticesIds) == 0){
        freeList(possibleOriginVerticesIds, NULL);
        return;
    }

    List possibleDestVerticesIds = getInRangeVerticesIds(roadIntersections, destination, radius);
    if(length(possibleDestVerticesIds) == 0){
        freeList(possibleOriginVerticesIds, free);
        freeList(possibleDestVerticesIds, NULL);
        return;
    }

    //obtendo o id do vertice origem do caminho:  
    char* sourceId = getNearestVertexId(possibleOriginVerticesIds, roadSystem, origin);
    freeList(possibleOriginVerticesIds, free);

    //obtendo o id do vertice destino do caminho:  
    char* targetId = getNearestVertexId(possibleDestVerticesIds, roadSystem, destination);
    freeList(possibleDestVerticesIds, free);


    //calculando o menor caminho e o caminho mais rapido:
    setGetEdgeWeightFunction(roadSystem, getStreetLength); 
    Stack* shorterPath = dijkstra(roadSystem, sourceId, targetId);
    
    setGetEdgeWeightFunction(roadSystem, getStreetDisplacementTime);
    Stack* fasterPath = dijkstra(roadSystem, sourceId, targetId);
    
    free(sourceId); free(targetId);
    
    if(stackLength(shorterPath[1]) <= 1){
        fprintf(txt, "Nao foi encontrado um caminho entre a origem () e o destino ().\n");
        freeDijkstraPath(shorterPath, 2);
        freeDijkstraPath(fasterPath, 2);
        return;   
    }
    
    //desenhando os resultados no svg:
    drawOnSvg(*minimumPaths, Ct);
    drawPath(pathId, roadSystem, origin, destination, *minimumPaths, txt, shorterPath[1], cmc, 's'); // 's': shorter path
    drawPath(pathId, roadSystem, origin, destination, *minimumPaths, txt, fasterPath[1], cmr, 'f');  // 'f': faster path

    freeDijkstraPath(shorterPath, 2);
    freeDijkstraPath(fasterPath, 2);
}


List getInRangeVerticesIds(PQuadTree tree, Point location, double radius){
    double circX = getPointX(location);
    double circY = getPointY(location);
    return getInfoKeysLocatedInsideCircle(tree, circX, circY, radius);
}

char* getNearestVertexId(List possibleVerticesIds, Graph graph, Point location){
    PossibleVertex* possibleVertex;
    int possibleVerticesAmount = length(possibleVerticesIds);
    Info* possibleVertices = (Info*) malloc(possibleVerticesAmount * sizeof(Info));

    int i = 0;
    Node current = getFirst(possibleVerticesIds);
    while(current != NULL){
        possibleVertex = (PossibleVertex*) malloc(sizeof(PossibleVertex));
        strcpy(possibleVertex->id, get(possibleVerticesIds, current));
        possibleVertex->point = getGraphVertexInfo(graph, possibleVertex->id);
        possibleVertex->distance = distanceBetweenPoints(possibleVertex->point, location);
        
        possibleVertices[i] = possibleVertex;

        current = getNext(possibleVerticesIds, current);
        i++;
    }

    quicksort(possibleVertices, 0, possibleVerticesAmount-1, comparePossibleVertices);
    
    char* nearestVertexId = (char*) malloc(50*sizeof(char));
    strcpy(nearestVertexId, ((PossibleVertex*) possibleVertices[0])->id);

    for(int i = 0; i<possibleVerticesAmount; i++)
        free(possibleVertices[i]);
    free(possibleVertices);

    return nearestVertexId;
}

int comparePossibleVertices(Info PVertex1, Info PVertex2){

    PossibleVertex* pVertex1 = (PossibleVertex*) PVertex1;
    PossibleVertex* pVertex2 = (PossibleVertex*) PVertex2;    

    if(pVertex1->distance < pVertex2->distance)
        return -1;
    else if(pVertex1->distance == pVertex2->distance)
        return 0;
    else
        return 1;    
}

void writePathDescriptionOnTxt(Graph roadSystem, Point destLocation, File txt, Info* pathArray, int pathLength, char weightType);


void drawPath(int pathId, Graph roadSystem, Point origin, Point destination, Svg minimumPaths, File txt, Stack path, char* pathColor, char weightType){
  
    stackPop(&path);
    char* vertexId;
    Point vertexLocation;
    double x, y;
    
    int pathLength = stackLength(&path);
    Info* pathArray = stackToArray(&path);
    
    fprintf(minimumPaths, "<path id=\"path%d\" stroke=\"%s\" stroke-width=\"1\" fill=\"none\" d=\"M%.2lf %.2lf ", pathId, pathColor, getPointX(origin), getPointY(origin));

    for(int i = 1; i<pathLength-1; i++){
        vertexId = getDijkstraVertexId(pathArray[i]);
        vertexLocation = getGraphVertexInfo(roadSystem, vertexId);
        x = getPointX(vertexLocation);
        y = getPointY(vertexLocation);
        
        fprintf(minimumPaths, "L%.2lf %.2lf ", x, y);
    }

    //objeto animado que percorre o caminho:
    fprintf(minimumPaths, "/>\n\t<circle cx=\"\" cy=\"\" r=\"5\" fill=\"red\">\n\t\t<animateMotion dur=\"6s\" repeatCount=\"indefinite\">\n\t\t\t<mpath href=\"#path%d\"/>\n\t\t</animateMotion>\n\t</circle>\n", pathId);
    
    writePathDescriptionOnTxt(roadSystem, destination, txt, pathArray, pathLength, weightType);
    free(pathArray);
}


void determinePhysicalQuantity(char weightType, char* physicalQuantity, char* unit);
void calculateStreetDirection(Graph roadSystem, char* currentVertexId, char* nextVertexId, char* direction);

void writePathDescriptionOnTxt(Graph roadSystem, Point destLocation, File txt, Info* pathArray, int pathLength, char weightType){
    
    char* currentVertexId, *nextVertexId, *thirdVertexId;
    char direction[10];
    char* streetName, *nextStreetName;
    double x = getPointX(destLocation); 
    double y = getPointY(destLocation);
    double totalPathCost;

    char physicalQuantity[10], unit[10]; 
    determinePhysicalQuantity(weightType, physicalQuantity, unit);

    fprintf(txt, "\n\nCaminho:\n");

    for(int i = 0; i<pathLength-1; i++){

        currentVertexId = getDijkstraVertexId(pathArray[i]);
        nextVertexId = getDijkstraVertexId(pathArray[i+1]);
        calculateStreetDirection(roadSystem, currentVertexId, nextVertexId, direction);
        streetName = getStreetName(getGraphEdgeInfo(roadSystem, currentVertexId, nextVertexId));
        
        if(i<pathLength-2) {
            
            thirdVertexId = getDijkstraVertexId(pathArray[i+2]);
            nextStreetName = getStreetName(getGraphEdgeInfo(roadSystem, nextVertexId, thirdVertexId));
            fprintf(txt, "Siga na direção %s na rua %s até o cruzamento com a rua %s. ", direction, streetName, nextStreetName);
        
        }else{
            totalPathCost = getDijkstraVertexDistanceFromOrigin(pathArray[i+1]);
            fprintf(txt, "Siga na direção %s na rua %s até o ponto (%.2lf, %.2lf).\n%s total: %.2lf %s.\n\n", direction, streetName, x, y, physicalQuantity, totalPathCost, unit);
        }   
    }
}

void determinePhysicalQuantity(char weightType, char* physicalQuantity, char* unit){
    
    if(weightType == 's'){
        strcpy(physicalQuantity, "Distancia");
        strcpy(unit, "metros");
    }else{
       strcpy(physicalQuantity, "Tempo");
       strcpy(unit, "segundos");
    }  
}


void calculateStreetDirection(Graph roadSystem, char* currentVertexId, char* nextVertexId, char* direction){
        
    Point curretVertexLocation = getGraphVertexInfo(roadSystem, currentVertexId);
    double x1 = getPointX(curretVertexLocation), y1 = getPointY(curretVertexLocation);
    
    Point nextVertexLocation = getGraphVertexInfo(roadSystem, nextVertexId);
    double x2 = getPointX(nextVertexLocation), y2 = getPointY(nextVertexLocation);

    if(x1 != x2){

        if(x1 - x2 > 0)
            strcpy(direction, "leste");
        else
            strcpy(direction, "oeste"); 
    
    }else{

        if(y1 - y2 > 0)
            strcpy(direction, "sul");
        else
            strcpy(direction, "norte");
    }
}