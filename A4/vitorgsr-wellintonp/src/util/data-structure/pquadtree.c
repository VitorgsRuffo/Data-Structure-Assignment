#include "../../include/headers.h"
#include "../../include/figures.h"
#include "./pquadtree.h"
#include "./queue.h"
#include "../tools.h"
#include "../algorithm/convexhull.h"

typedef struct pquadtreenode {
    Point point;
    Info info; 
    struct pquadtreenode* northWest;
    struct pquadtreenode* northEast; 
    struct pquadtreenode* southWest;
    struct pquadtreenode* southEast;
    struct pquadtreenode* parentNode;
}pquadtreenode;

typedef struct pquadtree {
    getInfoKey getKey;
    getInfoPoint getPoint;
    pquadtreenode* root;
    int size;
}pquadtree;


pquadtreenode* findPointNodeInPQuadTree(pquadtreenode *node, double x, double y);

// Obs: Confirmar se há necessidade ou não "*" no "get" (parâmetro de createPQuadTree)
PQuadTree createPQuadTree(getInfoKey getKey, getInfoPoint getPoint){

    if(getKey == NULL)
        return NULL;

    pquadtree *tree = (pquadtree*) malloc(sizeof(pquadtree));
    if(tree == NULL)
        return NULL;
    
    (*tree).getKey = getKey;
    (*tree).getPoint = getPoint;
    (*tree).root = NULL;
    (*tree).size = 0;

    return tree;
}

int PQuadTreeSize(PQuadTree Tree){
    if(Tree == NULL) return -1;

    pquadtree *tree = (pquadtree*) Tree;
    return tree->size;
}

void saveInfoKeyOnListIfItsInsideShape(Info info, ExtraInfo extraInfo);
void savePointOnListIfItsInsideShape(Info info, ExtraInfo extraInfo);
void saveNodeOnListIfItsInsideShape(Info info, ExtraInfo extraInfo);

List getObjectsLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2, nodeVisitingFunction saveObjectOnListIfItsInsideShape);
List getObjectsLocatedInsideCircle(PQuadTree Tree, double x, double y, double r, nodeVisitingFunction saveObjectOnListIfItsInsideShape);


List getInfoKeysLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2){
    if(Tree == NULL) return NULL;
    List infoKeyList = getObjectsLocatedInsideRectangle(Tree, x1, y1, x2, y2, saveInfoKeyOnListIfItsInsideShape);
    return infoKeyList;
}

List getPointsLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2){
    if(Tree == NULL) return NULL;
    List pointList = getObjectsLocatedInsideRectangle(Tree, x1, y1, x2, y2, savePointOnListIfItsInsideShape);
    return pointList;
}

List getNodesLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2){
    if(Tree == NULL) return NULL;
    List nodeList = getObjectsLocatedInsideRectangle(Tree, x1, y1, x2, y2, saveNodeOnListIfItsInsideShape);
    return nodeList;
}


List getInfoKeysLocatedInsideCircle(PQuadTree Tree, double x, double y, double r){
    if(Tree == NULL) return NULL;
    List infoKeyList = getObjectsLocatedInsideCircle(Tree, x, y, r, saveInfoKeyOnListIfItsInsideShape);
    return infoKeyList;
}

List getPointsLocatedInsideCircle(PQuadTree Tree, double x, double y, double r){
    if(Tree == NULL) return NULL;
    List pointList = getObjectsLocatedInsideCircle(Tree, x, y, r, savePointOnListIfItsInsideShape);
    return pointList;
}

List getNodesLocatedInsideCircle(PQuadTree Tree, double x, double y, double r){
    if(Tree == NULL) return NULL;
    List nodeList = getObjectsLocatedInsideCircle(Tree, x, y, r, saveNodeOnListIfItsInsideShape);
    return nodeList;
}


typedef void* Shape;
typedef int (*isPointInsideShape)(Shape, Point);

typedef struct ObjectsInShape {
    pquadtree* tree;
    List objectList;
    Shape shape;
    isPointInsideShape testFunction;
}ObjectsInShape;

