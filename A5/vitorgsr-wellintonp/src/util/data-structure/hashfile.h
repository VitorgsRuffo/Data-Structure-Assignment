#ifndef HASHFILE_H
#define HASHFILE_H

#include <stdio.h>

typedef void* Hashfile;
typedef void* Record;
typedef char* (*getKey)(Record);
typedef char* (*recordToString)(Record);

/*
* Cria um arquivo binario em "path" que segue a organização hash. O arquivo é organizado em "buckets" blocos chamados de bucket.
* Em cada bucket pode ser armazenado até "recordsPerBucket" registros. O tamanho de um registro é "recordSize" bytes.
* É necessario fornecer uma funcao que dado um registro retorna a sua chave.
*/
Hashfile createHashFile(char* path, int buckets, int recordsPerBucket, int recordSize, getKey get);

/*
* Abre um arquivo hash existente para leitura e escrita.
* Retorna NULL se nao for possivel abri-lo (provavelmente porque não existe ou está protegido contra escrita).
*/
Hashfile openHashFile(char* path);

/*
* Escreve o registro, cuja chave é "key" e esta armazenado em "rec", no arquivo.
* O tamanho do registro deve ser aquele especificado na criação do arquivo hash.
* Retorna 0 se a escrita falhar, se nao retorna 1.
*/
int writeHashFile(Hashfile* Hf, char* key, Record rec);

/*
* Le o registro, cuja chave é "key", do arquivo e armazena no buffer "rec".
* O tamanho do buffer deve ser aquele especificado na criação do arquivo hash.
* Retorna 0 se a leitura falhar, se nao retorna 1.
*/
int readHashFile(Hashfile Hf, char* key, Record rec);

/*
* Atualiza o registro, cuja chave é "key", com os conteudos de "rec".
* O tamanho do registro "rec" deve ser aquele especificado na criação do arquivo hash.
* Retorna 0 se a atualizacao falhar, se nao retorna 1.
*/
int updateHashFile(Hashfile* Hf, char* key, Record rec);

/*
* Remove o registro, cuja chave é "key", do arquivo e armazena no buffer "rec".
* O tamanho do buffer deve ser aquele especificado na criação do arquivo hash.
* Se um buffer nao for passado (isto e, rec == NULL) o registro removido nao e armazenado.
* Retorna 0 se a remocao falhar, se nao retorna 1.
*/
int removeHashFile(Hashfile Hf, char* key, Record rec);

/*
* Imprime no arquivo de texto "dumpName" uma representação da organização e conteudo do arquivo hash "Hf".
* É necessario fornecer uma funcao (function) que retorna uma string que representa um registro.
*/
void dumpHashFile(Hashfile Hf, recordToString function, char* dumpName);

/*
*  Fecha o arquivo hash "Hf". Se keep == 1 o arquivo permanece armazenado em disco, se nao ele e apagado.
*/
void closeHashFile(Hashfile Hf, int keep);

#endif