#include "../../include/headers.h"
#include <unistd.h>
#include "../input/parameters.h"
#include "../svg.h"
#include "paths.h"
#include "../data-structure/list.h"
#include "../algorithm/sort.h"
#include "../algorithm/dijkstra.h"
#include "../algorithm/convexhull.h"
#include "../algorithm/prim.h"
#include "../../elements/urban-elements/street.h"
#include "../../elements/urban-elements/covidAddress.h"

typedef struct {
    char id[50];
    Point point;
    double distance;
}PossibleVertex;

Graph calculateSecureRoadSystem(City Ct, Point** covidRegionArray, int* covidRegionPointsAmount);
List getInRangeVerticesIds(PQuadTree tree, Point location, double radius);
char* getNearestVertexId(List possibleVerticesIds, Graph graph, Point location);
int comparePossibleVertices(Info pVertex1, Info pVertex2);
void drawPath(int pathId, Graph roadSystem, Point origin, Point destination, Svg* minimumPaths, File txt, Stack path, char* pathColor, char weightType);
void drawAvoidedCovidRegion(Svg minimumPaths, Point* covidRegion, int covidRegionPointsAmount);

void findBestCarPath(int isSecure, int pathId, Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt){
    
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

    Graph roadSystem;
    Point* covidRegion; int covidRegionPointsAmount;

    if(isSecure)
        roadSystem = calculateSecureRoadSystem(Ct, &covidRegion, &covidRegionPointsAmount);
    else
        roadSystem = getRoadSystem(Ct);

    if(roadSystem == NULL) return;

    Point* locations = getLocations(Ct);
    int index1 = atoi(&r1[1]);
    int index2 = atoi(&r2[1]);
    
    Point origin = locations[index1];
    Point destination = locations[index2];

    PQuadTree roadIntersections = getRoadIntersections(Ct);
    double radius = 50;

    List possibleOriginVerticesIds = getInRangeVerticesIds(roadIntersections, origin, radius);
    if(possibleOriginVerticesIds == NULL)
        return;

    if(length(possibleOriginVerticesIds) == 0 ){
        freeList(possibleOriginVerticesIds, NULL);
        return;
    }

    List possibleDestVerticesIds = getInRangeVerticesIds(roadIntersections, destination, radius);
    if(possibleDestVerticesIds == NULL)
        return;
    
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

    if(shorterPath == NULL){
        fprintf(txt, "Nao foi possivel calcular a rota, pois o ponto de destino esta indisponivel\n");
        
        drawOnSvg(*minimumPaths, Ct);

        if(isSecure)
            drawAvoidedCovidRegion(*minimumPaths, covidRegion, covidRegionPointsAmount);

        finishSvg(*minimumPaths);

        return;
    }
    
    setGetEdgeWeightFunction(roadSystem, getStreetDisplacementTime);
    Stack* fasterPath = dijkstra(roadSystem, sourceId, targetId);

    if(fasterPath == NULL)
        return;
    
    free(sourceId); free(targetId);

    if(stackLength(&shorterPath[1]) <= 1){
        fprintf(txt, "Nao foi encontrado um caminho entre a origem e o destino.\n");
        
        drawOnSvg(*minimumPaths, Ct);

        if(isSecure)
            drawAvoidedCovidRegion(*minimumPaths, covidRegion, covidRegionPointsAmount);

        finishSvg(*minimumPaths);
        
        freeDijkstraPath(shorterPath, 2);
        freeDijkstraPath(fasterPath, 2);
        return;   
    }

    drawOnSvg(*minimumPaths, Ct);
    
    if(isSecure)
        drawAvoidedCovidRegion(*minimumPaths, covidRegion, covidRegionPointsAmount);
    
    //desenhando os resultados no svg:
    drawPath(pathId, roadSystem, origin, destination, minimumPaths, txt, shorterPath[1], cmc, 's'); // 's': shorter path
    drawPath(pathId, roadSystem, origin, destination, minimumPaths, txt, fasterPath[1], cmr, 'f');  // 'f': faster path

    freeDijkstraPath(shorterPath, 2);
    freeDijkstraPath(fasterPath, 2);
}

