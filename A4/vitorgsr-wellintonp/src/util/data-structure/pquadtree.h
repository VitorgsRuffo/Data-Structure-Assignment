

#ifndef P_QUAD_TREE_H
#define P_QUAD_TREE_H

#include "./list.h"
#include "./stack.h"
#include "../../elements/point.h"

typedef void *PQuadTree;
typedef void *PQuadTreeNode;
typedef void *Info;
typedef char *InfoKey;
typedef void *ExtraInfo;

typedef void (*freeInfo)(Info); 
typedef Point (*getInfoPoint)(Info); 
typedef InfoKey (*getInfoKey)(Info);
typedef void (*nodeVisitingFunction)(Info, ExtraInfo);

/*
    
*/

/*
    Pré-condição: É necessario receber uma funcao que retorna a chave de ordenação do dado armazenado e uma funcao que retorna o ponto que localiza esse dado.
    Pós-condição: Cria e retorna uma quadtree vazia. 
*/
PQuadTree createPQuadTree(getInfoKey getKey, getInfoPoint getPoint); 

/*
    Pré-condição: Requer a referencia para uma p-quadtree.
    Pós-condição: retorna a quantidade de elementos da p-quadtree. 
*/
int PQuadTreeSize(PQuadTree Tree);

/*
    Pré condição: Requer a referencia para uma p-quadtree e os vértices opostos (x1,y1) e (x2,y2) de um retangulo.
    Pós condição: Cria e retorna uma lista contendo as chaves de ordenaçao das informaçoes cuja coordenada se encontra dentro do retangulo.

    Obs: memoria sera alocada para as chaves.
    Obs: é necessario desalocar a memoria usada pela lista e pelas chaves apos o seu uso.
*/
List getInfoKeysLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2);


/*
    Pré condição: Requer a referencia para uma p-quadtree, centro e o raio de um circulo.
    Pós condição: Cria e retorna uma lista contendo as chaves de ordenaçao das informaçoes cuja coordenada se encontra dentro do circulo.
    
    Obs: memoria sera alocada para as chaves.
    Obs: é necessario desalocar a memoria usada pela lista e pelas chaves apos o seu uso.
*/
List getInfoKeysLocatedInsideCircle(PQuadTree Tree, double x, double y, double r);


/*
    Pré condição: Requer a referencia para uma p-quadtree, e os vértices opostos (x1,y1) e (x2,y2) de um retangulo.
    Pós condição: Cria e retorna uma lista contendo os pontos cujas coordenadas se encontram dentro do retangulo.

    Obs: memoria sera alocada para os pontos.
    Obs: é necessario desalocar a memoria usada pela lista e pelos pontos apos o seu uso.
*/
List getPointsLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2);


/*
    Pré condição: Requer a referencia para uma p-quadtree, centro e o raio de um circulo. 
    Pós condição: Cria e retorna uma lista contendo os pontos cujas coordenadas se encontram dentro do circulo.

    Obs: memoria sera alocada para os pontos.
    Obs: é necessario desalocar a memoria usada pela lista e pelos pontos apos o seu uso.
*/
List getPointsLocatedInsideCircle(PQuadTree Tree, double x, double y, double r);


/*
    Pré condição: Requer a referencia para uma p-quadtree, e os vértices opostos (x1,y1) e (x2,y2) de um retangulo.
    Pós condição: Cria e retorna uma lista contendo os nós cujas coordenadas se encontram dentro do retangulo.

    Obs: é necessario desalocar a memoria usada pela lista apos o seu uso.
*/
List getNodesLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2);


/*
    Pré condição: Requer a referencia para uma p-quadtree, centro e o raio de um circulo. 
    Pós condição: Cria e retorna uma lista contendo os nos cujas coordenadas se encontram dentro do circulo.

    Obs: é necessario desalocar a memoria usada pela lista apos o seu uso.
*/
List getNodesLocatedInsideCircle(PQuadTree Tree, double x, double y, double r);


