#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../data-structure/graph.h"
#include "../data-structure/stack.h"

/*
* Apontador void para uma instancia de estrutura de DijkstraVertex utilizada no algoritmo de Dijkstra.
* Esse TAD compoem o(s) caminho(s) que é retornado pelo algoritmo. Ele possui um id do vertice do grafo que ele representa e a distancia daquele vertice até a origem. 
*/
typedef void* DijkstraVertex;

/*
* O algoritmo de Dijkstra determina o menor caminho a partir de um vértice inicial até todos os demais vertices de um grafo. Também é possivel calcular o menor caminho entre um vertice inicial e um destino especifico.
* No algoritmo é usado a estrutura "dijkstraVertex" para fazer a manipulacao e o calculo dos caminhos.
* Os parametros da funcao sao: um Grafo, o id do vértice inicial do caminho e o id do final do caminho (sendo os dois primeiros obrigatórios e o último opcional).
* Caso o usuario tenha especificado um targetId, o algoritmo ira calcular o menor caminho de "sourceId" até "targetId" e irá retornar uma pilha,
* onde cada elemento é um dijkstraVertex, e nessa pilha temos em seu topo a origem "sourceId" e na base o destino "target Id".
* Caso o usuario nao tenha especificado um targetId, o algoritmo calcula todos os menores caminhos a partir do sourceId e irá retornar um vetor com varias pilhas e, 
* cada pilha desse vetor contém um dos caminhos calculados.
* Em ambos os casos sempre sera retornado uma pilha extra (na posicao 0 do vetor) que contera todos os dijkstra vertices usados nos calculos. É recomendado que essa pilha não seja alterada, pois, ela sera necessaria no desalocamento do vetor de caminhos retornado pelo dijkstra.
* O usuario tem acesso ao(s) caminho(s) a partir da pilha 1. Ele pode ter acesso ao(s) caminho(s) desempilhando os dijkstra vertices e acessando os seus ids e distancias da origem atraves das funcoes especificadas abaixo.
* Apos o uso dos caminhos o usuario deve desalocar o vetor de caminhos utilizando a funcao "freeDijkstraPath".
* Caso o tamanho de uma das pilhas seja 1 (o unico vertice ali dentro é o destino), não foi possivel achar um caminho até aquele vertice. Provavelmente nao existem arestas chegando naquele vertice. 
*/
Stack* dijkstra(Graph Gr, char* sourceId, char* targetId);

/*
* Retorna o id do vertice do grafo que o dijkistraVertex passado representa.
*/
char* getDijkstraVertexId(DijkstraVertex Dv);

/*
* Retorna a distancia entre o vertice do grafo que o dijkistraVertex passado representa e a origem.
*/
double getDijkstraVertexDistanceFromOrigin(DijkstraVertex Dv);

/*
* Cria e retorna uma string personalizada para os elementos da estrutura dijkstraVertex;
*/
char* dijkstraVertexToString(DijkstraVertex Dv);

/*
* Desaloca toda a memoria utilizada pelo vetor de caminhos retornado pela funcao dijkstra.
*/
void freeDijkstraPath(Stack* path, int size);

#endif 