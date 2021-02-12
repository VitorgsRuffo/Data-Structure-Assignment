#include "../include/headers.h"
#include "../include/elements.h"
#include "../include/util.h"
#include <unistd.h>

char* buildGeoSvgPath(Parameters Param);

Svg openSvg(char* filePath);

Svg createSvg(Parameters Param, City Ct, char* fileType){
    if(Param == NULL || Ct == NULL || fileType == NULL)
        return NULL;

    char* filePath;
    if(!strcmp(fileType, "geo"))
        filePath = buildGeoSvgPath(Param); 

    else if(!strcmp(fileType, "qry"))
        filePath = buildQryOutputPath(Param, "svg"); 
        
    Svg svg = NULL;
    
    if(access(filePath, F_OK ) == -1)  //se a funcao access retornar -1 significa que o arquivo cujo caminho é "filePath" ainda nao existe, portanto, iremos cria-lo. Não iremos cria-lo caso ele ja exista nesse diretorio.       
        svg = openSvg(filePath); 
                                   
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

    if(svg == NULL) return NULL;

    fprintf(svg, "<svg>\n");
    return svg;
}

typedef void (*buildElementSvgTag)(char*, void*);

void drawElementsOnSvg(Svg svg, DataStructure elements, buildElementSvgTag buildTag);

void buildCircleSvgTag(char* circleTag, Circle Circ);

void buildRectangleSvgTag(char* rectangleTag, Rectangle Rect);

void buildTextSvgTag(char* textTag, Text Txt);

void buildBaseRadioSvgTag(char* baseRadioTag, BaseRadio BaseR);

void buildBlockSvgTag(char* blockTag, Block Blk);

void buildHydrantSvgTag(char* hydrantTag, Hydrant Hyd);

void buildSemaphoreSvgTag(char* semaphoreTag, Semaphore Semap);

void buildHealthCenterSvgTag(char* HealthCenterTag, HealthCenter HealthC);

void buildCovidAddressSvgTag(char* covidAddressTag, CovidAddress Ca);

void buildHouseSvgTag(char* houseTag, House H);

void drawQueryElementsOnSvg(Svg svg, List elementsList);


int drawOnSvg(Svg svg, City Ct){
    if(svg == NULL || Ct == NULL)
        return 0;
    
    DataStructure circles = getCircles(Ct);
    drawElementsOnSvg(svg, circles, &buildCircleSvgTag);

    DataStructure rectangles = getRectangles(Ct);
    drawElementsOnSvg(svg, rectangles, &buildRectangleSvgTag);

    DataStructure texts = getTexts(Ct);
    drawElementsOnSvg(svg, texts, &buildTextSvgTag);

    DataStructure blocks = getBlocks(Ct);
    drawElementsOnSvg(svg, blocks, &buildBlockSvgTag);

    DataStructure semaphores = getSemaphores(Ct);
    drawElementsOnSvg(svg, semaphores, &buildSemaphoreSvgTag);
    
    DataStructure hydrants = getHydrants(Ct);
    drawElementsOnSvg(svg, hydrants, &buildHydrantSvgTag);

    DataStructure baseRadios = getBaseRadios(Ct);
    drawElementsOnSvg(svg, baseRadios, &buildBaseRadioSvgTag);

    DataStructure healthCenters = getHealthCenters(Ct);
    drawElementsOnSvg(svg, healthCenters, &buildHealthCenterSvgTag);

    DataStructure covidAddresses = getCovidAddresses(Ct);
    drawElementsOnSvg(svg, covidAddresses, &buildCovidAddressSvgTag);

    DataStructure houses = getHousesTree(Ct);
    drawElementsOnSvg(svg, houses, &buildHouseSvgTag);


    List queryElementsList = getQueryElements(Ct);
    drawQueryElementsOnSvg(svg, queryElementsList);

    return 1;
}

typedef struct {
    Svg svg;
    buildElementSvgTag buildTag;
    char* elementTag;
} SvgTag;

void drawElementOnSvg(Info info, ExtraInfo extraInfo);

void drawElementsOnSvg(Svg svg, DataStructure elements, buildElementSvgTag buildTag){
   
    if(svg == NULL || elements == NULL || buildTag)
        return;
    
    SvgTag extraInfo;
    extraInfo.svg = svg; 
    extraInfo.buildTag = buildTag; 
    extraInfo.elementTag = (char*) malloc(500 * sizeof(char));

    preOrderTraversal(elements, drawElementOnSvg, &extraInfo);
   
    free(extraInfo.elementTag);
}

