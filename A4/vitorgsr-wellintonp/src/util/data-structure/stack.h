#ifndef STACK
#define STACK

/*
* apontador void para uma instancia do TAD que esta presente em um no da pilha.
*/
typedef void* Info;

/*
*apontador void para um no de uma pilha.
*/
typedef void* StackNode;

/*
*apontador void para uma instancia de pilha.
*/
typedef void* Stack;

/*
Pré-condição: nenhuma.
Pós-condição: cria e retorna a referencia para uma pilha vazia.
*/
Stack createStack();

/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: verifica se a pilha está vazia. Se estiver vazia retorna 1, caso contrário retorna 0.
*/
int empty(Stack* Head);

/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: retorna a quantidade de nós contidos na pilha;
*/
int stackLength(Stack* Head);

/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha e o endereço da informação a ser armazenada.
Pós-condição: Insere um novo nó no topo da pilha e retorna 1. Se a insercao falhar retorna 0.
*/
int stackPush(Stack* PointerToHead, Info data);


/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: libera o nó do topo da pilha e retorna o seu conteúdo.
*/
Info stackPop(Stack* PointerToHead);

/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: retorna o dado presente no nó do topo da pilha.
*/
Info stackTop(Stack* PointerToHead);

/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: retorna o dado presente no nó imediatamente antes do nó no topo da pilha.
*/
Info nextToTop(Stack* PointerToHead);

/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: transfere os dados dos nos da pilha para um vetor e retorna o endereço desse vetor.
*/
Info* stackToArray(Stack* PointerToHead);

/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: Percorre a pilha printando suas informações.
*/
int printStack(Stack* PointerToHead, char* (*tadToString)(void*));


/*
Pré-condição: requer o endereço de um ponteiro para o nó no topo da pilha.
Pós-condição: libera a memoria total usada pela pilha.
*/
void freeStack(Stack* PointerToHead, void (*freeTad)(void*));

#endif