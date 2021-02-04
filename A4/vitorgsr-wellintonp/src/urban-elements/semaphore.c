#include "../include/headers.h"
#include "../include/util.h"
#include "../include/urbanElements.h"

typedef struct semaphore{
    char* id;
    char* x;
    char* y;
    char* radius;
    Point coordinates;
    char* sw;
    char* cfill;
    char* cstrk;
}semaphore;

Semaphore createSemaphore(char* id, char* x, char* y, char* sw, char* cfill, char* cstrk){

    semaphore *semap = (semaphore*) malloc(sizeof(semaphore));

    semap->id = (char*) malloc((strlen(id) + 1) * sizeof(char));
    semap->x = (char*) malloc((strlen(x) + 1) * sizeof(char));
    semap->y = (char*) malloc((strlen(y) + 1) * sizeof(char));
    semap->radius = (char*) malloc(4 * sizeof(char));
    semap->sw = (char*) malloc(20 * sizeof(char));
    semap->cfill = (char*) malloc(20 * sizeof(char));
    semap->cstrk = (char*) malloc(20 * sizeof(char));

    strcpy(semap->id, id);
    strcpy(semap->x, x);
    strcpy(semap->y, y);
    strcpy(semap->radius, "10");
    semap->coordinates = createPoint(atof(x), atof(y));
    strcpy(semap->sw, sw);
    strcpy(semap->cfill, cfill);
    strcpy(semap->cstrk, cstrk);

    return semap;
}

char* getSemaphoreId(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreId"))
        return NULL;
    semaphore *semap = (semaphore*) Semap;
    return semap->id;
}

char* getSemaphoreX(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreX"))
        return NULL;
    semaphore *semap = (semaphore*) Semap;
    return semap->x;
}

char* getSemaphoreY(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreY"))
        return NULL;
    semaphore *semap = (semaphore*) Semap;
    return semap->y;
}

char* getSemaphoreRadius(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreRadius"))
        return NULL;
    semaphore *semap = (semaphore*) Semap;
    return semap->radius;
}

Point getSemaphoreCoordinates(Semaphore Semap){
    semaphore *semap = (semaphore*) Semap;
    return semap->coordinates;
}

char* getSemaphoreSw(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreSw"))
        return NULL;
    semaphore *semap = (semaphore*) Semap;
    return semap->sw;
}

void setSemaphoreSw(Semaphore Semap, char* sw){
    if(isElementNull(Semap, "semaforo", "setSemaphoreSw"))
        return;
    semaphore *semap = (semaphore*) Semap;
    strcpy(semap->sw, sw);
}

char* getSemaphoreCfill(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreCfill"))
        return NULL;
    semaphore *semap = (semaphore*) Semap;
    return semap->cfill;
}

char* getSemaphoreCstrk(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreCstrk"))
        return NULL;
    semaphore *semap = (semaphore*) Semap;
    return semap->cstrk;
}

double getSemaphoreArea(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "getSemaphoreArea"))
        return 0;

    semaphore *semap = (semaphore*) Semap;
    return 3.141592 * ( atof(semap->radius) * atof(semap->radius) );      
}

char* semaphoreToString(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "semaphoreToString"))
        return NULL;

    semaphore *semap = (semaphore*) Semap;

    char* semaphoreInfoString = (char*) malloc(200 * sizeof(char));
    sprintf(semaphoreInfoString, "Tipo: semaforo, id: %s, x: %s, y: %s, sw: %s, cfill: %s, cstrk: %s", semap->id, semap->x, semap->y, semap->sw, semap->cfill, semap->cstrk);
    return semaphoreInfoString;
}

void printSemaphore(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "printSemaphore"))
        return;
    semaphore *semap = (semaphore*) Semap;
    printf("Semaforo:\nId: %s\nx: %s\ny: %s\nsw: %s\ncfill: %s\ncstrk: %s\n\n\n", 
           semap->id, semap->x, semap->y, semap->sw, semap->cfill, semap->cstrk);
}

void freeSemaphore(Semaphore Semap){
    if(isElementNull(Semap, "semaforo", "freeSemaphore"))
        return;

    semaphore *semap = (semaphore*) Semap;
    free(semap->id);  
    free(semap->x); 
    free(semap->y);
    free(semap->radius);
    free(semap->coordinates);
    free(semap->sw);
    free(semap->cfill);
    free(semap->cstrk);  

    free(semap);
}