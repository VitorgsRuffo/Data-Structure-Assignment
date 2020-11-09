#ifndef COVID_INCIDENCE_H
#define COVID_INCIDENCE_H

/*
* Pré-Condição: requer uma referencia para a string do comando ci, uma referencia para uma instancia do TAD desenho e um arquivo txt.
* Pós-Condição: Determina a região de incidência relativa aos casos (comando cv) reportados dentro da região delimitada pela circunferência 
                de cento em (x,y) e raio r. Determina a categoria da região. Se necessário sugere um posto de atendimento no centróide da região. 
*/
void executeCovidIncidenceReportInRegion(char* command, Drawing Dr, File txt);

#endif