Graph calculateSecureRoadSystem(City Ct, Point** covidRegionArray, int* covidRegionPointsAmount){
    Graph roadSystem = getRoadSystem(Ct);

    //Calculando a regiao de covid da cidade:
    PQuadTree covidAddresses = getCovidAddresses(Ct);
    
    int covidAddressesAmount = PQuadTreeSize(covidAddresses);
    CovidAddress* covidAdressesArray = PQuadTreeToArray(covidAddresses);

    Point* covidPoints = (Point*) malloc(sizeof(Point) * covidAddressesAmount);
    for(int i = 0; i<covidAddressesAmount; i++)
        covidPoints[i] = getCovidAddressCoordinates(covidAdressesArray[i]);
    
    Stack covidRegion = convexHull(covidPoints, covidAddressesAmount);
    if(covidRegion == NULL){
        free(covidAdressesArray);
        free(covidPoints);
        return NULL;
    } 

    *covidRegionPointsAmount = stackLength(&covidRegion);
    *covidRegionArray = stackToArray(&covidRegion); //vetor com os pontos que representam a regiao de covid da cidade (poligono)

    free(covidAdressesArray);
    free(covidPoints);

    Graph secureRoadSystem = createGraph(getGraphOrder(roadSystem));

    //Calculando os vertices do novo grafo que vai representar um sistema viario seguro, que evita a regiao de covid.
    //Esses vertices não estao dentro da regiao de covid.
    List verticesIds = getGraphVertices(roadSystem);
    Node current = getFirst(verticesIds);
    char* id; Point vertexCoordinates;

    while(current != NULL){
        id = (char*) get(verticesIds, current);
        vertexCoordinates = getGraphVertexInfo(roadSystem, id);

        if(!isPointInsidePolygon(vertexCoordinates, *covidRegionArray, *covidRegionPointsAmount))
            insertVertex(secureRoadSystem, id, vertexCoordinates);
        
        current = getNext(verticesIds, current);
    }

    //Calculando as arestas desse novo grafo:
    verticesIds = getGraphVertices(secureRoadSystem);

    current = getFirst(verticesIds);
    List adjacentVerticesIds; Node currentAdjacent; char* adjacentId; Info edgeInfo;

    while(current != NULL){
        //Para cada vertice do grafo seguro vamos tentar inserir as suas arestas do grafo original. 
        //Caso o vertice destino da aresta nao esteja no grafo seguro, ela nao é inserida. (Pois parte da aresta esta na regiao de covid)

        id = (char*) get(verticesIds, current);
        adjacentVerticesIds = getAdjacentVertices(roadSystem, id);
        currentAdjacent = getFirst(adjacentVerticesIds);

        while(currentAdjacent != NULL){
            
            adjacentId = (char*) get(adjacentVerticesIds, currentAdjacent);
            edgeInfo = getGraphEdgeInfo(roadSystem, id, adjacentId);
            insertEdge(secureRoadSystem, id, adjacentId, edgeInfo, freeStreet);
        
            currentAdjacent = getNext(adjacentVerticesIds, currentAdjacent);
        }

        current = getNext(verticesIds, current);
    }

    return secureRoadSystem;
}


void findBestBikePath(int pathId, Svg* minimumPaths, char* command, City Ct, Parameters Param, File txt){

    char sufix[20], r1[5], r2[5], cmc[20];
    sscanf(&command[4], "%s %s %s %s", sufix, r1, r2, cmc);

    //preparando svg para receber os resultados visuais:
    if(strcmp(sufix, "-") == 0){
        if(*minimumPaths == NULL)
            return;
    }else{
        finishSvg(*minimumPaths);
        *minimumPaths = createSvg(Param, Ct, "qry", sufix);
    }

    Graph bikePath = getBikePath(Ct);

    if(bikePath == NULL){
        fprintf(txt, "Nao ha uma arvore geradora minima\n");
        return;
    }

    // Obtendo os pontos salvos nos registradores do parametro
    Point* locations = getLocations(Ct);
    
    int index1 = atoi(&r1[1]);
    int index2 = atoi(&r2[1]);
    
    Point origin = locations[index1];
    Point destination = locations[index2];

    PQuadTree roadIntersections = getRoadIntersections(Ct);
    double radius = 50;

    List possibleOriginVerticesIds = getInRangeVerticesIds(roadIntersections, origin, radius);
    if(possibleOriginVerticesIds == NULL)
        return;

    if(length(possibleOriginVerticesIds) == 0){
        freeList(possibleOriginVerticesIds, NULL);
        return;
    }

    List possibleDestVerticesIds = getInRangeVerticesIds(roadIntersections, destination, radius);
    if(possibleOriginVerticesIds == NULL)
        return;
    
    if(length(possibleDestVerticesIds) == 0){
        freeList(possibleOriginVerticesIds, free);
        freeList(possibleDestVerticesIds, NULL);
        return;
    }

    //obtendo o id do vertice origem do caminho:  
    char* sourceId = getNearestVertexId(possibleOriginVerticesIds, bikePath, origin);
    freeList(possibleOriginVerticesIds, free);

    //obtendo o id do vertice destino do caminho:  
    char* targetId = getNearestVertexId(possibleDestVerticesIds, bikePath, destination);
    freeList(possibleDestVerticesIds, free);

    //calculando o menor caminho
    setGetEdgeWeightFunction(bikePath, getStreetLength);
    Stack* shorterPath = dijkstra(bikePath, sourceId, targetId);

    if(shorterPath == NULL){
        fprintf(txt, "Nao foi possivel calcular a rota para o caminho de bicicleta\n");
        //remove(); remover o svg vazio criado
        return;
    }

    free(sourceId); 
    free(targetId);

    if(stackLength(shorterPath[1]) <= 1){
        fprintf(txt, "Nao foi encontrado um caminho entre a origem () e o destino ().\n");
        freeDijkstraPath(shorterPath, 2);
        return;   
    }

    //desenhando os resultados no svg:
    drawOnSvg(*minimumPaths, Ct);
    drawPath(pathId, bikePath, origin, destination, minimumPaths, txt, shorterPath[1], cmc, 's'); // 's': shorter path

    freeDijkstraPath(shorterPath, 2);
}


