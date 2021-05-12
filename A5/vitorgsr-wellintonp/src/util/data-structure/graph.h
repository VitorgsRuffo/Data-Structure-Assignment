#ifndef GRAPH
#define GRAPH

#include "list.h"

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
* Representa uma aresta do grafo.
*/
typedef void* Edge;

/*
* Ponteiro para uma funcao que recebe uma informacao (que esta dentro de uma aresta) e retorna o campo da informacao que pode ser interpretado como o peso de uma aresta.
*/
typedef double (*getEdgeWeight)(Info);

/*
* Ponteiro para uma funcao que desaloca uma informacao. 
*/
typedef void (*freeFunction)(Info);

/*
* Ponteiro para uma funcao que recebe uma informacao (que esta dentro de um vertice/aresta) e a imprime na saida padrao.
*/
typedef void (*printInfo)(Info);


/*
* Cria e retorna uma nova instancia de grafo que ainda nao possui vertices nem arestas. 
*/
Graph createGraph(int order);


/*
* Retorna a quantidade de vértices do grafo.
*/
int getGraphOrder(Graph Gr);


/*
* Retorna uma lista contendo os identificadores de todos os vertices do grafo.
*/
List getGraphVertices(Graph Gr);


/*
* Indica para o grafo qual funcao deve ser usada para obter o peso da aresta a partir de sua informacao.
*/
int setGetEdgeWeightFunction(Graph Gr, getEdgeWeight get);


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
* Insere no grafo uma nova aresta que parte do vertice "sourceId" e vai até o vertice "targetId". Essa aresta é associada a informacao "info" e a funcao de desalocamento da informacao da aresta "freeInfo".
* Retorna 1 se a insercao for bem sucedida, se nao retorna 0.
*/
int insertEdge(Graph Gr, char* sourceId, char* targetId, Info info, freeFunction freeInfo);


/*
* Retorna a informacao associada ao vertice identificado por "id".
*/
Info getGraphVertexInfo(Graph Gr, char* id);


/*
* Retorna o id do vértice "Vt" do parametro.
*/
char* getGraphVertexId(Graph Gr, Vertex Vt);


/*
* Retorna o endereço do vertice na qual o id dele é igual o originId do parâmetro.
*/
Vertex getGraphVertex(Graph Gr, char* originId);


/*
* Retorna a lista de arestas referente ao vertice "Vt" do parametro.
*/
List getGraphVertexEdges(Graph Gr, Vertex Vt);

/*
* Remove o vertice, cujo id foi passado, do grafo. É necessario informar se o grafo é direcionado ou nao.
* A passagem de funcao de desalocar informacao de vertices e opcional.
* Se a funcao for passada, a informacão associada ao vertice tambem é desalocada.
* Retorna 1 se a remocao for bem sucedida, se nao retorna 0.
*/
int removeVertex(Graph Gr, int graphIsDirected, char* id, freeFunction freeInfo);

/*
* Retorna a informacao associada a aresta que parte do vertice "sourceId" e vai até o vertice "targetId".
*/
Info getGraphEdgeInfo(Graph Gr, char* sourceId, char* targetId);


/*
* Retorna o id do vértice do qual a aresta passada sai.
*/
char* getGraphEdgeSourceId(Graph Gr, Edge Ed);


/*
* Retorna o id do vértice no qual a aresta passada chega.
*/
char* getGraphEdgeTargetId(Graph Gr, Edge Ed);


/*
* Retorna o peso associado a aresta passada.
*/
double getGraphEdgeWeight(Graph Gr, Edge Ed);


/*
* Retorna a funcao que desaloca a informacao armazenada dentro da aresta passada.
*/
freeFunction getGraphEdgeFreeFunction(Graph Gr, Edge Ed);


/*
* Remove a aresta que parte do vertice "sourceId" e vai até o vertice "targetId".
  Se freeInfo == 1 a informacao associada a aresta é desalocada da memoria.
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
void printGraph(Graph Gr, printInfo printVertexInfo, printInfo printEdgeInfo);


/*
* Desaloca a memoria utilizada pelo grafo. A passagem de funcao de desalocar informacao de vertices e opcional.
* Se a funcao for passada, as informacoes de vertices tambem sao desalocadas.
* Se freeEdgeInfo == 1, as informacoes das arestas tambem sao desalocadas
*/
void freeGraph(Graph Gr, freeFunction freeVertexInfo, int freeEdgeInfo);

#endif