/*
    Pré-condição: Requer a referencia para uma p-quadtree, um function pointer do tipo nodeVisitingFunction (definido acima), e um void pointer para uma informacao extra.
    Pós-condição: Percorre a arvore em profundidade. Para cada nó visitado a funcao (*function)(info, extraInfo) é chamada, onde "info" é a informacao referente ao nó.
*/
void preOrderTraversal(PQuadTree Tree, nodeVisitingFunction function, ExtraInfo extraInfo);


/*
    Pré-condição: Requer a referencia para uma p-quadtree, um function pointer do tipo nodeVisitingFunction (definido acima), e um void pointer para uma informacao extra.
    Pós-condição: Percorre a arvore em largura. Para cada nó visitado a funcao (*function)(info, extraInfo) é chamada, onde "info" é a informacao referente ao nó.
*/
void levelOrderTraversal(PQuadTree Tree, nodeVisitingFunction function, ExtraInfo extraInfo);
    
/*
    Pré condição: Requer a referencia para uma p-quadtree, um function pointer do tipo nodeVisitingFunction (definido acima), e um void pointer para uma informacao extra.
    Pós-condição: Percorre a arvore comparando as keys e retorna o node referente a key do parametro. Caso nao encontre, retoran NULL.
*/
PQuadTreeNode searchForObjectByKeyInPQuadTree(PQuadTree Tree, char* key);

/*
    Pré condição: Insere na árvore a informação "info" localizada em "P".
    Pós-condição: Retorna referência ao nó da árvore onde a info foi armazenada.
*/
PQuadTreeNode insertPQuadTree(PQuadTree Tree, Point P, Info info);

/*
* Pré-Condição: Requer uma instancia de p-quadtree e uma pilha de objetos.
* Pós-Condição: insere os objetos na arvore de maneira que a mesma fique balanceada.
*/
int balancedlyInsertObjectsInPQuadTree(PQuadTree Tree, Stack Objects);


/*
    Pré condição: Requer uma instancia de p-quadtree e um nó presente nesta arvore.
    Pós condição: Remove da arvore o nó passado por parametro, e, retorna a informação armazenada dentro dele.
*/
Info removePQuadTreeNode(PQuadTree Tree, PQuadTreeNode Node);


/*
    Pré condição: Requer uma instancia de p-quadtree, e um ponto (x,y) como referência para a busca.
    Pós condição: Retorna uma referência ao nó da árvore associado à coordenada (x,y). Caso não exista tal nó, retorna NULL.
*/
PQuadTreeNode getPQuadTreeNode(PQuadTree Tree, double x, double y);


/*
    Pré condição: Requer uma instancia de p-quadtree e um nó.
    Pós condição: Retorna a informação armazenada na árvore no nó referenciado por node. O ponteiro "node" deve referenciar um nó válido dentro da árvore.
*/
Info getPQuadTreeNodeInfo(PQuadTree Tree, PQuadTreeNode Node);


/*
    Pré condição: Requer uma instancia de p-quadtree.
    Pós condição: retorna um vetor contendo as informações da arvore;
*/
Info* PQuadTreeToArray(PQuadTree Tree);


/*
    Pré condição: requer uma instancia de p-quadtree. A passagem de uma funcao de desalocar informacao e opcional.
    Pós condição: desaloca a memoria usada pela arvore e seus nós. Se uma funcao de desalocar for passada, as informacoes tambem sao desalocadas.

    Obs: nao desaloca a memoria usada pelas listas retornadas nas funcoes acima.
*/
void freePQuadTree(PQuadTree Tree, freeInfo freefunction);


/*
    Pré-condição: Requer uma instancia de p-quadtree.
    Pós-condição: imprime na saida padrao o conteudo de cada nó.
*/
void printPQuadTree(PQuadTree Tree); 


/*
    Pré-condição: Requer uma instancia de um no de uma p-quadtree.
    Pós-condição: imprime na saida padrao as coordenadas do nó.
*/
void printPQuadTreeNodeCoordinates(PQuadTreeNode Node);

#endif
