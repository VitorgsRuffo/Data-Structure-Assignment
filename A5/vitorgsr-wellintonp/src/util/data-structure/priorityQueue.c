#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "priorityQueue.h"
#include "hashtable.h"


typedef struct {
    int size;
    int capacity;
    HashTable keyIndexTable; //tabela que mapeia as chaves dos informacoes da heap para os seus indices no vetor que representa a heap.
    Info* binaryHeap;
    getInfoPriority getPriority; 
    getInfoKey getKey;
}priorityQueue;

typedef struct {
    char id[50]; //chave (id) que distingue diferentes infos da heap.
    int index;   //indice da info no array que representa a heap.
}keyIndex;
typedef void* KeyIndex;
char* getKeyIndexKey(KeyIndex KI);
void updateKeyIndexTableAfterSwappingElements(priorityQueue* pqueue, char* key1, char* key2);

int isLess(priorityQueue* pqueue, int node1Index, int node2Index);
void swapInformations(Info* info1, Info* info2);
void increaseBinaryHeapCapacity(priorityQueue* pqueue);
void sink(priorityQueue* pqueue, int elementToSinkIndex);
void swim(priorityQueue* pqueue, int elementToSwimIndex);
void heapify(priorityQueue* pqueue);


PriorityQueue createPriorityQueue(int capacity, getInfoPriority getPriority, getInfoKey getKey){
    if(capacity <= 0) return NULL;

    priorityQueue* pqueue = (priorityQueue*) malloc(sizeof(priorityQueue));
    if(pqueue == NULL) return NULL;

    pqueue->size = 0;        
    pqueue->capacity = capacity;
    pqueue->getPriority = getPriority;
    pqueue->getKey = getKey;
    pqueue->keyIndexTable = createHashTable(capacity, getKeyIndexKey);

    pqueue->binaryHeap = (Info*) malloc(capacity * sizeof(Info));
    if(pqueue->binaryHeap == NULL){
        free(pqueue);
        return NULL;
    }

    return pqueue;
}


PriorityQueue createFilledPriorityQueue(Info* infos, int infoAmount, getInfoPriority getPriority, getInfoKey getKey){
    if(infos == NULL || infoAmount <= 0) return NULL;

    priorityQueue* pqueue = (priorityQueue*) malloc(sizeof(priorityQueue));
    if(pqueue == NULL) return NULL;

    pqueue->size = infoAmount;        
    pqueue->capacity = ceil(infoAmount * 0.4) + infoAmount; //a binary heap tera um espaço extra caso existam mais elemento a serem inseridos.
    pqueue->getPriority = getPriority;
    pqueue->getKey = getKey;

    pqueue->binaryHeap = (Info*) malloc(pqueue->capacity * sizeof(Info));
    if(pqueue->binaryHeap == NULL){
        free(pqueue);
        return NULL;
    }

    for(int i = 0; i<infoAmount; i++)
        *(pqueue->binaryHeap + i) = *(infos + i);         //pQueue->binaryHeap[i] = elements[i];
        
    pqueue->keyIndexTable = createHashTable(pqueue->capacity, getKeyIndexKey);
    
    for(int i = 0; i<infoAmount; i++){
        keyIndex* ki = (keyIndex*) malloc(sizeof(keyIndex)); 
        strcpy(ki->id, (*getKey)(pqueue->binaryHeap[i]));
        ki->index = i;
        insertHashTable(&(pqueue->keyIndexTable), (Info) ki);
    }

    heapify(pqueue);
    
    return pqueue;
}


int getPriorityQueueSize(PriorityQueue PQueue){
    
    if(PQueue == NULL) return -1;

    priorityQueue* pqueue = (priorityQueue*) PQueue;
    return pqueue->size;
}


int isPriorityQueueEmpty(PriorityQueue PQueue){
    
    if(PQueue == NULL) return -1;
    priorityQueue* pqueue = (priorityQueue*) PQueue;
    
    if(pqueue->size == 0)
        return 1;
    
    return 0;
}


int priorityQueueInsert(PriorityQueue PQueue, Info info){
    if(PQueue == NULL || info == NULL) return 0;
    priorityQueue* pqueue = (priorityQueue*) PQueue;

    if(pqueue->size + 1 > pqueue->capacity)      
        increaseBinaryHeapCapacity(pqueue);
    
    pqueue->binaryHeap[pqueue->size] = info;

    //Inserindo um registro na tabela que mapeia a chave da informacao ao seu indice no vetor que representa a heap.
    keyIndex* ki = (keyIndex*) malloc(sizeof(keyIndex)); 
    strcpy(ki->id, (*pqueue->getKey)(info));
    ki->index = pqueue->size;
    insertHashTable(&(pqueue->keyIndexTable), ki);
    
    swim(pqueue, pqueue->size);

    pqueue->size++;
    return 1;
}


