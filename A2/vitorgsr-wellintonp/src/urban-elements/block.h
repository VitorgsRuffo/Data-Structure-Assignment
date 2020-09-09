#ifndef BLOCK_H
#define BLOCK_H

/*
*   Tipo abstrato de dado que representa o elemento urbano quadra.
*/
typedef void* Block;


/*  
* Pré-Condição: requer os dados (strings) que compoem uma quadra.
* Pós-Condição: retorna o endereco de uma nova instancia de quadra que possui as informacoes passadas.
*/
Block createBlock(char* cep, char* x, char* y, char* w, char* h, char* sw, char* cfill, char* cstrk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna o cep da quadra passada.
*/
char* getBlockCep(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna a cordenada x da quadra passada.
*/
char* getBlockX(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna a coordenada y da quadra passada.
*/
char* getBlockY(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna a largura da quadra passada.
*/
char* getBlockWidth(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna a altura da quadra passada.
*/
char* getBlockHeight(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna a espessura da borda da quadra passada.
*/
char* getBlockSw(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna a cor de preenchimento da quadra passada.
*/
char* getBlockCfill(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra e uma cor de preenchimento.
* Pós-Condição: preenche o fundo da quadra com a cor passada.
*/
void setBlockCfill(Block Blk, char* cfill);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna a cor da borda da quadra passada.
*/
char* getBlockCstrk(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra e uma cor para a borda.
* Pós-Condição: preenche a cor da borda da quadra com a cor passada.
*/
void setBlockCstrk(Block Blk, char* cstrk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna o valor de arredondamento das bordas da quadra.
*/
char* getBlockRx(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra e um grau de arredondamento de borda.
* Pós-Condição: arredonda a borda da quadra passada.
*/
void setBlockRx(Block Blk, char* rx);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: retorna o valor da area da quadra.
*/
double getBlockArea(Block Blk);

/*
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
char* blockToString(Block Blk);

/*
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printBlock(Block Blk);

/*  
* Pré-Condição: requer o endereco de uma instancia de quadra.
* Pós-Condição: libera a memoria usada pela instancia de quadra que foi passada.
*/
void freeBlock(Block Blk);


#endif