#include "../include/headers.h"
#include "../include/elements.h"
#include "./data-structure/stack.h"
#include "tools.h"

void swapInformations(Info* info1, Info* info2) { 
    Info temp;

    temp = *info1;
    *info1 = *info2;
    *info2 = temp;  
} 

char** createCommandParts(int numberOfParts){
    char** commandParts = (char**) malloc(sizeof(char*) * numberOfParts);
    
    for(int i = 0; i<numberOfParts; i++)
        commandParts[i] = (char*) malloc(60 * sizeof(char));
    
    return commandParts;
}

char* getFileNameWithoutPathAndExtension(char* fullFileName){ //Retorna somente o nome do arquivo, retirando possiveis caminho e a sua extensão.
    
    int j = 0;
    int fullFileNameLength = strlen(fullFileName); 

    char* fileNameWithoutExtension;

    for(int i = 0; i<fullFileNameLength; ++i){  

        if(fullFileName[i] == '/'){
            j = i + 1;
        }

        if(fullFileName[i] == '.' && fullFileName[i+1] != '/'){ //corrige o erro ./dir/arq.extension
            
            fullFileName[i] = ' ';
            fileNameWithoutExtension = (char*) malloc((strlen(&fullFileName[j]) - 3) * sizeof(char));
            sscanf(&fullFileName[j],"%s", fileNameWithoutExtension);
            fullFileName[i] = '.';
            break;
        }
    }
    return fileNameWithoutExtension;
}

char* buildQryOutputPath(Parameters Param, char* extension){
    char* outputDirectory = getOutputDirectory(Param);
    int outputDirectoryLength = strlen(outputDirectory);

    char* fullGeoName = getGeoName(Param);
    char* geoNameWithoutPathAndExtension = getFileNameWithoutPathAndExtension(fullGeoName);
    
    char* fullQryName = getQryName(Param);
    char* qryNameWithoutPathAndExtension = getFileNameWithoutPathAndExtension(fullQryName);

    int qryOutputPathLength = strlen(outputDirectory) + strlen(geoNameWithoutPathAndExtension) + strlen(qryNameWithoutPathAndExtension) + strlen(".ext") + 5;
    char* qryOutputPath = (char*) malloc(qryOutputPathLength * sizeof(char));

    if(outputDirectory[outputDirectoryLength - 1] == '/'){
        sprintf(qryOutputPath, "%s%s-%s.%s", outputDirectory, geoNameWithoutPathAndExtension, qryNameWithoutPathAndExtension, extension);    
    }else{
        sprintf(qryOutputPath, "%s/%s-%s.%s", outputDirectory, geoNameWithoutPathAndExtension, qryNameWithoutPathAndExtension, extension);    
    }

    free(geoNameWithoutPathAndExtension);
    free(qryNameWithoutPathAndExtension);
    return qryOutputPath;
}

char* getUrbanElementToString(Info urbanElementInfo, char* urbanElementType){
    char* urbanElementToString = NULL;

    if(urbanElementType[0] == 'q')
        urbanElementToString = blockToString(urbanElementInfo);

    else if(urbanElementType[0] == 'h')
        urbanElementToString = hydrantToString(urbanElementInfo);
        
    else if(urbanElementType[0] == 's')
        urbanElementToString = semaphoreToString(urbanElementInfo);
        
    else if(urbanElementType[0] == 'r') 
        urbanElementToString = baseRadioToString(urbanElementInfo);
       
    return urbanElementToString;
}


//---------------------------------Convex Hull--------------------------------//

Point p0; 

double distSq(Point p1, Point p2) { 
    double p1x = getPointX(p1); double p1y = getPointY(p1);
    double p2x = getPointX(p2); double p2y = getPointY(p2);

    return (p1x - p2x)*(p1x - p2x) + 
        (p1y - p2y)*(p1y - p2y); 
} 

int orientation(Point p, Point q, Point r){ 
    
    double px = getPointX(p); double py = getPointY(p);
    double qx = getPointX(q); double qy = getPointY(q);
    double rx = getPointX(r); double ry = getPointY(r);

    double val = (qy - py) * (rx - qx) - 
            (qx - px) * (ry - qy); 

    if (((int) val) == 0) return 0;
    return (((int) val) > 0)? 1 : 2;
} 


int compare(const void *vp1,  const void *vp2) { 

    Point p1 = (Point) vp1; 
    Point p2 = (Point) vp2;

    int o = orientation(p0, p1, p2); 
    if (o == 0) 
        return (distSq(p0, p2) >= distSq(p0, p1))? -1 : 1; 

    return (o == 2)? -1: 1; 
}


Stack convexHull(Point* points, int n) { 

    int ymin = getPointY(*points), min = 0; // same as: int ymin = getPointY(points[0]), min =0;
    
    for (int i = 1; i < n; i++) { 
        int y = getPointY(*(points + i)); 

        if ((y < ymin) || (ymin == y && 
            getPointX(*(points + i)) < getPointX(*(points + min)))) 

            ymin = getPointY(*(points + i)), min = i; 
    } 

    swapInformations(points, points + min); 

    p0 = *points;
    qsort(*(points + 1), n-1, sizeof(Point), compare); 

    int m = 1; 
    for (int i=1; i<n; i++) { 
    
        while (i < n-1 && orientation(p0, *(points + i), *(points + i + 1)) == 0) 
            i++; 

        *(points + m) = *(points + i);
        m++; 
    } 

    if (m < 3) 
        return NULL; 

    Stack head = createStack();
    stackPush(&head, *(points)); 
    stackPush(&head, *(points + 1));
    stackPush(&head, *(points + 2));

    for (int i = 3; i < m; i++) { 
        while (orientation(nextToTop(&head), stackTop(&head), *(points + i)) != 2) 
            stackPop(&head); 
        
        stackPush(&head, *(points + i));
    } 

    return head;
} 
//------------------------------------------------------------------------------//