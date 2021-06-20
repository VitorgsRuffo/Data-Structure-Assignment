#include "../../include/headers.h"
#include "sort.h"
#include "../tools.h"


// general compare functions -----------------------------------

int compareIntegers(Info Integer1, Info Integer2){
    int* integer1 = (int*) Integer1;    
    int* integer2 = (int*) Integer2;

    int result = 0;

    if(*integer1 > *integer2) result = 1;
    else if(*integer1 < *integer2) result = -1;

    return result;
}

int compareStrings(Info String1, Info String2){

    char* string1 = (char*) String1;    
    char* string2 = (char*) String2;

    return strcmp(string1, string2);
}

//---------------------------Shellsort-------------------------------


void shellsort(Info* array, int n, compare function){ 

    for (int gap = n/2; gap > 0; gap /= 2){ 
          
        for (int i = gap; i < n; i += 1) { 
            
            Info temp = array[i]; 

            int j;             
            for (j = i; j >= gap && (*function)(array[j - gap], temp) > 0; j -= gap) 
                array[j] = array[j - gap]; 
              
            array[j] = temp; 
        } 
    } 
}

//----------------------------Quicksort-----------------------------

int getArrayPartitionIndex(Info* array, int start, int end, compare function){
   
    Info pivot = *(array + end); 
    int partitionIndex = start;

    int compareResult;

    for(int i = start; i<end; i++){

        compareResult = (*function)(*(array + i), pivot);

        if(compareResult <= 0){                                             
            swapInformations((array + i), (array + partitionIndex));
            partitionIndex++;
        }
    }

    swapInformations((array + partitionIndex), (array + end));
    return partitionIndex;
}

void quicksort(Info* array, int start, int end, compare function){
    int partitionIndex;

    if(start < end){
        partitionIndex = getArrayPartitionIndex(array, start, end, function);
        quicksort(array, start, partitionIndex-1, function);
        quicksort(array, partitionIndex+1, end, function);
    }
}
