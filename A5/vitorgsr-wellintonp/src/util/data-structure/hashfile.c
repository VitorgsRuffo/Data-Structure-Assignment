#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfile.h"

/* Esta implementação utiliza uma organizacao estatica para o arquivo hash: 
*  
*   Cabeçalho:
*       name
*       totalBuckets
*       buckets 
*       recordsPerBucket 
*       recordSize
*       get 
*       bucketsOffset
*       bucketSize
*   Diretorio: (endereço dos buckets)
*       offset0
*       offset1
*       offset2
*       ...
*   Buckets:
*       bucket0
*       bucket1
*       bucket2
*       ...
*   buckets de Overflow:
*       bucketOverflow0[0]
*       bucketOverflow2[0]
*       bucketOverflow1[0]
*       bucketOverflow2[1]
*       bucketOverflow0[1]
*       ...
* 
*/

typedef struct {
    int storedRecords;         // Quantidade de registros armazenados.
    int overflowBucketOffset;  // Offset do inicio do arquivo para o bucket de overflow.
    unsigned char records[];   // Bloco de bytes que armazena os registros.
}bucket;

typedef struct {
    char name[100];            // nome do arquivo
    int totalBuckets;          // buckets iniciais + buckets de overflow.
    int buckets;
    int totalRecords;          // quantidade de registros inseridos no arquivo.
    int recordsPerBucket;
    int recordSize;
    getKey get;                // funcao de obter a chave de um registro.
    int bucketsOffset;         // sizeof(cabeçalho) + sizeof(diretorio): Representa o offset em bytes para o primeiro bucket.
    int bucketSize;            // Total de bytes que um bucket ocupa.
}Header;

typedef struct {
    FILE* file;
    Header header;                 // copia do header do arquivo mantida na memoria principal. Desta forma não é necessario acessar o disco quando uma operacao precisar dessas informacoes (como o corre, por exemplo, no inicio da funcao writeHashFile).  É claro que caso o cabeçalho, armazenado na memoria principal, atualize devemos escrever essa nova versao no arquivo armazenado no disco.
    int directory[];               // copia do diretorio do arquivo mantida na memoria principal.
}hashfile;

int hashFunction(char* key, int hashStructureSize);
void reorganizeHashFile(hashfile** hf);

Hashfile createHashFile(char* path, int buckets, int recordsPerBucket, int recordSize, getKey get){
    
    if(buckets <= 0 || recordsPerBucket <= 0 || recordSize <= 0 || get == NULL)
        return NULL;

    hashfile* hf = (hashfile*) malloc(sizeof(hashfile) + sizeof(int[buckets]));
    if(hf == NULL) return NULL;

    hf->file = fopen(path, "wb+");
    if(hf->file == NULL){
        free(hf);
        return NULL;
    }

    //Escrevendo o cabeçalho do arquivo:
    strcpy(hf->header.name, path);
    hf->header.totalBuckets = buckets;
    hf->header.buckets = buckets;
    hf->header.totalRecords = 0;
    hf->header.recordsPerBucket = recordsPerBucket;
    hf->header.recordSize = recordSize;
    hf->header.get = get;
    hf->header.bucketsOffset = sizeof(Header) + sizeof(int[buckets]); 
    hf->header.bucketSize = sizeof(bucket) + 
                            sizeof(unsigned char [recordsPerBucket * recordSize]);  

    fwrite(&(hf->header), sizeof(Header), 1, hf->file);


    //Escrevendo o diretorio do arquivo: o diretorio é um vetor de inteiros. O i-ésimo inteiro representa o offset em bytes do i-ésimo bucket a partir do inicio do arquivo.

    for(int i = 0; i<buckets; i++){
        
        int bucketAddress = hf->header.bucketsOffset + ( i * hf->header.bucketSize ); 
        
        hf->directory[i] = bucketAddress;
        fwrite(&bucketAddress, sizeof(int), 1, hf->file);
    }


    //Escrevendo os buckets do arquivo:

    bucket* buc = (bucket*) malloc(hf->header.bucketSize);
    buc->storedRecords = 0;
    buc->overflowBucketOffset = -1;

    for(int i = 0; i<buckets; i++)
        fwrite(buc, hf->header.bucketSize, 1, hf->file);
    
    free(buc);

    return hf;
}

Hashfile openHashFile(char* path){
    
    FILE* file = fopen(path, "rb+");
    if(file == NULL) return NULL;
    
    Header header;
    fread(&header, sizeof(Header), 1, file);

    hashfile* hf = (hashfile*) malloc(sizeof(hashfile) + sizeof(int[header.buckets]));
    if(hf == NULL){
        fclose(file);
        return NULL;
    }
    hf->file = file;
    hf->header = header;
    fread(hf->directory, sizeof(int), header.buckets, file);

    fseek(file, 0, SEEK_SET);
    return hf;
}

// Sempre que o cabeçalho em memoria atualizar devemos atualizar o cabeçalho em disco.
void updateFileHeader(hashfile* hf){
    fseek(hf->file, 0, SEEK_SET);
    fwrite(&hf->header, sizeof(Header), 1, hf->file);
}

