#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char Linea[50];
    char ID[5];           // El ID (primera letra)
    char Produccion[100]; // El argumento de la expresión
    struct Node *sig;  
} Node;

#define Empty_Pointer NULL  
#define MAX_LINE_LENGTH 100 

int initializeDataDictionary(const char* dictionaryName);
void printNodes(Node *head);
void processNodes(Node *head);

#endif


