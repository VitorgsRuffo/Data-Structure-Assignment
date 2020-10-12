#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"
#include "../drawing/drawing.h"
#include "../include/query.h"

void executeCovidCasesReport(char* command, Drawing Dr){
    if(isElementNull(Dr, "drawing", "executeCovidCasesReport"))
        return;

    /* to do list:

        - interpret the command. (create TAD address)

        - get block node (searchForUrbanElementByIdentifier)
        - get block list
        - get block info ( + get each attribute and assign to a block struct)

        - create house info struct

        - call function that will calculate the house attributes based on the side of the block.
                -if side == N
                    call function that will calculate the house attributes on side N.
                
                -if side == S
                    ...

        - create house tag

        - get query elements list

        - insert
    */
}