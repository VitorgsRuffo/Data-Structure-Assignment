#include "../../include/headers.h"
#include "../../include/elements.h"
#include "../tools.h"
#include "openInput.h"
#include "../data-structure/stack.h"
#include "../data-structure/hashtable.h"
#include "../../elements/urban-elements/city.h"

//numero maximo de partes que um comando vindo de um arquivo geo pode ter
#define maxNumberOfGeoCommandParts 8

void readCircle(Stack* circles, char* command, char** commandParts, ElementsCustomization elementsCustom);
void readRectangle(Stack* rectangles, char* command, char** commandParts, ElementsCustomization elementsCustom);
void readText(Stack* texts, char* command, char** commandParts);

void readBlock(Stack* blocks, char* command, char** commandParts, ElementsCustomization elementsCustom, City Ct);
void setBlocksDemographicDensity(DataStructure blocks, DataStructure regions);

void readHydrant(Stack* hydrants, char* command, char** commandParts, ElementsCustomization elementsCustom);
void readSemaphore(Stack* semaphores, char* command, char** commandParts, ElementsCustomization elementsCustom);
void readBaseRadio(Stack* baseRadios, char* command, char** commandParts, ElementsCustomization elementsCustom);
void readFiguresCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readBlockCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readHydrantCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readSemaphoreCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);
void readBaseRadioCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom);

void readHealthCenter(Stack* healthCenters, char* command, int id, char** commandParts);
void readRegion(City Ct, char* command, int id, char** commandParts);

void freeReadGeoResources(char* command, char** commandParts, ElementsCustomization elementsCustom);

void readGeo(File geo, City Ct){
    char* command = (char*) malloc((commandMaxLength + 1) * sizeof(char));     
    int commandLength;
    char commandType[10];
    char** commandParts;
    commandParts = createCommandParts(maxNumberOfGeoCommandParts);
    

    ElementsCustomization elementsCustom = createElementsCustomization();

    //esses dados precisam ser pre-processados antes de serem inseridos na estrutura. (p-quadtree)
    Stack circles = createStack();
    Stack rectangles = createStack();
    Stack texts = createStack();
    Stack blocks = createStack();
    Stack hydrants = createStack();
    Stack baseRadios = createStack();
    Stack semaphores = createStack();
    Stack healthCenters = createStack();

    DataStructure regions = getRegions(Ct);


    int uniqueId = 0; // Contador para atribuir Ids aos tads que necessitarem.
    while(!feof(geo)){
        if(fgets(command, commandMaxLength, geo) == NULL) // se tertarmos ler alem da ultima linha do arquivo fgets retornara NULL e sairemos do loop de leitura.
            break;
        
        commandLength = strlen(command); 
        
        if(command[commandLength-1] == '\n')  //remover \n do final de cada comando.
            command[commandLength-1] = '\0';


        sscanf(command, "%s ", commandType);
        if(!strcmp(commandType, "c")) //lidando com circulo:
            readCircle(&circles, command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "r")) //lidando com retangulo:
            readRectangle(&rectangles ,command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "t")) //lidando com texto:   
            readText(&texts ,command, commandParts);
            
        else if(!strcmp(commandType, "q")) //lidando com quadra: 
            readBlock(&blocks, command, commandParts, elementsCustom, Ct);

        else if(!strcmp(commandType, "h")) //lidando com hidrante:
            readHydrant(&hydrants ,command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "s")) //lidando com semaforos:   
            readSemaphore(&semaphores ,command, commandParts, elementsCustom);            

        else if(!strcmp(commandType, "rb")) //lidando com radio-bases:    
            readBaseRadio(&baseRadios ,command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "sw")) //lidando com as novas estilizacoes de circulo e retangulo:
            readFiguresCustomization(command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "cq")) //lidando com as novas estilizacoes de quadra:
            readBlockCustomization(command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "ch")) //lidando com as novas estilizacoes de hidrante:
            readHydrantCustomization(command, commandParts, elementsCustom);

        else if(!strcmp(commandType, "cs"))//lidando com as novas estilizacoes de semaforo:
            readSemaphoreCustomization(command, commandParts, elementsCustom);
        
        else if(!strcmp(commandType, "cr"))//lidando com as novas estilizacoes de radio-base: 
            readBaseRadioCustomization(command, commandParts, elementsCustom);
        
        else if(!strcmp(commandType, "ps"))//lidando com postos: 
            readHealthCenter(&healthCenters ,command, uniqueId, commandParts);

        else if(!strcmp(commandType, "dd"))//lidando com regioes:
            readRegion(regions, command, uniqueId, commandParts);
        
        uniqueId++;
    }

    balancedlyInsertObjectsInPQuadTree(getCircles(Ct), circles);

    balancedlyInsertObjectsInPQuadTree(getRectangles(Ct), rectangles);

    balancedlyInsertObjectsInPQuadTree(getTexts(Ct), texts);

    balancedlyInsertObjectsInPQuadTree(getBlocks(Ct), blocks);

    setBlocksDemographicDensity(getBlocks(Ct), regions);

    balancedlyInsertObjectsInPQuadTree(getHydrants(Ct), hydrants);

    balancedlyInsertObjectsInPQuadTree(getBaseRadios(Ct), baseRadios);

    balancedlyInsertObjectsInPQuadTree(getSemaphores(Ct), semaphores);

    balancedlyInsertObjectsInPQuadTree(getHealthCenters(Ct), healthCenters);

    freeReadGeoResources(command, commandParts, elementsCustom);
}