List getInRangeVerticesIds(PQuadTree tree, Point location, double radius){

    if(location == NULL)
        return NULL;

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


void drawPath(int pathId, Graph roadSystem, Point origin, Point destination, Svg* minimumPaths, File txt, Stack path, char* pathColor, char weightType){
  
    stackPop(&path);
    
    char* vertexId;
    Point vertexLocation;
    double x, y;
    int pathLength = stackLength(&path);
    Info* pathArray = stackToArray(&path);

    fprintf(*minimumPaths, "<path id=\"path%d\" stroke=\"%s\" stroke-width=\"2\" fill=\"none\" d=\"M%.2lf %.2lf ", pathId, pathColor, getPointX(origin), getPointY(origin));

    for(int i = 1; i<pathLength-1; i++){
        vertexId = getDijkstraVertexId(pathArray[i]);
        vertexLocation = getGraphVertexInfo(roadSystem, vertexId);
        
        x = getPointX(vertexLocation);
        y = getPointY(vertexLocation);
        
        fprintf(*minimumPaths, "L%.2lf %.2lf ", x, y);
    }
    
    //objeto animado que percorre o caminho:
    
    fprintf(*minimumPaths, "\"/>\n\t<circle cx=\"\" cy=\"\" r=\"5\" fill=\"red\">\n\t\t<animateMotion dur=\"6s\" repeatCount=\"indefinite\">\n\t\t\t<mpath href=\"#path%d\"/>\n\t\t</animateMotion>\n\t</circle>\n", pathId);
    
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

/*
void drawAvoidedCovidRegion(Svg minimumPaths, Point* covidRegion, int covidRegionPointsAmount){
    char* covidRegionTag = (char*) malloc(10000 * sizeof(char));
    if(covidRegionTag == NULL) return NULL;
    
    int stringLength = strlen("\t<polygon points=\"");
    sprintf(covidRegionTag, "\t<polygon points=\"");

    char* aux = covidRegionTag + stringLength;
    char pointX[10], pointY[10];
    
    for(int i = 0; i<covidRegionPointsAmount; i++){
        sprintf(pointX, "%.2f", getPointX(*(covidRegion + i)));
        sprintf(pointY, "%.2f", getPointY(*(covidRegion + i)));
        sprintf(aux, "%.2f,%.2f ", pointX, pointY);
        aux += (strlen(pointX) + strlen(pointY) + 2);
    }

    char* covidRegionColor = "yellow"; 

    sprintf(aux,"\" style=\"fill:%s;stroke:red;stroke-width:2;fill-opacity:0.6\" />\n", covidRegionColor);
    
    fprintf(minimumPaths, "%s", covidRegionTag);
}*/


void drawAvoidedCovidRegion(Svg minimumPaths, Point* covidRegion, int covidRegionPointsAmount){
   
    fprintf(minimumPaths, "\t<polygon points=\"");
    
    for(int i = 0; i<covidRegionPointsAmount; i++)
        fprintf(minimumPaths, "%.2f,%.2f ", getPointX(*(covidRegion + i)), getPointY(*(covidRegion + i)));
    
    fprintf(minimumPaths,"\" style=\"fill:yellow;stroke:red;stroke-width:2;fill-opacity:0.6\" />\n");
}