void function(pquadtreenode* node, ObjectsInShape objectsInShape);

List getObjectsLocatedInsideRectangle(PQuadTree Tree, double x1, double y1, double x2, double y2, nodeVisitingFunction saveObjectOnListIfItsInsideShape){
    
    char w[20], h[20], x[20], y[20];
    sprintf(w, "%lf", (x2-x1));
    sprintf(h, "%lf", (y2-y1));
    sprintf(x, "%lf", x1);
    sprintf(y, "%lf", y1);
    
    ObjectsInShape* objectsInShape = (ObjectsInShape*) malloc(sizeof(ObjectsInShape));
    objectsInShape->tree = (pquadtree*) Tree;
    objectsInShape->objectList = createList();
    objectsInShape->shape = createRectangle("r1", w, h, x, y, "blue", "black", "5.0");
    objectsInShape->testFunction = isPointInsideRect;

    levelOrderTraversal(Tree, saveObjectOnListIfItsInsideShape, objectsInShape);

    List objectList = objectsInShape->objectList;

    freeRectangle(objectsInShape->shape);
    free(objectsInShape);

    return objectList;
}


List getObjectsLocatedInsideCircle(PQuadTree Tree, double x, double y, double r, nodeVisitingFunction saveObjectOnListIfItsInsideShape){

    char cx[20], cy[20], cr[20];
    sprintf(cx, "%lf", x);
    sprintf(cy, "%lf", y);
    sprintf(cr, "%lf", r);

    ObjectsInShape* objectsInShape = (ObjectsInShape*) malloc(sizeof(ObjectsInShape));
    objectsInShape->tree = (pquadtree*) Tree;
    objectsInShape->objectList = createList();
    objectsInShape->shape = createCircle("c1", cr, cx, cy, "blue", "black", "5.0");
    objectsInShape->testFunction = isPointInsideCirc;

    levelOrderTraversal(Tree, saveObjectOnListIfItsInsideShape, objectsInShape);

    List objectList = objectsInShape->objectList;

    freeCircle(objectsInShape->shape);
    free(objectsInShape);

    return objectList;
}


void saveInfoKeyOnListIfItsInsideShape(Info info, ExtraInfo extraInfo){

    ObjectsInShape* objectsInShape = (ObjectsInShape*) extraInfo;

    pquadtree* tree = objectsInShape->tree;
    isPointInsideShape testFunction = objectsInShape->testFunction;
    Shape shape = objectsInShape->shape;
    
    Point infoPoint = (*(tree->getPoint))(info);


    if((*testFunction)(shape, infoPoint)){
        
        //free(infoPoint);

        char* infoKey = (*(tree->getKey))(info);
        
        char* infoKeyCopy = (char*) malloc((strlen(infoKey) + 1) * sizeof(char));

        strcpy(infoKeyCopy, infoKey);

        insert(objectsInShape->objectList, infoKeyCopy);
    }
}


void savePointOnListIfItsInsideShape(Info info, ExtraInfo extraInfo){
    
    ObjectsInShape* objectsInShape = (ObjectsInShape*) extraInfo;

    pquadtree* tree = objectsInShape->tree;
    isPointInsideShape testFunction = objectsInShape->testFunction;
    Shape shape = objectsInShape->shape;
    
    Point infoPoint = (*(tree->getPoint))(info);
    
    if((*testFunction)(shape, infoPoint)){
        
        double nodeX = getPointX(infoPoint);
        double nodeY = getPointY(infoPoint);

        Point P = createPoint(nodeX, nodeY);

        insert(objectsInShape->objectList, P);
    }
}


void saveNodeOnListIfItsInsideShape(Info info, ExtraInfo extraInfo){
    
    ObjectsInShape* objectsInShape = (ObjectsInShape*) extraInfo;

    pquadtree* tree = objectsInShape->tree;
    isPointInsideShape testFunction = objectsInShape->testFunction;
    Shape shape = objectsInShape->shape;
    
    Point infoPoint = (*(tree->getPoint))(info);

    if((*testFunction)(shape, infoPoint)){
        
        pquadtreenode* node = findPointNodeInPQuadTree(tree->root, getPointX(infoPoint), getPointY(infoPoint));
    
        insert(objectsInShape->objectList, node);
    }
}


