#include "../../include/headers.h"
#include "../../include/util.h"
#include "../../include/elements.h"

//numero maximo de partes que um comando vindo de um arquivo via pode ter
#define maxNumberOfViaCommandParts 8

void readVertex(char* command, char** commandParts, City Ct);
void readEdge(char* command, char** commandParts, City Ct);
void removeIsolatedVertices(Graph roadSystem, PQuadTree roadIntersections);

Graph createCityRoadSystem(City Ct, int readVerticesAmount);

void freeReadViaResources(char* command, char** commandParts);

void readVia(File via, City Ct){
                                             
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];
    char** commandParts = createCommandParts(maxNumberOfViaCommandParts);
    
    int readVerticesAmount = 0;
    int isRoadSystemCreated = 0;

    while(!feof(via)){
        if(fgets(command, commandMaxLength, via) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;
        
        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n')  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';
        
        sscanf(command, "%s ", commandType);

        if(commandType[0] == 'v'){ //lidando com vertices
            readVertex(command, commandParts, Ct);
            readVerticesAmount++;
        }
        else if(commandType[0] == 'e'){ //lidando arestas
            
            if(!isRoadSystemCreated){ //quando acabarmos de ler os vertices, vamos começar a ler as arestas. Para isso, primeiro, precisamos criar o grafo.
                Graph cityRoadSystem = createCityRoadSystem(Ct, readVerticesAmount);
                setRoadSystem(Ct, cityRoadSystem);
                isRoadSystemCreated = 1;
            }
                
            readEdge(command, commandParts, Ct);
        }
    }

    //removendo vertices que nao possuem arestas:
    removeIsolatedVertices(getRoadSystem(Ct), getRoadIntersections(Ct));

    freeReadViaResources(command, commandParts);
}

void readVertex(char* command, char** commandParts, City Ct){
    sscanf(&command[2], "%s %s %s", commandParts[0], commandParts[1], commandParts[2]);
    IdedPoint iP = createIdedPoint(commandParts[0], atof(commandParts[1]), atof(commandParts[2]));

    Point idedPointCoordinates = getIdedPointCoordinates(iP);

    PQuadTree roadIntersections = getRoadIntersections(Ct);
    insertPQuadTree(roadIntersections, idedPointCoordinates, iP);
}

void readEdge(char* command, char** commandParts, City Ct){
    sscanf(&command[2], "%s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);   

    Street newStreet = createStreet(commandParts[6], commandParts[2], commandParts[3], atof(commandParts[4]), atof(commandParts[5]));
    
    Graph cityRoadSystem = getRoadSystem(Ct);

    insertEdge(cityRoadSystem, commandParts[0], commandParts[1], newStreet, freeStreet);
}


void insertIntersectionOnRoadSystem(Info info, ExtraInfo ei);

Graph createCityRoadSystem(City Ct, int readVerticesAmount){

    Graph newCityRoadSystem = createGraph(readVerticesAmount);
    PQuadTree roadIntersections = getRoadIntersections(Ct);

    preOrderTraversal(roadIntersections, insertIntersectionOnRoadSystem, newCityRoadSystem);

    return newCityRoadSystem;
}

void insertIntersectionOnRoadSystem(Info info, ExtraInfo ei){
    Graph newCityRoadSystem = ei;
    IdedPoint iP = info;
    
    insertVertex(newCityRoadSystem, getIdedPointId(iP), getIdedPointCoordinates(iP));
}

void removeIsolatedVertices(Graph roadSystem, PQuadTree roadIntersections){

    List vertices = getGraphVertices(roadSystem);

    Node current = getFirst(vertices);

    //
    Point currentPoint = getGraphVertexInfo(roadSystem, "beS.SO");
            
    freeIdedPoint(removePQuadTreeNode(roadIntersections, 
                                        getPQuadTreeNode(roadIntersections, 
                                                        getPointX(currentPoint),
                                                        getPointY(currentPoint)) ));

    removeVertex(roadSystem, 1, "beS.SO", NULL);

    while(current != NULL){
        
        char* currentId = (char*) get(vertices, current);
        
        List edges = getGraphVertexEdges(roadSystem, getGraphVertex(roadSystem, currentId));


        if(length(edges) <= 0){
            
            currentPoint = getGraphVertexInfo(roadSystem, currentId);
            
            freeIdedPoint(removePQuadTreeNode(roadIntersections, 
                                              getPQuadTreeNode(roadIntersections, 
                                                               getPointX(currentPoint),
                                                               getPointY(currentPoint)) ));

            removeVertex(roadSystem, 1, currentId, NULL);
        }

        current = getNext(vertices, current);
    }

    free(vertices);
}

void freeReadViaResources(char* command, char** commandParts){
    free(command);   

    for(int i = 0; i<8; i++)
        free(commandParts[i]);
    
    free(commandParts);
}