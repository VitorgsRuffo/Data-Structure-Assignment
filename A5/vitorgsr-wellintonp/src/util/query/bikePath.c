#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../algorithm/prim.h"
#include "../input/openInput.h"
#include "../svg.h"

Graph createUndirectedRoadSystem(Graph roadSystem);
void drawCityBikePathOnSvg(Svg bikePathSvg, Graph cityBikePath);

void createCityBikePath(char* command, City Ct, Parameters Param){
    
    char sufix[50];
    sscanf(command, "%s", sufix);

    Graph roadSystem = getRoadSystem(Ct);
    if(roadSystem == NULL) return;


    Graph undirectedRoadSystem = createUndirectedRoadSystem(roadSystem);
    if(undirectedRoadSystem == NULL) return;
    
    setGetEdgeWeightFunction(undirectedRoadSystem, getStreetLength);

    Graph cityBikePath = prim(undirectedRoadSystem, NULL);
    if(cityBikePath == NULL) return;
    
    setBikePath(Ct, cityBikePath);

    Svg bikePathSvg = createSvg(Param, Ct, "qry", sufix);
    drawCityBikePathOnSvg(bikePathSvg, cityBikePath);
    finishSvg(bikePathSvg);

    freeGraph(undirectedRoadSystem, NULL, 0);
}

Graph createUndirectedRoadSystem(Graph roadSystem){
    Graph undirectedRoadSystem = createGraph(getGraphOrder(roadSystem));

    //adicionando os vertices no novo grafo:
    List verticesIds = getGraphVertices(roadSystem);
    
    Node current = getFirst(verticesIds);
    char* currentVertexId; 
    Point currentVertexCoordinates;

    while(current != NULL){
        currentVertexId = (char*) get(verticesIds, current);
        currentVertexCoordinates = getGraphVertexInfo(roadSystem, currentVertexId);

        insertVertex(undirectedRoadSystem, currentVertexId, currentVertexCoordinates);

        current = getNext(verticesIds, current);
    }

    //adicionando as arestas no novo grafo. Todas as arestas (u,v), existente no grafo original, são adicionadas ao novo grafo.
    //Alem disso, para cada uma delas, uma aresta (v,u) é adicionada logo em seguida. Assim, ao final do algoritmo o novo grafo
    //é semelhante ao original, porem é nao direcionado.

    current = getFirst(verticesIds);
    List adjacentVerticesIds; 
    Node currentAdjacent; 
    char* currentAdjacentVertexId; 
    Info currentEdgeInfo;

    while(current != NULL){

        currentVertexId = (char*) get(verticesIds, current);
        adjacentVerticesIds = getAdjacentVertices(roadSystem, currentVertexId);
        
        currentAdjacent = getFirst(adjacentVerticesIds);

        while(currentAdjacent != NULL){
            
            currentAdjacentVertexId = (char*) get(adjacentVerticesIds, currentAdjacent);
            currentEdgeInfo = getGraphEdgeInfo(roadSystem, currentVertexId, currentAdjacentVertexId);

            insertEdge(undirectedRoadSystem, currentVertexId, currentAdjacentVertexId, currentEdgeInfo, NULL);
            insertEdge(undirectedRoadSystem, currentAdjacentVertexId, currentVertexId, currentEdgeInfo, NULL);

            currentAdjacent = getNext(adjacentVerticesIds, currentAdjacent);
        }

        freeList(adjacentVerticesIds, NULL);

        current = getNext(verticesIds, current);
    }

    freeList(verticesIds, NULL);

    return undirectedRoadSystem;
}

#define vertex_radius 5.0 
#define vertex_tag_length 500


void drawCityBikePathOnSvg(Svg bikePathSvg, Graph cityBikePath){

    char* verticesTags = (char*) malloc((getGraphOrder(cityBikePath)*vertex_tag_length)*sizeof(char));
    char buffer[vertex_tag_length];
    int offset = 0;

    List verticesIds = getGraphVertices(cityBikePath);
    Node currentIdNode = getFirst(verticesIds);

    Point currentCoordinates;

    while(currentIdNode != NULL){
        char* currentId = (char*) get(verticesIds, currentIdNode);
        
        currentCoordinates = getGraphVertexInfo(cityBikePath, currentId);
        double vertex1X = getPointX(currentCoordinates);
        double vertex1Y = getPointY(currentCoordinates);

        //criando a tag svg do vertice atual:
        //sprintf(buffer, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" stroke=\"red\" stroke-width=\"1\" fill=\"black\" />\n\t<text x=\"%.lf\" y=\"%.lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> %s </text>\n", vertex1X, vertex1Y, vertex_radius, vertex1X, vertex1Y, currentId);
        sprintf(buffer, "\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"%.2lf\" stroke=\"red\" stroke-width=\"1\" fill=\"black\" />\n", vertex1X, vertex1Y, vertex_radius);
        sprintf(verticesTags+offset, "%s", buffer);
        offset += strlen(buffer);

        //criando as tags svg das arestas do vertice atual:
        List adjacentVerticesIds = getAdjacentVertices(cityBikePath, currentId);
        
        Node currentAdjacentIdNode = getFirst(adjacentVerticesIds);

        while(currentAdjacentIdNode != NULL){

            char* currentAdjacentId = (char*) get(adjacentVerticesIds, currentAdjacentIdNode);
            currentCoordinates = getGraphVertexInfo(cityBikePath, currentAdjacentId);
            double vertex2X = getPointX(currentCoordinates);
            double vertex2Y = getPointY(currentCoordinates);

            fprintf(bikePathSvg, "\t<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n", vertex1X, vertex1Y, vertex2X, vertex2Y);

            currentAdjacentIdNode = getNext(adjacentVerticesIds, currentAdjacentIdNode);
        }

        freeList(adjacentVerticesIds, NULL);

        currentIdNode = getNext(verticesIds, currentIdNode);
    } 
    

    fprintf(bikePathSvg, "%s", verticesTags);
    
    free(verticesTags);
    freeList(verticesIds, NULL);
}