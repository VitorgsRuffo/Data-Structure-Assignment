#include "../include/headers.h"
#include "../include/utils.h"

typedef struct node {
    struct node *previous;
    Info info;
    struct node *next;
}node;

typedef struct list {
    node *first;
    node *last;
}list;

List createList(){
    list *li = (list*) malloc(sizeof(list));

    if(li == NULL){
        printf("Erro ao alocar memória para a criação da lista\nFinalizando o programa...");
        exit(1);
    }

    li->first = NULL;
    li->last = NULL;
    return li;
}

int length(List Li){
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return -1;
    }
    list *li = (list*) Li;
    if(li->first == NULL){
        return 0;
    }else{
        node *NODE = li->first;
        int nodeAmount = 0;
        while(NODE != NULL){
            nodeAmount++;
            NODE = NODE->next;
        }
        return nodeAmount;
    }
}

Node insert(List Li, Info info){
    if(Li == NULL || info == NULL){
        printf("Erro: a lista ou a informação a ser inserida não existem..\n");
        return NULL;
    }
    list *li = (list*) Li;

    node *NODE = (node*) malloc(sizeof(node));
    NODE->info = info;

    if(li->first == NULL){ //lista vazia
        li->first = NODE;
        NODE->previous = NULL;
    }else{
        NODE->previous = li->last;
        NODE->previous->next = NODE;
    }
    li->last = NODE;
    NODE->next = NULL;

    return NODE;
}

void removeNode(List Li, Node nodeToRemove, void (*freeTAD)(void*)){ //Tem problema alterara um pouco a assinatura ?
    if(isElementNull(Li, "Li", "removeNode"))
        return;
        
    if(isElementNull(nodeToRemove, "nodeToRemove", "removeNode"))
        return;
        
    list *li = (list*) Li;
    node *NODE = li->first;

    while(NODE != NULL){

        if(NODE == nodeToRemove){
            (*freeTAD)(NODE->info);

            if(NODE->previous == NULL){ //remocao no inicio
                li->first = NODE->next;
                li->first->previous = NULL;

            }else if(NODE->next == NULL){ //remocao no final
                li->last = NODE->previous;
                li->last->next = NULL;

            }else{ //remocao no meio
                NODE->previous->next = NODE->next;
                NODE->next->previous = NODE->previous;
            }
           
            free(NODE);
            return; //no encontrado e removido
        }
        NODE = NODE->next;
    }
    printf("Erro na remocao: no nao encontrado...\n");
}

Info get(List Li, Node Posic){/*tem que checar se o Posic esta presente em Li ?*/
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return 0;
    }
    if(Posic == NULL){
        printf("Erro: posic nao existe..\n");
        return 0;
    }
    //lista *li = (lista*) Li;
    node *NODE = (node*) Posic;
    return NODE->info;
}

Node insertBefore(List Li, Node Posic, Info Information){   /*tem que checar se o Posic esta presente em Li ?*/
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return NULL;
    }
    if(Posic == NULL){
        printf("Erro: posic nao existe..\n");
        return NULL;
    }

    if(Information == NULL){
        printf("Erro: informacao nao existe..\n");
        return NULL;
    }
    list *li = (list*) Li;
    node *NODE = (node*) Posic;
    
    node *previousNODE = (node*) malloc(sizeof(node));
    previousNODE->info = Information;

    if(NODE->previous == NULL){
        previousNODE->previous = NULL;
        previousNODE->next = NODE;

        li->first = previousNODE;
        NODE->previous = previousNODE;
    }else{
        previousNODE->next = NODE;
        previousNODE->previous = NODE->previous; 

        previousNODE->previous->next = previousNODE;
        NODE->previous = previousNODE;
    }

    return previousNODE;
}

Node insertAfter(List Li, Node Posic, Info Information){   /*tem que checar se o Posic esta presente em Li ?*/
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return NULL;
    }
    if(Posic == NULL){
        printf("Erro: posic nao existe..\n");
        return NULL;
    }

    if(Information == NULL){
        printf("Erro: informacao nao existe..\n");
        return NULL;
    }
    list *li = (list*) Li;
    node *NODE = (node*) Posic;

    node *afterNODE = (node*) malloc(sizeof(node));
    afterNODE->info = Information;

    if(NODE->next == NULL){
        afterNODE->next = NULL;
        afterNODE->previous = NODE;

        NODE->next = afterNODE;
        li->last = afterNODE;
    }else{
        afterNODE->next = NODE->next;
        afterNODE->previous = NODE;

        NODE->next->previous = afterNODE;
        NODE->next = afterNODE;
    }

    return afterNODE;
}

Node getFirst(List Li){
     if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return NULL;
    }
    if(length(Li) == 0){
        printf("Erro: a lista esta vazia..\n");
        return NULL;
    }
    
    list *li = (list*) Li;
    return li->first;
}

Node getNext(List Li, Node Posic){ /*tem que checar se o Posic esta presente em Li ?*/
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return NULL;
    }
    if(Posic == NULL){
        printf("Erro: posic nao existe..\n");
        return NULL;
    }

    node *NODE = (node*) Posic;
    return NODE->next;
}

Node getLast(List Li){
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return NULL;
    }
    if(length(Li) == 0){
        printf("Erro: a lista esta vazia..\n");
        return NULL;
    }

    list *li = (list*) Li;
    return li->last;
}

Node getPrevious(List Li, Node Posic){ /*tem que checar se o Posic esta presente em Li ?*/
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return NULL;
    }
    if(Posic == NULL){
        printf("Erro: posic nao existe..\n");
        return NULL;
    }

    node *NODE = (node*) Posic;
    return NODE->previous;
}

Node searchForElementByIdentifier(List Li, char* (*getElementId)(void*), char* idToSearch){

    if(isElementNull(Li, "lista", "searchForElementByIdentifier"))
        return NULL;

    char elementId[15];
    Info elementInformation;
    Node NODE;
    List elementsList = (list*) Li;
    
    NODE = getFirst(elementsList);
    
    while (NODE != NULL){
        elementInformation = get(elementsList, NODE);
        strcpy(elementId, (*getElementId)(elementInformation));
        
        if(!strcmp(elementId, idToSearch))
            return NODE;    
        else
            NODE = getNext(elementsList, NODE);               
    }

    return NULL;
}

void printList(List Li, void (*printInformation)(void*)){
    if(Li == NULL){
        printf("Erro: a lista nao existe..\n");
        return;
    }
    
    list *li = (list*) Li;
    if(li->first == NULL){
        printf("Erro: lista vazia..\n");
        return;
    }
    
    node *NODE = li->first; 
    while(NODE != NULL){
        (*printInformation)(NODE->info);
        NODE = NODE->next;
    }
}

void freeList(List Li, void (*freeTAD)(void*)){
    if(Li == NULL){
        printf("Erro: lista nao existente..\n");
        return;
    }

    list *li = (list*) Li;
    
    if(li->first != NULL){
        node *NODE = li->first;
        node *helperNODE = NODE->next;
        while(1){
            freeTAD(NODE->info);
            free(NODE);
            NODE = helperNODE;
            if(NODE == NULL){
                break;
            }
            helperNODE = helperNODE->next;
        }
    }

    li->first = NULL; li->last = NULL;
    free(li);
}