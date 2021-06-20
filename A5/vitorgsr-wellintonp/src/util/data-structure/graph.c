#include "../../include/headers.h"
#include "graph.h"
#include "hashtable.h"

typedef struct {
    char id[50];
    Info info;
    List edges;
}vertex;

typedef struct {
    char targetId[50];
    char sourceId[50];
    Info info;
    freeFunction freeInfo;
}edge;

typedef struct {
    int order;
    vertex* vertices;
    int insertedVerticesAmount; //quantidade de vertices que ja foram inseridos no grafo.
    HashTable indicesTable;
    getEdgeWeight get;
}graph;

/* Tipo de dados que sera guardado na tabela hash.
*  Vamos usar uma tabela hash para relacionar o id de um vertice a sua posicao no vetor de vertices do grafo. (Afim de facilitar consultas)
*/
typedef struct {
    char id[50];
    int index;
}idIndex;


//Funcoes privadas auxiliares:
/*
* Busca na tabela de indices qual é o indice do vertice identificado por "id" no vetor de vertices do grafo.
* O valor encontrado é retornado. Se o vertice nao existir no grafo o indice -1 é retornado.
*/
int getVertexIndex(graph* gr, char* id);

char* getVertexId(Info IdIndex);

/*
* Busca a aresta (sourceId, targetId) no grafo. Se encontrada seu endereço e retornado. Se nao NULL e retornado.
*/
edge* findEdge(graph* gr, char* sourceId, char* targetId);

void freeEdge(Info Ed);
void freeEdgeAndInfo(Info Ed);

Graph createGraph(int order){
    graph* gr = (graph*) malloc(sizeof(graph));
    if(gr == NULL) return NULL;

    gr->order = order;

    gr->vertices = (vertex*) malloc(order * sizeof(vertex));
    if(gr->vertices == NULL){
        free(gr);
        return NULL;
    }

    for(int i = 0; i<order; i++){
        strcpy(gr->vertices[i].id, "00");
        gr->vertices[i].info = NULL;
        gr->vertices[i].edges = NULL;
    }

    gr->insertedVerticesAmount = 0;
    
    // Desde o inicio ja sabemos quantos elementos vamos inserir na tabela hash. Portanto, vamos calcular um tamanho para ela de modo que sua ocupação fique menor ou igual a 70%.
    int tableSize = ceil((10.00 * order) / 7.00); 

    gr->indicesTable = createHashTable(tableSize, getVertexId);
    if(gr->indicesTable == NULL){
        free(gr);
        free(gr->vertices);
        return NULL;
    }

    gr->get = NULL;
    
    return gr;
}


int getGraphOrder(Graph Gr){

    if(Gr == NULL) return -1;
    graph* gr = (graph*) Gr;

    return gr->insertedVerticesAmount;
}


List getGraphVertices(Graph Gr){
    if(Gr == NULL) return NULL;
    graph* gr = (graph*) Gr;

    List vertices = createList();
    if(vertices == NULL) return NULL;

    for(int i = 0; i<gr->insertedVerticesAmount; i++)
        insert(vertices, gr->vertices[i].id);

    return vertices;
}


int setGetEdgeWeightFunction(Graph Gr, getEdgeWeight get){
    if(Gr == NULL || get == NULL ) return 0;
    graph* gr = (graph*) Gr;
    
    gr->get = get;
    return 1;
}


int isVertexMemberOfGraph(Graph Gr, char* id){
    if(Gr == NULL || id == NULL) return 0;
    graph* gr = (graph*) Gr;

    if(isThereKeyInHashTable(gr->indicesTable, id))
        return 1;   
    else
        return 0;
}