int writeHashFile(Hashfile* Hf, char* key, Record rec){
    if(Hf == NULL || key == NULL || rec == NULL) return 0;
    if(*Hf == NULL) return 0;

    hashfile** hf = (hashfile**) Hf;

    int overflowBuckets = (*hf)->header.totalBuckets - (*hf)->header.buckets;
    int seventyPercentOfInitialBuckets = 0.7 * (*hf)->header.buckets;

    if(overflowBuckets >= seventyPercentOfInitialBuckets) //se a quantidade de buckets de overflow for superior a 70% dos buckets iniciais, o arquivo vai ser reorganizado.
        reorganizeHashFile(hf);
    

    int bucketIndex = hashFunction(key, (*hf)->header.buckets);
    int bucketOffset = (*hf)->directory[bucketIndex]; //int bucketOffset = hd.bucketsOffset + (bucketIndex * hd.bucketSize);

    fseek((*hf)->file, bucketOffset, SEEK_SET);

    //Lendo o bucket que sera manipulado:
    bucket buc;
    fread(&buc, (*hf)->header.bucketSize, 1, (*hf)->file);

    while(1){
        if(buc.storedRecords >= (*hf)->header.recordsPerBucket){ //se o bucket atual estiver cheio

            if(buc.overflowBucketOffset != -1){//existe um bucket de overflow
                //Lendo o bucket de overflow
                bucketOffset = buc.overflowBucketOffset;
                fseek((*hf)->file, bucketOffset, SEEK_SET);
                fread(&buc, (*hf)->header.bucketSize, 1, (*hf)->file);
                continue;

            }else{ //se nao existe um bucket de overflow

                //Armazenando o registro em um novo bucket de overflow:
                bucket* overflow = (bucket*) malloc((*hf)->header.bucketSize);
                overflow->storedRecords = 1;
                overflow->overflowBucketOffset = -1;
                memcpy(overflow->records, rec, (*hf)->header.recordSize);

                //Escrevendo o bucket de overflow no final do arquivo:
                fseek((*hf)->file, 0, SEEK_END);
                int overflowBucketOffset = ftell((*hf)->file);
                fwrite(overflow, (*hf)->header.bucketSize, 1, (*hf)->file);

                //Ligando o bucket atual ao novo bucket de overflow:
                buc.overflowBucketOffset = overflowBucketOffset;
                fseek((*hf)->file, bucketOffset, SEEK_SET);
                fwrite(&buc, (*hf)->header.bucketSize, 1, (*hf)->file);
                
                //Atualizando o cabeçalho com a nova quantidade total de buckets e de registros:
                (*hf)->header.totalBuckets++;
                (*hf)->header.totalRecords++;
                updateFileHeader(*hf);

                break;
            }

            
        }else{//se o bucket atual nao estiver cheio

            memcpy(&buc.records[buc.storedRecords * (*hf)->header.recordSize], rec, (*hf)->header.recordSize);
            buc.storedRecords++;

            fseek((*hf)->file, bucketOffset, SEEK_SET);
            fwrite(&buc, (*hf)->header.bucketSize, 1, (*hf)->file);

            //Atualizando o cabeçalho com a nova quantidade total de registros:
            (*hf)->header.totalRecords++;
            updateFileHeader(*hf);

            break;
        }
    }

    return 1;
}

int readHashFile(Hashfile Hf, char* key, Record rec){
    if(Hf == NULL || key == NULL || rec == NULL) return 0;

    hashfile* hf = (hashfile*) Hf;

    int bucketIndex = hashFunction(key, hf->header.buckets);
    int bucketOffset = hf->directory[bucketIndex]; //int bucketOffset = hd.bucketsOffset + (bucketIndex * hd.bucketSize);

    fseek(hf->file, bucketOffset, SEEK_SET);

    //Lendo o bucket que (possivelmente) contem o registro:
    bucket buc;
    fread(&buc, hf->header.bucketSize, 1, hf->file);

    Record currentRecord = malloc(hf->header.recordSize);

    while(1){

        for(int i = 0; i<hf->header.recordsPerBucket; i++){
            
            memcpy(currentRecord, 
                   &buc.records[i * hf->header.recordSize], 
                   hf->header.recordSize);

            char* currentKey = (*(hf->header.get))(currentRecord);
            
            if(strcmp(currentKey, key) == 0){ //registro encontrado.
                memcpy(rec, currentRecord, hf->header.recordSize);
                free(currentRecord);
                return 1;
            }
        }

        
        if(buc.overflowBucketOffset == -1){ //o registro nao foi encontrado no bucket atual e não existem mais buckets na cadeia, portanto, o registro nao existe.
            free(currentRecord);
            return 0;
        }

        //a busca continua no proximo bucket da cadeia...    
        bucketOffset = buc.overflowBucketOffset;
        fseek(hf->file, bucketOffset, SEEK_SET);
        fread(&buc, hf->header.bucketSize, 1, hf->file);
    }

    return 0;
}

