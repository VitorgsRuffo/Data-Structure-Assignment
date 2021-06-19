#include "../../include/headers.h"
#include "dijkstra.h"
#include "../data-structure/hashtable.h"
#include "../data-structure/priorityQueue.h"


#define Infinity 999999999

typedef struct {
    char id[50];
    double shortestKnownDistance;
    char previousId[50];
    int visited;
}dijkstraVertex;

char* getDijkstraVertexId(DijkstraVertex Dv);
double getDijkstraVertexDistanceFromOrigin(DijkstraVertex Dv);
void setDijkstraVertexDistanceFromOrigin(DijkstraVertex Dv, double distance);

Stack* preparingDijkstraResult(char* targetId, HashTable dijkstraInfoTable, int graphOrder, char* sourceId, Info* dijkstraVertices);


Stack* dijkstra(Graph Gr, char* sourceId, char* targetId){

    if(Gr == NULL || sourceId == NULL)
        return NULL;

    //Vamos criar uma tabela para manter as informacoes calculadas ao longo do algoritmo:
    //Alem disso, devemos manter uma fila de prioridade com os vertices ainda nao visitados. (a prioridade se aplica á menor distancia que vertices tem da origem)
    /*
        Vertice   |   menor distancia conhecida da origem  | vertice anterior
        id01
        ...
        id0n
    */

    int graphOrder = getGraphOrder(Gr);
    
    int tableSize = ceil((10.00 * graphOrder) / 7.00); // Desde o inicio ja sabemos quantos elementos vamos inserir na tabela hash. Portanto, vamos calcular um tamanho para ela de modo que sua ocupação fique menor ou igual a 70%.
    HashTable dijkstraInfoTable = createHashTable(tableSize, getDijkstraVertexId);
        

    int index = 0;
    Info* dijkstraVertices = (Info*) malloc(graphOrder * sizeof(Info));
    if(dijkstraVertices == NULL) return NULL;

    List vertices = getGraphVertices(Gr);
    Node currentNode = getFirst(vertices);
    Info currentInfo;
    
    while(currentNode != NULL){

        currentInfo = get(vertices, currentNode);

        dijkstraVertex* vertex = (dijkstraVertex*) malloc(sizeof(dijkstraVertex)); 

        strcpy(vertex->id, (char*) currentInfo);

        if(strcmp((char*) currentInfo, sourceId) == 0)
            vertex->shortestKnownDistance = 0;
        else
            vertex->shortestKnownDistance = Infinity;

        strcpy(vertex->previousId, "-");

        vertex->visited = 0;
        
        dijkstraVertices[index] = vertex;
        insertHashTable(&dijkstraInfoTable, (Info) vertex);

        index++;
        currentNode = getNext(vertices, currentNode);

    } //ao fim do loop teremos uma tabela onde cada registro corresponde as informacoes que serao calculadas pelo algoritmo relacionadas a cada um dos vertices.
      
    //Tambem criaremos uma fila de prioridade que sempre mantem o vertice com a menor distancia da origem em primeiro.
    PriorityQueue unvisitedVertices = createFilledPriorityQueue(dijkstraVertices, graphOrder, getDijkstraVertexDistanceFromOrigin, getDijkstraVertexId);


    //Algoritmo:
    dijkstraVertex* currentDijkstraVertex;
    Vertex currentVertex;
    List edges;

    while(!isPriorityQueueEmpty(unvisitedVertices)){
        
        //Vamos visitar o vertice que ainda nao foi visitado e possui a menor distancia conhecida do vertice de origem: 
        currentDijkstraVertex = (dijkstraVertex*) priorityQueuePoll(unvisitedVertices);

        char* currentVertexId = currentDijkstraVertex->id;
        currentVertex = getGraphVertex(Gr, currentVertexId);
        
        //Vamos analisar os vertices adjacentes ao vertice atual:
        edges = getGraphVertexEdges(Gr, currentVertex);
        currentNode = getFirst(edges);
        Edge currentEdge;                   

        char* currentEdgeTargetId;
        dijkstraVertex* currentDijkstraAdjacentVertex;

        while(currentNode != NULL){
            
            currentEdge = get(edges, currentNode);
            currentEdgeTargetId = getGraphEdgeTargetId(Gr, currentEdge);

            //So vamos visitar o vertice adjacente atual caso ele ainda nao foi visitado:
            currentDijkstraAdjacentVertex = (dijkstraVertex*) getHashTableInfo(dijkstraInfoTable, currentEdgeTargetId);
            
            if(!currentDijkstraAdjacentVertex->visited){

                //Vamos calcular a menor distancia conhecida do vertice atual até a origem + a distancia do vertice atual até o vertice adjacente ligado a ele atraves da aresta atual:
                double distance = currentDijkstraVertex->shortestKnownDistance + getGraphEdgeWeight(Gr, currentEdge);
            
                //Se essa distancia for menor que a distancia conhecida encontramos um caminho menor para se chegar ao vertice alvo, portanto, atualizamos essa nova informacao na tabela/fila de prioridade.
                if(distance < currentDijkstraAdjacentVertex->shortestKnownDistance){

                    decreaseInfoPriority(unvisitedVertices, currentDijkstraAdjacentVertex->id, distance, setDijkstraVertexDistanceFromOrigin);
                    strcpy(currentDijkstraAdjacentVertex->previousId, currentVertexId);
                }
            }
                    
            currentNode = getNext(edges, currentNode);
        }
        
        currentDijkstraVertex->visited = 1;
        
        if(targetId != NULL)
            if(strcmp(currentDijkstraVertex->id, targetId) == 0)
                break;

    }

    //Preparando retorno: vamos retornar um vetor de pilhas onde cada pilha possui o menor caminho partindo da origem (topo da pilha) até um destino (base da pilha). 
    //                    Caso o usuario tenha especificado um destino apenas uma pilha é retornada.
    //                    Cada item da pilha é um "dijkstra vertex" que possui o id de um vertice a menor distancia entre aquele vertice e a origem, etc.
    //                    Obs: a primeira stack retornada contem todos os dijkstra vertex. Assim, o desalocamento dos mesmos se torna mais facil.

    Stack* path = preparingDijkstraResult(targetId, dijkstraInfoTable, graphOrder, sourceId, dijkstraVertices);
    
    free(dijkstraVertices);
    freeList(vertices, NULL);
    freePriorityQueue(unvisitedVertices, NULL);
    freeHashTable(dijkstraInfoTable, NULL);

    return path;
}