int insertVertex(Graph Gr, char* id, Info info){
    if(Gr == NULL || id == NULL) return 0;
    graph* gr = (graph*) Gr;

    if(gr->insertedVerticesAmount >= gr->order) return 0;
    if(isVertexMemberOfGraph(Gr, id)) return 0;

    //Instanciamos um objeto que guarda o id e o indice (no vetor de vertices do grafo) do novo vertice a ser inserido.
    idIndex* vertexIdIndex = (idIndex*) malloc(sizeof(idIndex));
    strcpy(vertexIdIndex->id, id);
    vertexIdIndex->index = gr->insertedVerticesAmount;

    if(!insertHashTable(&gr->indicesTable, vertexIdIndex)){
        free(vertexIdIndex);
        return 0;
    }

    strcpy(gr->vertices[gr->insertedVerticesAmount].id, id);
    gr->vertices[gr->insertedVerticesAmount].info = info;
    gr->vertices[gr->insertedVerticesAmount].edges = createList();

    gr->insertedVerticesAmount++;

    return 1;
}


int insertEdge(Graph Gr, char* sourceId, char* targetId, Info info, freeFunction freeInfo){
    if(Gr == NULL || sourceId == NULL || targetId == NULL) return 0;
    graph* gr = (graph*) Gr;

    //Obtendo o indice do vertice, no vetor de vertices do grafo, que sera a origem da nova aresta a ser inserida.
    int sourceIndex = getVertexIndex(gr, sourceId);
    if(sourceIndex == -1) return 0;


    //Checando se a aresta ja existe no grafo:
    List edges = gr->vertices[sourceIndex].edges;
    Node current = getFirst(edges);
    while(current != NULL){

        edge* currentEd = (edge*) get(edges, current);

        if(!strcmp(targetId, currentEd->targetId))
            return 0;

        current = getNext(edges, current);
    }

    //Obtendo o indice do vertice, no vetor de vertices do grafo, que sera o destino da nova aresta a ser inserida.
    int targetIndex = getVertexIndex(gr, targetId);
    if(targetIndex == -1) return 0;


    edge* newEdge = (edge*) malloc(sizeof(edge));
    if(newEdge == NULL) return 0;

    strcpy(newEdge->sourceId, sourceId);
    strcpy(newEdge->targetId, targetId);
    newEdge->info = info;
    newEdge->freeInfo = freeInfo;

    if(insert(gr->vertices[sourceIndex].edges, newEdge) == NULL){
        free(newEdge);
        return 0;
    }
   
    return 1;
}


Info getGraphVertexInfo(Graph Gr, char* id){
    if(Gr == NULL || id == NULL ) return 0;
    graph* gr = (graph*) Gr;

    //Obtendo o indice do vertice, no vetor de vertices do grafo, cujo identificador é "id".
    int index = getVertexIndex(gr, id);
    if(index == -1) return NULL;

    return gr->vertices[index].info;
}


char* getGraphVertexId(Graph Gr, Vertex Vt){
    if(Gr == NULL || Vt == NULL) return NULL;
    
    vertex* vt = (vertex*) Vt;
    return vt->id;
}


Vertex getGraphVertex(Graph Gr, char* id){
    
    if(Gr == NULL) return NULL;
    graph* gr = (graph*) Gr;

    int index = getVertexIndex(gr, id);
    if(index == -1) return NULL;

    return &(gr->vertices[index]);
}


List getGraphVertexEdges(Graph Gr, Vertex Vt){

    if(Gr == NULL || Vt == NULL) return NULL;
    
    graph* gr = (graph*) Gr;
    vertex* vt = (vertex*) Vt;

    int index = getVertexIndex(gr, vt->id);
    if(index == -1) return NULL;

    return gr->vertices[index].edges;
}

