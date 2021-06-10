#ifndef PRIM_H
#define PRIM_H

/*
* Pré condição: requer um grafo e um id de um vertice desse grafo. 
* Pós condição: criar e retorna um novo grafo que representa a arvore geradora minima do grafo passado, gerada a partir do originId passado.
*               Se o id nao for passado o algoritmo escolhe um vertice arbitrario para ser a origem.
*               O grafo retornado contem as mesmas informacoes de vertices/arestas correspondentes no grafo original. 
*               Assim, devemos desalocar as informacoes no grafo original com "freeGraph(Gr, freeVertexInfo, 1)" e desalocar o segundo grafo com "freeGraph(Gr, NULL, 0)" para evitar frees duplos.
*/
Graph prim(Graph Gr, char* originId);

#endif
