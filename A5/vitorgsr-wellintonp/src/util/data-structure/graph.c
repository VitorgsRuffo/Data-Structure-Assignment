#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"
#include "hashtable.h"

typedef struct {
    char id[50];
    Info info;
    List edges;
}vertex;

typedef struct {
    vertex* target;
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
*  Vamos usar uma tabela hash para relacionar o id de um vertice á sua posicao no vetor de vertices do grafo. (Afim de facilitar consultas)
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

    //Obtendo o indice do vertice, no vetor de vertices do grafo, que sera o destino da nova aresta a ser inserida.
    int targetIndex = getVertexIndex(gr, targetId);
    if(targetIndex == -1) return 0;

    edge* newEdge = (edge*) malloc(sizeof(edge));
    if(newEdge == NULL) return 0;

    newEdge->info = info;
    newEdge->target = &(gr->vertices[targetIndex]);
    newEdge->freeInfo = freeInfo;

    if(insert(gr->vertices[sourceIndex].edges, newEdge) == NULL){
        free(newEdge);
        return 0;
    }
   
    return 1;
}


int setGetEdgeWeightFunction(Graph Gr, getEdgeWeight get){
    if(Gr == NULL || get == NULL ) return 0;
    graph* gr = (graph*) Gr;
    
    gr->get = get;
    return 1;
}


Info getVertexInfo(Graph Gr, char* id){
    if(Gr == NULL || id == NULL ) return 0;
    graph* gr = (graph*) Gr;

    //Obtendo o indice do vertice, no vetor de vertices do grafo, cujo identificador é "id".
    int index = getVertexIndex(gr, id);
    if(index == -1) return NULL;

    return gr->vertices[index].info;
}


Info getEdgeInfo(Graph Gr, char* sourceId, char* targetId){
    if(Gr == NULL || sourceId == NULL || targetId == NULL) return 0;
    graph* gr = (graph*) Gr;

    edge* ed = findEdge(gr, sourceId, targetId);
    
    if(ed == NULL) return NULL;
    else           return ed->info; 
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

        if(!strcmp(currentEdge->target->id, targetId)){
            
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

        insert(adjacentVertices, (Info) currentEdge->target->id);

        currentNode = getNext(edges, currentNode);
    }

    return adjacentVertices;
}


void printGraph(Graph Gr){
    if(Gr == NULL) return;
    graph* gr = (graph*) Gr;

    for(int i = 0; i<gr->order; i++){
        printf("\nvertex Id: %s\n", gr->vertices[i].id);
        
        List edges = gr->vertices[i].edges;
        Node currentNode = getFirst(edges);
        edge* currentEdge;

        while(currentNode != NULL){

            currentEdge = (edge*) get(edges, currentNode);

            printf("edge: (%s, %s)\n", gr->vertices[i].id, currentEdge->target->id);

            currentNode = getNext(edges, currentNode);
        }
    }
}


void freeGraph(Graph Gr, freeFunction freeVertexInfo, int freeEdgeInfo){
    if(Gr == NULL) return;
    graph* gr = (graph*) Gr;

    for(int i = 0; i<gr->order; i++){
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

        if(!strcmp(currentEdge->target->id, targetId))
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