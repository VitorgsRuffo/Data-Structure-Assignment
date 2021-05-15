#include "../../include/headers.h"
#include "../data-structure/pquadtree.h"
#include "../../elements/urban-elements/block.h"
#include "../../elements/urban-elements/city.h"

//struct: max

typedef struct {
    int max;
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

    /*
        <- east
        west ->

    */
    Point left = createPoint(0,0); 
    Point middle = createPoint(0,0);
    Point right = createPoint(0,0);

    if(northFaceCases > variables.max){
        setPointX(left, blockX);
        setPointY(left, (blockY + blockH));
        
        setPointX(middle, (blockX + (blockW/2.0)));
        setPointY(middle, (blockY + blockH));

        setPointX(right, (blockX + blockW));
        setPointY(right, (blockY + blockH));
    }
    
    if(southFaceCases > variables.max){
        setPointX(left, (blockX + blockW));
        setPointY(left, blockY);

        setPointX(middle, (blockX + (blockW/2.0)));
        setPointY(middle, blockY);

        setPointX(right, blockX);
        setPointY(right, blockY);
    }

    if(eastFaceCases > variables.max){
        setPointX(left, blockX);
        setPointY(left, blockY);

        setPointX(middle, blockX);
        setPointY(middle, (blockY + (blockH/2.0)));

        setPointX(right, blockX);
        setPointY(right, (blockY + blockH));
    }

    if(westFaceCases > variables.max){
        setPointX(left, blockX + blockW);
        setPointY(left, blockY + blockH);

        setPointX(middle, blockX + blockW);
        setPointY(middle, (blockY + (blockH/2.0)));

        setPointX(right, blockX + blockW);
        setPointY(right, blockY);
    }
}
















void deleteBlockIfItsInsideCircle(Info blockInfo, ExtraInfo extraInfo);

void deleteBlocksInCircle(Variables variables){

    //buscando as quadras inteiramente dentro do circulo:
    levelOrderTraversal(variables.elements, deleteBlockIfItsInsideCircle, &variables);

    //removendo as quadras selecionadas da arvore:
    Node currentNode = getFirst(variables.pointsToRemove);
    while(currentNode != NULL){
        
        Info pointToRemove = get(variables.pointsToRemove, currentNode);
        double px = getPointX(pointToRemove);
        double py = getPointY(pointToRemove);

        Info nodeToRemove = getPQuadTreeNode(variables.elements, px, py);
        freeBlock(removePQuadTreeNode(variables.elements, nodeToRemove));

        removeNode(variables.pointsToRemove, currentNode, NULL);
        currentNode = getFirst(variables.pointsToRemove);
    }

}

void deleteBlockIfItsInsideCircle(Info blockInfo, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;

    setRectangleX(variables->building, getBlockX(blockInfo));
    setRectangleY(variables->building, getBlockY(blockInfo));
    setRectangleWidth(variables->building, getBlockWidth(blockInfo));
    setRectangleHeight(variables->building, getBlockHeight(blockInfo));
    

    if(isRectangleInsideCircle(variables->circle, variables->building)){

        char* blockString = blockToString(blockInfo);
        fprintf(variables->txt, "\"%s\" foi removido.\n", blockString);
        free(blockString);

        insert(variables->pointsToRemove, getBlockCoordinates(blockInfo));
    }

}
