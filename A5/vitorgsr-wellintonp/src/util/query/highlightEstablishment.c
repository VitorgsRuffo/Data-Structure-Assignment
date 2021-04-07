#include "../../include/headers.h"
#include "highlightEstablishment.h"
#include "../../include/dataStructure.h"
#include "../../elements/figures/rectangle.h"
#include "../../elements/urban-elements/establishment.h"
#include "../../elements/urban-elements/person.h"

typedef struct {
    File txt;
    char codt[5];
    DataStructure* people;
    Rectangle regionRect;
    DataStructure* establishmentsType;
    List queryElements;
}Variables;

void buildDelitionRectange(Rectangle rect, List queryElements);
void highlightEstablishmentsInRange(Info establishmentInfo, ExtraInfo extraInfo);

void executeHighlightEstablishmentInRange(char* command, City Ct, File txt){

    char x[20]; char y[20]; char w[20]; char h[20]; char codt[5];
    sscanf(&command[6], "%s %s %s %s %s", codt, x, y, w, h);

    Variables variables;

    // Retangulo que representa a regiao delimitante
    Rectangle rect = createRectangle("..", w, h, x, y, "..", "..", "..");

    DataStructure establishments = getEstablishmentsTree(Ct);
    
    variables.txt = txt;
    strcpy(variables.codt, codt);
    variables.people = getPeople(Ct);
    variables.regionRect = rect;
    variables.establishmentsType = getEstablishmentTypes(Ct);  

    levelOrderTraversal(establishments, highlightEstablishmentsInRange, &variables);

    buildDelitionRectange(rect, getQueryElements(Ct));
    free(rect);
}

void writeEstablishmentInformationOnTxt(Info establishmentInfo, Info establishmentsTypeInfo, Info personInfo, File txt);

void highlightEstablishmentsInRange(Info establishmentInfo, ExtraInfo extraInfo){

    Variables* variables = (Variables*) extraInfo;  
    
    Point estabCoordinates = getEstablishmentCoordinates(establishmentInfo);
    double estabX = getPointX(estabCoordinates); 
    double estabY = getPointY(estabCoordinates);

    double estabWidth = getEstablishmentWidth(establishmentInfo);
    double estabHeight = getEstablishmentHeight(establishmentInfo);

    char* ownerCpf = getEstablishmentCpf(establishmentInfo);
    Info owner = getHashTableInfo(*(variables->people), ownerCpf);
    Info establishmentTypeInfo = getHashTableInfo(*(variables->establishmentsType), getEstablishmentCode(establishmentInfo));

    char x[20]; char y[20]; char w[20]; char h[20];
    sprintf(x, "%lf", estabX); sprintf(y, "%lf", estabY);
    sprintf(w, "%lf", estabWidth); sprintf(h, "%lf", estabHeight);

    Rectangle establishmentRect = createRectangle("..", w, h, x, y, "..", "..", "..");

    if(!strcmp(variables->codt, "*")){
        if(isRectangleInsideRectangle(establishmentRect, variables->regionRect)){
            writeEstablishmentInformationOnTxt(establishmentInfo, establishmentTypeInfo, owner, variables->txt);
            setEstablishmentColor(establishmentInfo, "pink");
        }
    }

    else{
        char* currentEstablishmentType = getEstablishmentCode(establishmentInfo);
        int checkTypes = strcmp(currentEstablishmentType, variables->codt);

        if(isRectangleInsideRectangle(establishmentRect, variables->regionRect) && checkTypes == 0){
            writeEstablishmentInformationOnTxt(establishmentInfo, establishmentTypeInfo, owner, variables->txt);
            setEstablishmentColor(establishmentInfo, "pink");
        }
    }

    free(establishmentRect);
}


void writeEstablishmentInformationOnTxt(Info establishmentInfo, Info establishmentsTypeInfo, Info personInfo, File txt){

    char* establishmentString = establishmentToString(establishmentInfo, establishmentsTypeInfo);
    char* ownerName = getPersonName(personInfo);
    
    fprintf(txt, "%s", establishmentString);
    fprintf(txt, "Nome do proprietario: %s", ownerName);
    fprintf(txt, "\n\n");

    free(establishmentString);
}

void buildDelitionRectange(Rectangle rect, List queryElements){
    
    Point rectangleCoordinates = getRectangleCoordinates(rect);
    double x = getPointX(rectangleCoordinates);
    double y = getPointY(rectangleCoordinates);
    double w = atof(getRectangleWidth(rect));
    double h = atof(getRectangleHeight(rect));

    char* delitionRectangleTag = (char*) malloc(300 * sizeof(char));
    if(delitionRectangleTag == NULL)
        return;

    sprintf(delitionRectangleTag, "\t<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"black\" stroke-width=\"1.5\" fill=\"black\" fill-opacity=\"0.0\" />\n", w, h, x, y); 

    insert(queryElements, delitionRectangleTag);
}