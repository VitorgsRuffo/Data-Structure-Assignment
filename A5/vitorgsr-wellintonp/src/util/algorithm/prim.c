#include "../../include/headers.h"
#include "../data-structure/graph.h"
#include "../data-structure/list.h"


/* pseudo-codigo:

    T = ∅;
    U = { 1 };
    while (U ≠ V)
        let (u, v) be the lowest cost edge such that u ∈ U and v ∈ V - U;
        T = T ∪ {(u, v)}
        U = U ∪ {v}
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
    
    insertVertex(Gr, originId, vertexInfo);
    
    int mstInsertedVerticesAmount = 1;

    while(mstInsertedVerticesAmount < order){

        


        //ao adicionar um vertices novo:
        mstInsertedVerticesAmount++;
    }

    return mst;
}