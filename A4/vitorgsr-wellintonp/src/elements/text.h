#ifndef TEXT_H
#define TEXT_H

/*
* Tipo abstrato de dados que representa um texto.
*/
typedef void* Text;

/*
* Pré-Condição: requer os dados (strings) que compoem um Texto.
* Pós-Condição: retorna o endereco de uma nova instancia de Texto que possui as informacoes passadas.
*/
Text createText(char* id, char* x, char* y, char* corb, char* corp, char* textContent);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto.
* Pós-Condição: retorna o id do texto passado.
*/
char* getTextId(Text Txt);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto.
* Pós-Condição: retorna o x do texto passado.
*/
char* getTextX(Text Txt);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto.
* Pós-Condição: retorna o y do texto passado.
*/
char* getTextY(Text Txt);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto.
* Pós-Condição: retorna uma instancia de ponto que representa a localizacao desse texto.
*/
Point getTextCoordinates(Text Txt);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto.
* Pós-Condição: retorna a corb do texto passado.
*/
char* getTextCorb(Text Txt);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto e uma cor.
* Pós-Condição: atribui a cor passada á cor de borda do texto.
*/
void setTextCorb(Text Txt, char* corb);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto.
* Pós-Condição: retorna a corp do texto passado.
*/
char* getTextCorp(Text Txt);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto e uma cor.
* Pós-Condição: atribui a cor passada á cor de preenchimento do texto.
*/
void setTextCorp(Text Txt, char* corb);

/*  
* Pré-Condição: requer o endereco de uma instancia de texto.
* Pós-Condição: retorna o conteudo de texto da intancia de texto passado.
*/
char* getTextContent(Text Txt);

/*  
* Pré-Condição: requer o endereco de uma instancia de Texto.
* Pós-Condição: retorna uma string com todas as informacoes da instancia de Texto passada.
*/
char* textToString(Text Txt);

/*
* Pré-Condição: requer o endereco de uma instancia de Texto.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printText(Text Txt);

/*
* Pré-Condição: requer o endereco de uma instancia de Texto.
* Pós-Condição: libera a memoria usada pela instancia de Texto que foi passada.
*/
void freeText(Text Txt);

#endif