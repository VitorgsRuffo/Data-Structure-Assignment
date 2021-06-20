#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../algorithm/sort.h"
#include "../algorithm/dijkstra.h"


typedef struct {
    HealthCenter healthCenter;
    double distance;
}NearHealthCenter;

typedef struct {
    char id[50];
    Point point;
    double distance;
}PossibleVertex;

typedef struct {
    Info* pathArray;
    int size;
    int id;
}Path;

typedef struct {
    int id;
    double distance;
}BestPath;


char* buildBlueHouseTag(House H);
void calculateDistanceFromHouseToHealthCenters(House H, NearHealthCenter** nearHealthCenters, int healthCentersAmount);
int compareNearHealthCenters(Info Hc1, Info Hc2);
char* buildLineSegmentTag(double x, double y, House H);
void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance);

List getVerticesIds(PQuadTree tree, Point location, double radius);
char* getNearestVertex(List possibleVerticesIds, Graph graph, Point location);

int isPathToHealthCenter(DijkstraVertex dv , List targetVerticesId);
void drawHealthCentersPath(List pathsToHealthCenter, int bestPathId, List queryElementsList, Point house, int pathId, Graph roadSystem);

void executeMedicalTreatmentSearching(char* command, City Ct, File txt, int pathId){
    
    // Recebendo parametros do comando
    int K; char cep[30]; char face; int number;
    sscanf(&command[4], "%d %s %c %d", &K, cep, &face, &number);

    // Criando o quadrado azul que representa o endereco
    House house = createHouse("none", cep, face, number, "none", Ct); 
    char* blueHouseTag = buildBlueHouseTag(house);
    List queryElementsList = getQueryElements(Ct);
    insert(queryElementsList, blueHouseTag);

    // Pegando a arvore de postos e transformando-a em array
    DataStructure healthCenters = getHealthCenters(Ct);
    HealthCenter* healthCentersArray = PQuadTreeToArray(healthCenters);

    // Pegando o tamanho da arvore
    int healthCentersAmount = PQuadTreeSize(healthCenters);

    // Alocando ponteiro para vetor de NearHealthCenter (struct interna)
    NearHealthCenter** nearHealthCenters = (NearHealthCenter**) malloc(healthCentersAmount * sizeof(NearHealthCenter*));
    
    // Alocando conteudo de cada posicao do vetor
    for(int i = 0; i<healthCentersAmount; i++){
        *(nearHealthCenters + i) = (NearHealthCenter*) malloc(sizeof(NearHealthCenter));
        (**(nearHealthCenters + i)).healthCenter = healthCentersArray[i];
    }

    // Freelando Array temporario
    free(healthCentersArray);
    
    // Calculando a distancia da casa criada até cada um dos postos
    calculateDistanceFromHouseToHealthCenters(house, nearHealthCenters, healthCentersAmount);
    
    // Ordenando os postos de acordo com a distancia da casa
    shellsort((Info*) nearHealthCenters, healthCentersAmount, compareNearHealthCenters);

    int healthCenterX, healthCenterY;
    char* lineSegmentTag;
    
    if(K > healthCentersAmount) 
        K = healthCentersAmount;
    

    Graph roadSystem = getRoadSystem(Ct);

    // Se o grafo for vazia, vamos executar o soc do jeito tradicional (Tracando apenas uma linha ate os postos)
    if(roadSystem == NULL){
        for(int i = 0; i < K; i++){
            healthCenterX = atof(getHealthCenterX((**(nearHealthCenters + i)).healthCenter));
            healthCenterY = atof(getHealthCenterY((**(nearHealthCenters + i)).healthCenter));
            lineSegmentTag = buildLineSegmentTag(healthCenterX, healthCenterY, house);
            insert(queryElementsList, lineSegmentTag);
            writeHealthCenterCoordinatesOnTxt(txt, i, healthCenterX, healthCenterY, (**(nearHealthCenters + i)).distance);
        }

        freeHouse(house);

        for(int i = 0; i<healthCentersAmount; i++)
        free(*(nearHealthCenters + i));

        free(nearHealthCenters);

        return;
    }
    
    
    // Pegando o grafo e a arvore que representa o sistema viario da cidade
    PQuadTree roadIntersections = getRoadIntersections(Ct);
    
    Point houseCoordinates = getHouseCoordinates(house);

    // Associando a casa a um vertice a um vertice mais proximo
    double radius = 50;

    List possibleOriginVerticesIds = getVerticesIds(roadIntersections, houseCoordinates, radius);
    if(length(possibleOriginVerticesIds) == 0){
        freeList(possibleOriginVerticesIds, NULL);
        return;
    }

    char* originId = getNearestVertex(possibleOriginVerticesIds, roadSystem, houseCoordinates);
    freeList(possibleOriginVerticesIds, free);

    // Associando postos a vertices mais proximos
    List targetVerticesId = createList();   // Lista que contem os id's dos vertices que sao associados a postos
    
    for(int i = 0; i<K; i++){
        NearHealthCenter* currentNearHealthCenter = nearHealthCenters[i];
        Point currentHcPoint = getHealthCenterCoordinates(currentNearHealthCenter->healthCenter);
        List possibleHcVerticesIds = getVerticesIds(roadIntersections, currentHcPoint, radius);
        
        if(length(possibleHcVerticesIds) == 0){
            freeList(possibleHcVerticesIds, NULL);
            printf("Nenhum vertice perto do posto %s\n", getHealthCenterId(currentNearHealthCenter->healthCenter));
            continue;
        }

        char* nearestHealthCenterId = getNearestVertex(possibleHcVerticesIds, roadSystem, currentHcPoint);        
        insert(targetVerticesId, nearestHealthCenterId);
    }

    setGetEdgeWeightFunction(roadSystem, getStreetLength);
    Stack* shorterPaths = dijkstra(roadSystem, originId, NULL);

    int graphOrder = getGraphOrder(roadSystem);
    List pathsToHealthCenter = createList();    // Criamos uma lista para salvar os arrays de dijkstraVertex que sao os caminhos ate os postos
    
    BestPath bestPath;
    bestPath.distance = 9999999;

    // Andando nas pilhas e transformando-as em arrays
    for(int i=1; i<graphOrder; i++){
        
        Path* path = (Path*) malloc(sizeof(Path));
        int pathLength = stackLength(&shorterPaths[i]); // Pega o tamanho da pilha na posicao i
        int indexLastItemOfArray = pathLength-1;        // Quando os elementos forem passados para um array, o ultimo elemento do array vai estar nessa posicao

        Info* pathArray = stackToArray(&shorterPaths[i]);   // Passando os elementos da pilha e inserindo no array
        
        path->pathArray = pathArray;
        path->size = pathLength;
        path->id = i;

        // Verificando se o ultimo id do array eh associado a algum posto  
        if(isPathToHealthCenter(pathArray[indexLastItemOfArray], targetVerticesId)){  // Se entrar no if significa que esse array tem o caminho para um posto, se nao só ignoramos pois nao sera util    
            insert(pathsToHealthCenter, path);
            int pathDistance = getDijkstraVertexDistanceFromOrigin(pathArray[indexLastItemOfArray]);
            if(pathDistance < bestPath.distance)
                bestPath.id = path->id;
            
        }else{
            free(pathArray);
            free(path);
        }
        
    }

    drawHealthCentersPath(pathsToHealthCenter, bestPath.id, queryElementsList, houseCoordinates, pathId, roadSystem);

    for(int i = 0; i < K; i++){
        healthCenterX = atof(getHealthCenterX((**(nearHealthCenters + i)).healthCenter));
        healthCenterY = atof(getHealthCenterY((**(nearHealthCenters + i)).healthCenter));
        writeHealthCenterCoordinatesOnTxt(txt, i, healthCenterX, healthCenterY, (**(nearHealthCenters + i)).distance);
    }
    
    freeHouse(house);

    for(int i = 0; i<healthCentersAmount; i++)
        free(*(nearHealthCenters + i));

    free(nearHealthCenters);
}


