#include "../../include/headers.h"
#include "../../include/urbanElements.h"
#include "../../include/dataStructure.h"
#include "../input/openInput.h"
#include "../tools.h"
#include "../svg.h"

#define node_spacing 20.00      //distancia entre nós folha.
#define node_w 45.00            //largura de um no
#define node_h 45.00            //altura de um no

#define initial_xbound 10.00    //a variavel xBound vai representar um limite do eixo x. Um novo no a ser printado nao pode vir antes desse limite, pois, ele se chocaria com nos que ja foram printados.
#define initial_y 10.00         //y do node root
#define levels_distance 200.00  //distancia em y entre diferentes niveis da arvores

Point drawTreeOnSvg(PQuadTree tree, PQuadTreeNode node, getKeyFunction getKey, double* xBound, double currentY, Svg treeSvg);
void drawParentChildConnection(Svg treeSvg, Point nodeDrawingCoordinates, Point nodeChildCoordinates);

void executeTreeStatePrinting(char* command, City Ct, Parameters Param){

    char treeType[5] = {'x','x','x','x'}, sufix[30];
    sscanf(&command[7], "%s %s", treeType, sufix);

    if(treeType[0] == 't') treeType[0] = 'a';
    DataStructure tree = getDataStructureByElementType(Ct, treeType);
    if(tree == NULL) return;

    if(treeType[0] == 'a') treeType[0] = 'r';
    getKeyFunction getKey = getKeyRetrievingFunctionByElementType(treeType);

    double xBound = initial_xbound;
    Svg treeSvg = createSvg(Param, Ct, "tree", sufix);
    if(treeSvg == NULL) return;
    
    PQuadTreeNode root = getPQuadTreeRoot(tree);
    drawTreeOnSvg(tree, root, getKey, &xBound, initial_y, treeSvg);
    finishSvg(treeSvg);
}



Point drawTreeOnSvg(PQuadTree tree, PQuadTreeNode node, getKeyFunction getKey, double* xBound, double currentY, Svg treeSvg) {
    
    double nodeInitialxBound = *xBound;
    Point nodeDrawingCoordinates = createPoint(0,0);

    //se o no nao existir printamos NULL em seu lugar:
    if(node == NULL){
        double nullNodeX = *xBound + node_spacing;
        double nullNodeY = currentY;
        setPointX(nodeDrawingCoordinates, nullNodeX);
        setPointY(nodeDrawingCoordinates, nullNodeY);
        
        char nullNodeContent[6];
        strcpy(nullNodeContent, "NULL");
        double contentX = nullNodeX + (node_w/2.0);
        double contentY = nullNodeY + (node_h/2.0) + 5; 

        char* nullNodeTag = (char*) malloc(400*sizeof(char));
        sprintf(nullNodeTag, "\t<rect width=\"%.2lf\" height=\"%.2lf\" x=\"%.2lf\" y=\"%.2lf\" stroke=\"black\" stroke-width=\"2\" fill=\"#A02C5A\" />\n\t<text x=\"%.2lf\" y=\"%.2lf\" fill=\"black\" stroke=\"black\" stroke-width=\"0.2\" dominant-baseline=\"middle\" text-anchor=\"middle\"> %s </text>\n", node_w, node_h, nullNodeX, nullNodeY, contentX, contentY, nullNodeContent);

        fprintf(treeSvg, "%s", nullNodeTag);
        free(nullNodeTag);
        *xBound = *xBound + node_spacing + node_w + node_spacing; 

        return nodeDrawingCoordinates;
    }

    Point nwChildCoordinates = drawTreeOnSvg(tree, getPQuadTreeNodeNwChild(tree, node), getKey, xBound, currentY + levels_distance, treeSvg);
    Point neChildCoordinates = drawTreeOnSvg(tree, getPQuadTreeNodeNeChild(tree, node), getKey, xBound, currentY + levels_distance, treeSvg);
    Point swChildCoordinates = drawTreeOnSvg(tree, getPQuadTreeNodeSwChild(tree, node), getKey, xBound, currentY + levels_distance, treeSvg);
    Point seChildCoordinates = drawTreeOnSvg(tree, getPQuadTreeNodeSeChild(tree, node), getKey, xBound, currentY + levels_distance, treeSvg);

    double nodeX = nodeInitialxBound + ((*xBound - nodeInitialxBound)/2.0);
    double nodeY = currentY;
    setPointX(nodeDrawingCoordinates, nodeX);
    setPointY(nodeDrawingCoordinates, nodeY);

    drawParentChildConnection(treeSvg, nodeDrawingCoordinates, nwChildCoordinates);
    drawParentChildConnection(treeSvg, nodeDrawingCoordinates, neChildCoordinates);
    drawParentChildConnection(treeSvg, nodeDrawingCoordinates, swChildCoordinates);
    drawParentChildConnection(treeSvg, nodeDrawingCoordinates, seChildCoordinates);
    free(nwChildCoordinates);
    free(neChildCoordinates);
    free(swChildCoordinates);
    free(seChildCoordinates);

    char* nodeId = (*getKey)(getPQuadTreeNodeInfo(tree, node));
    Point nodeCoordinates = getPQuadTreeNodeCoordinates(tree, node);
    char* nodeCoordinatesString = pointToString(nodeCoordinates);
    
    double contentX = nodeX + (node_w/2.0);
    double contentY = nodeY + (node_h/2.0); 
    char nodeContent[100];
    sprintf(nodeContent, "%s<tspan x=\"%.2lf\" dy=\"15\"  style=\"font-size:6.5px\">%s</tspan>", nodeId, contentX, nodeCoordinatesString);
    free(nodeCoordinatesString);

    char* nodeTag = (char*) malloc(400*sizeof(char));
    sprintf(nodeTag, "\t<rect width=\"%.2lf\" height=\"%.2lf\" x=\"%.2lf\" y=\"%.2lf\" stroke=\"black\" stroke-width=\"2\" fill=\"#A02C5A\" />\n\t<text x=\"%.2lf\" y=\"%.2lf\" fill=\"black\" stroke=\"black\" stroke-width=\"0.2\" dominant-baseline=\"middle\" text-anchor=\"middle\"> %s </text>\n", node_w, node_h, nodeX, nodeY, contentX, contentY, nodeContent);
    fprintf(treeSvg, "%s", nodeTag);
    free(nodeTag);

    *xBound = *xBound + node_spacing + node_w + node_spacing; 
    return nodeDrawingCoordinates;
}

//desenhando a conexao do no com o seu pai:
void drawParentChildConnection(Svg treeSvg, Point nodeDrawingCoordinates, Point nodeChildCoordinates){
    char connectionTag[200];
    double parentX = getPointX(nodeDrawingCoordinates) + (node_w/2.0);
    double parentY = getPointY(nodeDrawingCoordinates) + (node_h/2.0);;
    double childX = getPointX(nodeChildCoordinates) + (node_w/2.0);
    double childY = getPointY(nodeChildCoordinates);
    sprintf(connectionTag, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />", parentX, parentY, childX, childY);
    fprintf(treeSvg, "%s", connectionTag);
}