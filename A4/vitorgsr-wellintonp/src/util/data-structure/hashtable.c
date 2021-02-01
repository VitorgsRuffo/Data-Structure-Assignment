#include "../../include/headers.h"
#include "hashtable.h"
#include "list.h" 


typedef struct hashtable {
    int size;
    List* info;
    getInfoKey getKey;
}hashtable;


int hashFunction(hashtable* hashT, char *str);

HashTable createHashTable(int tableSize, getInfoKey getKey){
    
    if(tableSize <= 0)
        return NULL;

    hashtable* hashT = (hashtable*) malloc(sizeof(hashtable));
    if(hashT == NULL)
        return NULL;
    
    hashT->size = tableSize;
    
    hashT->info = (List*) malloc(tableSize * sizeof(List));
    if(hashT->info == NULL){
        free(hashT);
        return NULL;
    }

    for(int i = 0 ; i < tableSize; i++)
        hashT->info[i] = createList(); //same as *((*hashT).info + i) = createList();

    hashT->getKey = getKey;

    return hashT;    
}


int insertHashTable(HashTable HashT, Info info){

    if(HashT == NULL || info == NULL)
        return 0;        

    hashtable* hashT = (hashtable*) HashT;

    char* infoKey = (*(hashT->getKey))(info);

    int position = hashFunction(hashT, infoKey);

    insert(hashT->info[position], info);   //same as insert(*((*hashT).info + position), info);
    
    return 1;
}


int isThereKeyInHashTable(HashTable HashT, char* key){

    if(HashT == NULL || key == NULL)
        return 0;        

    hashtable* hashT = (hashtable*) HashT;

    int position = hashFunction(hashT, key);

    List infoList = hashT->info[position];   // same as List infoList = *((*hashT).info + position);

    Node currentNode = getFirst(infoList);
    Info info;
    char* infoKey;

    while(currentNode != NULL){

        info = get(infoList, currentNode);

        infoKey = (*(hashT->getKey))(info);

        if(!strcmp(key, infoKey))
            return 1;
        
        currentNode = getNext(infoList, currentNode);
    }

    return 0;
}

Info getHashTableInfo(HashTable HashT, char* key){

    if(HashT == NULL || key == NULL)
        return NULL;        

    hashtable* hashT = (hashtable*) HashT;

    int position = hashFunction(hashT, key);

    List infoList = hashT->info[position];   //same as List infoList = *((*hashT).info + position);

    Node currentNode = getFirst(infoList);
    Info info;
    char* infoKey;

    while(currentNode != NULL){

        info = get(infoList, currentNode);

        infoKey = (*(hashT->getKey))(info);

        if(!strcmp(key, infoKey))
            return info;
        
        currentNode = getNext(infoList, currentNode);
    }

    return NULL;
}


int removeHashTableInfo(HashTable HashT, char* key, freeInfo freeFunction){

    if(HashT == NULL || key == NULL)
        return 0;        

    hashtable* hashT = (hashtable*) HashT;

    int position = hashFunction(hashT, key);

    List infoList = hashT->info[position];   //same as List infoList = *((*hashT).info + position);

    Node currentNode = getFirst(infoList);
    Info info;
    char* infoKey;

    while(currentNode != NULL){

        info = get(infoList, currentNode);

        infoKey = (*(hashT->getKey))(info);

        if(!strcmp(key, infoKey)){
            removeNode(infoList, currentNode, freeFunction);
            return 1;
        }
        
        currentNode = getNext(infoList, currentNode);
    }

    return 0;
}


void printHashTable(HashTable HashT, void (*printInformation)(void*)){
    
    if(HashT == NULL)
        return;        
    
    hashtable* hashT = (hashtable*) HashT;

    printf("HashTable:\n");
    for(int i=0; i<hashT->size; i++){
        printf("[%d]: \n", i);
        printList(hashT->info[i], printInformation);
    }
}


void freeHashTable(HashTable HashT, freeInfo freeFunction){
    if(HashT == NULL)
        return;

    hashtable* hashT = (hashtable*) HashT;
    
    for(int i = 0; i<hashT->size; i++)
        freeList(hashT->info[i], freeFunction);

    free(hashT->info);
    free(hashT);
}


int hashFunction(hashtable* hashT, char *str){
    
    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c; 

    return (hash % hashT->size);
}