void drawHealthCentersPath(List pathsToHealthCenter, int bestPathId, List queryElementsList, Point houseCoordinates, int pathId, Graph roadSystem){

    Node currentNode = getFirst(pathsToHealthCenter);

    while(currentNode != NULL){

        Path* path = (Path*) get(pathsToHealthCenter, currentNode);
        
        Info* pathArray = path->pathArray;
        int arraySize = path->size;
        char buffer[400]; 
        char* pathString = (char*) malloc(10000 * sizeof(char));

        char* offset = pathString;
        
        if(path->id == bestPathId)
            sprintf(buffer, "<path transform=\"translate(7,7)\" id=\"path%d\" stroke=\"blue\" stroke-width=\"4\" fill=\"none\" d=\"M%.2lf %.2lf ", pathId, getPointX(houseCoordinates), getPointY(houseCoordinates));
        else
            sprintf(buffer, "<path id=\"path%d\" stroke=\"black\" stroke-width=\"4\" fill=\"none\" d=\"M%.2lf %.2lf ", pathId, getPointX(houseCoordinates), getPointY(houseCoordinates));
        
        sprintf(offset, "%s", buffer);
        offset += strlen(buffer);
        
        for(int i=0; i<arraySize; i++){
            char* vertexId = getDijkstraVertexId(pathArray[i]);
            Info vertexLocation = getGraphVertexInfo(roadSystem, vertexId);
            double x = getPointX(vertexLocation);
            double y = getPointY(vertexLocation);

            sprintf(buffer, "L%.2lf %.2lf ", x, y);
            sprintf(offset, "%s", buffer);
            offset += strlen(buffer);

        }

        sprintf(buffer, "\"/>\n\t<circle cx=\"\" cy=\"\" r=\"5\" fill=\"green\">\n\t\t<animateMotion dur=\"6s\" repeatCount=\"indefinite\">\n\t\t\t<mpath href=\"#path%d\"/>\n\t\t</animateMotion>\n\t</circle>\n", pathId);
        sprintf(offset, "%s", buffer);
        insert(queryElementsList, pathString);
        
        currentNode = getNext(pathsToHealthCenter, currentNode);

    }
}