Info priorityQueuePoll(PriorityQueue PQueue){
    if(PQueue == NULL) return NULL;
    priorityQueue* pqueue = (priorityQueue*) PQueue;
    
    //Invertemos o nó com a maior prioridade (nó da heap) com o ultimo nó (nó mais a direita do ultimo nivel).
    //Atualizando os novos indices na tabela:
    char* key1 = (*pqueue->getKey)(pqueue->binaryHeap[0]);
    char* key2 = (*pqueue->getKey)(pqueue->binaryHeap[pqueue->size-1]);

    updateKeyIndexTableAfterSwappingElements(pqueue, key1, key2);
    
    swapInformations(&(pqueue->binaryHeap[0]), &(pqueue->binaryHeap[pqueue->size-1]));
    
    //Guardamos a referencia para a informacao do com a maior prioridade, e, removemos ele da heap e da tabela de indices.
    Info elementToPoll = pqueue->binaryHeap[pqueue->size-1];
    pqueue->binaryHeap[pqueue->size-1] = NULL;

    removeHashTableInfo(pqueue->keyIndexTable, key1, free);

    pqueue->size--;

    //O elemento que passou a ser o novo nó provavelmente viola a propriedade heap, portanto, devemos executar a operacao sink nesse nó.
    sink(pqueue, 0);

    return elementToPoll;
}


int decreaseInfoPriority(PriorityQueue PQueue, char* infoKey, double smallerPriority, setInfoPriority set){
    if(PQueue == NULL || infoKey == NULL || set == NULL) return 0;
    priorityQueue* pqueue = (priorityQueue*) PQueue;
    
    keyIndex* ki = (keyIndex*) getHashTableInfo(pqueue->keyIndexTable, infoKey);
    Info targetInfo = pqueue->binaryHeap[ki->index];

    double infoCurrentPriority = (*pqueue->getPriority)(targetInfo);
    if(smallerPriority >= infoCurrentPriority)
        return 0;
    
    (*set)(targetInfo, smallerPriority);   

    swim(pqueue, ki->index);
    
    return 1;
}


void freePriorityQueue(PriorityQueue PQueue, freeFunction function){
    if(PQueue == NULL) return;
    priorityQueue* pqueue = (priorityQueue*) PQueue;

    if(function != NULL){    
        Info currentInfo;

        for(int i=0; i<pqueue->size; i++){    
            currentInfo = pqueue->binaryHeap[i];
            (*function)(currentInfo);
        }   
    }
    
    free(pqueue->binaryHeap);
    freeHashTable(pqueue->keyIndexTable, free);
    free(pqueue);
}


//funcoes privadas auxiliares:

int getLeftChildIndex(int parentIndex){
    return 2 * parentIndex + 1;
}

int getRightChildIndex(int parentIndex){
    return 2 * parentIndex + 2;
}

int getParentIndex(int childIndex){
    return (childIndex - 1) / 2;
}

int isLess(priorityQueue* pqueue, int node1Index, int node2Index){
    double node1Priority = (*(pqueue->getPriority))(pqueue->binaryHeap[node1Index]);
    double node2Priority = (*(pqueue->getPriority))(pqueue->binaryHeap[node2Index]);
    
    if(node1Priority < node2Priority) return 1;
    else                    return 0;
}

void increaseBinaryHeapCapacity(priorityQueue* pqueue){

    int newCapacity = pqueue->capacity * 2;
    Info* newBinaryHeap = (Info*) malloc(newCapacity * sizeof(Info));
    
    for(int i = 0; i<pqueue->size; i++)
        *(newBinaryHeap + i) = *(pqueue->binaryHeap + i); 
    
    free(pqueue->binaryHeap);
    
    pqueue->binaryHeap = newBinaryHeap;
    pqueue->capacity = newCapacity;
}

void swapInformations(Info* info1, Info* info2) { 
    Info temp;

    temp = *info1;
    *info1 = *info2;
    *info2 = temp;  
} 