void readCircle(Stack* circles, char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    Circle circle = createCircle(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6], getFiguresCwCustomization(elementsCustom));
    stackPush(circles, circle);
}

void readRectangle(Stack* rectangles, char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6], commandParts[7]);
    Rectangle rectangle = createRectangle(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6], commandParts[7], getFiguresRwCustomization(elementsCustom));
    stackPush(rectangles, rectangle);
}

void readText(Stack* texts, char* command, char** commandParts){
    sscanf(command, "%s %s %s %s %s %s %[^\n]s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    Text text = createText(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], commandParts[6]);
    stackPush(texts, text);
}

void readBlock(Stack* blocks, char* command, char** commandParts, ElementsCustomization elementsCustom, City Ct){
    sscanf(command, "%s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5]);
    Block block = createBlock(commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5], getBlockSwCustomization(elementsCustom), getBlockCfillCustomization(elementsCustom), getBlockCstrkCustomization(elementsCustom));
    stackPush(blocks, block);

    DataStructure* blocksTable = getBlocksTable(Ct);
    insertHashTable(blocksTable, block);
}

typedef struct {
    DataStructure regions;
    Rectangle region;
    Rectangle block;
}ddVariables;

void setBlockDemographicDensityIfItsInsideRegion(Info blockInfo, ExtraInfo extraInfo);

void setBlocksDemographicDensity(DataStructure blocks, DataStructure regions){
    ddVariables variables;
    variables.regions = regions;
    variables.region = createRectangle("..", "000000.000000", "000000.000000", "000000.000000", "000000.000000", "..", "..", "..");
    variables.block = createRectangle("..", "000000.000000","000000.000000","000000.000000","000000.000000","..", "..", "..");

    levelOrderTraversal(blocks, setBlockDemographicDensityIfItsInsideRegion, &variables);

    freeRectangle(variables.region);
    freeRectangle(variables.block);
}

void setBlockDemographicDensityIfItsInsideRegion(Info blockInfo, ExtraInfo extraInfo){

    ddVariables* variables = (ddVariables*) extraInfo; 

    setRectangleX(variables->block, getBlockX(blockInfo));
    setRectangleY(variables->block, getBlockY(blockInfo));
    setRectangleWidth(variables->block, getBlockWidth(blockInfo));
    setRectangleHeight(variables->block, getBlockHeight(blockInfo));


    Node currentNode = getFirst(variables->regions);
    Region region;
    char rx[10], ry[10], rw[10], rh[10];

    while(currentNode != NULL){
        region = get(variables->regions, currentNode);

        sprintf(rx, "%.2lf", getRegionX(region));
        sprintf(ry, "%.2lf", getRegionY(region));
        sprintf(rw, "%.2lf", getRegionWidth(region));
        sprintf(rh, "%.2lf", getRegionHeight(region));

        setRectangleX(variables->region, rx);
        setRectangleY(variables->region, ry);
        setRectangleWidth(variables->region, rw);
        setRectangleHeight(variables->region, rh);

        if(isRectangleInsideRectangle(variables->block, variables->region)){
            setBlockDemographicDensity(blockInfo, getRegionDemographicDensity(region));
            setBlockShadowColor(blockInfo);
            return;
        }

        currentNode = getNext(variables->regions, currentNode);
    }
    
}

void readHydrant(Stack* hydrants, char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    Hydrant hydrant = createHydrant(commandParts[1], commandParts[2], commandParts[3], getHydrantSwCustomization(elementsCustom), getHydrantCfillCustomization(elementsCustom), getHydrantCstrkCustomization(elementsCustom));
    stackPush(hydrants, hydrant);
}

void readSemaphore(Stack* semaphores, char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    Semaphore semaphore = createSemaphore(commandParts[1], commandParts[2], commandParts[3], getSemaphoreSwCustomization(elementsCustom), getSemaphoreCfillCustomization(elementsCustom), getSemaphoreCstrkCustomization(elementsCustom));
    stackPush(semaphores, semaphore);
}

void readBaseRadio(Stack* baseRadios, char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    BaseRadio baseRadio = createBaseRadio(commandParts[1], commandParts[2], commandParts[3], getBaseRadioSwCustomization(elementsCustom), getBaseRadioCfillCustomization(elementsCustom), getBaseRadioCstrkCustomization(elementsCustom));
    stackPush(baseRadios, baseRadio);
}

void readFiguresCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s", commandParts[0], commandParts[1], commandParts[2]);
    setFiguresCwCustomization(elementsCustom, commandParts[1]);
    setFiguresRwCustomization(elementsCustom, commandParts[2]);
}

void readBlockCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';
    
    setBlockSwCustomization(elementsCustom, commandParts[1]);
    setBlockCfillCustomization(elementsCustom, commandParts[2]);
    setBlockCstrkCustomization(elementsCustom, commandParts[3]);
}

void readHydrantCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';

    setHydrantSwCustomization(elementsCustom, commandParts[1]);
    setHydrantCfillCustomization(elementsCustom, commandParts[2]);
    setHydrantCstrkCustomization(elementsCustom, commandParts[3]);
}

void readSemaphoreCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';

    setSemaphoreSwCustomization(elementsCustom, commandParts[1]);
    setSemaphoreCfillCustomization(elementsCustom, commandParts[2]);
    setSemaphoreCstrkCustomization(elementsCustom, commandParts[3]);
}

void readBaseRadioCustomization(char* command, char** commandParts, ElementsCustomization elementsCustom){
    sscanf(command, "%s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3]);
    
    int swLength = strlen(commandParts[1]); //remove o "px" que acompanha o sw.
    commandParts[1][swLength-2] = '\0';

    setBaseRadioSwCustomization(elementsCustom, commandParts[1]);
    setBaseRadioCfillCustomization(elementsCustom, commandParts[2]);
    setBaseRadioCstrkCustomization(elementsCustom, commandParts[3]);
}

void readHealthCenter(Stack* healthCenters, char* command, int id, char** commandParts){
    sscanf(command, "%s %s %s", commandParts[0], commandParts[1], commandParts[2]);
    HealthCenter healthCenter = createHealthCenter(id, commandParts[1], commandParts[2]);
    stackPush(healthCenters, healthCenter);
}


void readRegion(DataStructure regions, char* command, int id, char** commandParts){
    sscanf(command, "%s %s %s %s %s %s", commandParts[0], commandParts[1], commandParts[2], commandParts[3], commandParts[4], commandParts[5]);
    Region region = createRegion(id, atof(commandParts[1]), atof(commandParts[2]), atof(commandParts[3]), atof(commandParts[4]), atof(commandParts[5]));
    insert(regions, region);
}

void freeReadGeoResources(char* command, char** commandParts, ElementsCustomization elementsCustom){
    free(command);   
    for(int i = 0; i<8; i++){
        free(commandParts[i]);
    } 
    free(commandParts);
    freeElementsCustomization(elementsCustom);
}