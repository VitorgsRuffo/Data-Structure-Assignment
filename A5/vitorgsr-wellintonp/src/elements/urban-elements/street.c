#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "street.h"

typedef struct {
    char name[50];
    char rightCep[50];
    char leftCep[50];
    double length;
    double avgSpeed;
    double displacementTime;
}street;


Street createStreet(char* name, char* rightCep, char* leftCep, double length, double avgSpeed){
    street* st = (street*) malloc(sizeof(street));
    if(st == NULL) return NULL;

    strcpy(st->name, name);
    strcpy(st->rightCep, rightCep);
    strcpy(st->leftCep, leftCep);
    st->length = length;
    st->avgSpeed = avgSpeed;
    st->displacementTime = length / avgSpeed;

    return st;
}


char* getStreetName(Street St){
    if(St == NULL) return NULL;
    street* st = (street*) St;
    return st->name;
}


char* getStreetRightCep(Street St){
    if(St == NULL) return NULL;
    street* st = (street*) St;
    return st->rightCep;
}


char* getStreetLeftCep(Street St){
    if(St == NULL) return NULL;
    street* st = (street*) St;
    return st->leftCep;
}


double getStreetLength(Street St){
    if(St == NULL) return -1.0;
    street* st = (street*) St;
    return st->length;
}


double getStreetAvgSpeed(Street St){
    if(St == NULL) return -1.0;
    street* st = (street*) St;
    return st->avgSpeed;
}


double getStreetDisplacementTime(Street St){
    if(St == NULL) return -1.0;
    street* st = (street*) St;
    return st->displacementTime;
}

void printStreet(Street St){
    if(St == NULL) return;
    street* st = (street*) St;
    
    printf("nome: %s, rcep: %s, lcep: %s, comp: %.2lf, velM: %.2lf, tdesl: %.2lf.\n",
          st->name, st->rightCep, st->leftCep, st->length, st->avgSpeed, st->displacementTime);
}

void freeStreet(Street St){
    if(St == NULL) return;
    street* st = (street*) St;
    free(st);
}