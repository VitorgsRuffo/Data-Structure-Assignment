#include "../../include/headers.h"
#include "../data-structure/graph.h"
#include "../data-structure/list.h"

/* 
 * Algoritmo de Prim (Árvore geradora mínima) 
 */

Graph prim(Graph Gr, char* originId){
    
    if(Gr == NULL) return NULL;

    int order = getGraphOrder(Gr);
    Graph mst = createGraph(order);

    //inserindo o primeiro vertice da arvore geradora minima.
    if(originId == NULL){
        List vertices = getVertices(Gr);
        originId = (char*) get(vertices, getFirst(vertices));
    }

    Info vertexInfo = getVertexInfo(Gr, originId);
    if(vertexInfo == NULL) return NULL;
    
    insertVertex(mst, originId, vertexInfo);
    
    int mstInsertedVerticesAmount = 1;

    //lista das possiveis arestas que farão parte da arvore geradora minima:
    List possibleEdges = createList();
    
    //ultimo vertice adicionado a arvore geradora minima:
    Vertex lastAddedVertex = getGraphVertex(Gr, originId);

    List edges;
    Node currentNode;  
    Edge currentEdge;
    char* sourceId; char* targetId;

    while(mstInsertedVerticesAmount < order){
        
        //iterando na lista de arestas do ultimo vertice adicionado a arvore e salvando as arestas que possivelmente faram parte da arvore.
        edges = getGraphVertexEdges(lastAddedVertex);
        currentNode = getFirst(edges);
        
        sourceId = getGraphVertexId(lastAddedVertex);

        while(currentNode != NULL){
        
            currentEdge = get(edges, currentNode);
            targetId = getGraphEdgeTargetId(Gr, currentEdge);

            //uma aresta (u,v) so podera fazer parte da lista de possiveis arestas se ela nao estiver na lista e se o vertice v ainda nao pertecer a arvore geradora minima. 
            if(!isVertexMemberOfGraph(mst, targetId) &&
                searchForNodeByInfo(possibleEdges, currentEdge) == NULL)
                    insert(possibleEdges, currentEdge);
                    
            currentNode = getNext(edges, currentNode);
        }

        //iterando na lista de possiveis arestas para encontrar a aresta de menor custo:
        currentNode = getFirst(possibleEdges);
        Edge lowestCostEdge = NULL;
        Node lowestCostNode;
        
        while(currentNode != NULL){                                 /* MAS E SE FOR NULL? */
            
            currentEdge = get(possibleEdges, currentNode);
            targetId = getGraphEdgeTargetId(Gr, currentEdge);

            if(getGraphEdgeWeight(Gr, lowestCostEdge) > getGraphEdgeWeight(Gr, currentEdge) && 
               !isVertexMemberOfGraph(mst, targetId)){

                lowestCostEdge = currentEdge;
                lowestCostNode = currentNode; 
            }
            
            currentNode = getNext(possibleEdges, currentNode);
        }

        //ao encontrarmos a aresta de menor peso devemos remove-la da lista de possiveis arestas.
        removeNode(possibleEdges, lowestCostNode, NULL);

        //inserindo o vertice v e as arestas (u,v) e (v,u) de menor custo na arvore:
        sourceId = getGraphEdgeSourceId(Gr, lowestCostEdge);                                    
        targetId = getGraphEdgeTargetId(Gr, lowestCostEdge);
        Info edgeInfo = getEdgeInfo(Gr, sourceId, targetId);
        freeFunction freeEdgeInfo = getGraphEdgeFreeFunction(Gr, sourceId, targetId);

        Info vertexInfo = getVertexInfo(Gr, targetId);
        insertVertex(mst, targetId, vertexInfo);

        insertEdge(mst, sourceId, targetId, edgeInfo, freeEdgeInfo);
        insertEdge(mst, targetId, sourceId, edgeInfo, freeEdgeInfo);

        mstInsertedVerticesAmount++;
        lastAddedVertex = getGraphVertex(mst, targetId);
    }
    return mst;
}