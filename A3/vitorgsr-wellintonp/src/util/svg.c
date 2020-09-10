#include "../include/headers.h"
#include "../include/util.h"
#include "../include/figures.h"
#include "../include/urbanElements.h"
#include "../drawing.h"
#include <unistd.h>

char* buildGeoSvgPath(Parameters Param);

Svg openSvg(char* filePath);

Svg createSvg(Parameters Param, Drawing Dr, char* fileType){
    if(Param == NULL){
        printf("Erro: os parametros nao existem..\n");
        exit(1);
    }

    if(Dr == NULL){
        printf("Erro: Drawing nao existe..\n");
        exit(1);
    }

    char* filePath;
    if(!strcmp(fileType, "geo"))
        filePath = buildGeoSvgPath(Param); 

    else if(!strcmp(fileType, "qry"))
        filePath = buildQryOutputPath(Param, "svg"); 
        
    Svg svg = NULL;
    
    if(access(filePath, F_OK ) != -1){ 
        printf("O arquivo Svg (%s) ja existe...\n", filePath);
    
    }else{ //se a funcao access retornar -1 significa que o arquivo cujo caminho é "filePath" ainda nao existe, portanto, iremos cria-lo. Não iremos cria-lo caso ele ja exista nesse diretorio.       
        svg = openSvg(filePath); 
    }                               

    free(filePath);
    return svg;
}

char* buildGeoSvgPath(Parameters Param){

    char* outputDirectory = getOutputDirectory(Param);
    int outputDirectoryLength = strlen(outputDirectory);

    char* fullFileName = getGeoName(Param);
    char* fileNameWithoutPathAndExtension = getFileNameWithoutPathAndExtension(fullFileName);  

    int filePathLength = strlen(outputDirectory) + strlen(fileNameWithoutPathAndExtension) + strlen(".svg") + 5;
    char* filePath = (char*) malloc(filePathLength * sizeof(char));

    if(outputDirectory[outputDirectoryLength - 1] == '/'){
        sprintf(filePath, "%s%s.svg", outputDirectory, fileNameWithoutPathAndExtension);    
    }else{
        sprintf(filePath, "%s/%s.svg", outputDirectory, fileNameWithoutPathAndExtension);    
    }

    free(fileNameWithoutPathAndExtension);
    return filePath;
}

Svg openSvg(char* filePath){
    
    Svg svg = fopen(filePath, "a");

    if(isElementNull(svg, "svg", "openSvg"))
        return NULL;

    fprintf(svg, "<svg>\n");
    return svg;
}

void drawElementsOnSvg(Svg svg, List elementsList, void (*buildElementSvgTag)(char*, void*));

void buildCircleSvgTag(char* circleTag, Circle Circ);

void buildRectangleSvgTag(char* rectangleTag, Rectangle Rect);

void buildTextSvgTag(char* textTag, Text Txt);

void buildBaseRadioSvgTag(char* baseRadioTag, BaseRadio BaseR);

void buildBlockSvgTag(char* blockTag, Block Blk);

void buildHydrantSvgTag(char* hydrantTag, Hydrant Hyd);

void buildSemaphoreSvgTag(char* semaphoreTag, Semaphore Semap);

void drawQueryElementsOnSvg(Svg svg, List elementsList);

void drawOnSvg(Svg svg, Drawing Dr){
    if(svg == NULL){
        printf("Erro: Ponteiro para o arquivo svg e NULL");
        exit(1);
    }
    if(Dr == NULL){
        printf("Erro: o TAD dos desenhos nao existe..\n");
        exit(1);
    }

    List circleList = getCircleList(Dr);
    drawElementsOnSvg(svg, circleList, &buildCircleSvgTag);

    List rectangleList = getRectangleList(Dr);
    drawElementsOnSvg(svg, rectangleList, &buildRectangleSvgTag);

    List textList = getTextList(Dr);
    drawElementsOnSvg(svg, textList, &buildTextSvgTag);

    List blockList = getBlockList(Dr);
    drawElementsOnSvg(svg, blockList, &buildBlockSvgTag);

    List semaphoreList = getSemaphoreList(Dr);
    drawElementsOnSvg(svg, semaphoreList, &buildSemaphoreSvgTag);
    
    List hydrantList = getHydrantList(Dr);
    drawElementsOnSvg(svg, hydrantList, &buildHydrantSvgTag);

    List baseRadioList = getBaseRadioList(Dr);
    drawElementsOnSvg(svg, baseRadioList, &buildBaseRadioSvgTag);

    List queryElementsList = getQueryElementsList(Dr);
    drawQueryElementsOnSvg(svg, queryElementsList);
}