void drawElementOnSvg(Info info, ExtraInfo extraInfo){
    
    SvgTag *exInfo = (SvgTag*) extraInfo;
    
    (*exInfo->buildTag)(exInfo->elementTag, info);
    fprintf(exInfo->svg, "%s", exInfo->elementTag);
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
    char* shadowColor;

    if((shadowColor = getShadowColor(Blk)) == NULL)
        strcpy(shadowColor, "rgba(0,0,0,0)");

    sprintf(blockTag, "\t<rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" rx=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n", width, height, (x + 8), (y + 8), rx , shadowColor, sw, shadowColor);
    sprintf(blockTag, "\t<rect width=\"%s\" height=\"%s\" x=\"%s\" y=\"%s\" rx=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%f\" y=\"%f\" fill=\"black\" stroke=\"white\" stroke-width=\"0.1\" dominant-baseline=\"middle\" text-anchor=\"middle\"> %s </text>\n", width, height, x, y, rx ,cstrk, sw, cfill, xCep, yCep, cep);
}    


void buildSemaphoreSvgTag(char* semaphoreTag, Semaphore Semap){
    char* x = getSemaphoreX(Semap);
    char* y = getSemaphoreY(Semap);
    char* radius = getSemaphoreRadius(Semap);
    char* sw = getSemaphoreSw(Semap);
    char* cfill = getSemaphoreCfill(Semap);
    char* cstrk = getSemaphoreCstrk(Semap);

    sprintf(semaphoreTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%s\" y=\"%s\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> S </text>\n", x, y, radius, cstrk, sw, cfill, x, y);
}

void buildHydrantSvgTag(char* hydrantTag, Hydrant Hyd){
    char* x = getHydrantX(Hyd);
    char* y = getHydrantY(Hyd);
    char* radius = getHydrantRadius(Hyd);
    char* sw = getHydrantSw(Hyd);
    char* cfill = getHydrantCfill(Hyd);
    char* cstrk = getHydrantCstrk(Hyd);

    sprintf(hydrantTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%s\" y=\"%s\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> H </text>\n", x, y, radius, cstrk, sw, cfill, x, y);
}

void buildBaseRadioSvgTag(char* baseRadioTag, BaseRadio BaseR){
    char* x = getBaseRadioX(BaseR);
    char* y = getBaseRadioY(BaseR);
    char* radius = getBaseRadioRadius(BaseR);
    char* sw = getBaseRadioSw(BaseR);
    char* cfill = getBaseRadioCfill(BaseR);
    char* cstrk = getBaseRadioCstrk(BaseR);

    sprintf(baseRadioTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n\t<text x=\"%s\" y=\"%s\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> RB </text>\n", x, y, radius, cstrk, sw, cfill, x, y);
}

void buildHealthCenterSvgTag(char* healthCenterTag, HealthCenter HealthC){
    char* x = getHealthCenterX(HealthC);
    char* y = getHealthCenterY(HealthC);
    char* radius = getHealthCenterRadius(HealthC);

    sprintf(healthCenterTag, "\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"mediumblue\" stroke-width=\"1\" fill=\"royalblue\" />\n\t<text x=\"%s\" y=\"%s\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> HC </text>\n", x, y, radius, x, y);
}

void buildCovidAddressSvgTag(char* covidAddressTag, CovidAddress Ca){

    Address address = getCovidAddress(Ca);
    Point covidAddressCoordinates = getAddressCoordinates(address);

    double covidAddressX = getPointX(covidAddressCoordinates);
    double covidAddressY = getPointY(covidAddressCoordinates);

    double x = covidAddressX - 15.00;
    double y = covidAddressY - 15.00;
  
    int casesNumber = getCovidAddressCasesNumber(Ca);

    sprintf(covidAddressTag, "\t<rect width=\"15.00\" height=\"15.00\" x=\"%lf\" y=\"%lf\" stroke=\"darkorange\" stroke-width=\"1\" fill=\"orange\" />\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> %d </text>\n", x, y, covidAddressX, covidAddressY, casesNumber);
}

void buildHouseSvgTag(char* houseTag, House H){

    double x = getHouseX(H);
    double y = getHouseY(H);
    double w = getHouseW(H);
    double h = getHouseH(H);
    double centerOfMassX = getHouseCenterOfMassX(H);
    double centerOfMassY = getHouseCenterOfMassY(H);
    int casesNumber = getHouseCasesNumber(H);

    sprintf(houseTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"darkorange\" stroke-width=\"1\" fill=\"orange\" />\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" dy=\".3em\"> %d </text>\n", w, h, x, y, centerOfMassX, centerOfMassY, casesNumber);
}

void drawQueryElementsOnSvg(Svg svg, List elementsList){
    
    Node NODE = getFirst(elementsList);
    if(NODE == NULL) return;
    
    
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