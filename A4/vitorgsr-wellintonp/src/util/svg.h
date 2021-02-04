#ifndef SVG_H
#define SVG_H


/*
*apontador para um arquivo.
*/
typedef FILE* Svg;


/*
* Pré-Condição: recebe os parametros do terminal, uma instancia do TAD Desenho e a string informando o tipo do arquivo (geo ou qry).
* Pós-Condição: retorna o endereço do arquivo SVG aberto.  
*/
Svg createSvg(Parameters Param, Drawing Dr, char* fileType);

/*
* Pré-Condição: requer uma referencia para uma arquivo e uma instancia do TAD Desenho.
* Pós-Condição: desenha no arquivo, no formato de tag svg, os elementos presentes nas listas do TAD desenho.
*/
void drawOnSvg(Svg svg, Drawing Dr);

/*
* Pré-Condição: requer um ponteiro para o arquivo svg aberto
* Pós-Condição: insere a tag de fechamento do arquivo svg.
*/
void finishSvg(Svg svg);

#endif