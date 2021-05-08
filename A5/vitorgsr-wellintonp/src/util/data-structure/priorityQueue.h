/*
* Tipo abstrato de dados: fila com prioridade.
* É semelhante a uma fila comum porem os seus elementos são atendidos de acordo com a sua prioridade.
* Elementos com maior prioridade saem primeiro da fila. Se dois elementos têm prioridade igual o primeiro a entrar é o primeiro a sair.
*/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef void* Info;
typedef void* PriorityQueue;

/*
* Ponteiro para uma funcao que desaloca uma informacao. 
*/
typedef void (*freeFunction)(Info);

/*
* Ponteiro para uma funcao que recebe uma informacao (elemento dentro da fila) e retorna o campo da informacao que pode ser interpretado como a prioridade daquele elemento.
*/
typedef double (*getInfoPriority)(Info);

/*
* Ponteiro para uma funcao que recebe uma informacao (elemento dentro da fila) e um double. Ela altera a prioridade do elemento.
*/
typedef void (*setInfoPriority)(Info, double);

/*
* Ponteiro para uma funcao que recebe uma informacao (elemento dentro da fila) e retorna a chave que identifica aquele elemento.
*/
typedef char* (*getInfoKey)(Info);

/*
* Cria e retorna uma nova instancia vazia de fila com prioridade.
* É necessario fornecer a capacidade maxima da fila, uma funcao de pegar a prioridade/chave de um elemento da fila. 
*/
PriorityQueue createPriorityQueue(int capacity, getInfoPriority getPriority, getInfoKey getKey);

/*
* Cria e retorna uma nova instancia de fila com prioridade. Esta instancia ja possui alguns elementos inicias que serao passados por parametro
* É necessario fornecer uma funcao de pegar a prioridade/chave de um elemento da fila. 
*/
PriorityQueue createFilledPriorityQueue(Info* infos, int infoAmount, getInfoPriority getPriority, getInfoKey getKey);

/*
* Retorna a quantidade de elementos na fila.
*/
int getPriorityQueueSize(PriorityQueue PQueue);

/*
* Retorna 1 se a fila estiver vazia, se nao retorna 0.
*/
int isPriorityQueueEmpty(PriorityQueue PQueue);

/*
* Insere a informacao passada por parametro na fila. Sua posição na fila dependera da sua prioridade.
*/
int priorityQueueInsert(PriorityQueue PQueue, Info info);

/*
* Remove da fila e retorna o elemento com a maior prioridade.
* O usuario fica responsavel por desalocar o elemento retornado.
*/
Info priorityQueuePoll(PriorityQueue PQueue);

/*
* Diminui a prioridade do elemento cuja chave foi passada por parametro.
* É necessario passar uma funcao de alterar a prioridade de um elemento por parametro.
*/
int decreaseInfoPriority(PriorityQueue PQueue, char* infoKey, double smallerPriority, setInfoPriority set);

/*
* Desaloca a memoria utilizada pela fila. 
* A passagem da funcao de desalocar informacao é opcional. Se a funcao for passada, as informacoes presentes na fila sao desalocadas.
*/
void freePriorityQueue(PriorityQueue PQueue, freeFunction function);

#endif