//traversing functions:
void executeFunctionTraversingTree(pquadtreenode *node, nodeVisitingFunction function, ExtraInfo extraInfo);

void preOrderTraversal(PQuadTree Tree, nodeVisitingFunction function, ExtraInfo extraInfo){
    if(Tree == NULL || function == NULL) return;
    pquadtree* tree = (pquadtree*) Tree;
    executeFunctionTraversingTree(tree->root, function, extraInfo);
}

void executeFunctionTraversingTree(pquadtreenode *node, nodeVisitingFunction function, ExtraInfo extraInfo) {

    (*function)(node->info, extraInfo);

    if (node->northWest != NULL) executeFunctionTraversingTree(node->northWest, function, extraInfo);
    if (node->northEast != NULL) executeFunctionTraversingTree(node->northEast, function, extraInfo);
    if (node->southWest != NULL) executeFunctionTraversingTree(node->southWest, function, extraInfo);
    if (node->southEast != NULL) executeFunctionTraversingTree(node->southEast, function, extraInfo);
}


void levelOrderTraversal(PQuadTree Tree, nodeVisitingFunction function, ExtraInfo extraInfo){
    if(Tree == NULL || function == NULL) return;

    pquadtree* tree = (pquadtree*) Tree;
    pquadtreenode* root = tree->root;

    if(root == NULL)
        return;

    Queue queue = createQueue();
    queuePush(queue, root);
    
    pquadtreenode* currentNode;

    while(!isQueueEmpty(queue)){
        
        currentNode = queuePop(queue);

        (*function)(currentNode->info, extraInfo);

        if(currentNode->northWest != NULL)
            queuePush(queue, currentNode->northWest);

        if(currentNode->northEast != NULL)
            queuePush(queue, currentNode->northEast);

        if(currentNode->southWest != NULL)
            queuePush(queue, currentNode->southWest);

        if(currentNode->southEast != NULL)
            queuePush(queue, currentNode->southEast);
    }

    freeQueue(queue, NULL);
}


PQuadTreeNode searchForObjectByKeyInPQuadTree(PQuadTree Tree, char* key){
    if(Tree == NULL || key == NULL) 
        return NULL;
    
    pquadtree* tree = (pquadtree*) Tree;
    pquadtreenode* root = tree->root;

    if(root == NULL) return NULL;

    Queue queue = createQueue();
    queuePush(queue, root);
    
    pquadtreenode* currentNode;

    while(!isQueueEmpty(queue)){
        
        currentNode = queuePop(queue);

        if(!strcmp((*(tree->getKey))(currentNode->info), key)){
            freeQueue(queue, NULL);
            return currentNode;
        }

        if(currentNode->northWest != NULL)
            queuePush(queue, currentNode->northWest);

        if(currentNode->northEast != NULL)
            queuePush(queue, currentNode->northEast);

        if(currentNode->southWest != NULL)
            queuePush(queue, currentNode->southWest);

        if(currentNode->southEast != NULL)
            queuePush(queue, currentNode->southEast);
    }

    freeQueue(queue, NULL);
    return NULL;
}


