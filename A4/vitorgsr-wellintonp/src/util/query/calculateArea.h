#ifndef CALCULATE_AREA_H
#define CALCULATE_AREA_H

/*
* Pré-Condição: requer uma referencia para a string do comando dq, uma referencia para uma instancia do TAD desenho, um arquivo txt.
* Pós-Condição: calcula a area de todos os elementos urbanos que estiverem totalmente dentro do retangulo especificado no comando. Os resultados desse calculo no .svg e no .txt.
*/
void executeUrbanElementsTotalAreaCalculationInRange(char* command, Drawing Dr, File txt);


#endif