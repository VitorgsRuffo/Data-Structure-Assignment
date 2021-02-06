#ifndef QUEUE_H
#define QUEUE_H

#include "stack.h"

typedef void* Queue;
typedef void* Info;
typedef void (*freeInfo)(Info); 

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
    Pré-condição: requer uma instancia de fila nao vazia.
    Pós-condição: cria e retorna uma pilha contendo as mesmas informacoes que estavam na fila. 
*/
Stack queueToStack(Queue Q);

/*
    Pré-condição: requer uma instancia de fila. A passagem de uma funcao de desalocar informacao e opcional.
    Pós-condição: desaloca toda a memoria usada pela fila. Se uma funcao de desalocar for passada, as informacoes tambem sao desalocadas.
*/
void freeQueue(Queue Q, freeInfo freeFunction);

#endif