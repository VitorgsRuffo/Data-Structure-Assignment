#ifndef BASE_RADIO_H
#define BASE_RADIO_H

/*
*   Tipo abstrato de dado que representa o elemento urbano radio-base.
*/
typedef void* BaseRadio;

/*  
* Pré-Condição: requer os dados (strings) que compoem uma radio-base.
* Pós-Condição: retorna o endereco de uma nova instancia de radio-base que possui as informacoes passadas.
*/
BaseRadio createBaseRadio(char* id, char* x, char* y, char* sw, char* cfill, char* cstrk);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna o id da radio-base passada.
*/
char* getBaseRadioId(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna a coordenada x da radio-base passada.
*/
char* getBaseRadioX(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna a coordenada y da radio-base passada.
*/
char* getBaseRadioY(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna o raio da radio-base passada.
*/
char* getBaseRadioRadius(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna a espessura da borda da radio-base passada.
*/
char* getBaseRadioSw(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de base radio e uma espessura.
* Pós-Condição: atribui a espessura passada a borda da base radio.
*/
void setBaseRadioSw(BaseRadio BaseR, char* sw);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna a cor de preenchimento da radio-base passada.
*/
char* getBaseRadioCfill(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna a cor da borda da radio-base passada.
*/
char* getBaseRadioCstrk(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: retorna o valor da area da radio-base.
*/
double getBaseRadioArea(BaseRadio BaseR);

/*
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
char* baseRadioToString(BaseRadio BaseR);

/*
* Pré-Condição: requer o endereco de uma instancia de base de radio.
* Pós-Condição: imprimir na saida padrão essa variavel.
*/
void printBaseRadio(BaseRadio BaseR);

/*  
* Pré-Condição: requer o endereco de uma instancia de radio-base.
* Pós-Condição: libera a memoria usada pela instancia de radio-base que foi passada.
*/
void freeBaseRadio(BaseRadio BaseR);

#endif