int removeVertex(Graph Gr, int graphIsDirected, char* id, freeFunction freeInfo){
    if(Gr == NULL || id == NULL ) return 0;
    graph* gr = (graph*) Gr;

    int index = getVertexIndex(gr, id);
    if(index == -1) return 0;
    
    //removendo todas as arestas que saem ou chegam no vertice a ser removido:
    List verticesIds = getGraphVertices(Gr);
    Node currentIdNode = getFirst(verticesIds);
    char* currentId;

    while(currentIdNode != NULL){

        currentId = get(verticesIds, currentIdNode);

        removeEdge(Gr, id, currentId, 1);

        if(graphIsDirected)
            removeEdge(Gr, currentId, id, 1);
        
        else//se o grafo for nao-direcionado uma conexao entre vertices u e v sera representada por duas arestas: (u,v) (v,u). Ambas arestas guardam a mesma informacao, assim, nao queremos desalocar essa informacao duas vezes, portanto, ao desalocar a segunda aresta passamos o valor 0.  
            removeEdge(Gr, currentId, id, 0);
        

        currentIdNode = getNext(verticesIds, currentIdNode);
    }

    //removendo o indice do vertice da tabela de indices:
    removeHashTableInfo(gr->indicesTable, id, free);

    //removendo o vertice do vetor de vertices e atualizando a tabela de indices:
    if(freeInfo != NULL)
        (*freeInfo)(gr->vertices[index].info);
    
    freeList(gr->vertices[index].edges, NULL); //todas as arestas que saem do vertice ja foram desalocadas entao desalocamos apenas a lista.

    idIndex* vertexIdIndex;
    for(int i = index; i<gr->insertedVerticesAmount-1; i++){
        gr->vertices[i] = gr->vertices[i+1];
        vertexIdIndex = (idIndex*) getHashTableInfo(gr->indicesTable, gr->vertices[i].id);
        vertexIdIndex->index = i;
    }

    freeList(verticesIds, NULL);
    gr->insertedVerticesAmount--;
    return 1;
}

Info getGraphEdgeInfo(Graph Gr, char* sourceId, char* targetId){
    if(Gr == NULL || sourceId == NULL || targetId == NULL) return 0;
    graph* gr = (graph*) Gr;

    edge* ed = findEdge(gr, sourceId, targetId);
    
    if(ed == NULL) return NULL;
    else           return ed->info; 
}

char* getGraphEdgeSourceId(Graph Gr, Edge Ed){
    if(Gr == NULL || Ed == NULL) return NULL;
    
    edge* ed = (edge*) Ed;
    return ed->sourceId;
}

char* getGraphEdgeTargetId(Graph Gr, Edge Ed){
    if(Gr == NULL || Ed == NULL) return NULL;
    
    edge* ed = (edge*) Ed;
    return ed->targetId;
}

double getGraphEdgeWeight(Graph Gr, Edge Ed){
    if(Gr == NULL) return -1.0;
    if(Ed == NULL) return 999999999;

    graph* gr = (graph*) Gr;
    edge* ed = (edge*) Ed;

    return (*(gr->get))(ed->info);
}

freeFunction getGraphEdgeFreeFunction(Graph Gr, Edge Ed){
    if(Gr == NULL || Ed == NULL) return NULL;
    
    edge* ed = (edge*) Ed;
    return ed->freeInfo;
}


int removeEdge(Graph Gr, char* sourceId, char* targetId, int freeInfo){
    if(Gr == NULL || sourceId == NULL || targetId == NULL) return 0;
    graph* gr = (graph*) Gr;

    //Obtendo o indice do vertice, no vetor de vertices do grafo, que é a origem da aresta.
    int sourceIndex = getVertexIndex(gr, sourceId);
    if(sourceIndex == -1) return 0;

    //Percorrendo lista de edges até encontrar a aresta...
    List edges = gr->vertices[sourceIndex].edges;
    Node currentNode = getFirst(edges);
    edge* currentEdge;

    while(currentNode != NULL){

        currentEdge = (edge*) get(edges, currentNode);

        if(!strcmp(currentEdge->targetId, targetId)){
            
            removeNode(edges, currentNode, NULL);

            if(currentEdge->info != NULL && freeInfo == 1)
                (*currentEdge->freeInfo)(currentEdge->info);
            
            free(currentEdge);
            
            return 1;
        }
            
        currentNode = getNext(edges, currentNode);
    }

    return 0;
}


int isAdjacent(Graph Gr, char* vertex1Id, char* vertex2Id){
    if(Gr == NULL || vertex1Id == NULL || vertex2Id == NULL) return 0;
    graph* gr = (graph*) Gr;

    edge* ed = findEdge(gr, vertex1Id, vertex2Id);
    if(ed == NULL) return 0;
    else           return 1; 
}