Info* checkShortestDistance(List pathsToHealthCenter){

    Node currentNode = getFirst(pathsToHealthCenter);
    Info* shortestPathArray = NULL;
    double shortestDistance = 0; double currentDistance = 0;
    Node nodeToRemove;

    // Percorrendo a lista de path e dentro dela estao os pathArrays e o size de cada um deles
    while(currentNode != NULL){

        Path* currentArray = (Path*) get(pathsToHealthCenter, currentNode);

        int indexOfLastDijkstraVertex = currentArray->size-1;
        DijkstraVertex* lastDijkstraVertex = currentArray->pathArray[indexOfLastDijkstraVertex];
    
        currentDistance = getDijkstraVertexDistanceFromOrigin(lastDijkstraVertex);

        if(shortestDistance < currentDistance){
            shortestDistance = currentDistance;
            nodeToRemove = currentNode;
            shortestPathArray = currentArray->pathArray;
        }

        currentNode = getNext(pathsToHealthCenter, currentNode);
    }

    removeNode(pathsToHealthCenter, nodeToRemove, NULL);
    return shortestPathArray;
}


int isPathToHealthCenter(DijkstraVertex Dv , List targetVerticesId){
    
    Node currentNode = getFirst(targetVerticesId);
    char* healthCenterVertexId = getDijkstraVertexId(Dv);

    while(currentNode != NULL){
        char* currentId = (char*) get(targetVerticesId, currentNode);
        
        if(!strcmp(healthCenterVertexId, currentId))
            return 1;

        currentNode = getNext(targetVerticesId, currentNode);
    }

    return 0;
}


List getVerticesIds(PQuadTree tree, Point location, double radius){
    double circX = getPointX(location);
    double circY = getPointY(location);
    return getInfoKeysLocatedInsideCircle(tree, circX, circY, radius);
}


int compareVertices(Info PVertex1, Info PVertex2);

