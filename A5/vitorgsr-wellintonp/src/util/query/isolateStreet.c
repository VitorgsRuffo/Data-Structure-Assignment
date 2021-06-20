#include "../../include/headers.h"
#include "../../elements/urban-elements/block.h"
#include "../../elements/idedPoint.h"
#include "./isolateStreet.h"

typedef struct {
    int max;
    Graph roadSystem;
    Graph bikePath;
    PQuadTree roadIntersections;
    List queryElements;
    File txt;
}Variables;

void isolateBlockStreetIfItsHighlyInfected(Info block, ExtraInfo extraInfo);

void executeStreetIsolation(char* command, City Ct, File txt){
    int max;
    sscanf(&command[3], "%d", &max);

    PQuadTree blocks = getBlocks(Ct);
    Variables variables;

    variables.max = max;
    variables.roadSystem = getRoadSystem(Ct);
    variables.bikePath = getBikePath(Ct);
    variables.roadIntersections = getRoadIntersections(Ct);
    variables.queryElements = getQueryElements(Ct);
    variables.txt = txt;
    
    levelOrderTraversal(blocks, isolateBlockStreetIfItsHighlyInfected, &variables);
}


void drawIsolationOnSvg(List queryElements, Point start, Point end);
void writeIsolationInformationOnTxt(File txt, char* cep, char face, int cases);
int removeBlockStreet(Variables* variables, Point left, Point middle, Point right, double blockH);

void isolateBlockStreetIfItsHighlyInfected(Info block, ExtraInfo extraInfo){
    
    Variables* variables = (Variables*) extraInfo;

    int northFaceCases = getBlockCovidCases(block, 'n');
    int southFaceCases = getBlockCovidCases(block, 's');
    int eastFaceCases = getBlockCovidCases(block, 'e');
    int westFaceCases = getBlockCovidCases(block, 'w');

    double blockX = atof(getBlockX(block));
    double blockY = atof(getBlockY(block));
    double blockW = atof(getBlockWidth(block));
    double blockH = atof(getBlockHeight(block));
    char* cep = getBlockCep(block);

    Point left = createPoint(0,0); 
    Point middle = createPoint(0,0);
    Point right = createPoint(0,0);
    
    if(northFaceCases > variables->max){
        setPointX(left, blockX);
        setPointY(left, (blockY + blockH));
        
        setPointX(middle, (blockX + (blockW/2.0)));
        setPointY(middle, (blockY + blockH));

        setPointX(right, (blockX + blockW));
        setPointY(right, (blockY + blockH));

        if(removeBlockStreet(variables, left, middle, right, blockH)){
            drawIsolationOnSvg(variables->queryElements, left, right);
            writeIsolationInformationOnTxt(variables->txt, cep, 'N', northFaceCases);
        }
    }
    
    if(southFaceCases > variables->max){
        setPointX(left, (blockX + blockW));
        setPointY(left, blockY);

        setPointX(middle, (blockX + (blockW/2.0)));
        setPointY(middle, blockY);

        setPointX(right, blockX);
        setPointY(right, blockY);
        
        if(removeBlockStreet(variables, left, middle, right, blockH)){
            drawIsolationOnSvg(variables->queryElements, left, right);
            writeIsolationInformationOnTxt(variables->txt, cep, 'S', southFaceCases);
        }
    }

    if(eastFaceCases > variables->max){
        setPointX(left, blockX);
        setPointY(left, blockY);

        setPointX(middle, blockX);
        setPointY(middle, (blockY + (blockH/2.0)));

        setPointX(right, blockX);
        setPointY(right, (blockY + blockH));
        
        if(removeBlockStreet(variables, left, middle, right, blockH)){
            drawIsolationOnSvg(variables->queryElements, left, right);
            writeIsolationInformationOnTxt(variables->txt, cep, 'L', eastFaceCases);
        }
    }

    if(westFaceCases > variables->max){
        setPointX(left, blockX + blockW);
        setPointY(left, blockY + blockH);

        setPointX(middle, blockX + blockW);
        setPointY(middle, (blockY + (blockH/2.0)));

        setPointX(right, blockX + blockW);
        setPointY(right, blockY);
        
        if(removeBlockStreet(variables, left, middle, right, blockH)){
            drawIsolationOnSvg(variables->queryElements, left, right);
            writeIsolationInformationOnTxt(variables->txt, cep, 'O', westFaceCases);
        }
    }
    
    freePoint(left);
    freePoint(middle);
    freePoint(right);
}


int removeBlockStreet(Variables* variables, Point left, Point middle, Point right, double blockH){
    double circX, circY, circR = blockH/3.0;
    List vertices;

    //Obtendo o id do vertice que esta no extremo esquerdo da rua.
    circX = getPointX(left);
    circY = getPointY(left);
    vertices = getInfoKeysLocatedInsideCircle(variables->roadIntersections, circX, circY, circR);
    if(length(vertices) == 0){
        freeList(vertices, NULL);
        return 0;
    }
    char* leftVertexId = get(vertices, getFirst(vertices));
    freeList(vertices, NULL);

    //Obtendo o id do vertice que esta no extremo direito da rua.
    circX = getPointX(right);
    circY = getPointY(right);
    vertices = getInfoKeysLocatedInsideCircle(variables->roadIntersections, circX, circY, circR);
    if(length(vertices) == 0){
        freeList(vertices, NULL);
        return 0;
    } 
    char* rigthVertexId = get(vertices, getFirst(vertices));
    freeList(vertices, NULL);
    
    
    //Obtendo o id do vertice que esta no meio da rua (se existente).
    circX = getPointX(middle);
    circY = getPointY(middle);
    vertices = getNodesLocatedInsideCircle(variables->roadIntersections, circX, circY, circR);

    if(length(vertices) == 0){

        removeEdge(variables->roadSystem, leftVertexId, rigthVertexId, 1);
        removeEdge(variables->roadSystem, rigthVertexId, leftVertexId, 1);
        
        if(variables->bikePath != NULL){
            removeEdge(variables->bikePath, leftVertexId, rigthVertexId, 1);
            removeEdge(variables->bikePath, rigthVertexId, leftVertexId, 0);
        }
        
    }else{
        PQuadTreeNode middleVertex = get(vertices, getFirst(vertices));
        char* middleVertexId = 
            getIdedPointId(
                getPQuadTreeNodeInfo(
                    variables->roadIntersections, middleVertex));
        
        freeList(vertices, NULL);

        removeVertex(variables->roadSystem, 1, middleVertexId, freePoint);

        if(variables->bikePath != NULL)
            removeVertex(variables->bikePath, 0, middleVertexId, freePoint);
            
        removePQuadTreeNode(variables->roadIntersections, middleVertex);

        free(middleVertexId);
    }

    free(leftVertexId);
    free(rigthVertexId);
    return 1;
}


void drawIsolationOnSvg(List queryElements, Point start, Point end){

    double x1 = getPointX(start);
    double y1 = getPointY(start);
    double x2 = getPointX(end);
    double y2 = getPointY(end);

    char* isolationTag = (char*) malloc(300*sizeof(char));
    if(isolationTag == NULL) return;
    sprintf(isolationTag, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:7\" />\n", x1, y1, x2, y2);
    insert(queryElements, isolationTag);    
}


void writeIsolationInformationOnTxt(File txt, char* cep, char face, int cases){
    fprintf(txt, "Rua isolada - cep: %s, face: %c, numero de casos de covid: %d.\n\n", cep, face, cases);
}