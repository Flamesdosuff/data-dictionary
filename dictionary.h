#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char Linea[50];
    char ID[5];           // el ID es decir la primera Letra
    char Produccion[10];  // el argumento de la expresion       
    struct Node *sig;  
} Node;

#define Empty_Pointer NULL  
#define MAX_LINE_LENGTH 100 




int initializeDataDictionary(const char* dictionaryName);

#endif


