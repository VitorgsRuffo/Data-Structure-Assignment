#ifndef QUEUE_H
#define QUEUE_H

typedef void* Queue;
typedef void* Info;

/*

*/

/*
    Pré-condição: nenhuma.
    Pós-condição: cria e retorna uma fila vazia.
*/
Queue createQueue();

/*
    Pré-condição: requer uma instancia de fila.
    Pós-condição: retorna 1 se a fila estiver vazia, se nao, retorna 0.
*/
int isQueueEmpty(Queue Q);

/*
    Pré-condição: requer uma instancia de fila.
    Pós-condição: insere o elemento passado no final da fila e retorna 1. Se a insercao falhar retorna 0. 
*/
int queuePush(Queue Q, Info info);

/*
    Pré-condição: requer uma instancia de fila nao vazia.
    Pós-condição: remove o elemento na frente da fila e o retorna. 
*/
Info queuePop(Queue Q); 

/*
    Pré-condição: requer uma instancia de fila.
    Pós-condição: desaloca toda a memoria usada pela fila.
*/
void freeQueue(Queue Q);

#endif