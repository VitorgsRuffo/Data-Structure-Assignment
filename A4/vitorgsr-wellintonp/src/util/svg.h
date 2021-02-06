#ifndef SVG_H
#define SVG_H


/*
*apontador para um arquivo.
*/
typedef FILE* Svg;


/*
* Pré-Condição: recebe os parametros do terminal, uma instancia do TAD cidade e a string informando o tipo do arquivo (geo ou qry).
* Pós-Condição: retorna o endereço do arquivo SVG aberto.  
*/
Svg createSvg(Parameters Param, City Ct, char* fileType);

/*
* Pré-Condição: requer uma referencia para uma arquivo e uma instancia do TAD cidade.
* Pós-Condição: desenha no arquivo, no formato de tag svg, os elementos presentes nas estruturas do TAD cidade.
*/
int drawOnSvg(Svg svg, City Ct);

/*
* Pré-Condição: requer um ponteiro para o arquivo svg aberto
* Pós-Condição: insere a tag de fechamento do arquivo svg.
*/
void finishSvg(Svg svg);

#endif