List getAdjacentVertices(Graph Gr, char* vertexId){
    if(Gr == NULL || vertexId == NULL) return NULL;
    graph* gr = (graph*) Gr;

    int vertexIndex = getVertexIndex(gr, vertexId);
    if(vertexIndex == -1)
        return NULL;

    List adjacentVertices = createList(); 
    if(adjacentVertices == NULL) return NULL;

    List edges = gr->vertices[vertexIndex].edges;
    Node currentNode = getFirst(edges);
    edge* currentEdge;

    while(currentNode != NULL){

        currentEdge = (edge*) get(edges, currentNode);

        insert(adjacentVertices, (Info) currentEdge->targetId);

        currentNode = getNext(edges, currentNode);
    }

    return adjacentVertices;
}


void printGraph(Graph Gr, printInfo printVertexInfo, printInfo printEdgeInfo){
    if(Gr == NULL) return;
    graph* gr = (graph*) Gr;

    for(int i = 0; i<gr->insertedVerticesAmount; i++){
        printf("\nvertex Id: %s\n", gr->vertices[i].id);
        if(gr->vertices[i].info != NULL && printVertexInfo != NULL)
            (*printVertexInfo)(gr->vertices[i].info);
        
        List edges = gr->vertices[i].edges;
        Node currentNode = getFirst(edges);
        edge* currentEdge;

        while(currentNode != NULL){

            currentEdge = (edge*) get(edges, currentNode);

            printf("edge: (%s, %s)\n", gr->vertices[i].id, currentEdge->targetId);
            
            if(printEdgeInfo != NULL && currentEdge->info != NULL)
                (*printEdgeInfo)(currentEdge->info);
                
            currentNode = getNext(edges, currentNode);
        }
    }
}

void printVerticesId(Graph Gr){

    //List verticesIds = getGraphVertices(Gr);

    /*void printVertex(void* current){
        printf("%s\n", (char*) current);
    }*/

    //printList(verticesIds, printVertex);
}


void freeGraph(Graph Gr, freeFunction freeVertexInfo, int freeEdgeInfo){
    if(Gr == NULL) return;
    graph* gr = (graph*) Gr;

    for(int i = 0; i<gr->insertedVerticesAmount; i++){
        if(gr->vertices[i].info != NULL && freeVertexInfo != NULL)
            (*freeVertexInfo)(gr->vertices[i].info);
        
        if(freeEdgeInfo == 0)
            freeList(gr->vertices[i].edges, freeEdge);
        else
            freeList(gr->vertices[i].edges, freeEdgeAndInfo); 

    }
    free(gr->vertices);
    freeHashTable(gr->indicesTable, free);
    free(gr);
}


//Funcoes privadas auxiliares:

int getVertexIndex(graph* gr, char* id){
    idIndex* vertexIdIndex = (idIndex*) getHashTableInfo(gr->indicesTable, id);
    if(vertexIdIndex == NULL)
        return -1;

    return vertexIdIndex->index;
}

char* getVertexId(Info IdIndex){
    idIndex* vertexIdIndex = (idIndex*) IdIndex;
    return vertexIdIndex->id;
}

edge* findEdge(graph* gr, char* sourceId, char* targetId){
    //Obtendo o indice do vertice, no vetor de vertices do grafo, que é a origem da aresta.
    int sourceIndex = getVertexIndex(gr, sourceId);
    if(sourceIndex == -1)
        return NULL;

    //Percorrendo lista de edges até encontrar a aresta...
    List edges = gr->vertices[sourceIndex].edges;
    Node currentNode = getFirst(edges);
    edge* currentEdge;

    while(currentNode != NULL){

        currentEdge = (edge*) get(edges, currentNode);

        if(!strcmp(currentEdge->targetId, targetId))
            return currentEdge;

        currentNode = getNext(edges, currentNode);
    }

    return NULL; //se a aresta nao for encontrada NULL é retornado.
}

void freeEdge(Info Ed){
    edge* ed = (edge*) Ed;
    free(ed);
}

void freeEdgeAndInfo(Info Ed){
    edge* ed = (edge*) Ed;
    (*ed->freeInfo)(ed->info);
    free(ed);
}