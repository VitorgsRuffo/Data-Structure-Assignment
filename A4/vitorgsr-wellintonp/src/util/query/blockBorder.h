#ifndef BLOCK_BORDER_H
#define BLOCK_BORDER_H

/*
* Pré-Condição: requer uma referencia para a string do comando cbq, uma referencia para uma instancia do TAD desenho, um arquivo txt. 
* Pós-Condição: mudar a cor da borda de todas as quadras que estiverem inteiramente dentro do circulo especificado no comando.
*/
void executeBlocksBorderColorChanging(char* command, Drawing Dr, File txt);

#endif