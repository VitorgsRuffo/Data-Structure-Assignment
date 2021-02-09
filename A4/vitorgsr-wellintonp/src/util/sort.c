#include "../include/headers.h"
#include "sort.h"


int compareIntegers(Info Integer1, Info Integer2){
    int* integer1 = (int*) Integer1;    
    int* integer2 = (int*) integer2;

    int result = 0;

    if(integer1 > integer2) result = 1;
    else if(integer1 < integer2) result = -1;

    return result;
}

int compareStrings(Info String1, Info String2){

    char* string1 = (char*) String1;    
    char* string2 = (char*) String2;

    return strcmp(string1, string2);
}

void shellsort(Info* arr, int n, compare function){ 

    for (int gap = n/2; gap > 0; gap /= 2){ 
          
        for (int i = gap; i < n; i += 1) { 
            
            Info temp = arr[i]; 
  
            int j;             
            for (j = i; j >= gap && (*function)(arr[j - gap], temp) > 0; j -= gap) 
                arr[j] = arr[j - gap]; 
              
            arr[j] = temp; 
        } 
    } 
}