char* getDijkstraVertexId(DijkstraVertex Dv){

    if(Dv == NULL) return NULL;
        
    dijkstraVertex* dv = (dijkstraVertex*) Dv;
    return dv->id;
}


double getDijkstraVertexDistanceFromOrigin(DijkstraVertex Dv){

    if(Dv == NULL) return -1;
        
    dijkstraVertex* dv = (dijkstraVertex*) Dv;
    return dv->shortestKnownDistance;
}


char* dijkstraVertexToString(DijkstraVertex Dv){

    if(Dv == NULL) return NULL;
    dijkstraVertex* dv = (dijkstraVertex*) Dv;

    char* toString = (char*) malloc(75 * sizeof(char));
    //sprintf(toString, "id:%s - distance from origin: %.2lf",dv->id, dv->shortestKnownDistance);
    strcpy(toString, dv->id);
    return toString;
}

void freeDijkstraPath(Stack* path, int size){

    if(path == NULL) return;
    
    freeStack(path, free); //desaloca a primeira pilha e todos os dijkstra vertices.

    for(int i = 1; i<size-1; i++)
        freeStack(path + i, NULL); //desaloca as demais pilhas.
    
    free(path);
}


//funcoes privadas auxiliares:

Stack* preparingDijkstraResult(char* targetId, HashTable dijkstraInfoTable, int graphOrder, char* sourceId, Info* dijkstraVertices){

    Stack* path;
    dijkstraVertex* currentDijkstraVertex;

    if(targetId != NULL){

        path = (Stack*) malloc(2 * sizeof(Stack)); 
        if(path == NULL)
            return NULL;

        *(path + 1) = createStack(); // a segunda stack contera apenas os dijstra vertex que compoem o caminho entre a origem e o destino.

        currentDijkstraVertex = (dijkstraVertex*) getHashTableInfo(dijkstraInfoTable, targetId);
        
        if(currentDijkstraVertex == NULL)
            return NULL;
        
        while(strcmp(currentDijkstraVertex->previousId, "-") != 0){
            
            stackPush(path + 1, currentDijkstraVertex);
            currentDijkstraVertex = (dijkstraVertex*) getHashTableInfo(dijkstraInfoTable, currentDijkstraVertex->previousId);
        }
        
        stackPush(path + 1, currentDijkstraVertex);     


    }else{

        path = (Stack*) malloc(((graphOrder-1) + 1) * sizeof(Stack)); //teremos graphOrder-1 caminhos (pois, nao consideramos o caminho da origem até si mesma). Logo precisaremos de graphOrder-1 stacks + 1 stack que contenha todos os dijkstra vertices.
        if(path == NULL) return NULL;
        
        int j = 1;

        for(int i = 0; i<graphOrder; i++){

            currentDijkstraVertex = (dijkstraVertex*) dijkstraVertices[i];

            if(strcmp(currentDijkstraVertex->id, sourceId) == 0) continue;//nao vamos criar um caminho da origem até a origem

            *(path + j) = createStack();
            
            while(strcmp(currentDijkstraVertex->previousId, "-") != 0){
                stackPush((path + j), currentDijkstraVertex);
                currentDijkstraVertex =  (dijkstraVertex*) getHashTableInfo(dijkstraInfoTable, currentDijkstraVertex->previousId);
            }

            stackPush((path + j), currentDijkstraVertex);

            j++;
        }
    }

    *path = createStack();  //a primeira stack contem todos os dijkstra vertex.
    for(int i = 0; i<graphOrder; i++)
        stackPush(path, dijkstraVertices[i]);

    return path;
}


void setDijkstraVertexDistanceFromOrigin(DijkstraVertex Dv, double distance){

    if(Dv == NULL || distance < 0) return;
        
    dijkstraVertex* dv = (dijkstraVertex*) Dv;
    dv->shortestKnownDistance = distance;
}