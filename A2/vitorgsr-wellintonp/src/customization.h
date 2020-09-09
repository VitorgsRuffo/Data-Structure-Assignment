#ifndef CUSTOMIZATION_H
#define CUSTOMIZATION_H

/*
*   Tipo abstrato de dados que representa as customizacoes (espessura da borda, cor de preenchimento e cor de borda) dos elementos que serao desenhados no .svg
*/
typedef void* ElementsCustomization;

/*  
* Pré-Condição: nenhuma.
* Pós-Condição: retorna o endereco de uma nova instancia do TAD Customizacao de Elementos.
*/
ElementsCustomization createElementsCustomization();

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna o valor da espessura da borda das quadras.
*/
char* getBlockSwCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor de prenchimento das quadras.
*/
char* getBlockCfillCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor da borda das quadras.
*/
char* getBlockCstrkCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna o valor da espessura da borda dos hidrantes.
*/
char* getHydrantSwCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor de prenchimento dos hidrantes.
*/
char* getHydrantCfillCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor da borda dos hidrantes.
*/
char* getHydrantCstrkCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna o valor da espessura da borda das radio-bases.
*/
char* getBaseRadioSwCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor de prenchimento das radio-bases.
*/
char* getBaseRadioCfillCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor da borda das radio-bases.
*/
char* getBaseRadioCstrkCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna o valor da espessura da borda dos semaforos.
*/
char* getSemaphoreSwCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor de prenchimento dos semaforos.
*/
char* getSemaphoreCfillCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna a cor da borda dos semaforos.
*/
char* getSemaphoreCstrkCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna o valor da espessura da borda dos retangulos.
*/
char* getFiguresCwCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos.
* Pós-Condição: retorna o valor da espessura da borda dos circulos.
*/
char* getFiguresRwCustomization(ElementsCustomization Custom);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e um valor de espessura de borda.
* Pós-Condição: mudar o valor da espessura da borda de quadras para o valor passado.
*/
void setBlockSwCustomization(ElementsCustomization Custom, char* sw);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor.
* Pós-Condição: mudar a cor do preenchimento de quadras para a cor passada. 
*/
void setBlockCfillCustomization(ElementsCustomization Custom, char* cfill);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor..
* Pós-Condição: mudar a cor da borda de quadras para a cor passada.
*/
void setBlockCstrkCustomization(ElementsCustomization Custom, char* cstrk);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma valor de espessura de borda.
* Pós-Condição: mudar o valor da espessura da borda de radio-bases.
*/
void setBaseRadioSwCustomization(ElementsCustomization Custom, char* sw);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor.
* Pós-Condição: mudar a cor do preenchimento de radio-bases para a cor passada. 
*/
void setBaseRadioCfillCustomization(ElementsCustomization Custom, char* cfill);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor.
* Pós-Condição: mudar a cor da borda de radio-bases para a cor passada.
*/
void setBaseRadioCstrkCustomization(ElementsCustomization Custom, char* cstrk);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e um valor de espessura de borda.
* Pós-Condição: mudar o valor da espessura da borda de hidrante para o valor passado.
*/
void setHydrantSwCustomization(ElementsCustomization Custom, char* sw);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor.
* Pós-Condição: mudar a cor do preenchimento de hidrantes para a cor passada. 
*/
void setHydrantCfillCustomization(ElementsCustomization Custom, char* cfill);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor.
* Pós-Condição: mudar a cor da borda de hidrantes para a cor passada.
*/
void setHydrantCstrkCustomization(ElementsCustomization Custom, char* cstrk);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e um valor de espessura de borda.
* Pós-Condição: mudar o valor da espessura da borda de semaforo para o valor passado.
*/
void setSemaphoreSwCustomization(ElementsCustomization Custom, char* sw);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor.
* Pós-Condição: mudar a cor do preenchimento de semaforo para a cor passada. 
*/
void setSemaphoreCfillCustomization(ElementsCustomization Custom, char* cfill);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e uma cor.
* Pós-Condição: mudar a cor da borda de semaforos para a cor passada.
*/
void setSemaphoreCstrkCustomization(ElementsCustomization Custom, char* cstrk);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e um valor de espessura de borda.
* Pós-Condição: mudar o valor da espessura da borda de circulos para o valor passado.
*/
void setFiguresCwCustomization(ElementsCustomization Custom, char* cw);

/*  
* Pré-Condição: requer uma instancia do TAD Customizacao de Elementos e um valor de espessura de borda.
* Pós-Condição: mudar o valor da espessura da borda de retangulos para o valor passado.
*/
void setFiguresRwCustomization(ElementsCustomization Custom, char* rw);


/*  
* Pré-Condição: requer o endereco de uma instancia de Customizacao de Elementos.
* Pós-Condição: libera a memoria usada pela instancia de Customizacao de Elementos que foi passada.
*/
void freeElementsCustomization(ElementsCustomization Custom);
 
#endif