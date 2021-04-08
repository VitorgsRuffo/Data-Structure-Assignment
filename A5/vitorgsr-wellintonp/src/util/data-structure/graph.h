#ifndef GRAPH
#define GRAPH

#include "list.h"

/* to do list:
*   - solve free edge info problem.
*/

/* É um elemento matematico definido pelo par ordenado G = (V, E).
*  V: conjunto de vertices.
*  E: subconjunto de VxV.
*/
typedef void* Graph;

/*
* Representa um vertice do grafo.
*/
typedef void* Vertex;

/*
* Representa uma informacao generica.
*/
typedef void* Info;

/*
* Ponteiro para uma funcao que recebe uma informacao (que esta dentro de uma aresta) e retorna o campo da informacao que pode ser interpretado como o peso de uma aresta.
*/
typedef double (*getEdgeWeight)(Info);

/*
* Ponteiro para uma funcao que desaloca uma informacao. 
*/
typedef void (*freeFunction)(Info);

/*
* Cria e retorna uma nova instancia de grafo que ainda nao possui vertices nem arestas. 
*/
Graph createGraph(int order);

/*
* Retorna 1 se o vertice identificado por "id" faz parte do conjunto de vertices V do grafo G.
* Se nao, retorna 0.
*/
int isVertexMemberOfGraph(Graph Gr, char* id);

/*
* Insere no grafo um novo vertice identificado por "id" e associado a informacao "info". 
* Retorna 1 se a insercao for bem sucedida, se nao retorna 0.
*/
int insertVertex(Graph Gr, char* id, Info info);

/*
* Insere no grafo uma nova aresta que parte do vertice "sourceId" e vai até o vertice "targetId". Essa aresta é associada a informacao "info".
  Retorna 1 se a insercao for bem sucedida, se nao retorna 0.
*/
int insertEdge(Graph Gr, char* sourceId, char* targetId, Info info, freeFunction freeInfo);

/*
* Indica para o grafo qual funcao deve ser usada para obter o peso da aresta a partir de sua informacao.
*/
int setGetEdgeWeightFunction(Graph Gr, getEdgeWeight get);

/*
* Retorna a informacao associada ao vertice identificado por "id".
*/
Info getVertexInfo(Graph Gr, char* id);

/*
* Retorna a informacao associada a aresta que parte do vertice "sourceId" e vai até o vertice "targetId".
*/
Info getEdgeInfo(Graph Gr, char* sourceId, char* targetId);

/*
* Remove a aresta que parte do vertice "sourceId" e vai até o vertice "targetId".
  Se uma funcao de remover informacao for passada, a informacao associada a aresta é desalocada da memoria.
  Retorna 1 se a remocao for bem sucedida, se nao retorna 0.
*/
int removeEdge(Graph Gr, char* sourceId, char* targetId, int freeInfo);

/*
* Retorna 1 se o vertice identificado por "vertex2Id" for adjacente ao vertice identificado por "vertex1Id".
* Isto é, (vertice1, vertice2) pertence ao conjunto E. Se nao, retorna 0.
*/
int isAdjacent(Graph Gr, char* vertex1Id, char* vertex2Id);

/*
* Retorna uma lista contendo os identificadores dos vertices adjacentes ao vertice identificado por "vertexId".
*/
List getAdjacentVertices(Graph Gr, char* vertexId);

/*
* Imprime o grafo na saida padrao.
*/
void printGraph(Graph Gr);

/*
* Desaloca a memoria utilizada pelo grafo. A passagem de funcoes de desalocar informacao e opcional.
* Se as funcões de desalocar forem passadas, as suas correspondentes informacoes tambem sao desalocadas.
*/
void freeGraph(Graph Gr, freeFunction freeVertexInfo, int freeEdgeInfo);

#endif