void sink(priorityQueue* pqueue, int elementToSinkIndex){
    
    int heapSize = pqueue->size;

    while(1){
        int leftChildIndex = 2 * elementToSinkIndex + 1; 
        int rightChildIndex = 2 * elementToSinkIndex + 2; 
        int smallestChildIndex = leftChildIndex; //Inicialmente assumimos que o filho da esquerda é o menor.

        //Se o filho da direita existir (isto é, seu indice é menor que o tamanho do heap) testamos se ele é menor que o filho da esquerda para encontrar o filho com a menor prioridade.
        if(rightChildIndex < heapSize && isLess(pqueue, rightChildIndex, leftChildIndex)) 
            smallestChildIndex = rightChildIndex;

        //Caso o elemento a ser "sinkado" ja esta no ultimo nivel da arvore (isto é, o indice do seu filho esquerda é maior ou igual ao tamanho do heap), ou, esse elemento ja é menor que o menor de seus filhos nos finalizamos a execuçao pois ele ja foi "sinkado" adequadamente. 
        if (leftChildIndex >= heapSize || isLess(pqueue, elementToSinkIndex, smallestChildIndex)) break;

        //Por fim, invertemos o elemento a ser "sinkado" com o seu filho com a menor prioridade e realizamos de novo os testes acima até o elemento alcançar uma posicao que deixe a arvore valida (de acordo com a propriedade heap).
        //Atualizando os novos indices na tabela:
        char* key1 = (*pqueue->getKey)(pqueue->binaryHeap[smallestChildIndex]);
        char* key2 = (*pqueue->getKey)(pqueue->binaryHeap[elementToSinkIndex]);

        updateKeyIndexTableAfterSwappingElements(pqueue, key1, key2);
        
        swapInformations(&(pqueue->binaryHeap[smallestChildIndex]), &(pqueue->binaryHeap[elementToSinkIndex]));
        elementToSinkIndex = smallestChildIndex;
    }
}

void swim(priorityQueue* pqueue, int elementToSwimIndex){

    //obtendo o indice do nó pai do elemento que vamos "swimar".
    int parentIndex = (elementToSwimIndex - 1) / 2;

    //Continuamente "swimamos" o elemento eté que ele chegue na raiz da heap, ou, ele se torne maior que o seu pai. Assim, garantimos a integridade da propriedade heap.
    while (elementToSwimIndex > 0 && isLess(pqueue, elementToSwimIndex, parentIndex)) {

        //Atualizando os novos indices na tabela:
        char* key1 = (*pqueue->getKey)(pqueue->binaryHeap[parentIndex]);
        char* key2 = (*pqueue->getKey)(pqueue->binaryHeap[elementToSwimIndex]);
        updateKeyIndexTableAfterSwappingElements(pqueue, key1, key2);

        swapInformations(&(pqueue->binaryHeap[parentIndex]), &(pqueue->binaryHeap[elementToSwimIndex]));
        elementToSwimIndex = parentIndex;

        //Pegamos o indice do novo pai do elemento a ser "swimado" para em seguida fazer o teste novamente.
        parentIndex = (elementToSwimIndex - 1) / 2;
    }
}

/*
* Essa funcao nos ajuda a transformar a arvore binaria completa que esta em pqueue->binaryHeap em um heap binario.
* Para isso visitamos todas as sub-arvores (partindo da ultima (cuja raiz é o ultimo nó que não é folha) até a primeira (cuja raiz é a propria raiz da arvore toda))
* Em cada visita "sinkamos" o no raiz de modo a tornar aquela sub arvore um heap binario.
*/
void heapify(priorityQueue* pqueue){
    
    //o ultimo no não-folha é o pai da ultima folha (cujo indice é n-1).
    int lastNonLeafNodeIndex = ((pqueue->size - 1) - 1) / 2;
    for(int i = lastNonLeafNodeIndex; i >= 0; i--)
        sink(pqueue, i);
}

char* getKeyIndexKey(KeyIndex KI){
    keyIndex* ki = (keyIndex*) KI;
    return ki->id;
}

void updateKeyIndexTableAfterSwappingElements(priorityQueue* pqueue, char* key1, char* key2){
    
    keyIndex* ki1 = (keyIndex*) getHashTableInfo(pqueue->keyIndexTable, key1);
    int temp = ki1->index;

    keyIndex* ki2 = (keyIndex*) getHashTableInfo(pqueue->keyIndexTable, key2);
    
    ki1->index = ki2->index;
    ki2->index = temp;
}

void printPriorityQueue(priorityQueue* pqueue){
    if(pqueue == NULL) return;

    int queueSize = pqueue->size;

    printf("\n --- Printando Priority Queue ---\n\n");
    
    if(queueSize == 0){
        printf("A fila esta vazia...\n\n");
        return;
    }

    for(int i=0; i<queueSize; i++)
        printf("Key: %s, priority: %.2lf\n", (*pqueue->getKey)(pqueue->binaryHeap[i]), (*pqueue->getPriority)(pqueue->binaryHeap[i]));

    printf("\n");
}