#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct queueNode {
    Info info;
    struct queueNode *prox;
}queueNode;

typedef struct {
    queueNode *first;
    queueNode *last;
}queue;


Queue createQueue(){
    queue *q = (queue*) malloc(sizeof(queue));

    (*q).first = NULL;
    (*q).last = NULL;

    return q;
}


int isQueueEmpty(Queue Q){
    
    queue* q = (queue*) Q;

    if((*q).first == NULL)
        return 1;
    else 
        return 0;
}


int queuePush(Queue Q, Info info){

    if(Q == NULL || info == NULL)
        return 0;

    queue* q = (queue*) Q;
    
    queueNode* newNode = (queueNode*) malloc(sizeof(queueNode));
    if(newNode == NULL)
        return 0;

    newNode->info = info;
    newNode->prox = NULL;
    
    if(q->first == NULL){ //insercao em fila vazia

        q->first = newNode;
        q->last = newNode;

    }else{

        queueNode* lastNode = q->last;
        lastNode->prox = newNode;  
        q->last = newNode;
    }

    return 1; //insercao bem sucedida
}


Info queuePop(Queue Q){

    if(Q == NULL)
        return NULL;

    queue* q = (queue*) Q;
    Info info;

    if(q->first == NULL) //if(lista_vazia)
        return NULL;

    if(q->first == q->last){//if(lista tem apenas um nó)

        queueNode* node = q->first;
        info = node->info;
        free(node);
        q->first = NULL;
        q->last = NULL;

    }else{ //if(lista tem um ou mais nós)

        queueNode* firstNode = q->first;
        info = firstNode->info;

        q->first = firstNode->prox;
        free(firstNode);
    }

    return info;
}


void freeQueue(Queue Q){

    if(Q == NULL)
        return;

    queue* q = (queue*) Q;

    queueNode* firstNode = q->first;

    while(firstNode != NULL){

        q->first = q->first->prox;
        free(firstNode);
        firstNode = q->first;
    }

    free(q);
}