PQuadTreeNode insertPQuadTree(PQuadTree Tree, Point P, Info info){

    if(Tree == NULL || P == NULL || info == NULL) return NULL;

    pquadtree* tree = (pquadtree*) Tree;

    pquadtreenode* newNode = (pquadtreenode*) malloc(sizeof(pquadtreenode));
    (*newNode).point = P;
    (*newNode).info = info;
    (*newNode).northWest = NULL;
    (*newNode).northEast = NULL;
    (*newNode).southWest = NULL;
    (*newNode).southEast = NULL;

    if((*tree).root == NULL){
        (*tree).root = newNode;
        (*tree).root->parentNode = NULL;
    }else{

        pquadtreenode* currentNode = (*tree).root;
        double pointX = getPointX(P); 
        double pointY = getPointY(P);

        double nodePointX, nodePointY;
        
        while(1){    
            nodePointX = getPointX((*currentNode).point);
            nodePointY = getPointY(currentNode->point);
            
            //northWest
            if(pointX <= nodePointX && pointY <= nodePointY){
                if(pointX == nodePointX && pointY == nodePointY){
                    free(newNode);
                    return NULL;
                }
            
                if((*currentNode).northWest == NULL){
                    (*currentNode).northWest = newNode;
                    newNode->parentNode = currentNode;
                    break;
                }
                    
                else
                    currentNode = (*currentNode).northWest;
                 
            //northEast
            }else if(pointX > nodePointX && pointY <= nodePointY){
                  
                if((*currentNode).northEast == NULL){
                    (*currentNode).northEast = newNode;
                    newNode->parentNode = currentNode;

                    break;
                }
                    
                else
                    currentNode = (*currentNode).northEast;

            //southWest
            }else if(pointX <= nodePointX && pointY > nodePointY){

                if((*currentNode).southWest == NULL){
                    (*currentNode).southWest = newNode;
                    newNode->parentNode = currentNode;
                    break;
                }
                    
                else
                    currentNode = (*currentNode).southWest;
                    
            //southEast
            }else if(pointX > nodePointX && pointY > nodePointY){
                  if((*currentNode).southEast == NULL){
                    (*currentNode).southEast = newNode;
                    newNode->parentNode = currentNode;
                    break;
                }
                    
                else
                    currentNode = (*currentNode).southEast;
            }
        } 
    }

    tree->size++;
    return newNode;
}


//remove function:

void reinsertNotToRemoveNodesOnPQuadTree(pquadtree* tree, pquadtreenode* node, Info nodeToRemoveInfo);

void freePQuadTreeLeafNodes(pquadtreenode* node, freeInfo freeFunction);

void pushInfosToQueue(Info info, Queue infos);

Info removePQuadTreeNode(PQuadTree Tree, PQuadTreeNode Node){
    
    if(Tree == NULL || Node == NULL) return NULL;

    pquadtree* tree = (pquadtree*) Tree;
    pquadtreenode* node = (pquadtreenode*) Node;

    Info info = node->info;

    //cortando a sub-arvore cuja raiz é nó que queremos remover.
    pquadtreenode* parentNode = node->parentNode;

    if(parentNode != NULL){
        if(parentNode->northWest == node)   
            parentNode->northWest = NULL;

        else if(parentNode->northEast == node)
            parentNode->northEast = NULL;

        else if(parentNode->southWest == node)
            parentNode->southWest = NULL;

        else if(parentNode->southEast == node)
            parentNode->southEast = NULL;

        //re-inserindo na arvore os nós que estão abaixo do nó a ser removido, e, removendo esse nó.
        reinsertNotToRemoveNodesOnPQuadTree(tree, node, info);

    }else{ //o nó a ser removido é o root!

        Queue infos = createQueue();
        
        levelOrderTraversal(Tree, pushInfosToQueue, infos);

        queuePop(infos); //removendo a info do root da fila de informacoes.

        freePQuadTreeLeafNodes(tree->root, NULL);
        tree->root = NULL;

        Stack infosStack = queueToStack(infos);
        freeQueue(infos, NULL);

        balancedlyInsertObjectsInPQuadTree(Tree, infosStack);
    }   

    tree->size--;
    return info;
}


void reinsertNotToRemoveNodesOnPQuadTree(pquadtree* tree, pquadtreenode* node, Info nodeToRemoveInfo){

    if(node == NULL) 
        return; 
    
    reinsertNotToRemoveNodesOnPQuadTree(tree, node->northWest, nodeToRemoveInfo); 
    reinsertNotToRemoveNodesOnPQuadTree(tree, node->northEast, nodeToRemoveInfo);  
    reinsertNotToRemoveNodesOnPQuadTree(tree, node->southWest, nodeToRemoveInfo);
    reinsertNotToRemoveNodesOnPQuadTree(tree, node->southEast, nodeToRemoveInfo); 
    
    Info info = node->info;

    if(info != nodeToRemoveInfo){ //if (nó atual nao é o nó a ser removido) then, adicionar esse nó devolta na arvore
        Point point = node->point;
        insertPQuadTree(tree, point, info);
    }
    
    free(node);
}

