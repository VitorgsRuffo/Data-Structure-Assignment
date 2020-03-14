#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parameters.h"


int main (int argc, char* argv[]){

    Parameter parameter;
    

    deal_with_parameters(argc, argv, &parameter);

    return 0;
}