char* getNearestVertex(List possibleVerticesIds, Graph graph, Point location){
    PossibleVertex* possibleVertex;
    int possibleVerticesAmount = length(possibleVerticesIds);
    Info* possibleVertices = (Info*) malloc(possibleVerticesAmount * sizeof(Info));

    int i = 0;
    Node current = getFirst(possibleVerticesIds);
    while(current != NULL){
        possibleVertex = (PossibleVertex*) malloc(sizeof(PossibleVertex));
        strcpy(possibleVertex->id, get(possibleVerticesIds, current));
        possibleVertex->point = getGraphVertexInfo(graph, possibleVertex->id);
        possibleVertex->distance = distanceBetweenPoints(possibleVertex->point, location);
        
        possibleVertices[i] = possibleVertex;

        current = getNext(possibleVerticesIds, current);
        i++;
    }

    quicksort(possibleVertices, 0, possibleVerticesAmount-1, compareVertices);
    
    char* nearestVertexId = (char*) malloc(50*sizeof(char));
    strcpy(nearestVertexId, ((PossibleVertex*) possibleVertices[0])->id);

    for(int i = 0; i<possibleVerticesAmount; i++)
        free(possibleVertices[i]);
    free(possibleVertices);

    return nearestVertexId;
}


int compareVertices(Info PVertex1, Info PVertex2){

    PossibleVertex* pVertex1 = (PossibleVertex*) PVertex1;
    PossibleVertex* pVertex2 = (PossibleVertex*) PVertex2;    

    if(pVertex1->distance < pVertex2->distance)
        return -1;
    else if(pVertex1->distance == pVertex2->distance)
        return 0;
    else
        return 1;    
}


char* buildBlueHouseTag(House H){

    char* houseTag = (char*) malloc(200 * sizeof(char));
    if(houseTag == NULL)
        return NULL;

    double x = getPointX(getHouseCoordinates(H));
    double y = getPointY(getHouseCoordinates(H));
    double w = getHouseW(H);
    double h = getHouseH(H);

    sprintf(houseTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"white\" stroke-width=\"1\" fill=\"lightblue\" />\n", w, h, x, y);
    return houseTag;
}


void calculateDistanceFromHouseToHealthCenters(House H, NearHealthCenter** nearHealthCenters, int healthCentersAmount){
    
    double healthCenterX, healthCenterY;

    double houseCenterOfMassX = getPointX(getHouseCenterOfMass(H));
    double houseCenterOfMassY = getPointY(getHouseCenterOfMass(H));

    for(int i = 0; i<healthCentersAmount; i++){
        healthCenterX = atof(getHealthCenterX( (**(nearHealthCenters + i)).healthCenter ));
        healthCenterY = atof(getHealthCenterY( (**(nearHealthCenters + i)).healthCenter ));
        
        (**(nearHealthCenters + i)).distance = sqrt(pow((healthCenterX - houseCenterOfMassX), 2) + pow((healthCenterY - houseCenterOfMassY), 2));
    }
}


int compareNearHealthCenters(Info Hc1, Info Hc2){

    NearHealthCenter* hc1 = (NearHealthCenter*) Hc1;
    NearHealthCenter* hc2 = (NearHealthCenter*) Hc2;

    if(hc1->distance > hc2->distance)
        return 1;

    else if(hc1->distance < hc2->distance)
        return -1;

    else
        return 0;
}


char* buildLineSegmentTag(double x, double y, House H){

    char* lineSegmentTag = (char*) malloc(200 * sizeof(char));
    if(lineSegmentTag == NULL) return NULL;

    double houseCenterOfMassX = getPointX(getHouseCenterOfMass(H));
    double houseCenterOfMassY = getPointY(getHouseCenterOfMass(H));

    sprintf(lineSegmentTag, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"0.8\" stroke-dasharray=\"5,5\"/>", houseCenterOfMassX, houseCenterOfMassY, x, y);
    return lineSegmentTag;
}


void writeHealthCenterCoordinatesOnTxt(File txt, int i, double x, double y, double distance){
    i++;
    fprintf(txt, "Posto de saude (%d) - x: %.2lf, y: %.2lf, distancia: %.2lf.\n\n", i, x, y, distance);
}