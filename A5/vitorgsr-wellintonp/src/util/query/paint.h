#ifndef PAINT_H
#define PAINT_H

/*
* Pré-Condição: requer uma referencia para a string do comando pnt?, uma referencia para uma instancia do TAD cidade, um arquivo txt e o tipo da pintura (pnt ou pnt*).
* Pós-Condição: pinta um elemento ou um conjunto de elementos de acordo com o tipo de pintura passada e as cores presentes no comando. No final escreve o resultado em um arquivo txt.
*/
void executeElementPainting(char* command, City Ct, File txt, char* paintingType);

#endif