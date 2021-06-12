#ifndef MEDICAL_TREATMENT_H
#define MEDICAL_TREATMENT_H

/*
* Pré-Condição: requer uma referencia para a string do comando soc, uma referencia para uma instancia do TAD cidade e um arquivo txt.
* Pós-Condição: Procura os K postos mais proximos de um certo endereço, traça um segmento de reta do endereço até os postos e destaca o endereço. 
*/
void executeMedicalTreatmentSearching(char* command, City Ct, File txt, int pathId);


#endif