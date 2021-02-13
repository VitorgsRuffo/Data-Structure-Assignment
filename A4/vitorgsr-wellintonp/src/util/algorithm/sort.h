#ifndef SORT_H
#define SORT_H

/*
    Info é um ponteiro para qualquer tipo de informacao.
*/
typedef void* Info;

/*
Function pointer para uma funcao que compara duas informacoes:
    - retorna positivo se a primeira for maior;
    - retorna 0 se as informacoes forem iguais;
    - retorna negativo se a primeira for menor.
*/
typedef int (*compare)(Info, Info);


// Funcao de comparacao de inteiros. Ela pode ser apontada por function pointers do tipo compare.
int compareIntegers(Info Integer1, Info Integer2);

// Funcao de comparacao de strings. Ela pode ser apontada por function pointers do tipo compare.
int compareStrings(Info String1, Info String2);

/*
    Pré condição: requer um array de informações, o tamanho desse array e uma função de comparação dos elementos do array.
    Pós condição: Ordena o array. 
*/
void shellsort(Info* array, int n, compare function);

/*
    Pré condição: requer um array de informações, o indice do primeiro elemento e ultimo e uma função de comparação dos elementos do array.
    Pós condição: Ordena o array. 
*/
void quicksort(Info* array, int start, int end, compare function);

#endif