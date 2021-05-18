#include "../../include/headers.h"
#include "../../elements/urban-elements/block.h"
#include "../../elements/urban-elements/city.h"
#include "../input/openInput.h"

typedef struct {
    int max;
    Graph roadSystem;
    Graph bikeSystem;
    PQuadTree roadIntersections;
    List queryElements;
    File txt;
}Variables;


void executeStreetIsolation(char* command, City Ct, File txt){
    int max;
    sscanf(&command[3], "%d", &max);

    PQuadTree blocks = getBlocks(Ct);

    isolateHighlyInfectedBlockStreets();

}

void isolateHighlyInfectedBlockStreets(){

}

void drawIsolationOnSvg(List queryElements, Point start, Point end);
void writeIsolationInformationOnTxt(File txt, char* cep, char* face, int cases);

void isolateBlockStreetIfItsHighlyInfected(Info block, ExtraInfo extraInfo){

    // Pegar o numero de casos de uma face e comparar com max
    // comparar se é maior que max. Se for maior, executar um bloco de código. Se não, continua verificando as outras faces do bloco
    
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

    /*
        <- east
        west ->

    */
    Point left = createPoint(0,0); 
    Point middle = createPoint(0,0);
    Point right = createPoint(0,0);

    List vertices;
    double rectX1, rectY1, rectX2, rectY2;

    if(northFaceCases > variables.max){
        setPointX(left, blockX);
        setPointY(left, (blockY + blockH));
        
        setPointX(middle, (blockX + (blockW/2.0)));
        setPointY(middle, (blockY + blockH));

        setPointX(right, (blockX + blockW));
        setPointY(right, (blockY + blockH));

        function(left, middle, right);
        drawIsolationOnSvg(variables.queryElements, left, right);
        writeIsolationInformationOnTxt(variables.txt, cep, 'N', northFaceCases);
    }
    
    if(southFaceCases > variables.max){
        setPointX(left, (blockX + blockW));
        setPointY(left, blockY);

        setPointX(middle, (blockX + (blockW/2.0)));
        setPointY(middle, blockY);

        setPointX(right, blockX);
        setPointY(right, blockY);
        
        function(left, middle, right);
        drawIsolationOnSvg(variables.queryElements, left, right);
        writeIsolationInformationOnTxt(variables.txt, cep, 'S', southFaceCases);
    }

    if(eastFaceCases > variables.max){
        setPointX(left, blockX);
        setPointY(left, blockY);

        setPointX(middle, blockX);
        setPointY(middle, (blockY + (blockH/2.0)));

        setPointX(right, blockX);
        setPointY(right, (blockY + blockH));
        
        function(left, middle, right);
        drawIsolationOnSvg(variables.queryElements, left, right);
        writeIsolationInformationOnTxt(variables.txt, cep, 'L', eastFaceCases);
    }

    if(westFaceCases > variables.max){
        setPointX(left, blockX + blockW);
        setPointY(left, blockY + blockH);

        setPointX(middle, blockX + blockW);
        setPointY(middle, (blockY + (blockH/2.0)));

        setPointX(right, blockX + blockW);
        setPointY(right, blockY);
        
        function(left, middle, right);
        drawIsolationOnSvg(variables.queryElements, left, right);
        writeIsolationInformationOnTxt(variables.txt, cep, 'O', westFaceCases);
    }
    
    freePoint(left);
    freePoint(middle);
    freePoint(right);
}


void function (Variables variables, Point left, Point middle, Point right, double blockW, double blockH){
    double rectX1, rectY1, rectX2, rectY2, rectW = blockW/2.0, rectH = blockH/2.0;
    List vertices;

    //Obtendo o id do vertice que esta no extremo esquerdo da rua.
    rectX1 = getPointX(left) - rectW;
    rectY1 = getPointY(left);
    rectX2 = getPointX(left);
    rectY2 = getPointY(left) + rectH;
    vertices = getInfoKeysLocatedInsideRectangle(variables.roadIntersections, rectX1, rectY1, rectX2, rectY2);
    if(length(vertices) == 0){
        freeList(vertices, NULL);
        return;
    }
    char* leftVertexId = get(vertices, getFirst(vertices));
    freeList(vertices, NULL);

    //Obtendo o id do vertice que esta no extremo direito da rua.
    rectX1 = getPointX(right);
    rectY1 = getPointY(right);
    rectX2 = rectX1 + rectW;
    rectY2 = rectY1 + rectH;
    vertices = getInfoKeysLocatedInsideRectangle(variables.roadIntersections, rectX1 ,rectY1 ,rectX2 , rectY2);
    if(length(vertices) == 0){
        freeList(vertices, NULL);
        return;
    } 
    char* rigthVertexId = get(vertices, getFirst(vertices));
    freeList(vertices, NULL);
    
    
    //Obtendo o id do vertice que esta no meio da rua (se existente).
    rectX1 = getPointX(middle);
    rectY1 = getPointY(middle);
    rectX2 = rectX1 + rectW;
    rectY2 = rectY1 + rectH;
    vertices = getNodesLocatedInsideRectangle(variables.roadIntersections, rectX1 ,rectY1 ,rectX2 , rectY2);

    if(length(vertices) == 0){

        removeEdge(variables.roadSystem, leftVertexId, rigthVertexId, 1);
        removeEdge(variables.roadSystem, rigthVertexId, leftVertexId, 1);
        
        if(variables.bikePath != NULL){
            removeEdge(variables.bikePath, leftVertexId, rigthVertexId, 1);
            removeEdge(variables.bikePath, rigthVertexId, leftVertexId, 0);
        }
        
    }else{
        PQuadTreeNode middleVertex = get(vertices, getFirst(vertices));
        char* middleVertexId = 
            getIdedPointId(
                getPQuadTreeNodeInfo(
                    variables.roadIntersections, middleVertex));
        
        freeList(vertices, NULL);

        // Removendo arestas do sistema viario para carro
        removeVertex(variables.roadSystem, 1, middleVertexId, freePoint);

        if(variables.bikePath != NULL)
            removeVertex(variables.bikePath, 0, middleVertexId, freePoint);
            
        removePQuadTreeNode(variables.roadIntersections, middleVertex);
    }
}


void drawIsolationOnSvg(List queryElements, Point start, Point end){

    double x1 = getPointX(start);
    double y1 = getPointY(start) + 10;
    double x2 = getPointX(end);
    double y2 = getPointY(end) + 10;

    char* isolationTag = (char*) malloc(300*sizeof(char));
    if(isolationTag == NULL) return;
    sprintf(isolationTag, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:1.5\" />\n", x1, y1, x2, y2);
    insert(queryElements, isolationTag);    
}


void writeIsolationInformationOnTxt(File txt, char* cep, char* face, int cases){
    fprintf(txt, "Rua isolada - cep: %s, face: %c, numero de casos de covid: %d.\n\n", cep, face, cases);
}