void pushInfosToQueue(Info info, Queue infos){

    queuePush(infos, info);
}


PQuadTreeNode getPQuadTreeNode(PQuadTree Tree, double x, double y){

    if(Tree == NULL) return NULL;

    pquadtree* tree = (pquadtree*) Tree;
    return findPointNodeInPQuadTree(tree->root, x, y);
}


Info getPQuadTreeNodeInfo(PQuadTree Tree, PQuadTreeNode Node){
    
    if(Tree == NULL || Node == NULL) return NULL;

    pquadtreenode* node = (pquadtreenode*) Node;
    return node->info;
}


//p-quadtree to array:

typedef struct {
    Info* infos;
    int index;
}InfoArray;

void addPQuadTreeInfoToArray(Info info, ExtraInfo extraInfo);

Info* PQuadTreeToArray(PQuadTree Tree){
    if(Tree == NULL) return NULL;
    pquadtree* tree = (pquadtree*) Tree;


    InfoArray arr;

    arr.infos = (Info*) malloc(tree->size * sizeof(Info));
    if(arr.infos == NULL) return NULL;

    arr.index = 0;

    levelOrderTraversal(Tree, addPQuadTreeInfoToArray, &arr);
    
    return arr.infos;
}

void addPQuadTreeInfoToArray(Info info, ExtraInfo extraInfo){

    InfoArray* arr = (InfoArray*) extraInfo; 

    arr->infos[arr->index] = info;
    arr->index++;
} 


//tree freeing function:

void freePQuadTree(PQuadTree Tree, freeInfo freefunction){

    if(Tree == NULL) return;

    pquadtree* tree = (pquadtree*) Tree;
    pquadtreenode* root = tree->root;

    freePQuadTreeLeafNodes(root, freefunction);

    free(Tree);
}


void freePQuadTreeLeafNodes(pquadtreenode* node, freeInfo freeFunction)  { 
    
    if (node == NULL) return; 
    
    freePQuadTreeLeafNodes(node->northWest, freeFunction); 
    freePQuadTreeLeafNodes(node->northEast, freeFunction);
    freePQuadTreeLeafNodes(node->southWest, freeFunction);
    freePQuadTreeLeafNodes(node->southEast, freeFunction); 
    
    if(freeFunction != NULL)
        (*freeFunction)(node->info);
    
    free(node); 
}


//print functions:

void printPQuadTreeNode(Info info, ExtraInfo extraArgs);

void printPQuadTree(PQuadTree Tree){
    if(Tree == NULL) return;
    levelOrderTraversal(Tree, printPQuadTreeNode, Tree);
}


void printPQuadTreeNode(Info info, ExtraInfo extraArgs){

    pquadtree* tree = (pquadtree*) extraArgs;
    Point point = (*(tree->getPoint))(info);

    double pointX = getPointX(point);
    double pointY = getPointY(point);

    printf("Id: %s\n", (*tree->getKey)(info));
    printf("X: %f\n", pointX);
    printf("Y: %f\n", pointY);

    pquadtreenode* node = findPointNodeInPQuadTree(tree->root, pointX, pointY);

    if(node->northWest != NULL)
        printf("northWest: %s\n", (*tree->getKey)( (*(node->northWest)).info ));
    else
        printf("northWest: NULL\n");


    if(node->northEast != NULL)
        printf("northEast: %s\n", (*tree->getKey)( (*(node->northEast)).info ));
    else
        printf("northEast: NULL\n");


    if(node->southWest != NULL)
        printf("southWest: %s\n", (*tree->getKey)( (*(node->southWest)).info ));
    else
        printf("southWest: NULL\n");


    if(node->southEast != NULL)
        printf("southEast: %s\n\n", (*tree->getKey)( (*(node->southEast)).info ));
    else
        printf("southEast: NULL\n\n");
}