void drawElementsOnSvg(Svg svg, List elementsList, void (*buildElementSvgTag)(char*, void*)){
    Node NODE = getFirst(elementsList);

    if(NODE == NULL){
        printf("Erro: a lista de elementos esta vazia, falha ao desenhar no svg..\n");
    }
    
    char* elementTag = (char*) malloc(500 * sizeof(char));
    Info information;
    while(NODE != NULL){
        information = get(elementsList, NODE);

        (*buildElementSvgTag)(elementTag, information);
        
        fprintf(svg, "%s", elementTag);

        NODE = getNext(elementsList, NODE);        
    }

    free(elementTag);
}

void buildCircleSvgTag(char* circleTag, Circle Circ){
    char* radius = getCircleRadius(Circ);
    char* x = getCircleX(Circ);
    char* y = getCircleY(Circ);
    char* corb = getCircleCorb(Circ);
    char* corp = getCircleCorp(Circ);
    char* cw = getCircleCw(Circ);

    sprintf(circleTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n", x, y, radius, corb, cw, corp);
}

void buildRectangleSvgTag(char* rectangleTag, Rectangle Rect){
    char* width = getRectangleWidth(Rect);
    char* height = getRectangleHeight(Rect);
    char* x = getRectangleX(Rect);
    char* y = getRectangleY(Rect);
    char* corb = getRectangleCorb(Rect);
    char* corp = getRectangleCorp(Rect);
    char* rw = getRectangleRw(Rect);

    sprintf(rectangleTag, "\t<rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n", width, height, x, y, corb, rw, corp);
}

void buildTextSvgTag(char* textTag, Text Txt){
    char* x = getTextX(Txt);
    char* y = getTextY(Txt);
    char* corb = getTextCorb(Txt);
    char* corp = getTextCorp(Txt);
    char* textContent = getTextContent(Txt);

    sprintf(textTag, "\t<text x=\"%s\" y=\"%s\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\" > %s </text>\n", x, y, corb, corp, textContent);
}

void buildBlockSvgTag(char* blockTag, Block Blk){
    char* cep = getBlockCep(Blk);
    char* x = getBlockX(Blk);
    char* y = getBlockY(Blk);
    char* width = getBlockWidth(Blk);
    char* height = getBlockHeight(Blk);
    char* sw = getBlockSw(Blk);
    char* cfill = getBlockCfill(Blk);
    char* cstrk = getBlockCstrk(Blk);
    char* rx = getBlockRx(Blk);
    float xCep =  atof(x)+(atof(width)/2);
    float yCep =  atof(y)+(atof(height)/2);

    sprintf(blockTag, "\t<rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" rx=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%f\" y=\"%f\" fill=\"black\" stroke=\"white\" stroke-width=\"0.1\" dominant-baseline=\"middle\" text-anchor=\"middle\"> %s </text>\n", width, height, x, y, rx ,cstrk, sw, cfill, xCep, yCep, cep);
}    


void buildSemaphoreSvgTag(char* semaphoreTag, Semaphore Semap){
    char* x = getSemaphoreX(Semap);
    char* y = getSemaphoreY(Semap);
    char* sw = getSemaphoreSw(Semap);
    char* cfill = getSemaphoreCfill(Semap);
    char* cstrk = getSemaphoreCstrk(Semap);

    sprintf(semaphoreTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"10.0\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%s\" y=\"%s\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> S </text>\n", x, y, cstrk, sw, cfill, x, y);
}

void buildHydrantSvgTag(char* hydrantTag, Hydrant Hyd){
    char* x = getHydrantX(Hyd);
    char* y = getHydrantY(Hyd);
    char* sw = getHydrantSw(Hyd);
    char* cfill = getHydrantCfill(Hyd);
    char* cstrk = getHydrantCstrk(Hyd);

    sprintf(hydrantTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"10.0\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%s\" y=\"%s\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> H </text>\n", x, y, cstrk, sw, cfill, x, y);
}

void buildBaseRadioSvgTag(char* baseRadioTag, BaseRadio BaseR){
    char* x = getBaseRadioX(BaseR);
    char* y = getBaseRadioY(BaseR);
    char* sw = getBaseRadioSw(BaseR);
    char* cfill = getBaseRadioCfill(BaseR);
    char* cstrk = getBaseRadioCstrk(BaseR);

    sprintf(baseRadioTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"10.0\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%s\" y=\"%s\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> RB </text>\n", x, y, cstrk, sw, cfill, x, y);
}

void drawQueryElementsOnSvg(Svg svg, List elementsList){
    Node NODE = getFirst(elementsList);

    if(NODE == NULL){
        printf("Erro: a lista de elementos do query esta vazia, falha ao desenhar no svg..\n");
    }
    
    Info information;
    while(NODE != NULL){
        information = get(elementsList, NODE);
        
        fprintf(svg, "%s", (char*) information);

        NODE = getNext(elementsList, NODE);        
    }

}

void finishSvg(Svg svg){
    fprintf(svg, "</svg>");
    fclose(svg);
}