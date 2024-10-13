#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char value[50];      
    struct Node *sig;  
} Node;

#define Empty_Pointer NULL  
#define MAX_LINE_LENGTH 100 

int initializeDataDictionary(const char* dictionaryName);

#endif


