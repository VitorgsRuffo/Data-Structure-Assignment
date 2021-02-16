#include "../../include/headers.h"
#include "highlightEstablishment.h"
#include "../../include/dataStructure.h"
#include "../../elements/figures/rectangle.h"
#include "../../elements/urban-elements/establishment.h"
#include "../../elements/urban-elements/person.h"

typedef struct {
    File txt;
    char codt[5];
    DataStructure people;
    Rectangle regionRect;
    DataStructure establishmentsType;
    List queryElements;
}Variables;

void highlightEstablishmentsInRange(Info establishmentInfo, ExtraInfo extraInfo);

void executeHighlightEstablishmentInRange(char* command, City Ct, File txt){

    char x[20]; char y[20]; char w[20]; char h[20]; char codt[5];
    sscanf(&command[6], "%s %s %s %s %s", codt, x, y, w, h);

    Variables variables;

    // Retangulo que representa a regiao delimitante
    Rectangle rect = createRectangle("..", w, h, x, y, "..", "..", "..");

    DataStructure establishments = getEstablishmentsTable(Ct);
    
    variables.txt = txt;
    strcpy(variables.codt, codt);
    variables.people = getPeople(Ct);
    variables.regionRect = rect;
    variables.establishmentsType = getEstablishmentTypes(Ct);
    variables.queryElements = getQueryElements(Ct);

    levelOrderTraversal(establishments, highlightEstablishmentsInRange, &variables);

    free(rect);
}


void buildHighlightCircumference(Info establishmentInfo, List queryElements);
void writeEstablishmentInformationOnTxt(Info establishmentInfo, Info establishmentsTypeInfo, Info personInfo, File txt);

void highlightEstablishmentsInRange(Info establishmentInfo, ExtraInfo extraInfo){
    
    Variables* variables = (Variables*) extraInfo;
    Point estabCoordinates = getEstablishmentCoordinates(establishmentInfo);

    double estabX = getPointX(estabCoordinates); 
    double estabY = getPointY(estabCoordinates);
    double estabWidth = getEstablishmentWidth(establishmentInfo);
    double estabHeight = getEstablishmentHeight(establishmentInfo);

    char* ownerCpf = getEstablishmentCpf(establishmentInfo);
    Info owner = getHashTableInfo(variables->people, ownerCpf);
    Info establishmentTypeInfo = getHashTableInfo(variables->establishmentsType, getEstablishmentCode(establishmentInfo));

    char x[20]; char y[20]; char w[20]; char h[20];
    sprintf(x, "%lf", estabX); sprintf(y, "%lf", estabY);
    sprintf(w, "%lf", estabWidth); sprintf(h, "%lf", estabHeight);

    Rectangle establishmentRect = createRectangle("..", w, h, x, y, "..", "..", "..");

    if(!strcmp(variables->codt, "*")){
        if(isRectangleInsideRectangle(establishmentRect, variables->regionRect)){
            writeEstablishmentInformationOnTxt(establishmentInfo, establishmentTypeInfo, owner, variables->txt);
            buildHighlightCircumference(establishmentInfo, variables->queryElements);
        }
    }

    else{
        char* currentEstablishmentType = getEstablishmentCode(establishmentInfo);
        int checkTypes = strcmp(currentEstablishmentType, variables->codt);

        if(isRectangleInsideRectangle(establishmentRect, variables->regionRect) && checkTypes == 0){
            writeEstablishmentInformationOnTxt(establishmentInfo, establishmentTypeInfo, owner, variables->txt);
            buildHighlightCircumference(establishmentInfo, variables->queryElements);
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


void buildHighlightCircumference(Info establishmentInfo, List queryElements){
    
    Point centerOfMassPoint = getEstablishmentCenterOfMass(establishmentInfo);
    double centerOfMassX = getPointX(centerOfMassPoint);
    double centerOfMassY = getPointY(centerOfMassPoint);
    double radius = 80.0;

    char* circumferenceTag = (char*) malloc(300 * sizeof(char));
    if(circumferenceTag == NULL)
        return;

    sprintf(circumferenceTag, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"lawngreen\" stroke-width=\"3\" fill=\"black\" fill-opacity=\"0.0\" />\n", centerOfMassX, centerOfMassY, radius);
    
    insert(queryElements, circumferenceTag);
}