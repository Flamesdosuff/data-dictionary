#include "dictionary.h"

int initializeDataDictionary(const char "diccionaryName") {
    long mainHeader = Empty_Pointer;
    printf("Initializing Data Dictionary...\n");
    FILE *dictionary = fopen("diccionario.dat","w+");
    fwrite(&mainHeader,sizeof(mainHeader),1,dictionary);
    long currentDir = ftell(dictionary);
    
    
}