void printPQuadTreeNodeCoordinates(PQuadTreeNode Node){
    pquadtreenode* node = (pquadtreenode*) Node;

    double x = getPointX(node->point);
    double y = getPointY(node->point);

    printf("Node - x:%.2lf, y:%.2lf\n", x, y);
}


//Funcoes genericas privadas:

pquadtreenode* findPointNodeInPQuadTree(pquadtreenode *node, double x, double y) {
    
    double px = getPointX(node->point);
    double py = getPointY(node->point);

    if (x == px && y == py) 
        return node;

    if (x <= px) {
        if (y <= py) {
            
            if (node->northWest != NULL) 
                return findPointNodeInPQuadTree(node->northWest, x, y);                     
            else 
                return NULL; //o ponto nao se encontra na arvore. 
            
        } else {

            if (node->southWest != NULL) 
                return findPointNodeInPQuadTree(node->southWest, x, y);              
            else 
                return NULL; //o ponto nao se encontra na arvore. 
        }

    } else {
        if (y <= py) {

            if (node->northEast != NULL) 
                return findPointNodeInPQuadTree(node->northEast, x, y);           
            else 
                return NULL; //o ponto nao se encontra na arvore. 

        } else {

            if (node->southEast) 
                return findPointNodeInPQuadTree(node->southEast, x, y);           
            else 
                return NULL; //o ponto nao se encontra na arvore. 
        }
    }

    return NULL;
}


Stack preProcessObjects(PQuadTree Tree, Stack Objects);

int balancedlyInsertObjectsInPQuadTree(PQuadTree Tree, Stack Objects){
    
    if(Tree == NULL || Objects == NULL)
        return 0;

    Stack preProcessedObjects = preProcessObjects(Tree, Objects);
    if(preProcessedObjects == NULL)
        return 0;

    pquadtree* tree = (pquadtree*) Tree;
    Info info; 
    Point point;

    while(!empty(&preProcessedObjects)){
        
        info = stackPop(&preProcessedObjects);
        point = (*(*tree).getPoint)(info);     
        insertPQuadTree(Tree, point, info);
    }


    return 1;
}

Stack preProcessObjects(PQuadTree Tree, Stack Objects){

    pquadtree* tree = (pquadtree*) Tree;

    //stack com os tads ja pre processados
    Stack preProcessedObjects = createStack();

    //vetor com as tads "crus".
    int objectsAmount = stackLength(&Objects);
    Info* Objs = stackToArray(&Objects);

    //lista com os pontos dos tads.
    List pointsList = createList();
    for(int i = 0; i<objectsAmount; i++)
        insert(pointsList, (*(*tree).getPoint)(Objs[i]));

    Point* pointsArray;

    while(1){
        pointsArray = listToArray(pointsList);

        if(pointsArray == NULL) //todos os pontos ja foram processados.
            break;

        int pointsAmount = length(pointsList);

        Stack convexHullStack = convexHull(pointsArray, pointsAmount);

        if(convexHullStack == NULL){ //sobraram 1 ou 2 pontos. Agora basta empilhar o(s) tad(s) correspondente(s) 
           
            for(int i=0; i<pointsAmount; i++){
                for(int j = 0; j<objectsAmount; j++){
                    if((*(*tree).getPoint)(Objs[j]) == pointsArray[i]){
                        stackPush(&preProcessedObjects, Objs[j]);
                        break;
                    }
                }
            }         
            break;
        }

        while(!empty(&convexHullStack)){
            Point p = stackPop(&convexHullStack);

            for(int i = 0; i<objectsAmount; i++){
                if((*(*tree).getPoint)(Objs[i]) == p){
                    stackPush(&preProcessedObjects, Objs[i]);
                    break;
                }
            }

            Node nodeToRemove = searchForNodeByInfo(pointsList, p);
            removeNode(pointsList, nodeToRemove, NULL);
        }  

    }

    free(pointsArray);
    free(Objs);
    freeList(pointsList, NULL);

    return preProcessedObjects;
}