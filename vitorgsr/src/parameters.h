#ifndef PARAMETERS_H
#define PARAMETERS_H

struct parameter{
    char* inputDir;
    char* geoFileName;
    char* qryFileName;
    char* outputDir;

    char* geoFullPath;
    char* qryFullPath;
    char* svgFullPath;
    char* svgQryFullPath;
};

typedef struct parameter Parameter;



void deal_with_parameters(int paraNum, char* parameters[], Parameter *parameter);



#endif