int updateHashFile(Hashfile* Hf, char* key, Record rec){
    return 0;
}

int removeHashFile(Hashfile Hf, char* key, Record rec){
    return 0;
}

void dumpHashFile(Hashfile Hf, recordToString function, char* dumpName){
    if(Hf == NULL || function == NULL || dumpName == NULL) return;
    
    FILE* dump = fopen(dumpName, "a");
    if(dump == NULL) return;

    hashfile* hf = (hashfile*) Hf;

    fprintf(dump, "--------------------------------------------------C A B E Ç A L H O--------------------------------------------------\n\n");
    fprintf(dump, "\ttotalBuckets: %d | buckets: %d | recordsPerBucket: %d | recordSize: %d | bucketsOffset: %d | bucketSize: %d\n\n", 
                  hf->header.totalBuckets, hf->header.buckets, hf->header.recordsPerBucket, hf->header.recordSize, hf->header.bucketsOffset, hf->header.bucketSize);

    fprintf(dump, "--------------------------------------------------D I R E T O R I O--------------------------------------------------\n\n");

    for(int i = 0; i<hf->header.buckets; i++)
        fprintf(dump, "[bucket %d] -> %d\n", i, hf->directory[i]);
    

    fprintf(dump, "\n--------------------------------------------------B U C K E T S--------------------------------------------------\n");
    Record record = malloc(hf->header.recordSize);

    fseek(hf->file, hf->header.bucketsOffset, SEEK_SET);

    for(int i = 0; i<hf->header.totalBuckets; i++){
        
        bucket buc;
        int bucketOffset = ftell(hf->file);
        fread(&buc, hf->header.bucketSize, 1, hf->file);

        if(i < hf->header.buckets)  // imprimindo buckets iniciais 
            fprintf(dump, "\n(offset: %d) BUCKET [%d]:\n", bucketOffset, i);

        else                // imprimindo buckets de overflow
            fprintf(dump, "\n(offset: %d) OVERFLOW BUCKET [%d]:\n", bucketOffset, i);

        fprintf(dump, "\tstoredRecords: %d.\n\toverflowBucketOffset: %d.\n\tRecords:\n", 
                       buc.storedRecords, buc.overflowBucketOffset);
        
        for(int j = 0; j<hf->header.recordsPerBucket; j++){
            
            if(j < buc.storedRecords){
                memcpy(record, 
                    &buc.records[j * hf->header.recordSize], 
                    hf->header.recordSize);

                char* recordString = (*function)(record);
                fprintf(dump, "\t%s.\n", recordString);
                free(recordString);
            }else{
                fprintf(dump, "\tEspaço livre.\n");
            }
        }
    }
    free(record);
    fprintf(dump, "\n-----------------------------------------------------------------------------------------------------------------");
}

void closeHashFile(Hashfile Hf, int keep){
    
    if(Hf == NULL) return;
    hashfile* hf = (hashfile*) Hf;

    fclose(hf->file);
    if(!keep) //se o usuario nao deseja manter o arquivo em disco
        remove(hf->header.name);
    free(hf);
}

//funcoes privadas auxiliares:

/*
*   Re-cria o arquivo alocando buckets suficientes para todos os registros ja armazenados, alem de deixar um espaço livre de 20%.
*/
void reorganizeHashFile(hashfile** hf){
    
    hashfile* oldHf = *hf;

    //extraindo os registros do arquivo antigo:
    int totalRecords = oldHf->header.totalRecords;
    int maximumAmountOfBytes = oldHf->header.totalBuckets * oldHf->header.recordsPerBucket * oldHf->header.recordSize;
    unsigned char records[maximumAmountOfBytes];
    
    int recordSize = oldHf->header.recordSize;

    fseek(oldHf->file, oldHf->header.bucketsOffset, SEEK_SET);
    bucket buc;

    int recordsOffset = 0;

    while(fread(&buc, oldHf->header.bucketSize, 1, oldHf->file) == 1){
    
        memcpy(records+recordsOffset, buc.records, buc.storedRecords*recordSize);
        recordsOffset += buc.storedRecords*recordSize;
    }

    //criando arquivo novo e escrevendo os registros nele:
    int newBuckets = oldHf->header.totalBuckets * 1.20;
    hashfile* newHf = (hashfile*) createHashFile(oldHf->header.name, newBuckets, oldHf->header.recordsPerBucket, oldHf->header.recordSize, oldHf->header.get);
    if(newHf == NULL) return;

    Record record = malloc(recordSize);

    for(int i = 0; i<totalRecords; i++){
        
        memcpy(record, &records[i * recordSize], recordSize);
        char* key = (*(newHf->header.get))(record);
        writeHashFile((Hashfile*) &newHf, key, record);
    }

    free(record);
    free(oldHf);
    *hf = newHf;
}

int hashFunction(char* key, int hashStructureSize){

    if(hashStructureSize == 0 || key == NULL) return -1;

    unsigned long hash = 5381;
    int c;

    while((c = *key++))
        hash = ((hash << 5) + hash) + c;

    return (hash % hashStructureSize);
}