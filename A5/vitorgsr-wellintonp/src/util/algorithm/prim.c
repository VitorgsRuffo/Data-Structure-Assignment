#include "../../include/headers.h"
#include "../data-structure/graph.h"
#include "../data-structure/list.h"

/* 
 * Algoritmo de Prim (Árvore geradora mínima).
 */

Graph prim(Graph Gr, char* originId){
    
    if(Gr == NULL) return NULL;

    int order = getGraphOrder(Gr);
    Graph mst = createGraph(order);

    //inserindo o primeiro vertice da arvore geradora minima.
    if(originId == NULL){
        List vertices = getGraphVertices(Gr);
        originId = (char*) get(vertices, getFirst(vertices));
        printf("\n\norigin : %s\n\n", originId);
        freeList(vertices, NULL);
    }

    Info vertexInfo = getGraphVertexInfo(Gr, originId);
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
        edges = getGraphVertexEdges(Gr, lastAddedVertex);
        currentNode = getFirst(edges);
        
        sourceId = getGraphVertexId(Gr, lastAddedVertex);
        printf("\n\nLast added id: %s\n\n", sourceId);

        while(currentNode != NULL){
        
            currentEdge = get(edges, currentNode);
            targetId = getGraphEdgeTargetId(Gr, currentEdge);

            //uma aresta (u,v) so podera fazer parte da lista de possiveis arestas se o vertice v ainda nao pertecer a arvore geradora minima. 
            //uma aresta do tipo (u, u) nao pode fazer parte da lista de possiveis arestas.
            if(!isVertexMemberOfGraph(mst, targetId) &&
                strcmp(sourceId, targetId) != 0)
                    insert(possibleEdges, currentEdge);
                    
            currentNode = getNext(edges, currentNode);
        }

        //iterando na lista de possiveis arestas para encontrar a aresta de menor custo:
        currentNode = getFirst(possibleEdges);
        Edge lowestCostEdge = NULL;
        Node lowestCostNode;
        
        while(currentNode != NULL){                                 
            
            currentEdge = get(possibleEdges, currentNode);
            targetId = getGraphEdgeTargetId(Gr, currentEdge);

            if(getGraphEdgeWeight(Gr, lowestCostEdge) > getGraphEdgeWeight(Gr, currentEdge) && 
               !isVertexMemberOfGraph(mst, targetId)){

                lowestCostEdge = currentEdge;
                lowestCostNode = currentNode; 
            }
            
            currentNode = getNext(possibleEdges, currentNode);
        }

        // Verificando se realmente foi encontrado uma lowestCostEdge
        if(lowestCostEdge != NULL){
            
            //ao encontrarmos a aresta de menor peso devemos remove-la da lista de possiveis arestas.
            removeNode(possibleEdges, lowestCostNode, NULL);

            //inserindo o vertice v e as arestas (u,v) e (v,u) de menor custo na arvore:
            sourceId = getGraphEdgeSourceId(Gr, lowestCostEdge);                                    
            targetId = getGraphEdgeTargetId(Gr, lowestCostEdge);
            Info edgeInfo = getGraphEdgeInfo(Gr, sourceId, targetId);

            Info vertexInfo = getGraphVertexInfo(Gr, targetId);
            insertVertex(mst, targetId, vertexInfo);

            insertEdge(mst, sourceId, targetId, edgeInfo, NULL);
            insertEdge(mst, targetId, sourceId, edgeInfo, NULL);

            mstInsertedVerticesAmount++;
            lastAddedVertex = getGraphVertex(mst, targetId);
        }
    }

    freeList(possibleEdges, NULL);
    
    return mst;
}
